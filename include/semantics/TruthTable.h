//
// Created by rober on 26/12/2024.
//

#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "syntax/Parser.h"

class TruthTable {
public:
    std::vector<std::map<std::string, bool>> generate(const std::vector<std::string>& variables);
    bool isTautology(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table);
    bool isContradiction(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table);
    bool isSatisfiable(const std::shared_ptr<Node>& formula, const std::vector<std::map<std::string, bool>>& table);
};

class Evaluator {
public:
    bool evaluate(const std::shared_ptr<Node>& formula, const std::map<std::string, bool>& values);
};

#endif // TRUTH_TABLE_H
