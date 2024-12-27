//
// Created by rober on 26/12/2024.
//

#include "syntax/Tokenizer.h"
#include <regex>

std::vector<std::string> Tokenizer::tokenize(const std::string& formula) {
    std::regex tokenRegex(R"([()¬&|=⊥>]|[a-zA-Z]+)");
    std::sregex_iterator begin(formula.begin(), formula.end(), tokenRegex);
    std::sregex_iterator end;
    std::vector<std::string> tokens;

    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }

    return tokens;
}
