#include "../../include/utils/PermutationUtils.h"

// Inverte a ordem dos elementos em um vetor dentro do intervalo [start, end].
void reverseVector(std::vector<std::string>& vec, int start, int end) {
    while (start < end) {
        std::swap(vec[start], vec[end]);
        start++;
        end--;
    }
}

//Gera a próxima permutação lexicográfica do vetor dado, se existir.
//Se já estiver na última permutação, retorna falso.
bool nextPermutation(std::vector<std::string>& route) {
    int i = static_cast<int>(route.size()) - 2;
    while (i >= 0 && route[i] >= route[i + 1]) i--;
    if (i < 0) return false;
    int j = static_cast<int>(route.size()) - 1;
    while (route[j] <= route[i]) j--;
    std::swap(route[i], route[j]);

    reverseVector(route, i + 1, static_cast<int>(route.size()) - 1);

    return true;
}