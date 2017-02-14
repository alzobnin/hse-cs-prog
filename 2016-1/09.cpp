// Размер каждого объекта, который он занимает на стеке локальных переменных,
// должен быть известен на этапе компиляции.

#include <iostream>
#include <string>
#include <vector>

class C {
public:
     int x;
     double y;
     std::string z;
     const char * ptr;
};

// Каким будет sizeof(C)?
// Этот размер складывается из размеров отдельных полей.
// А ещё учитывается выравнивание: компилятор старается расположить поля в памяти так,
// чтобы адреса больших объектов были кратны машинному слову (4 или 8 байтам).

int main() {
    std::cout << sizeof(int) << "\n";  // у меня - 4
    std::cout << sizeof(double) << "\n";  // 8
    std::cout << sizeof(std::string) << "\n";  // 8
    std::cout << sizeof(const char *) << "\n";  // 8
    std::cout << sizeof(std::vector<int>) << "\n";  // 24 
    std::cout << sizeof(C) << "\n";  // 32
}

// Заметьте, sizeof(std::vector<int>), например, никак не зависит от числа элементов в векторе
// (и вообще известен и фиксирован на момент компиляции).
// Дело в том, что sizeof - это размер на стеке. Вектор содержит внутри три указателя.
// А сами элементы хранятся в выделенной динамической памяти (на начало которой один из этих указателей и указывает).


// ==============

// Изучим теперь наследование.
// Наследование - это способ организовывать иерархии классов.
// При этом класс-наследник приобретает (неприватные) поля, функции-члены и т. д. базового класса
// (быть может, модифицируя их область видимости).
// А с точки зрения памяти сначала в ней размещается подобъект базового класса, а затем уже - поля производного класса.

// Язык C++ - один из немногих языков с множественным наследованием.
// Множественное наследование считается сложным (и не всегда оправданным). Мы намеренно не будем здесь его рассматривать.

// Базовый класс:
class Base {
public:
    Base(int x) {
        // какой-то конструктор
    }
    int a;
    double b;
    void f() const {
    }
private:
    int z;
    void g() {
    }
};

// Производный класс
class Derived: public Base {  // public-наследование: все public-поля остаются public-полями в наследнике
public:
    Derived(double y)
    : Base(42)  // подобъект базового класса необходимо проинициализировать вызовом конструктора
    , a(y)  // и только потом инициализируются поля
    , b(0)
    , c(-1)
    {
    }
    float a;
    long b;
    void h() const {
    }
private:
    int c;
};

// А можно было бы организовать класс так:
class Derived2 {  // наследования нет
public:
    Base base;  // вместо базового класса просто поле типа base
    float a;
    long b;
    void h() const {
    }
    Derived2(): base(42) {}  // его мы тоже инициализируем, но как обычное поле
private:
    int c;
}; 
// Такая организация данных называется "композицией".
// (Есть рекомендация предпочитать композицию наследованию, но сегодня речь всё-таки о наследовании.)

void foo(const Base& b) {
}

int main() {
    Derived d1;
    Derived2 d2;

    d1.a;
    d1.Base::a;
 
    foo(d1);  // объект производного класса может быть автоматически преобразован к типу базового класса
    foo(d2.base);  // а вот во втором случае придётся везде явно писать имя поля .base.
}


// Написать базовый класс Figure
// вывести из него наследников Circle, Rectangle, Square, Triangle, ...
// Реализовать виртуальную функцию Draw
// Продемонстрировать работу с массивом указателей на Figure


// ==============

// Теперь напишем хрестоматийный пример - сделаем иерархию животных с базовым классом Animal

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Animal {
  public:
    Animal(const std::string& name)
    :name_(name) {
    }
    std::string voice() const {  // каждое животное будет по-своему подавать свой голос
        return "Default voice";
    }
    const std::string& name() const {
        return name_;
    }
  
  private:
    std::string name_;  // у животных есть имя
};

class Cat: public Animal {
  public:
    Cat(const std::string& name, int color)
    : Animal(name)
    , color_(color)
    {
    }

    std::string voice() const {
         return "Myau";
    }

  private:
    int color_;  // у кошки есть цвет
};

class Dog: public Animal {
  public:

    Dog(const std::string& name, int breed, int color)
    : Animal(name)
    , breed_(breed)
    , color_(color)
    {
    }

    std::string voice() const {
        return "Gav!";
    }

  private:
    int breed_;  // у собаки есть порода
    int color_;
};


// Общий оператор вывода в поток (работает с любым животным)
// (Конечно, такого же поведения здесь можно было бы достичь и просто с шаблонами.)
std::ostream& operator << (
    std::ostream& out,
    const Animal& animal) {
    return out << animal.name();
}

int main() {
    Cat c("Tom", 1);
    Dog d("Buffa", 2, 3);

    std::cout << c.voice() << "\n";  // Печатает "Myau"
    std::cout << d.voice() << "\n";  // Печатает "Gav!"


    // Но что если мы хотим сделать вектор животных?
    // Элементы вектора должны иметь один и тот же тип.
    // Если это будет просто Animal, то мы не сможем восстановить специфичные данные для кошки/собаки по таким элементам.
    // Ссылкой Animal& это тоже быть не может (ссылка должна быть проинициализирована сразу же).
    // Это может быть указатель!

    std::vector<Animal*> animals;
    animals.push_back(&c);
    animals.push_back(&d);
    // Положим пока для простоты в вектор адреса уже существующих объектов на стеке
    
    for (auto a : animals)
        std::cout << a->voice() << "\n";
    // Почему-то этот цикл печатает два раза "Default voice"!

    // Всё дело в том, что функция voice не была объявлена как виртуальная!
}


// Перепишем немного нашу иерархию классов (опуская подробности):
class Animal {
  public:
    Animal(const std::string& name) {
    }
    virtual std::string voice() const = 0 {  // функция объявлена чисто виртуальной: = 0 означает, что само по себе животное не может быть создано
        return "Default voice";
    }
    virtual ~Animal() {  // хорошо бы добавить ещё в класс виртуальный деструктор
    }
};

class Cat: public Animal {
  public:
    Cat(const std::string& name, int color): Animal(name) {
    }
    std::string voice() const override {  // переопределяем виртуальную функцию базового класса!
         return "Myau";
    }
};

class Dog: public Animal {
  public:
    Dog(const std::string& name, int breed, int color): Animal(name) {
    }
    std::string voice() const override {  // переопределяем виртуальную функцию базового класса!
        return "Gav!";
    }
};

int main() {
    Cat c("Tom", 1);
    Dog d("Buffa", 2, 3);

    std::vector<Animal*> animals;
    animals.push_back(&c);
    animals.push_back(&d);
    
    // Теперь такой код выводит правильные голоса:
    for (auto a : animals)
        std::cout << a->voice() << "\n";

    // Функция voice теперь виртуальная.
    // В подобъектах базового класса Animal компилятор заводит (и сам инициализирует) дополнительное поле:
    // указатель на таблицу с правильным набором функций для каждого объекта.
    // Для кошки этот указатель указывает на функцию Cat::voice, а для собаки - на Dog::voice.
    // Поэтому и получается вызвать правильную функцию даже при работе с указателем (ссылкой) на базовый класс.
}

