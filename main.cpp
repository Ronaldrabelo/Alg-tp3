#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <unordered_map>

using namespace std;

using Graph = map<string, map<string, int>>;

void reverseVector(vector<string>& vec, int start, int end) {
    while (start < end) {
        swap(vec[start], vec[end]);
        start++;
        end--;
    }
}

bool next_permutation(vector<string>& route) {
    int i = static_cast<int>(route.size()) - 2;
    while (i >= 0 && route[i] >= route[i + 1]) i--;
    if (i < 0) return false;
    int j = static_cast<int>(route.size()) - 1;
    while (route[j] <= route[i]) j--;
    swap(route[i], route[j]);

    reverseVector(route, i + 1, static_cast<int>(route.size()) - 1);

    return true;
}


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
pair<int, vector<string>> bruteForceTSP(vector<string> cities, const Graph& graph) {
    vector<string> bestRoute;
    int minCost = numeric_limits<int>::max();

    do {
        int currentCost = calculateRouteCost(cities, graph);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestRoute = cities;
        }
    } while (next_permutation(cities));

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

pair<int, vector<string>> greedyTSP(const vector<string>& cities, const Graph& graph) {
    vector<string> route;
    unordered_map<string, bool> visited;
    string current = cities[0];
    route.push_back(current);
    visited[current] = true;
    int cost = 0;

    for (size_t i = 1; i < cities.size(); ++i) {
        string nextCity;
        int minDist = numeric_limits<int>::max();

        for (const auto& neighbor : graph.at(current)) {
            if (!visited[neighbor.first] && neighbor.second < minDist) {
                minDist = neighbor.second;
                nextCity = neighbor.first;
            }
        }

        if (nextCity.empty()) return {numeric_limits<int>::max(), {}};
        route.push_back(nextCity);
        visited[nextCity] = true;
        cost += minDist;
        current = nextCity;
    }

    if (graph.at(current).count(route[0])) {
        cost += graph.at(current).at(route[0]);
        route.push_back(route[0]);
    } else {
        return {numeric_limits<int>::max(), {}};
    }
    return {cost, route};
}

int main() {
    char strategy;
    int V, E;

    cin >> strategy >> V >> E;

    vector<string> cities;
    Graph graph;
    unordered_map<string, bool> cityExists;


    for (int i = 0; i < E; ++i) {
        string city1, city2;
        int distance;
        cin >> city1 >> city2 >> distance;

        graph[city1][city2] = distance;
        graph[city2][city1] = distance;

        if (!cityExists[city1]) {
            cities.push_back(city1);
            cityExists[city1] = true;
        }
        if (!cityExists[city2]) {
            cities.push_back(city2);
            cityExists[city2] = true;
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

        // reverse(route.begin() + 1, route.end());

        cout << minCost << endl;
        for (int cityIndex : route) {
            cout << indexToCity[cityIndex] << " ";
        }
        cout << endl;
    } else if (strategy == 'g') {
        pair<int, vector<string>> result;
        result = greedyTSP(cities, graph);
        cout << result.first << endl;
        for (const auto& city : result.second) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}
