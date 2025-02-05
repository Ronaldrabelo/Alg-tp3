#include "../../include/utils/GraphUtils.h"
#include <limits>

// Calcula o custo total de uma rota percorrendo todas as cidades na ordem especificada.
// Se houver uma cidade sem conexão válida, retorna um valor infinito.
int calculateRouteCost(const std::vector<std::string>& route, const Graph& graph) {
    int cost = 0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        const auto& from = route[i];
        const auto& to = route[i + 1];
        if (graph.count(from) > 0 && graph.at(from).count(to) > 0) {
            cost += graph.at(from).at(to);
        } else {
            return std::numeric_limits<int>::max();
        }
    }
    const auto& last = route.back();
    const auto& first = route[0];
    if (graph.count(last) > 0 && graph.at(last).count(first) > 0) {
        cost += graph.at(last).at(first);
    } else {
        return std::numeric_limits<int>::max();
    }
    return cost;
}