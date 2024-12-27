//
// Created by rober on 26/12/2024.
//

#ifndef RESOLVER_H
#define RESOLVER_H

#include <vector>
#include <set>
#include <string>

using Clause = std::set<std::string>;
using CNF = std::vector<Clause>;

class Resolver {
public:
    // Perform resolution on a given CNF formula
    bool resolve(const CNF& cnf);

private:
    // Helper function to find resolvable literals
    bool findResolvable(const Clause& clause1, const Clause& clause2, std::string& literal) const;

    // Resolves two clauses and produces a new clause
    Clause resolveClauses(const Clause& clause1, const Clause& clause2, const std::string& literal) const;

    // Check if a clause is empty
    bool isEmptyClause(const Clause& clause) const;
};

#endif // RESOLVER_H
