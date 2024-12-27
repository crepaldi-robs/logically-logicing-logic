//
// Created by rober on 26/12/2024.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

class Tokenizer {
public:
    std::vector<std::string> tokenize(const std::string& formula);
};

#endif // TOKENIZER_H
