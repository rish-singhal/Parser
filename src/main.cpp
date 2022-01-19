#include "solver.h"

#include <iostream>
#include <string>
#include <utility>

int main()
{
    while (true)
    {
        std::cout << "> ";
        std::string input;
        getline(std::cin, input);
        if (input == "exit")
            break;

        const auto &[isError, value] = solve(input);
        if (isError)
            std::cout << "The input `" << input << "` is invalid\n";
        else
            std::cout << value << "\n";
    }
    return 0;
}
