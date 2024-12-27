//
// Created by rober on 26/12/2024.
//

#include "inference/InferenceRules.h"
#include <stdexcept>
#include <regex>

// Helper function: Extract antecedent and consequent from an implication
std::pair<std::string, std::string> parseImplication(const std::string& formula) {
    std::regex implicationRegex(R"((.+?) = (.+))");
    std::smatch match;
    if (std::regex_match(formula, match, implicationRegex)) {
        return {match[1], match[2]};
    }
    throw std::invalid_argument("Invalid implication format: " + formula);
}

// Modus Ponens: (p → q, p) ⟹ q
bool InferenceRules::modusPonens(const std::string& premise1, const std::string& premise2, const std::string& conclusion) {
    auto [antecedent, consequent] = parseImplication(premise1);
    return (premise2 == antecedent && conclusion == consequent);
}

// Modus Tollens: (p → q, ¬q) ⟹ ¬p
bool InferenceRules::modusTollens(const std::string& premise1, const std::string& negatedConclusion) {
    auto [antecedent, consequent] = parseImplication(premise1);
    return (negatedConclusion == "¬" + consequent);
}

// Hypothetical Syllogism: (p → q, q → r) ⟹ p → r
bool InferenceRules::hypotheticalSyllogism(const std::string& premise1, const std::string& premise2) {
    auto [antecedent1, consequent1] = parseImplication(premise1);
    auto [antecedent2, consequent2] = parseImplication(premise2);
    return (consequent1 == antecedent2);
}

// Validate Argument
bool InferenceRules::validateArgument(const std::vector<std::string>& premises, const std::string& conclusion) {
    // Combine premises to form a single logical structure
    std::string combined = "(" + premises[0] + ")";
    for (size_t i = 1; i < premises.size(); ++i) {
        combined += " & (" + premises[i] + ")";
    }
    combined += " = " + conclusion;

    // Simulate logical reasoning (truth table or resolution can be added here)
    // For simplicity, we assume the formula is valid if Modus Ponens applies
    for (const auto& premise : premises) {
        if (modusPonens(combined, premise, conclusion)) {
            return true;
        }
    }
    return false;
}
