//
// Created by rober on 26/12/2024.
//

#include "semantics/TruthTable.h"
#include <cmath>
#include <stdexcept>

// Generate truth table for all combinations of variables
std::vector<std::map<std::string, bool>> TruthTable::generate(const std::vector<std::string>& variables) {
    size_t numRows = std::pow(2, variables.size());
    std::vector<std::map<std::string, bool>> table(numRows);

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < variables.size(); ++j) {
            table[i][variables[j]] = (i & (1 << (variables.size() - j - 1))) != 0;
        }
    }

    return table;
}

// Evaluate a formula for a given truth assignment
bool Evaluator::evaluate(const std::shared_ptr<Node>& formula, const std::map<std::string, bool>& values) {
    if (!formula) return false;

    if (formula->type == NodeType::Operand) {
        if (formula->value == "⊥") return false;
        if (formula->value == ">") return true;
        return values.at(formula->value);
    }

    if (formula->value == "¬") {
        return !evaluate(formula->left, values);
    }

    bool left = evaluate(formula->left, values);
    bool right = evaluate(formula->right, values);

    if (formula->value == "&") return left && right;
    if (formula->value == "|") return left || right;
    if (formula->value == "=") return !left || right;

    throw std::runtime_error("Unknown operator: " + formula->value);
}

// Check if the formula is a tautology
bool TruthTable::isTautology(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table) {
    Evaluator evaluator;
    for (const auto& row : table) {
        if (!evaluator.evaluate(formula, row)) {
            return false;
        }
    }
    return true;
}

// Check if the formula is a contradiction
bool TruthTable::isContradiction(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table) {
    Evaluator evaluator;
    for (const auto& row : table) {
        if (evaluator.evaluate(formula, row)) {
            return false;
        }
    }
    return true;
}

// Check if the formula is satisfiable
bool TruthTable::isSatisfiable(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table) {
    Evaluator evaluator;
    for (const auto& row : table) {
        if (evaluator.evaluate(formula, row)) {
            return true;
        }
    }
    return false;
}
