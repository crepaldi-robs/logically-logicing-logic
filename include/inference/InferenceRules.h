//
// Created by rober on 26/12/2024.
//

#ifndef INFERENCE_RULES_H
#define INFERENCE_RULES_H

#include <string>
#include <vector>
#include <map>

class InferenceRules {
public:
    bool modusPonens(const std::string& premise1, const std::string& premise2, const std::string& conclusion);
    bool modusTollens(const std::string& premise1, const std::string& negatedConclusion);
    bool hypotheticalSyllogism(const std::string& premise1, const std::string& premise2);

    bool validateArgument(const std::vector<std::string>& premises, const std::string& conclusion);
};

#endif // INFERENCE_RULES_H
