//
// Created by rober on 26/12/2024.
//

#include "cnf/CNFConverter.h"

#include <bits/stdc++.h>

// Step 1: Eliminate implications (α → β ≡ ¬α ∨ β)
std::shared_ptr<Node> CNFConverter::eliminateImplications(const std::shared_ptr<Node>& root) {
    if (!root) return nullptr;

    if (root->type == NodeType::Operator && root->value == "=") {
        auto left = eliminateImplications(root->left);
        auto right = eliminateImplications(root->right);
        return std::make_shared<Node>(Node{NodeType::Operator, "|",
            std::make_shared<Node>(Node{NodeType::Operator, "¬", left, nullptr}),
            right});
    }

    return std::make_shared<Node>(Node{
        root->type, root->value,
        eliminateImplications(root->left),
        eliminateImplications(root->right)
    });
}

// Step 2: Push negations inward (using De Morgan's Laws)
std::shared_ptr<Node> CNFConverter::pushNegations(const std::shared_ptr<Node>& root) {
    if (!root) return nullptr;

    if (root->type == NodeType::Operator && root->value == "¬") {
        auto child = root->left;
        if (child->type == NodeType::Operator) {
            if (child->value == "¬") {
                // Double negation elimination
                return pushNegations(child->left);
            } else if (child->value == "&") {
                // ¬(A ∧ B) ≡ ¬A ∨ ¬B
                return std::make_shared<Node>(Node{NodeType::Operator, "|",
                    pushNegations(std::make_shared<Node>(Node{NodeType::Operator, "¬", child->left, nullptr})),
                    pushNegations(std::make_shared<Node>(Node{NodeType::Operator, "¬", child->right, nullptr}))});
            } else if (child->value == "|") {
                // ¬(A ∨ B) ≡ ¬A ∧ ¬B
                return std::make_shared<Node>(Node{NodeType::Operator, "&",
                    pushNegations(std::make_shared<Node>(Node{NodeType::Operator, "¬", child->left, nullptr})),
                    pushNegations(std::make_shared<Node>(Node{NodeType::Operator, "¬", child->right, nullptr}))});
            }
        }
    }

    return std::make_shared<Node>(Node{
        root->type, root->value,
        pushNegations(root->left),
        pushNegations(root->right)
    });
}

// Step 3: Distribute OR over AND
std::shared_ptr<Node> CNFConverter::distributeOrOverAnd(const std::shared_ptr<Node>& root) {
    if (!root) return nullptr;

    if (root->type == NodeType::Operator && root->value == "|") {
        auto left = distributeOrOverAnd(root->left);
        auto right = distributeOrOverAnd(root->right);

        if (left->type == NodeType::Operator && left->value == "&") {
            // A ∨ (B ∧ C) ≡ (A ∨ B) ∧ (A ∨ C)
            return std::make_shared<Node>(Node{NodeType::Operator, "|",
                distributeOrOverAnd(std::make_shared<Node>(Node{NodeType::Operator, "|", left->left, right})),
                distributeOrOverAnd(std::make_shared<Node>(Node{NodeType::Operator, "|", left->right, right}))});
        }

        if (right->type == NodeType::Operator && right->value == "&") {
            // (A ∧ B) ∨ C ≡ (A ∨ C) ∧ (B ∨ C)
            return std::make_shared<Node>(Node{NodeType::Operator, "&",
                distributeOrOverAnd(std::make_shared<Node>(Node{NodeType::Operator, "|", left, right->left})),
                distributeOrOverAnd(std::make_shared<Node>(Node{NodeType::Operator, "|", left, right->right}))});
        }

        return std::make_shared<Node>(Node{NodeType::Operator, "|", left, right});
    }

    return std::make_shared<Node>(Node{
        root->type, root->value,
        distributeOrOverAnd(root->left),
        distributeOrOverAnd(root->right)
    });
}

// Helper function to collect clauses from CNF tree
void CNFConverter::collectClauses(const std::shared_ptr<Node>& root, std::vector<std::set<std::string>>& clauses) {
    if (!root) return;

    if (root->type == NodeType::Operator && root->value == "&") {
        collectClauses(root->left, clauses);
        collectClauses(root->right, clauses);
    } else {
        std::set<std::string> clause;
        std::stack<std::shared_ptr<Node>> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto node = stack.top();
            stack.pop();

            if (node->type == NodeType::Operator && node->value == "|") {
                stack.push(node->left);
                stack.push(node->right);
            } else {
                clause.insert(node->value);
            }
        }

        clauses.push_back(clause);
    }
}

// Main function to convert formula to CNF
std::vector<std::set<std::string>> CNFConverter::toCNF(const std::shared_ptr<Node>& root) {
    auto noImplications = eliminateImplications(root);
    auto negationsPushed = pushNegations(noImplications);
    auto distributed = distributeOrOverAnd(negationsPushed);

    std::vector<std::set<std::string>> clauses;
    collectClauses(distributed, clauses);

    return clauses;
}
