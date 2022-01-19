#include "solver.h"
#include "../tests/test.h"

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
        if (input == "test")
        {
           test_all();
           std::cout << "All tests passed\n";
           continue;
        }
        const auto &[isError, value] = solve(input);
        if (isError)
            std::cout << "The input `" << input << "` is invalid\n";
        else
            std::cout << value << "\n";
    }
    return 0;
}
