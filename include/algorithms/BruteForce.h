#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <vector>
#include <string>
#include <map>
#include <utility>

using Graph = std::map<std::string, std::map<std::string, int>>;

std::pair<int, std::vector<std::string>> bruteForce(std::vector<std::string> cities, const Graph& graph);

#endif // BRUTEFORCE_H