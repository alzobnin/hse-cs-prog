// Поговорим поподробнее про конструкторы и деструкторы класса.
// Напишем класс, в конструкторах и деструкторе которого будет просто печататься сообщение на экран:

#include <iostream>
#include <vector>

class C {
    static int counter;  // статическое поле - оно общее для всех объектов
    // считайте, что статическая переменная (или функция) просто помещена в класс как в пространство имён
    int number;  // будем нумеровать каждый вновь создаваемый объект, чтобы не запутаться
public:
    // при создании очередного объекта увеличиваем счётчик counter
    C(): number(counter++) {  // конструктор "по умолчанию" (то есть, без аргументов)
        std::cout << "Default constructor for " << number << "\n";
    }

    C(int a): number(counter++) {
        std::cout << "C(" << a << ") for " << number << "\n";
    }

    C(int a, int b, int c): number(counter++) {
        std::cout << "C(" << a << ", " << b << ", " << c << ") for " << number << "\n";
    }

    C(const C& other): number(other.number) {  // конструктор копирования
        std::cout << "Copy constructor\n";
    }

    C(C&& other): number(other.number) {  // конструктор перемещения - про move-семантику я расскажу на последней лекции
        std::cout << "Move constructor\n";
    }

    C& operator = (const C& b) {  // оператор присваивания
        number = b.number;
        std::cout << "operator = for " << number << "\n";
        return *this;
    }

    ~C() {  // деструктор
        std::cout << "Destructor for " << number << "\n";
    }
};

int C::counter = 0;  // статические переменные необходимо инициализировать вот так

int main() {
    std::vector<C> v;

    std::cout << "Before the first push_back\n";
    v.push_back(C(1));
    
    std::cout << "Before the second push_back\n";
    v.push_back(C(2));

    std::cout << "Before the end\n";
}

// Реализации вектора могут отличаться на разных платформах и для разных компиляторов,
// но, скорее всего, мы получим что-то такое:

Before the first push_back
C(1) for 0  // создаём временный объект (см. строку 50)
Move constructor  // перемещаем его в вектор
Destructor for 0  // удаляем временный объект
Before the second push_back
C(2) for 1  // создаём второй временный объект
Move constructor  // но нужно сделать реаллокацию! Перемещаем временный объект на новое место
Copy constructor  // и копируем на новое место предыдущий объект (не перемещаем, потому что в случае ошибки надо будет откатиться назад)
Destructor for 0  // удаляем первый объект со старого места
Destructor for 1  // удаляем временный объект
Before the end
Destructor for 0  // конец блока (строка 56): в деструкторе вектора вызываются деструкторы всех его элементов
Destructor for 1


// ===========================

// Ещё мне часто задают вопрос про связь функции-члена класса с внешними функциями,
// и про реализацию функций внутри или снаружи класса.
// Попробую прояснить.

class C {
private:
    double alpha, beta;
public:
    void foo(int x) const;  // декларация функции-члена класса, её тело будет определено позже

    void foo(int x) {  // перегруженная по константности функция-член класса с тем же именем
        // её тело определено прямо здесь
    }
};


void C::foo(int x) const {  // определение функции-члена класса, которое мы отложили
    // вне класса имена его функций, полей и т. д. нужно писать с префиксом C::
    // Все эти функции неявно получают на вход указатель this на текущий объект (который стоял слева от записи их вызова)
}

void foo(const C& reference, int x) {  // а это вообще внешняя функция, никак с классом не связанная
    // хотя она и принимает в качестве первого аргумента const C&.
    // Такая функция (если только она не задекларирована в классе как friend), имеет доступ только к публичным полям объектов типа C.
}

int main() {
    C c;
    c.foo(42);  // вызываем функцию-член класса void C::foo(int) const
    foo(c, 42);  // вызываем внешнюю (обычную) функцию
}


// ===========================

// Теперь вернёмся к классу "Матрица" с прошлого занятия
// и напишем для матрицы итератор, который бы перебирал её элементы построчно.

