Homework 3
Laura Douglas
14380964

How To Compile & Run
====================
In terminal:
gcc -o mmap mmap.c
./mmap


Description
===========
The program creates a shared memory mapping using the mmap() function, which maps the contents of the file /dev/zero into the address space of the program. The shared memory is then initialized with the value 2.

After the shared memory is created and initialized, the program creates a child process using the fork() function. The child process increments the value of the shared memory by 1 and then unmaps the shared memory using the munmap() function before exiting. The parent process waits for the child to exit and then prints the final value of the shared memory before un-mapping the shared memory and exiting.

