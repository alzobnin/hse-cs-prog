#include <iostream>
#include <string>

void append(std::string& res, char c) {
    if (res.back() != c)
        res.push_back(c);
}

std::string soundex(const std::string& word) {
    std::string res;
    res.push_back(word[0]);
    for (size_t i = 1; i != word.size(); ++i) {
        char c = word[i];
        switch (c) {
        case 'b':
        case 'f':
        case 'p':
        case 'v':
            append(res, '1');
            break;
        case 'c':
        case 'g':
        case 'j':
        case 'k':
        case 'q':
        case 's':
        case 'x':
        case 'z':
            append(res, '2');
            break;
        case 'd':
        case 't':
            append(res, '3');
            break;
        case 'l':
            append(res, '4');
            break;
        case 'm':
        case 'n':
            append(res, '5');
            break;
        case 'r':
            append(res, '6');
            break;
        }
    }
    while (res.size() < 4)
        res.push_back('0');
    res.resize(4);
    return res;
}

int main() {
    std::string word;
    std::cin >> word;
    std::cout << soundex(word) << "\n";
}

