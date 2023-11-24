#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_PRIMES 10000000

volatile int num_found = 0;
int *primes;

void handler(int sig) {
    printf("Found %d primes.\n", num_found);
    printf("Last 5 primes found: ");
    for (int i = num_found - 5; i < num_found; i++) {
        printf("%d ", primes[i]);
    }
    printf("\n");
    if (sig == SIGTERM) {
        printf("Goodbye!\n");
        exit(0);
    }
    alarm(10);
}

int is_prime(unsigned int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    primes = malloc(MAX_PRIMES * sizeof(int));
    if (primes == NULL) {
        perror("malloc failed");
        exit(1);
    }

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction failed");
        exit(1);
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction failed");
        exit(1);
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction failed");
        exit(1);
    }

    alarm(10);

    for (int i = 2; num_found < MAX_PRIMES; i++) {
        if (is_prime(i)) {
            primes[num_found++] = i;
        }
    }

    free(primes);

    return 0;
}
