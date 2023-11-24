#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

const char *signal_names[] = {
  "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
  "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1",
  "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM",
  "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",
  "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
  "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR",
  "SIGSYS"
};

void list_signals() {
  int i;
  for (i = 1; i < 32; i++) {
    printf("%2d) %-12s: %s\n", i, signal_names[i - 1], strsignal(i));
  }
}

int main(int argc, char *argv[])
{
    int signal_num = SIGTERM;  // default signal
    int pid;
    int c;
    int list_flag = 0;

    while ((c = getopt(argc, argv, "s:l")) != -1) {
        switch (c) {
            case 's':
                signal_num = atoi(optarg);
                break;
            case 'l':
                list_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [options] <pid>\nOptions:\n   -s <signal>   Sends <signal> to <pid>\n   -l            Lists all signal numbers with their names\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (list_flag) {
    // list all signal numbers with their names
    list_signals();
    exit(EXIT_FAILURE);
}

    if (argc - optind < 1) {
        fprintf(stderr, "Usage: %s [options] <pid>\nOptions:\n   -s <signal>   Sends <signal> to <pid>\n   -l            Lists all signal numbers with their names\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = atoi(argv[optind]);

    if (signal_num == 0) {
        // check if the PID exists and is able to receive signals
        if (kill(pid, 0) == 0) {
            printf("PID %d exists and is able to receive signals\n", pid);
        } else if (errno == EPERM) {
            printf("PID %d exists, but we can't send it signals\n", pid);
        } else {
            printf("PID %d does not exist\n", pid);
        }
        exit(EXIT_SUCCESS);
    }

    // send the specified signal to the PID
    if (kill(pid, signal_num) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
