#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <map>
#include <unordered_map>

using namespace std;

using Graph = map<string, map<string, int>>;

int calculateRouteCost(const vector<string>& route, const Graph& graph) {
    int cost = 0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        const auto& from = route[i];
        const auto& to = route[i + 1];
        if (graph.count(from) > 0 && graph.at(from).count(to) > 0) {
            cost += graph.at(from).at(to);
        } else {
            return numeric_limits<int>::max();
        }
    }
    const auto& last = route.back();
    const auto& first = route[0];
    if (graph.count(last) > 0 && graph.at(last).count(first) > 0) {
        cost += graph.at(last).at(first);
    } else {
        return numeric_limits<int>::max();
    }
    return cost;
}

pair<int, vector<string>> bruteForceTSP(const vector<string>& cities, const Graph& graph) {
    vector<string> bestRoute;
    int minCost = numeric_limits<int>::max();

    vector<string> route = cities;
    do {
        int currentCost = calculateRouteCost(route, graph);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestRoute = route;
        }
    } while (next_permutation(route.begin(), route.end()));

    return {minCost, bestRoute};
}

map<string, int> cityToIndex;
vector<string> indexToCity;

int tspDP(int currentCity, int visitedMask, const vector<vector<int>>& dist, vector<vector<int>>& memo) {
    if (visitedMask == (1 << dist.size()) - 1) {
        return dist[currentCity][0];
    }

    if (memo[currentCity][visitedMask] != -1) {
        return memo[currentCity][visitedMask];
    }

    int minCost = numeric_limits<int>::max();

    for (int nextCity = 0; nextCity < dist.size(); ++nextCity) {
        if (!(visitedMask & (1 << nextCity))) {
            int cost = dist[currentCity][nextCity] + tspDP(nextCity, visitedMask | (1 << nextCity), dist, memo);
            minCost = min(minCost, cost);
        }
    }

    memo[currentCity][visitedMask] = minCost;
    return minCost;
}

void reconstructRoute(int currentCity, int visitedMask, const vector<vector<int>>& dist, vector<vector<int>>& memo, vector<int>& route) {
    if (route.empty()) {
        route.push_back(currentCity);
    }

    if (visitedMask == (1 << dist.size()) - 1) {
        return;
    }

    bool nextCityFound = false;

    for (int nextCity = 0; nextCity < dist.size(); ++nextCity) {
        if (!(visitedMask & (1 << nextCity))) {
            int expectedCost = dist[currentCity][nextCity] + memo[nextCity][visitedMask | (1 << nextCity)];

            if (expectedCost == memo[currentCity][visitedMask]) {
                route.push_back(nextCity);
                reconstructRoute(nextCity, visitedMask | (1 << nextCity), dist, memo, route);
                nextCityFound = true;
                break;
            }
        }
    }

    if (!nextCityFound) {
        for (int nextCity = 0; nextCity < dist.size(); ++nextCity) {
            if (!(visitedMask & (1 << nextCity))) {
                route.push_back(nextCity);
                reconstructRoute(nextCity, visitedMask | (1 << nextCity), dist, memo, route);
                break;
            }
        }
    }
}

int main() {
    char strategy;
    int V, E;

    cin >> strategy >> V >> E;

    vector<string> cities;
    Graph graph;

    for (int i = 0; i < E; ++i) {
        string city1, city2;
        int distance;
        cin >> city1 >> city2 >> distance;

        graph[city1][city2] = distance;
        graph[city2][city1] = distance;

        if (find(cities.begin(), cities.end(), city1) == cities.end()) {
            cities.push_back(city1);
        }
        if (find(cities.begin(), cities.end(), city2) == cities.end()) {
            cities.push_back(city2);
        }
    }

    if (strategy == 'b') {
        pair<int, vector<string>> result = bruteForceTSP(cities, graph);
        int minCost = result.first;
        vector<string> bestRoute = result.second;

        cout << minCost << endl;
        for (const auto& city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    } else if (strategy == 'd') {
        for (size_t i = 0; i < cities.size(); ++i) {
            cityToIndex[cities[i]] = i;
            indexToCity.push_back(cities[i]);
        }

        vector<vector<int>> dist(V, vector<int>(V, numeric_limits<int>::max()));
        for (const auto& city_neighbors : graph) {
            const string& city1 = city_neighbors.first;
            const auto& neighbors = city_neighbors.second;
            int i = cityToIndex[city1];
            for (const auto& neighbor : neighbors) {
                const string& city2 = neighbor.first;
                int distance = neighbor.second;
                int j = cityToIndex[city2];
                dist[i][j] = distance;
            }
        }

        vector<vector<int>> memo(V, vector<int>(1 << V, -1));

        int minCost = tspDP(0, 1, dist, memo);

        vector<int> route;
        reconstructRoute(0, 1, dist, memo, route);

        cout << minCost << endl;
        for (int cityIndex : route) {
            cout << indexToCity[cityIndex] << " ";
        }
        cout << endl;
    }

    return 0;
}
