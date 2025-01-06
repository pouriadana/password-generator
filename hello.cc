#include <iostream>
#include <string>
#include <random>

int main()
{
    std::string viable_chars {"abcdefghijklmnopqrstuvwxyz"};
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> distrib(0,viable_chars.size()-1);
    const int pass_len{12};
    for (int i = 0; i < pass_len; ++i) {
        std::cout << viable_chars[distrib(engine)];
    }
    std::cout << '\n';
}