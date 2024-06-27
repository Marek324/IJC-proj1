# Last 10 primes / Comment eraser

Project was assigned in my C programming language course at FIT BUT. First part of the assignment was to make a program that prints out last 10 prime numbers before 666000000. Second part was to create a program that deletes C type comments from input. Final evaluation: 15/15

## Last 10 primes

Program that uses **Sieve of Eratosthenes** to print the last 10 primes before any number (e.g., 666000000 as per the assignment).

### Implementation details

This was implemented using every single bit in an array of unsigned longs. Working with only 1 bit in ulong is achieved by using bit masks. All bitset functions are implemented as inline functions and as macros as well.

### Installation 

1. Download files
2. In **primes.c** change *N* definition on line 11, for the number you need
3. Run 
```
make primes
```
or 
```
make primes-i
```

## Comment eraser

Program erases C-type comments from stdin or file.

### Implementation details

It reads input stream character by character and prints or doesn't print the character based on Finite State Machine.

### Installation

1. Download
2. Run 
```
make no-comment
```

### Usage

Linux: `./no-comment [FILE]`
