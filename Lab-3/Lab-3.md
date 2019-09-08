# Multithreading and Multiprocessing

> This lab aims to teach students how to handle the shared memory problems found in threaded work environments.

> As a side excercise, this lab hopes to expose students to the creation of subprocessing via the creating of a simplistic shell.

> The subprocessing occurs when a user enters a non-native shell command, this command gets delegated to the OS shell via the fork and system calls.

## How to build

> For shell use standard gcc

> For pi use _gcc -lpthreads -lm__ otherwise it wont link the pthreads and math libraries.
