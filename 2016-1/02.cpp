// В прошлый раз мы не успели рассмотреть оператор goto.
// Оператор безусловного перехода goto - ругательное слово из четырех букв.
// Он затрудняет чтение кода. Любую программу можно переписать без него.
// Почему же его оставили в C++? Какие были причины кроме обратной совместимости?
// Оказывается он очень удобен, например, в автоматически генерируемых программах
// (реализующих, скажем, конечный автомат)

#include <iostream>

using namespace std;

int main() {
    cout << "Input a positive value\n";
    int n;
    start:  // метка
    cin >> n;
    if (n <= 0)
        goto start;
    cout << "The value is " << n << "\n";
}

// Лучше переписать эту программу с помощью цикла с постусловием:

#include <iostream>

using namespace std;

int main() {
    cout << "Input a positive value\n";
    int n;
    do {
        cin >> n;
    } while (n <= 0);
    cout << "The value is " << n << "\n";
}


// ---------------------

// Сегодня мы познакомимся с векторами ("умными" динамическими массивами)

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};  // вектор из пяти элементов

    for (size_t i = 0; i != v.size(); ++i)  // используем специальный тип size_t для индексации
        cout << v[i] << " ";  // переберём и напечатаем эти элементы
    cout << "\n";
}

// Тип size_t - псевдоним для беззнакового целого типа (занимающего, как правило, 4 или 8 байт в зависимости от битности платформы),
// который следует использовать для индексов или размеров контейнеров

// Вывести элементы можно было бы ещё и так:

for (auto elem : v)  // автоматически выводим тип элемента (int)
    cout << elem << " ";


// Рассмотрим задачу: дано N чисел, надо их считать и вывести в обратном порядке

// Сначала - "наивное" решение

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;  // количество чисел
    
    vector<int> v;

    for (size_t i = 0; i != n; ++i) {
         int x;
         cin >> x;
         v.push_back(x); // добавляем элемент в конец вектора, он при этом динамически растет
    }

    for (int i = n - 1; i >= 0; --i) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

// Обратите внимание, что если бы мы во втором цикле написали бы size_t, то произошла бы неожиданная ошибка:
for (size_t i = n - 1; i >= 0; --i) { // Опасно!
    // В последний момент, когда от нулевого i будет вычитаться единица, i станет очень большим числом (так как size_t беззнаковый)
    // Программа начнёт вести себя неопределенно
    cout << v[i] << " ";
}


// Лучше было бы написать последний цикл как-то так:

for (size_t i = 0; i != v.size(); ++i) {
    cout << v[v.size() - i - 1] << " ";
}


// Заметим, что нам известно заранее количество элементов.
// Поэтому можно было бы сразу зарезервировать необходимое количество ячеек памяти в векторе.
// Иначе у нас при добавлении новых элементов могут происходить реаллокации:
// когда зарезервированная память исчерпывается, то вектор запрашивает больший кусок памяти и копирует туда старое содержимое


#include <iostream>
#include <vector>

int main() {
    int n;
    cin >> n; // количество чисел
    
    vector<int> v;
    v.reserve(n); // зарезервировали память под n целых чисел (но размер вектора пока все равно нулевой)
    // зарезервированная память пока никак не проинициализирована, обращаться к ней некорректно

    int x;
    for (size_t i = 0; i != n; ++i) {
         cin >> x;
         v.push_back(x); // добавляем элементы как обычно
    }
}


// А можно было бы сделать еще и так:

#include <iostream>
#include <vector>

int main() {
    int n;
    cin >> n; // количество чисел
    
    vector<int> v(n); // сразу инициализируем память под n целых чисел
    // размер вектора будет равен n, память будет заполнена нулями

    for (size_t i = 0; i != n; ++i) {
         cin >> v[i];
    }
}

// Если бы вместо int тут оказался бы более сложный тип, то делать так было расточительно:
// инициализация элементов значениями по умолчанию могла бы оказаться достаточно дорогой.



// Объём зарезервированной и реально занятой памяти в векторе можно узнать с помощью функций capacity() и size().
// Изменить их, соотвественно, можно с помощью reserve и resize.

#include <iostream>
#include <vector>

