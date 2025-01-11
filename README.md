# Context Powered Password Generator

A commandline program in C++ that creates random passwords from English small and capital letters combined with random numbers and symbols. The length is 12 by default but can be expanded to an arbitrary number. Aside from the length, the user can add a (birth) year and a favorite color (but can be any word) to be inserted into the password thus making it easier to remember. 

## Usage

```powershell
.\passgen --help
.\passgen -l 10
.\passgen -y 1994 -l 8
.\passgen -fc blue -y 2000
```
## Compilation
```powershell
g++ -std=c++2c -o passgen hello.cc
```
# Feature highlights
- ```std::random_device``` to allow for unique random generation in each run of the program
- Custom class ```Rand_int``` to ease random number creation in a given range
- Support up to 3 arguments to allow personalization of the password
- Error checking for wrong input
- Support arbitrary length password (if personalization is selected, only up to 100)

# Development plans
- [x] allow custom length
- [x] allow year integration
- [x] allow favorite color integration
- [ ] allow favorite number integraion