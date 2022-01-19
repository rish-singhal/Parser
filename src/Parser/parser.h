#pragma once

#include "../AST/node.h"

#include <memory>
#include <string>

class Parser
{
public:
    explicit Parser(const std::string& _tokens)
        : tokens(_tokens + '$'), // adds `$` at the end of the expression as a symbol for end of line
          m_position(/*Initial Position=*/-1) {}

    bool advance();

    bool factor(std::unique_ptr<ASTNode>& head);

    bool term(std::unique_ptr<ASTNode>& head);

    bool expr(std::unique_ptr<ASTNode>& head);

    std::pair<bool, std::unique_ptr<ASTNode>> parseAST();

private:
    const std::string operators = "+-/*";
    const std::string tokens;
    int32_t m_position;
};
