# Context Powered Password Generator

A commandline program in C++ that creates random passwords from English small and capital letters combined with random numbers and symbols. The length is 12 by default but can be expanded to an arbitrary number. Aside from the length, the user can add a (birth) year and a favorite color (but can be any word) to be inserted into the password thus making it easier to remember. 

## Usage

```.\passgen --help```
```.\passgen -l 10```
```.\passgen -y 1994 -l 8```
```.\passgen -fc blue -y 2000```