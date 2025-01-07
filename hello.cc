#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>

/* Symbolic constants */
#define MIN_PASS_LEN 12

/* Helper functions */
bool isdigit(std::string c)
{
    bool result;
    result = true;
    for (int i = 0; i < c.size(); ++i) {
        if (!(c[i] - '0' >= 0 && c[i] - '0' <= 9)) {
            result = false;
            break;
        }
    }
    return result;
}

/* Class definitions */
class Rand_int {
    private:
        std::random_device rd;
        std::default_random_engine engine;
        std::uniform_int_distribution<int> distrib;
    public:
        Rand_int(int low, int high) : distrib{low, high} {
            engine.seed(rd());
        }
        int operator()() {
            return distrib(engine);
        }
};

/* Main function */
int main(int argc, char *argv[])
{
    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};          // length == 26
    const std::string alphabet_capital {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};  // length == 26
    const std::string numsymbol {"0123456789!?<>(){}@#$%^&*"};          // length == 25
    std::string password{};
    int pass_len{0};
    if (argc == 1) {
        pass_len = MIN_PASS_LEN;
    }
    else if (argc >= 2 && isdigit(argv[1])) {
        pass_len = atof(argv[1]);
    }
    else {
        std::cout << "Illegal input\n";
        std::exit(EXIT_FAILURE);
    }
    /* Allow for the random selection of the type of character */
    Rand_int rfor_alphabet(0, alphabet.size()-1);                       // create a generator for the alphabet data size
    Rand_int rfor_numsymbol(0, numsymbol.size()-1);                     // create a generator for the number/symbol data size
    Rand_int rfor_candidate(0, 1000);
    char candidates[3] {0,0,0};                                         // hold, in each iteration, 3 different chars of different type: small, capital & num/sym
    for (int i = 0; i < pass_len; ++i) {
        candidates[0] = alphabet[rfor_alphabet()];
        candidates[1] = alphabet_capital[rfor_alphabet()];
        candidates[2] = numsymbol[rfor_numsymbol()];
        int rsubscript{ rfor_candidate()%3 };                           // select one char with a distinct type from the created candidate chars
        std::string chosen_char{ candidates[rsubscript] };
        password += chosen_char;
    }
    std::cout << '\n';
    std::cout << password << '\n';
    /* Integrate birthdate into the password*/
    int birthdate{static_cast<int>(atof(argv[2]))};
    int disected_birthdate[2] {0,0};
    disected_birthdate[0] = birthdate % 100;
    birthdate /= 100;
    disected_birthdate[1] = birthdate % 100;
} 