using namespace std;

int main() {
   vector<int> v = {1, 2, 3, 4, 5};
   cout << v.size() << "\n";  // напечатает 5
   cout << v.capacity() << "\n";  // зависит от реализации, но скорее всего, напечатает 8

   // попробуем подобавлять еще элементы и проследить, как меняется занятый и зарезервированный размер
   for (int i = 6; i != 10; ++i) {
       v.push_back(i);
       cout << "size: " << v.size() << "\n";
       cout << "capacity: " << v.capacity() << "\n";
   }
}

// Одна из стратегий - резервировать размер вдвое большего размера, чем нужно, когда зарезервированная память исчерпывается
// В среднем это приводит к тому, что добавление новых элементов в конец вектора требует константного времени
// Подробности вам расскажут на курсе алгоритмов в 3-м модуле


// ---------------

// Сортировка вектора

#include <algorithm> // в этом заголовочном файле находится функция sort
#include <iostream>
#include <vector>

int main() {
    size_t n;
    cin >> n;
    vector<int> v;

    int x;
    for (size_t i = 0; i != n; ++i) {
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end()); // передаем в функцию sort пару итераторов, ограничивающих полуинтервал обрабатываемого участка

    for (int elem : w) {
        cout << fixed << elem << " ";
    }
    cout << "\n";
}

// Если надо отсортировать по убыванию, то можно было бы написать так:

sort(v.rbegin(), v.rend());

// Обратите внимание, что сортировка будет работать только с контейнерами, предоставляющими произвольный доступ к элементам по индексу.
// Например, двусвязный список (list) - не такой.


// Если требуется особая сортировка, то можно написать свою функцию сравнения элементов (аналог оператора "меньше")
// Например, можно было бы сортировать вектор по убыванию вот так:

bool my_greater(int a, int b) {
    if (a > b)
        return true;
    else
        return false;
}

// Впрочем, никогда так не пишите, потому что то же самое можно записать так:

bool my_greater(int a, int b) {
    return a > b;
}

// Используем эту функцию так:

sort(v.begin(), v.end(), my_greater);


// Иногда удобно не выносить такую функцию отдельно, а определять её прямо в месте использования.
// Получится лямбда-функция:
sort(
    v.begin(),
    v.end(),
    [](int a, int b) { return a > b; }  // определяем лябда-функцию прямо в месте вызова
);

// Подробнее про лямбды мы поговорим позже.

// Наконец, вот ещё один (канонический) способ упорядочить вектор по убыванию:
sort(v.begin(), v.end(), greater<int>());  // передаём объект стандартного класса std::greater<int>, который умеет сравнивать пару элементов с помощью >



// -------------

// Разберёмся с двумерными массивами

#include <iostream>
#include <vector>

using namespace std;

int main() {
    size_t m, n;
    cin >> m >> n; // размеры матрицы
    vector<vector<int>> A(m); // сразу делаем вектор из m (пустых) строк

    for (size_t i = 0; i != m; ++i) {
        A[i].resize(n); // задаем размер каждой строки
        for (size_t j = 0; j != n; ++j)
           cin >> A[i][j];
    }

    // Предпочтительный способ вывода матрицы: перебираем элементы, а не индексы
    for (const auto& row : A) { // можно было бы написать имя типа vector<int>, но зачем?
        for (const auto& elem : row) { // про константные ссылки будет рассказано подробнее в следующий раз
            cout << elem << "\t";
        }
        cout << "\n";
    }

    // "Традиционный" способ вывода с перебором индексов
    for (size_t i = 0; i != m; ++i) {
        for (size_t j = 0; j != n; ++j)
            cout << A[i][j] << "\t";
        cout << "\n";
    }

}


// --------------

// Обратите внимание, что оператор [] у вектора никак не проверяет корректность индексов.
// Если вы обратитесь к вектору по некорректному индексу, то программа попадёт в неопределённое поведение.
// Вы должны сами следить за тем, чтобы индекс был корректным.

// Если вам не хочется делать много лишних проверок, то можно использовать функцию at:
vector<int> v = {1, 2, 3};
cout << v.at(100500);  // произойдёт исключение - его можно будет перехватить и обработать

