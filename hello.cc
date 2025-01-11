#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>
#include <string>
#include <string.h>

/* Symbolic constants */
#define MIN_PASS_LEN 12
#define MAX_PASS_LEN 100

/* Global variables */
bool filled[MAX_PASS_LEN];

/* Helper functions */
bool isdigit(std::string c)
// Given a string, return true if all of its characters are digits
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
bool isalphabetic(std::string c)
// given a string, return true of all characters belong to the English alphabet
{
    std::string digits {"0123456789"};
    bool truth_flag = true;
    for (int i = 0; i < digits.size(); ++i) {
        if (c.find(digits[i]) != c.npos) {
            truth_flag = false;
        }
    }
    return truth_flag;
}

void show_help()
// shows information on how to use the program
{
    std::cout << "\nUsage: passgen [COMMANDS]\n\n";
    std::cout << "    Commands:\n";
    std::cout << "\t<number>\t\t\tFirst command specifies the length of the password\n"
              << "\t<number>\t\t\tSecond command specifies the optional integration of birth year into the password\n"
              << "\t<English word>\t\t\tThird command specifies the optional integration of your favorite color into the password"
              << "\n\n\n";
}

void fill_arr_zero(bool arr[], int len)
// given a built-in array, fill all the elements with 0/false
{
    for (int i = 0; i < len; arr[i++] = false)
        ;
}

void fill_bytwo(bool arr[], int pos)
// fill pos and pos+1 in arr with 1/true values
{
    for (int i = pos; i < pos+2; arr[i++] = true)
        ;
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
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        show_help();
        std::exit(EXIT_SUCCESS);
    }
    /* Start analyzing command arguments */
    bool passlen_flag = false;
    bool byear_flag = false;
    bool favcolor_flagg = false;
    bool favnumber_flag = false;
    for (int ncommand = 1; ncommand < argc; ++ncommand) {                               // sub-0 is program name
        if (ncommand%2 != 0) {                                                          // argument specifier (e.g. -l or -y for length and year repsectively)...
            if (strlen(argv[ncommand]) < 2 || argv[ncommand][0] != '-') {               // ... starts on odd subscripts
                std::cerr << "Invalid argument(s)\n\n";
                std::exit(EXIT_FAILURE);
            }
            if (strlen(argv[ncommand]) == 2) {
                if (argv[ncommand][1] == 'l') {
                    passlen_flag = true;
                }
                if (argv[ncommand][1] == 'y') {
                    byear_flag = true;
                }
                else if (!passlen_flag && !byear_flag) {
                    std::cerr << "Invalid argument(s)\n\n";
                    std::exit(EXIT_FAILURE);
                }
            }
            else if (strlen(argv[ncommand]) == 3 && argv[ncommand][1] == 'f') {
                if (argv[ncommand][2] == 'c') {
                    favcolor_flagg = true;
                }
                else if (argv[ncommand][2] == 'n') {
                    favnumber_flag = true;
                }
                if (!favcolor_flagg && !favnumber_flag) {
                    std::cerr << "Invalid argument(s)\n\n";
                    std::exit(EXIT_FAILURE);
                }
            }
        }
    }
    // std::cout << "-l: " << passlen_flag
    //           << "\n-y: " << byear_flag
    //           << "\nfavcolor: " << favcolor_flagg
    //           << "\nfavnumber: " << favnumber_flag
    //           << '\n';
    int length_val{0};
    int byear_val{0};
    std::string favcolor_val{};
    int favnumber_val{0};
    for (int ncommand = 2; ncommand < argc; ++ncommand) {
        if (ncommand%2 == 0) {
            if (isdigit(argv[ncommand])) {
                if (strcmp(argv[ncommand - 1], "-l") == 0) {
                    length_val = atof(argv[ncommand]);
                }
                else if (strcmp(argv[ncommand - 1], "-y") == 0) {
                    byear_val = atof(argv[ncommand]);
                }
                else if (strcmp(argv[ncommand - 1], "-fn") == 0) {
                    favnumber_val = atof(argv[ncommand]);
                }
                else {
                    std::cerr << "Invalid argument(s)\n\n";
                    std::exit(EXIT_FAILURE);
                }
            }
            if (isalphabetic(argv[ncommand])) {
                if (strcmp(argv[ncommand - 1], "-fc") == 0) {
                    favcolor_val = argv[ncommand];
                }
                else {
                    std::cerr << "Invalid argument(s)\n\n";
                    std::exit(EXIT_FAILURE);
                }
            }
        }
    }
    // std::cout << "Length: " << length_val
    //           << "\nyear: " << byear_val
    //           << "\ncolor: " << favcolor_val
    //           << "\nnumber: " << favnumber_val
    //           << "\n";
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
        int rsubscript{rfor_candidate()%3};                                             // select one char with a distinct type from the created candidate chars
        std::string chosen_char{candidates[rsubscript]};
        password += chosen_char;
    }
    // std::cout << '\n';                                                               // DEBUG
    // std::cout << password << '\n';                                                   // DEBUG

    fill_arr_zero(filled, MAX_PASS_LEN);                                                // before inserting any meaning into the pass, reset all pos to 0/false

    /* Integrate birthdate into the password */
    bool birthdate_flag = false;
    if (argc > 2 && isdigit(argv[2])) {
        birthdate_flag = true;
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
        fill_bytwo(filled, sub1);                                                       // record birth year (pair 1) position in the password
        fill_bytwo(filled, sub2);                                                       // record birth year (pair 2) position in the password
        // std::cout << '\n' << password << '\n';                                       // DEBUG
    }
    /* Integrate favorite color into the password */
    bool favcolor_flag = false;
    if (argc > 3 && isalphabetic(argv[3])) {
        favcolor_flag = true;
        // std::cout << argv[3] << '\n';                                                // DEBUG
    }
    if (favcolor_flag == true) {
        std::string favcolor = argv[3];
        for (int color = 0; color < favcolor.size(); ++color) {
            for (int i = 0; i < password.size(); ++i) {
                if (filled[i] == false) {
                    password[i] = favcolor[color];
                    filled[i] = true;
                    break;
                }
            }
        }
        // std::cout << '\n' << password;                                               // DEBUG
    }
    std::cout << '\n' << password;
} 