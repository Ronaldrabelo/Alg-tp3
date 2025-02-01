#include "../../include/algorithms/DynamicProgramming.h"
#include <limits>
#include <algorithm>

std::map<std::string, int> cityToIndex;
std::vector<std::string> indexToCity;

int tspDP(int currentCity, int visitedMask, const std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& memo) {
    if (visitedMask == (1 << dist.size()) - 1) {
        return dist[currentCity][0];
    }

    if (memo[currentCity][visitedMask] != -1) {
        return memo[currentCity][visitedMask];
    }

    int minCost = std::numeric_limits<int>::max();

    for (size_t nextCity = 0; nextCity < dist.size(); ++nextCity) {
        if (!(visitedMask & (1 << nextCity))) {
            int cost = dist[currentCity][nextCity] + tspDP(static_cast<int>(nextCity), visitedMask | (1 << nextCity), dist, memo);
            minCost = std::min(minCost, cost);
        }
    }

    memo[currentCity][visitedMask] = minCost;
    return minCost;
}

void reconstructRoute(int currentCity, int visitedMask, const std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& memo, std::vector<int>& route) {
    if (route.empty()) {
        route.push_back(currentCity);
    }

    if (visitedMask == (1 << dist.size()) - 1) {
        return;
    }

    bool nextCityFound = false;

    for (size_t nextCity = 0; nextCity < dist.size(); ++nextCity) {
        if (!(visitedMask & (1 << nextCity))) {
            int expectedCost = dist[currentCity][nextCity] + memo[nextCity][visitedMask | (1 << nextCity)];

            if (expectedCost == memo[currentCity][visitedMask]) {
                route.push_back(static_cast<int>(nextCity));
                reconstructRoute(static_cast<int>(nextCity), visitedMask | (1 << nextCity), dist, memo, route);
                nextCityFound = true;
                break;
            }
        }
    }

    if (!nextCityFound) {
        for (size_t nextCity = 0; nextCity < dist.size(); ++nextCity) {
            if (!(visitedMask & (1 << nextCity))) {
                route.push_back(static_cast<int>(nextCity));
                reconstructRoute(static_cast<int>(nextCity), visitedMask | (1 << nextCity), dist, memo, route);
                break;
            }
        }
    }
}

std::pair<int, std::vector<std::string>> dynamicProgramming(const std::vector<std::string>& cities, const std::map<std::string, std::map<std::string, int>>& graph) {
    for (size_t i = 0; i < cities.size(); ++i) {
        cityToIndex[cities[i]] = static_cast<int>(i);
        indexToCity.push_back(cities[i]);
    }

    std::vector<std::vector<int>> dist(cities.size(), std::vector<int>(cities.size(), std::numeric_limits<int>::max()));
    for (const auto& city_neighbors : graph) {
        const std::string& city1 = city_neighbors.first;
        const auto& neighbors = city_neighbors.second;
        int i = cityToIndex[city1];
        for (const auto& neighbor : neighbors) {
            const std::string& city2 = neighbor.first;
            int distance = neighbor.second;
            int j = cityToIndex[city2];
            dist[i][j] = distance;
        }
    }

    std::vector<std::vector<int>> memo(cities.size(), std::vector<int>(1 << cities.size(), -1));

    int minCost = tspDP(0, 1, dist, memo);

    std::vector<int> route;
    reconstructRoute(0, 1, dist, memo, route);

    std::vector<std::string> routeCities;
    for (int cityIndex : route) {
        routeCities.push_back(indexToCity[cityIndex]);
    }

    return {minCost, routeCities};
}