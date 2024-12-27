//
// Created by rober on 26/12/2024.
//

#include "resolution/Resolver.h"
#include <iostream>
#include <algorithm>

// Check if a clause is empty
bool Resolver::isEmptyClause(const Clause& clause) const {
    return clause.empty();
}

// Find resolvable literals between two clauses
bool Resolver::findResolvable(const Clause& clause1, const Clause& clause2, std::string& literal) const {
    for (const auto& lit : clause1) {
        std::string negatedLit = (lit[0] == '¬') ? lit.substr(1) : "¬" + lit;
        if (clause2.find(negatedLit) != clause2.end()) {
            literal = lit;
            return true;
        }
    }
    return false;
}

// Resolve two clauses on a given literal
Clause Resolver::resolveClauses(const Clause& clause1, const Clause& clause2, const std::string& literal) const {
    Clause resolvedClause;

    // Remove the literal and its negation
    std::string negatedLiteral = (literal[0] == '¬') ? literal.substr(1) : "¬" + literal;
    for (const auto& lit : clause1) {
        if (lit != literal) {
            resolvedClause.insert(lit);
        }
    }
    for (const auto& lit : clause2) {
        if (lit != negatedLiteral) {
            resolvedClause.insert(lit);
        }
    }

    return resolvedClause;
}

// Perform resolution on a CNF formula
bool Resolver::resolve(const CNF& cnf) {
    CNF newClauses = cnf;
    bool progress = true;

    while (progress) {
        progress = false;
        size_t n = newClauses.size();

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                std::string resolvableLiteral;
                if (findResolvable(newClauses[i], newClauses[j], resolvableLiteral)) {
                    Clause resolvedClause = resolveClauses(newClauses[i], newClauses[j], resolvableLiteral);

                    if (isEmptyClause(resolvedClause)) {
                        // Empty clause indicates a contradiction
                        std::cout << "Contradiction found: Resolving clause "
                                  << i << " and " << j << " results in an empty clause.\n";
                        return true;
                    }

                    // Add the resolved clause if it's new
                    if (std::find(newClauses.begin(), newClauses.end(), resolvedClause) == newClauses.end()) {
                        newClauses.push_back(resolvedClause);
                        progress = true;
                    }
                }
            }
        }
    }

    // No contradiction found
    return false;
}
