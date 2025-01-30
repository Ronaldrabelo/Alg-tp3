#include "../../include/algorithms/Greedy.h"
#include <limits>
#include <unordered_map>

std::pair<int, std::vector<std::string>> greedy(const std::vector<std::string>& cities, const Graph& graph) {
    std::vector<std::string> route;
    std::unordered_map<std::string, bool> visited;
    std::string current = cities[0];
    route.push_back(current);
    visited[current] = true;
    int cost = 0;

    for (size_t i = 1; i < cities.size(); ++i) {
        std::string nextCity;
        int minDist = std::numeric_limits<int>::max();

        for (const auto& neighbor : graph.at(current)) {
            if (!visited[neighbor.first] && neighbor.second < minDist) {
                minDist = neighbor.second;
                nextCity = neighbor.first;
            }
        }

        if (nextCity.empty()) return {std::numeric_limits<int>::max(), {}};
        route.push_back(nextCity);
        visited[nextCity] = true;
        cost += minDist;
        current = nextCity;
    }

    if (graph.at(current).count(route[0])) {
        cost += graph.at(current).at(route[0]);
        route.push_back(route[0]);
    } else {
        return {std::numeric_limits<int>::max(), {}};
    }
    return {cost, route};
}