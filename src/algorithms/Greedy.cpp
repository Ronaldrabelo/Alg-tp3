#include "../../include/algorithms/Greedy.h"
#include <limits>
#include <unordered_map>


//Algoritmo guloso para resolver o problema usando a inserção mais próxima.
//Encontra uma solução aproximada para a rota mínima.
std::pair<int, std::vector<std::string>> nearestInsertion(const std::vector<std::string>& cities, const Graph& graph) {
    if (cities.size() < 2) return {0, cities};

    std::vector<std::string> route;
    std::unordered_map<std::string, bool> visited;

    std::string start = cities[0];
    std::string nearest;
    int minDist = std::numeric_limits<int>::max();

    for (const auto& city : cities) {
        if (city != start && graph.at(start).count(city) && graph.at(start).at(city) < minDist) {
            minDist = graph.at(start).at(city);
            nearest = city;
        }
    }

    if (nearest.empty()) return {std::numeric_limits<int>::max(), {}};

    route.push_back(start);
    route.push_back(nearest);
    visited[start] = visited[nearest] = true;
    int cost = minDist;

    while (route.size() < cities.size()) {
        std::string bestCity;
        int bestIncrease = std::numeric_limits<int>::max();
        size_t bestPos = 0;

        for (const auto& city : cities) {
            if (visited[city]) continue;

            for (size_t i = 0; i < route.size(); ++i) {
                std::string a = route[i];
                std::string b = route[(i + 1) % route.size()];

                if (graph.at(a).count(city) && graph.at(city).count(b)) {
                    int increase = graph.at(a).at(city) + graph.at(city).at(b) - graph.at(a).at(b);
                    if (increase < bestIncrease) {
                        bestIncrease = increase;
                        bestCity = city;
                        bestPos = i + 1;
                    }
                }
            }
        }

        if (bestCity.empty()) return {std::numeric_limits<int>::max(), {}};

        route.insert(route.begin() + bestPos, bestCity);
        visited[bestCity] = true;
        cost += bestIncrease;
    }

    if (graph.at(route.back()).count(route[0])) {
        cost += graph.at(route.back()).at(route[0]);
    } else {
        return {std::numeric_limits<int>::max(), {}};
    }

    return {cost, route};
}
