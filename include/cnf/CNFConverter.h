//
// Created by rober on 26/12/2024.
//

#ifndef CNF_CONVERTER_H
#define CNF_CONVERTER_H

#include <vector>
#include <set>
#include <string>
#include <memory>
#include "syntax/Parser.h"

class CNFConverter {
public:
    std::vector<std::set<std::string>> toCNF(const std::shared_ptr<Node>& root);

private:
    std::shared_ptr<Node> eliminateImplications(const std::shared_ptr<Node>& root);
    std::shared_ptr<Node> pushNegations(const std::shared_ptr<Node>& root);
    std::shared_ptr<Node> distributeOrOverAnd(const std::shared_ptr<Node>& root);
    void collectClauses(const std::shared_ptr<Node>& root, std::vector<std::set<std::string>>& clauses);
};

#endif // CNF_CONVERTER_H
