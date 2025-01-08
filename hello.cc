#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>
#include <string>

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

void show_help()
// shows information on how to use the program
{
    
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
    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};                          // length == 26
    const std::string alphabet_capital {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};                  // length == 26
    const std::string numsymbol {"0123456789!?<>(){}@#$%^&*"};                          // length == 25
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
    Rand_int rfor_alphabet(0, alphabet.size()-1);                                       // create a generator for the alphabet data size
    Rand_int rfor_numsymbol(0, numsymbol.size()-1);                                     // create a generator for the number/symbol data size
    Rand_int rfor_candidate(0, 1000);
    char candidates[3] {0,0,0};                                                         // hold, in each iteration, 3 different chars of different type: small, capital & num/sym
    for (int i = 0; i < pass_len; ++i) {
        candidates[0] = alphabet[rfor_alphabet()];
        candidates[1] = alphabet_capital[rfor_alphabet()];
        candidates[2] = numsymbol[rfor_numsymbol()];
        int rsubscript{ rfor_candidate()%3 };                                           // select one char with a distinct type from the created candidate chars
        std::string chosen_char{ candidates[rsubscript] };
        password += chosen_char;
    }
    // std::cout << '\n';                                                               // DEBUG
    // std::cout << password << '\n';                                                   // DEBUG
    /* Integrate birthdate into the password*/
    bool birthdate_flag = false;
    if (argc > 2 && isdigit(argv[2])) {
        birthdate_flag = true;
    }
    else {
        std::cout << '\n';                                                  
        std::cout << password << '\n';
    }
    if (birthdate_flag == true) {                                                       // cut the birthdate into two pairs of two digits each
        int birthdate{static_cast<int>(atof(argv[2]))};
        int disected_birthdate[2] {0,0};
        disected_birthdate[0] = birthdate % 100;                                        // last two digits (e.g. "94" in "1994")
        birthdate /= 100;                                               
        disected_birthdate[1] = birthdate % 100;                                        // first two digits (e.g. "19" in "1994")
        Rand_int rfor_replace(0, pass_len -2);                                          // at most the subscript of the penultimate character to support a pair
        int sub1{0};
        int sub2{0};
        while (abs(sub1-sub2) < 2) {
            sub1 = rfor_replace();
            sub2 = rfor_replace();
        }
        // std::cout << sub1 << '\t' << sub2;                                           // DEBUG
        password.replace(sub1, 2, std::to_string(disected_birthdate[1]));
        password.replace(sub2, 2, std::to_string(disected_birthdate[0]));
        std::cout << '\n' << password;
    }
} 