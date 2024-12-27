//
// Created by rober on 26/12/2024.
//

/*
#include <iostream>

int main() {
	std::cout << "Hello World!" << std::endl;
	return 0;
}
*/

#include <bits/stdc++.h>

#include <cnf/CNFConverter.h>
#include <inference/InferenceRules.h>
#include <resolution/Resolver.h>
#include <semantics/TruthTable.h>
#include <syntax/Parser.h>
#include <syntax/Tokenizer.h>

// Helper function to print the AST
void printAST(const std::shared_ptr<Node>& node, int depth = 0) {
    if (!node) return;

    std::string indent(depth * 2, ' ');
    std::cout << indent << node->value << " (" << (node->type == NodeType::Operator ? "Operator" : "Operand") << ")\n";

    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
}

void getAllAST(const std::shared_ptr<Node>& node, std::unordered_set<auto>& variablesSet) {
    if (!node) return;

    if (node->type != NodeType::Operator) variablesSet.insert(node->value);

    getAllAST(node->left, variablesSet);
    getAllAST(node->right, variablesSet);
}

// Example usage of Tokenizer and Parser (syntax)
void exampleSyntax() {
    std::cout << "Example syntax code:" << std::endl;

    Tokenizer tokenizer;
    Parser parser;

    std::string formula = "(p & q) = r";
    auto tokens = tokenizer.tokenize(formula);

    std::cout << "formula: " << formula << std::endl;

    std::cout << "Tokens:\n";
    for (const auto& token : tokens) {
        std::cout << "'" << token << "'" << " ";
    }
    std::cout << "\n";

    auto ast = parser.parse(tokens);

    std::cout << "\nAbstract Syntax Tree:\n";
    printAST(ast);

    std::cout << std::endl << std::endl;
}

// Example usage of TruthTable (semantics)
void exampleTruthTable() {
    std::cout << "Example truth table code:" << std::endl;

    Tokenizer tokenizer;
    Parser parser;
    TruthTable truthTable;
    Evaluator evaluator;

    // Formula input
    std::string formula = "(p | q) = r";
    auto tokens = tokenizer.tokenize(formula);
    auto ast = parser.parse(tokens);

    std::cout << "formula: " << formula << std::endl;

    // Generate truth table
    std::vector<std::string> variables;
    std::unordered_set<std::string> variablesSet;
    getAllAST(ast, variablesSet);
    // for (const auto& node : ast)
    //     if (node->type != NodeType::Operator)
    //         variablesSet.insert(node->value);
    std::cout << "variables: " << std::endl;
    for (const auto& var : variablesSet) {
        std::cout << "'" << var << "'" << " ";
        variables.push_back(var);
    }
    std::cout << std::endl;
    auto table = truthTable.generate(variables);

    // Display truth table
    std::cout << "Truth Table:\n";
    for (const auto& row : table) {
        for (const auto& [var, val] : row) {
            std::cout << var << ": " << (val ? "T" : "F") << " ";
        }
        std::cout << "=> " << (evaluator.evaluate(ast, row) ? "T" : "F") << "\n";
    }

    // Check properties
    std::cout << "\nProperties:\n";
    std::cout << "Tautology: " << (truthTable.isTautology(ast, table) ? "Yes" : "No") << "\n";
    std::cout << "Contradiction: " << (truthTable.isContradiction(ast, table) ? "Yes" : "No") << "\n";
    std::cout << "Satisfiable: " << (truthTable.isSatisfiable(ast, table) ? "Yes" : "No") << "\n";

    std::cout << std::endl << std::endl;
}

// Example usage of CNFConverter (cnf)
void exampleCNFConverter() {
    Parser parser;
    Tokenizer tokenizer;
    CNFConverter converter;

    std::string formula = "(p = q) & (¬q = ¬p)";

    auto tokens = tokenizer.tokenize(formula);

    auto ast = parser.parse(tokens);
    auto cnf = converter.toCNF(ast);

    for (const auto& clause : cnf) {
        for (const auto& literal : clause) {
            std::cout << literal << " ";
        }
        std::cout << std::endl;
    }

    // Example usage of InferenceRules (inference)

    InferenceRules inference;

    // Example: Modus Ponens
    std::string premise1 = "p = q";
    std::string premise2 = "p";
    std::string conclusion = "q";

    if (inference.modusPonens(premise1, premise2, conclusion)) {
        std::cout << "Modus Ponens is valid.\n";
    } else {
        std::cout << "Modus Ponens is invalid.\n";
    }

    // Example: Validate Argument
    std::vector<std::string> premises = {"p = q", "q = r"};
    std::string argumentConclusion = "p = r";

    if (inference.validateArgument(premises, argumentConclusion)) {
        std::cout << "The argument is valid.\n";
    } else {
        std::cout << "The argument is invalid.\n";
    }
}

// Example usage of Resolver (resolution)
void exampleResolver() {
    Resolver resolver;

    // Example CNF: (¬p ∨ q), (¬q ∨ r), (¬r)
    CNF cnf = {
        {"¬p", "q"},
        {"¬q", "r"},
        {"¬r"}
    };

    // Resolve the CNF
    if (resolver.resolve(cnf)) {
        std::cout << "The formula is unsatisfiable (a contradiction was found).\n";
    } else {
        std::cout << "The formula is satisfiable (no contradiction was found).\n";
    }
}

int main() {
    exampleSyntax();
    exampleTruthTable();
    exampleCNFConverter();
    exampleResolver();

    return 0;
}
