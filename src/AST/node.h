#pragma once

#include <memory>

struct ASTNode
{
    char token;
    std::unique_ptr<ASTNode> leftChild;
    std::unique_ptr<ASTNode> rightChild;

    explicit ASTNode() {};
    explicit ASTNode(const char& _token) : token(_token) {};
};
