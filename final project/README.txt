Summary:

This C program implements a command-line utility for Run-Length Encoding (RLE) compression and decompression. It includes four modes: compression (-c), decompression (-x), debugging (-d), and test file generation (-g). The user specifies the mode and file name as command-line arguments. The program utilizes function pointers for different modes and provides informative error messages for improper usage or file conditions.

Compile:
gcc -o rle main.c
