#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {
    int n = atoi(argv[1]);

    map<string, vector<int>> freqs;
    char c;
    string context;
    while (cin.get(c)) {
        if (context.size() == n) {
            if (freqs.find(context) == freqs.end())
                freqs[context].resize(256);
            ++freqs[context][static_cast<unsigned char>(c)];
        }
        context.push_back(c);
        if (context.size() > n)
            context.erase(context.begin());
    }

    context = "Россия";
    context.resize(n);
    cout << context;

    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i != 1000; ++i) {
        const auto& context_freqs = freqs[context];
        discrete_distribution<> distr(context_freqs.begin(), context_freqs.end());
        char c = distr(gen);
        cout.put(c);
        context.push_back(c);
        context.erase(context.begin());
    }
    cout << "\n";
}
