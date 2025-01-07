#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>

/* Helper functions */
bool isdigit(std::string c)
{
    /* Support up to 99 */
    bool result = false;
    if (c.size() > 2) {
        return result;
    }
    else {
        result = true;
        for (int i = 0; i < c.size(); ++i) {
            if (!(c[i] - '0' >= 0 && c[i] - '0' <= 9)) {
                result = false;
                break;
            }
        }
    }
    return result;
}
int main(int argc, char *argv[])
{
    const std::string viable_chars {"abcdefghijklmnopqrstuvwxyz"};          // length == 26
    const std::string viable_chars_capital {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};  // length == 26
    const std::string non_alphabetic_chars {"0123456789!?<>(){}@#$%^&*"};   // length == 25
    std::random_device rd;
    std::string password{};
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> distrib(0,viable_chars.size()-1);
    int pass_len{0};
    if (argc == 1) {
        pass_len = 12;
    }
    else if (argc == 2 && isdigit(argv[1])) {
        pass_len = atof(argv[1]);
    }
    else {
        std::cout << "Illegal input\n";
        std::exit(EXIT_FAILURE);
    }
    /* Allow for the random selection of the type of character */
    char candidates[3] {0,0,0};
    for (int i = 0; i < pass_len; ++i) {
        candidates[0] = viable_chars[distrib(engine)];
        candidates[1] = viable_chars_capital[distrib(engine)];
        candidates[2] = non_alphabetic_chars[distrib(engine)];
        int rsubscript{ distrib(engine)%3 };
        std::string chosen_char{ candidates[rsubscript] };
        password += chosen_char;
    }
    std::cout << '\n';
    std::cout << password << '\n';
}