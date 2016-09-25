// Рассмотрим подробнее контейнер std::unordered_map, основанный на хеш-таблице.
// Пользоваться им можно точно так же, как и std::map.
// 
// Отличия от std::map такие:
// 1. Средняя сложность операций равна O(1), если хеш-функция достаточно хороша.
// 2. Для ключей не требуется operator <.
//
// Однако, в отличие от std::map, элементы такого контейнера уже не получится перебрать в отсортированном порядке.

// Решим типовую задачу про подсчет слов двумя способами.


#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

//using Container = map<string, int>;
using Container = unordered_map<string, int>;

using Item = pair<string, int>;

int main() {
    Container freqs;

    string word;
    while (cin >> word)
        ++freqs[word];

    vector<Item> items(freqs.begin(), freqs.end());

    sort(
        items.begin(),
        items.end(),
        [](const Item& a, const Item& b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        }
    );

    for (const auto& item : items)
        cout << item.first << "\t" << item.second << "\n";
}


// Скомпилируем обе версии программы (с map и unordered_map) и с помощью консольной утилиты time
// измерим время работы на достаточно большом тексте.
// У меня на тексте объёмом 4 Мb получилось, что unordered_map почти в 2 раза быстрее.
// Так как мы потом всё равно переупорядочиваем элементы, то, конечно, в этой задаче выгоднее использовать unordered_map.

// Качество работы unordered_map определяется выбранной хеш-функцией.
// По умолчанию хеш-функция определена для встроенных типов и стандартных контейнеров,
// таких как string, vector, и т. д.
// Подробнее см. http://en.cppreference.com/w/cpp/utility/hash

// Впрочем, хеш-функцию мы можем написать самостоятельно:
#include <string>
#include <unordered_map>

using namespace std;

struct MyHash {
    size_t operator()(const string&) const {
        return 0; // самая бесполезная хеш-функция - хеш каждого элемента одинаковый
        // упражнение: напишите свою версию полиномиального хеша для строк
    }
};

int main() {
    unordered_map<string, int, MyHash> freqs;
    
    string word;
    while (cin >> word) {
        ++freqs[word];
    }
}


// Аналогично, для контейнера map можно определить класс, который будет сравнивать элементы
// вместо обычного оператора <:

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person {
    string Name;
    string Surname;
};

struct Comparator {
    bool operator() (const Person& a, const Person& b) const {
        return a.Surname < b.Surname
            || a.Surname == b.Surname && a.Name < b.Name;
    }
};

int main() {
    map<Person, int, Comparator> my_map;

    vector<Person> v;
    // ...
    sort(v.begin(), v.end(), Comparator());
}

// И в MyHash, и в Comparator переопределяется оператор вызова функции (круглые скобки).
// Это позволяет использовать объект такого типа просто как функцию.
// Объекты такого типа (которые могут притвориться функцией) называют ещё функторами
// (хотя это не имеет ничего общего с теорией категорий в математике).


// Теперь перейдём к изучению алгоритмов стандартной библиотеки
// Все они написаны в шаблонном виде, то есть, могут работать с любыми контейнерами,
// предоставляющими соответствующие итераторы.
// Простейший из них - это std::copy.
// Эта функция просто копирует последовательность элементов, заданную парой итераторов, в другое место.

// Например, копирование элементов из unordered_map в vector могло быть сделано так:

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    unordered_map<string, int> freqs;
    
    string word;
    while (cin >> word)
        ++freqs[word];

    using Item = pair<string, int>;
    vector<Item> items;
    items.resize(freqs.size());  // в контейнере должно быть достаточно места, чтобы всё поместилось

    copy(
        freqs.begin(),  // начало копируемого участка 
        freqs.end(),  // конец копируемого участка (не включается)
        items.begin(),  // начало участка, куда надо копировать
    );

}


// Напишем свои версии этого алгоритма, чтобы разобраться, как он устроен

// Первая версия
template <
    typename InputIterator,
    typename OutputIterator
>
OutputIterator Copy_If(
    InputIterator first,
    InputIterator last,
    OutputIterator out
) {
    for (; first != last; ++first) {
        *out = *first;
        ++out;
    }
    return out;  // функция должна вернуть выходной итератор, указывающий за последний скопированный элемент
}

// Вторая версия
template <typename InputIterator, typename OutputIterator>
OutputIterator Copy2(
    InputIterator first,
    InputIterator last,
    OutputIterator out
) {
    while (first != last)
        *out++ = *first++;
    return out;
}


// Другая разновидность этого алгоритма - copy_if.
// Эта функция дополнительно получает на вход предикат
// и копирует элемент, только если этот предикат для него вернул истину.

// Например, вот так можно скопировать только те пары (слово, частота), у которых частота больше единицы:

int main() {
    unordered_map<string, int> freqs;
    
    string word;
    while (cin >> word)
        ++freqs[word];

    using Item = pair<string, int>;
    vector<Item> items;
    items.resize(freqs.size());

    auto last = copy_if(
        freqs.begin(),
        freqs.end(),
        items.begin(),
        [](const Item& a) {
            return a.second > 1;
        }
    );

    // удаляем из вектора оставшиеся пустые элементы, в которые ничего не скопировалось
    items.erase(last, items.end());
}

// Вот как могла быть написана copy_if:
template <typename InputIterator, typename OutputIterator>
OutputIterator Copy2(
    InputIterator first,
    InputIterator last,
    OutputIterator out,
    Predicate f
) {
    while (first != last)
        if (f(*first))
            *out++ = *first;
        ++first;
    return out;
}

