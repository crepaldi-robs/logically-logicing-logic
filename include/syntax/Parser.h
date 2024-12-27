//
// Created by rober on 26/12/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>

enum class NodeType { Operand, Operator };

struct Node {
    NodeType type;
    std::string value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(NodeType type, const std::string& value,
         std::shared_ptr<Node> left = nullptr,
         std::shared_ptr<Node> right = nullptr)
        : type(type), value(value), left(std::move(left)), right(std::move(right)) {}
};

class Parser {
    int precedence(const std::string& op);
    bool isOperator(const std::string& token);

public:
    std::shared_ptr<Node> parse(const std::vector<std::string>& tokens);
};

#endif // PARSER_H
