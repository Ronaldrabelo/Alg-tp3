#include "../../include/algorithms/BruteForce.h"
#include "../../include/utils/PermutationUtils.h"
#include "../../include/utils/GraphUtils.h"
#include <limits>

//O algoritmo testa todas as permutações possíveis das cidades e calcula o custo de cada rota.
//Retorna a rota de menor custo encontrada.

std::pair<int, std::vector<std::string>> bruteForce(std::vector<std::string> cities, const Graph& graph) {
    std::vector<std::string> bestRoute;
    int minCost = std::numeric_limits<int>::max();

    do {
        int currentCost = calculateRouteCost(cities, graph);
        if (currentCost < minCost) {
            minCost = currentCost;
            bestRoute = cities;
        }
    } while (nextPermutation(cities));

    return {minCost, bestRoute};
}