#include <iostream>
#include <vector>

using std::vector;

template <typename T, int N>
class Matrix;

template <typename T, int N>
class RowIterator {
 private:
    // Нам нужно знать саму матрицу, с которой мы работаем (и даже иметь возможность её изменять)
    // Просто поле типа Matrix<T, N> не годится: оно тяжёлое, да и это будет просто копия исходной матрицы.
    // Можно использовать указатель или ссылку
    // Но ссылки нельзя перепривязывать к другим объектам, то есть, такие итераторы нельзя будет присваивать друг другу
    Matrix<T, N>* matrix;  // поэтому выберем указатель
    size_t row, column;
 public:
    // Значения параметров по умолчанию соответствуют последней позиции (итератору end()):
    RowIterator(Matrix<T, N>* _matrix, size_t _row = N, size_t _column = 0)
    : matrix(_matrix)
    , row(_row)
    , column(_column)
    {
    }

    const T& operator * () const {
        return (*matrix)(row, column);
    }
    
    RowIterator& operator++() {  // префиксный ++
        ++column;
        if (column == N) {
            column = 0;
            ++row;
        }
        return *this;
    }

    RowIterator operator++(int) {  // А это - постфиксный ++. Формально он получает на вход аргумент типа int
        auto temp = *this;
        ++*this;
        return temp;  // Мы здесь хотим реализовать стандартную семантику префиксного ++.
        // Поэтому он возвращает копию старого значения, но никак не ссылку на что бы то ни было.
        // (Ссылка на локальную переменную temp тут же бы стала невалидной после выхода из функции.)
    }

    bool operator == (RowIterator other) const {
        return row == other.row && column == other.column;
    }

    bool operator != (RowIterator other) const {
        return !(*this == other);
    }
};

// В самом классе Matrix напишем функции begin и end:
template <typename T, int N>
class Matrix {
 public:
    // ...

    RowIterator<T, N> begin() {
        return RowIterator<T, N>(this, 0, 0);
    }

    RowIterator<T, N> end() {
        return RowIterator<T, N>(this);
    }
};


int main() {
    Matrix<int, 5> A(7);

    // Теперь у нас заработает вот такой код:
    for (auto x : A)
        std::cout << x << " ";
    std::cout << "\n";
}


// ===========================

// Последний сюжет на сегодня - "итератор", возвращаемый функцией std::back_inserter
// Этой функции можно передать контейнер, обладающий функцией push_back,
// и при попытке записи этот "итератор" будет вставлять элементы в контейнер:

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v;

    // Копируем целые числа из стандартного потока ввода в изначально пустой вектор:
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),
        std::back_insert_iterator<std::vector<int>>(v)
    );

    for (auto x : v)
        std::cout << x << "\n";
}

// Попробуем написать такую штуку самостоятельно.

namespace mystd {

// Вспомним свою версию copy на всякий случай:
template <typename In, typename Out>
Out copy(In first, In last, Out out) {
    while (first != last) {
        *out++ = *first++;
    }
    return out;
}

// Вот класс нашего "итератора":
template <typename Container>
class back_insert_iterator {
 private:
     Container& container;  // "итератор" знает про свой контейнер

 public:
     back_insert_iterator(Container& _container)  // обратите внимание: ссылка может быть проинициализирована только в конструкторе
     : container(_container)
     {
     }

     // Неожиданная вещь: реализуем все эти операции тривиально
     back_insert_iterator& operator * () {  // обратите внимание: звёздочка возвращает себя, чтобы мы могли перехватить присваивание!
         return *this;
     }
     back_insert_iterator& operator ++ () {
         return *this;
     }
     back_insert_iterator& operator ++ (int) {
         return *this;
     }

     template <typename T>
     void operator = (const T& other) {
          container.push_back(other);  // а вот тут-то мы и положим элемент в контейнер!
     }
};

} // end of mystd namespace

