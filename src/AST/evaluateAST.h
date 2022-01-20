#pragma once

#include "node.h"

#include <string>

const std::string operators = "+-/*";

// returns isError: bool, resulting value: double
std::pair<bool, double> evaluateAST(const std::unique_ptr<ASTNode>& node)
{
    if (node)
    {
        if (std::isdigit(node->token))
            return {false, node->token - '0'};

        if (operators.find(node->token) != std::string::npos)
        {
            auto [leftIsError, leftValue] = evaluateAST(node->leftChild);
            auto [rightIsError, rightValue] = evaluateAST(node->rightChild);

            bool isError = leftIsError | rightIsError;

            if (node->token == '+')
                return {isError, leftValue + rightValue};
            if (node->token == '*')
                return {isError, leftValue * rightValue};
            if (node->token == '/')
                return {isError, leftValue / rightValue};
            if (node->token == '-')
                return {isError, leftValue - rightValue};

            assert(true);
        }
    }

    return {true, 0};
}
