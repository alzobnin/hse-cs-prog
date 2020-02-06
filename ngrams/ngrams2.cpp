#include <iostream>
#include <map>
#include <array>
#include <random>
#include <string>

using namespace std;

int main(int argc, char * argv[]) {
    int n = atoi(argv[1]);

    map<string, array<int, 256>> freqs;
    char c;
    string context;
    while (cin.get(c)) {
        if (context.size() == n)
            ++freqs[context][static_cast<unsigned char>(c)];
        context.push_back(c);
        if (context.size() > n)
            context.erase(context.begin());
    }

    context = "To be, or not to be";
    if (context.size() < n)
        context.resize(n, ' ');
    cout << context;
    context = context.substr(context.size() - n);

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
