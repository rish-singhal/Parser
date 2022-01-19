#pragma once

#include "./AST/evaluateAST.h"
#include "./Parser/parser.h"

#include <string>
#include <memory>

std::pair<bool, double> solve(const std::string& input)
{
    auto parser = Parser(input);
    auto [isError, node] = std::move(parser.parseAST());

    if (isError)
        return {isError, 0.0};

    return evaluateAST(node);
}
