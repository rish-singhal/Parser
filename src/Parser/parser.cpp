#include "parser.h"

// returns isError: bool
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
//        -> LPAREN expression RPAREN
// returns isError: bool
bool Parser::factor(std::unique_ptr<ASTNode>& head)
{
    assert(m_position < (uint32_t) tokens.size());
    if (std::isdigit(tokens[m_position]))
    {
        auto temporaryNode = std::make_unique<ASTNode>(tokens[m_position]);
        head = std::move(temporaryNode);
        return advance();
    }

    if (tokens[m_position] == '(')
    {
        bool isError = advance();
        if (isError)
            return isError;

        isError = expression(head);
        if (isError)
            return isError;

        assert(m_position < (uint32_t) tokens.size());
        if (tokens[m_position] == ')')
            return advance();

        return true; // unbalanced parenthesis
    }

    return false;
};

// term -> factor ((*|/) factor)*
// returns isError: bool
bool Parser::term(std::unique_ptr<ASTNode>& head)
{
    auto leftNode = std::make_unique<ASTNode>();
    bool isError = factor(leftNode);

    if (isError)
        return isError;

    assert(m_position < (uint32_t) tokens.size());
    while (tokens[m_position] == '*' || tokens[m_position] == '/')
    {
        auto temporaryNode = std::make_unique<ASTNode>(tokens[m_position]);
        temporaryNode->leftChild = std::move(leftNode);

        isError = advance();
        if (isError)
            return isError;

        isError = factor(temporaryNode->rightChild);
        if (isError)
            return isError;

        leftNode = std::move(temporaryNode);
    }

    head = std::move(leftNode);
    return false;
};

// expression -> term ((+|-) term)*
// returns isError: bool
bool Parser::expression(std::unique_ptr<ASTNode>& head)
{
    assert(m_position < (uint32_t) tokens.size());
    if (tokens[m_position] == '$')
        return false;

    auto leftNode = std::make_unique<ASTNode>();
    bool isError = term(leftNode);
    if (isError)
        return isError;

    assert(m_position < (uint32_t) tokens.size());
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

// returns isError: bool, pointer to the head node of AST
std::pair<bool, std::unique_ptr<ASTNode>> Parser::parseAST()
{
    std::unique_ptr<ASTNode> head = std::make_unique<ASTNode>();

    if ((uint32_t) tokens.size() == 0)
        return {false, std::move(head)};

    bool isError = advance();
    if (isError)
        return {isError, std::move(head)};

    isError = expression(head);
    if (isError)
        return {isError, std::move(head)};

    assert(m_position < (uint32_t) tokens.size());

    // checks if the end of input is reached
    if (tokens[m_position] != '$')
        return {true, std::move(head)};

    return {false, std::move(head)};
};
