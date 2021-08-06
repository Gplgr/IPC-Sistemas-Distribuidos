#About

This is a simple project for studying, analyzing and practicing with computing related to IPC (Interprocess Communication).
It consists in three main systems, signals, pipes and sockets.

###Signals

This folder contains two codes made in C language , in which the program launched by Destinatario is a counter that can be activated by either blocking wait or busy wait, and, respectively, awaits for a signal to be received and prints a time counter every 5 seconds, while also reacting to signals.
The Carteiro file is a signal launcher that receives the Program ID of another process and sends a signal to the ID'd process that is dependent on the input.

###Pipes

This folder contains an interaction of two process, in which one is a parent process and the other one is its child. A random number between 1 and 100 is produced at the child process and is added to the previous value, to be then sent to the parent through a pipe to check if it's a prime number or not, then printed to the user. This operation repeats a n number of times, n consisting on a positive integer that the user inputs.

###Sockets

The program executed on this folder is very similar to the previous one. The difference is that the communication is made through sockets instead of pipes, and the message is sent back to the child process instead of being interpreted by the parent process.

###Installation

Through the terminal, go to the folder of the program you want to use and execute the command
  ```sh
  make
  ```