#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include <map>
#include <string>
#include <vector>

using Graph = std::map<std::string, std::map<std::string, int>>;

int calculateRouteCost(const std::vector<std::string>& route, const Graph& graph);

#endif