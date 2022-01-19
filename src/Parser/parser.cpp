#include "parser.h"

bool Parser::advance()
{
    m_position++;
    while (m_position < (uint32_t) tokens.size() && tokens[m_position] == ' ')
        m_position++;

    // in case string is exhausted
    if (m_position >= (uint32_t) tokens.size())
        return true;

    return false;
};

// factor -> '0-9'
//        -> LPAREN expr RPAREN
bool Parser::factor(std::unique_ptr<ASTNode>& head)
{
    if (std::isdigit(tokens[m_position]))
    {
        auto tempNode = std::make_unique<ASTNode>(tokens[m_position]);
        head = std::move(tempNode);
        return advance();
    }

    if (tokens[m_position] == '(')
    {
        bool isError = advance();
        if (isError)
            return isError;

        isError = expr(head);
        if (isError)
            return isError;

        if (tokens[m_position] == ')')
            return advance();

        return false; // unbalanced parenthesis
    }

    return false;
};

// term -> factor ((*|/) factor)*
bool Parser::term(std::unique_ptr<ASTNode>& head)
{
    auto leftNode = std::make_unique<ASTNode>();
    bool isError = factor(leftNode);

    if (isError)
        return isError;

    while (tokens[m_position] == '*' || tokens[m_position] == '/')
    {
        auto tempNode = std::make_unique<ASTNode>(tokens[m_position]);
        tempNode->leftChild = std::move(leftNode);

        isError = advance();
        if (isError)
            return isError;

        isError = factor(tempNode->rightChild);
        if (isError)
            return isError;

        leftNode = std::move(tempNode);
    }

    head = std::move(leftNode);
    return false;
};

// expr -> term ((+|-) term)*
bool Parser::expr(std::unique_ptr<ASTNode>& head)
{
    if (tokens[m_position] == '$')
        return false;

    auto leftNode = std::make_unique<ASTNode>();
    bool isError = term(leftNode);
    if (isError)
        return isError;

    while (tokens[m_position] == '+' || tokens[m_position] == '-')
    {
        auto tempNode = std::make_unique<ASTNode>(tokens[m_position]);
        tempNode->leftChild = std::move(leftNode);

        isError = advance();
        if (isError)
            return isError;

        isError = term(tempNode->rightChild);
        if (isError)
            return isError;

        leftNode = std::move(tempNode);
    }

    head = std::move(leftNode);
    return false;
};

std::pair<bool, std::unique_ptr<ASTNode>> Parser::parseAST()
{
    std::unique_ptr<ASTNode> head = std::make_unique<ASTNode>();

    if ((uint32_t) tokens.size() == 0)
        return {false, std::move(head)};

    bool isError = advance();
    if (isError)
        return {isError, std::move(head)};

    isError = expr(head);
    if (isError)
        return {isError, std::move(head)};

    assert(m_position < (uint32_t) tokens.size());

    if (tokens[m_position] != '$')
        return {true, std::move(head)};

    return {false, std::move(head)};
};
