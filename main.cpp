#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "include/algorithms/BruteForce.h"
#include "include/algorithms/DynamicProgramming.h"
#include "include/algorithms/Greedy.h"

using namespace std;

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
        pair<int, vector<string>> result = bruteForce(cities, graph);
        int minCost = result.first;
        vector<string> bestRoute = result.second;

        cout << minCost << endl;
        for (const auto& city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    } else if (strategy == 'd') {
        pair<int, vector<string>> result = dynamicProgramming(cities, graph);
        int minCost = result.first;
        vector<string> bestRoute = result.second;

        cout << minCost << endl;
        for (const auto& city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    } else if (strategy == 'g') {
        pair<int, vector<string>> result = greedy(cities, graph);
        cout << result.first << endl;
        for (const auto& city : result.second) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}