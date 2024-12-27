//
// Created by rober on 26/12/2024.
//

#include "syntax/Parser.h"
#include <stack>
#include <stdexcept>

// Operator precedence: higher value means higher precedence
int Parser::precedence(const std::string& op) {
    if (op == "¬") return 3;
    if (op == "&") return 2;
    if (op == "|") return 1;
    if (op == "=") return 0;
    return -1; // For operands or invalid operators
}

// Check if the token is an operator
bool Parser::isOperator(const std::string& token) {
    return token == "¬" || token == "&" || token == "|" || token == "=";
}

// Parse tokens into an AST
std::shared_ptr<Node> Parser::parse(const std::vector<std::string>& tokens) {
    std::stack<std::shared_ptr<Node>> operands;
    std::stack<std::string> operators;

    for (const auto& token : tokens) {
        if (!isOperator(token) && token != "(" && token != ")") {
            // Operand
            operands.push(std::make_shared<Node>(NodeType::Operand, token));
        } else if (token == "(") {
            // Open parenthesis
            operators.push(token);
        } else if (token == ")") {
            // Close parenthesis: resolve sub-expression
            while (!operators.empty() && operators.top() != "(") {
                auto right = operands.top(); operands.pop();
                auto left = operands.top(); operands.pop();
                auto op = operators.top(); operators.pop();

                operands.push(std::make_shared<Node>(NodeType::Operator, op, left, right));
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop(); // Remove the open parenthesis
            }
        } else {
            // Operator: apply precedence
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                auto right = operands.top(); operands.pop();
                auto left = operands.top(); operands.pop();
                auto op = operators.top(); operators.pop();

                operands.push(std::make_shared<Node>(NodeType::Operator, op, left, right));
            }
            operators.push(token);
        }
    }

    // Resolve remaining operators
    while (!operators.empty()) {
        auto right = operands.top(); operands.pop();
        auto left = operands.top(); operands.pop();
        auto op = operators.top(); operators.pop();

        operands.push(std::make_shared<Node>(NodeType::Operator, op, left, right));
    }

    return operands.top(); // The final AST
}
