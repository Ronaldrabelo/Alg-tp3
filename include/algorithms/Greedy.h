#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <string>
#include <map>
#include <utility>

using Graph = std::map<std::string, std::map<std::string, int>>;

std::pair<int, std::vector<std::string>> nearestInsertion(const std::vector<std::string>& cities, const Graph& graph);

#endif // GREEDY_H