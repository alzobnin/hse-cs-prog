#include <iostream>
#include <string>
#include <vector>

bool conform(const std::string& evidence, const std::string& plate) {
    for (char c : evidence)
        if (plate.find(c) == std::string::npos)
            return false;
    return true;
}

int main() {
    int N;
    std::cin >> N;
    std::vector<std::string> evidences(N);
    for (auto& evidence : evidences)
        std::cin >> evidence;

    int M;
    std::cin >> M;
    int max_rank = 0;
    std::vector<std::string> plates(M);
    std::vector<int> ranks(M);
    for (size_t i = 0; i != M; ++i) {
        std::cin >> plates[i];
        for (const auto& evidence : evidences)
            if (conform(evidence, plates[i]))
                ++ranks[i];
        if (ranks[i] > max_rank)
            max_rank = ranks[i];
    }

    for (size_t i = 0; i != M; ++i)
        if (ranks[i] == max_rank)
            std::cout << plates[i] << "\n";
}

