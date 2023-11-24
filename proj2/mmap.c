#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
int *shared_memory_ptr;
int file_descriptor;

file_descriptor = open("/dev/zero", O_RDWR);
if (file_descriptor == -1) {
write(STDERR_FILENO, "open() failed\n", 14);
exit(EXIT_FAILURE);
}

shared_memory_ptr = mmap(NULL, sizeof(*shared_memory_ptr), PROT_READ|PROT_WRITE, MAP_SHARED, file_descriptor, 0);

if (shared_memory_ptr == MAP_FAILED) {
fprintf(stderr, "mmap() failed\n");
exit(EXIT_FAILURE);
}

if (close(file_descriptor) == -1) {
fprintf(stderr, "close() failed\n");
exit(EXIT_FAILURE);
}

*shared_memory_ptr = 2;
switch(fork()) {
case 0:
printf("Child: value = %d\n", *shared_memory_ptr);
(*shared_memory_ptr)++;
if (munmap(shared_memory_ptr, sizeof(*shared_memory_ptr)) == -1) {
fprintf(stderr, "munmap() failed\n");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
default:
wait(NULL);
printf("Parent: value = %d\n", *shared_memory_ptr);
if (munmap(shared_memory_ptr, sizeof(*shared_memory_ptr)) == -1) {
fprintf(stderr, "munmap() failed\n");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);

}

}


