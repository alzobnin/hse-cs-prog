// Сегодня мы продолжим знакомиться с шаблоном std::vector ("умным" динамическим массивом)

// Рассмотрим задачу: дано N чисел, надо их считать и вывести в обратном порядке

// Сначала - "наивное" решение

#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n; // количество чисел
    
    std::vector<int> v;

    int x;
    for (size_t i = 0; i != n; ++i) { // используем тип size_t для индексов и размеров контейнеров
         std::cin >> x;
         v.push_back(x); // добавляем элемент в конец вектора, он при этом динамически растет
    }

    for (int i = n - 1; i >= 0; --i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

// тип size_t - это псевдоним для беззнакового целого типа (занимающего, как правило, 4 или 8 байт в зависимости от битности платформы),
// который следует использовать для индексов или размеров контейнеров


// Обратите внимание, что если бы мы во втором цикле написали бы size_t, то произошла бы неожиданная ошибка

#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> v;

    int x;
    for (size_t i = 0; i != n; ++i) {
         std::cin >> x;
         v.push_back(x);
    }

    for (size_t i = n - 1; i >= 0; --i) { // Опасно!
    // В последний момент, когда от нулевого i будет вычитаться единица, i станет очень большим числом (так как size_t беззнаковый)
    // Программа начнет вести себя неопределенно
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

// Лучше было бы написать последний цикл как-то так:

for (size_t i = 0; i != v.size(); ++i) {
    std::cout << v[v.size() - i - 1] << " ";
}


// Заметим, что нам известно заранее количество элементов.
// Поэтому можно было бы сразу зарезервировать необходимое количество ячеек памяти в векторе.
// Иначе у нас при добавлении новых элементов могут происходить реаллокации:
// когда зарезервированная память исчерпывается, то вектор запрашивает больший кусок памяти и копирует туда старое содержимое


#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n; // количество чисел
    
    std::vector<int> v;
    v.reserve(n); // зарезервировали память под n целых чисел (но размер вектора пока все равно нулевой)
    // зарезервированная память пока никак не проинициализирована, обращаться к ней некорректно

    int x;
    for (size_t i = 0; i != n; ++i) {
         std::cin >> x;
         v.push_back(x); // добавляем элементы как обычно
    }
}


// А можно было бы сделать еще и так:

#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n; // количество чисел
    
    std::vector<int> v(n); // сразу инициализируем память под n целых чисел
    // размер вектора будет равен n, память будет заполнена нулями

    for (size_t i = 0; i != n; ++i) {
         std::cin >> v[i];
    }
}

// Если бы вместо int тут оказался бы более сложный тип, то делать так было расточительно:
// инициализация элементов значениями по умолчанию могла бы оказаться достаточно дорогой.



// Объем зарезервированной и реально занятой памяти в векторе можно узнать с помощью функций capacity() и size().
// Изменить их, соотвественно, можно с помощью reserve и resize.

#include <vector>
#include <iostream>

int main() {
   std::vector<int> v = {1, 2, 3, 4, 5};
   std::cout << v.size() << "\n"; // напечатает 5
   std::cout << v.capacity() << "\n"; // зависит от реализации, но скорее всего, напечатает 8

   // попробуем подобавлять еще элементы и проследить, как меняется занятый и зарезервированный размер
   for (int i = 6; i != 10; ++i) {
       v.push_back(i);
       std::cout << "size: " << v.size() << "\n";
       std::cout << "capacity: " << v.capacity() << "\n";
   }
}

// Одна из стратегий - резервировать размер вдвое большего размера, чем нужно, когда зарезервированная память исчерпывается
// В среднем это приводит к тому, что добавление новых элементов в конец вектора требует константного времени
// Подробности вам расскажут на курсе алгоритмов в 3-м модуле


// Вопрос из зала про двумерные массивы

#include <iostream>
#include <vector>

int main() {
    size_t M, N;
    std::cin >> M >> N; // размеры матрицы
    std::vector<std::vector<int>> A(M); // сразу делаем вектор из M (пустых) строк

    for (size_t i = 0; i != M; ++i) {
        A[i].resize(N); // задаем размер каждой строки
        for (size_t j = 0; j != N; ++j)
           std::cin >> A[i][j];
    }

    // Предпочтительный способ вывода матрицы: перебираем элементы, а не индексы
    for (const auto& row : A) { // можно было бы написать имя типа std::vector<int>, но зачем?
        for (const auto& elem : row) { // про константные ссылки будет рассказано подробнее в следующий раз
            std::cout << elem << "\t";
        }
        std::cout << "\n";
    }

    // "Традиционный" способ вывода с перебором индексов
    for (size_t i = 0; i != M; ++i) {
        for (size_t j = 0; j != N; ++j)
            std::cout << A[i][j] << "\t";
        std::cout << "\n";
    }

}


// Сортировка вектора


#include <vector>
#include <iostream>
#include <algorithm> // в этом заголовочном файле находится функция sort

int main() {
    size_t N;
    std::cin >> N;
    std::vector<double> v;

    double x;
    for (size_t i = 0; i != N; ++i) {
        std::cin >> x;
        v.push_back(x);
    }

    std::sort(v.begin(), v.end()); // передаем в функцию sort пару итераторов, ограничивающих полуинтервал обрабатываемого участка

    for (double elem : w) {
        std::cout << std::fixed << elem << " ";
    }
    std::cout << "\n";
}

// Если надо отсортировать по убыванию, то можно было бы написать так:

std::sort(v.rbegin(), v.rend());

// Обратите внимание, что сортировка будет работать только с контейнерами, предоставляющими произвольный доступ к элементам по индексу.
// Например, двусвязный список (std::list) - не такой.
