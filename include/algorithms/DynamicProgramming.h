#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <vector>
#include <string>
#include <map>

std::pair<int, std::vector<std::string>> dynamicProgramming(const std::vector<std::string>& cities, const std::map<std::string, std::map<std::string, int>>& graph);

#endif // DYNAMICPROGRAMMING_H