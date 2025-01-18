#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <map>

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
    } while (ranges::next_permutation(route).found);

    return {minCost, bestRoute};
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
        auto [minCost, bestRoute] = bruteForceTSP(cities, graph);

        cout << minCost << endl;
        for (const auto& city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}
