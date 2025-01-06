#include <iostream>
#include <string>
#include <random>

int main(int argc, char** argv)
{
    const std::string viable_chars {"abcdefghijklmnopqrstuvwxyz"};
    const std::string viable_chars_capital {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const std::string non_alphabetic_chars {"0123456789!?<>(){}@#$%^&*"};
    std::random_device rd;
    std::string password{};
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> distrib(0,viable_chars.size()-1);
    int pass_len{12};
    for (int i = 0; i < pass_len; i=i+3) {
        std::string t1{viable_chars[distrib(engine)]};
        std::string t2{viable_chars_capital[distrib(engine)]};
        std::string t3{non_alphabetic_chars[distrib(engine)]};
        password += t1 + t2 + t3;
    }
    std::cout << '\n';
    std::cout << password << '\n';
}