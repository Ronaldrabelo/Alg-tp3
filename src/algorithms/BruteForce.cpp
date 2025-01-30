#include "../../include/algorithms/BruteForce.h"
#include "../../include/utils/PermutationUtils.h"
#include "../../include/utils/GraphUtils.h"
#include <limits>

std::pair<int, std::vector<std::string>> bruteForce(std::vector<std::string> cities, const Graph& graph) {
    std::vector<std::string> bestRoute;
    int minCost = std::numeric_limits<int>::max();

    do {
        int currentCost = calculateRouteCost(cities, graph);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestRoute = cities;
        }
    } while (next_permutation(cities));

    return {minCost, bestRoute};
}