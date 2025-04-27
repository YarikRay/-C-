#ifndef PatternTemplatesH
#define PatternTemplatesH
#include <vector>

using namespace std;

const int max_size = 100; // определим размер массива

// Демонстрация паттерна "Итератор"
template <typename T>
class Iterator
{
protected:
    Iterator() {}
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool isDone() const = 0;
    virtual T GetCurrent() const = 0;
};

// Реализуем общий класс с функцией GetIterator
template <typename T>
class Get_Iterator
{
public:
    virtual class Iterator<T> *GetIterator() = 0; // создаем указатель на базовый класс Iterator
};


// Реализация "Итератора" для обхода массива
template <typename T>
class ArrayIterator:public Iterator<T>
{
private:
    const T *ArrayContainer; // указатель на массив
    int pos; // текущая позиция
    size_t Size;
public:
    ArrayIterator(T *container, size_t Size) : ArrayContainer(container), pos(0), Size(Size) {}

    // Переопределяем методы из базового класса
    void First() override { pos = 0; }
    void Next() override { pos++; }
    bool isDone() const override { return (pos >= Size); }
    T GetCurrent() const override { return ArrayContainer[pos]; }
};

// Шаблонный класс "Массив". В него будем класть тетради
template <typename T>
class ArrayClass : public Get_Iterator<T>
{
private:

    T Books[max_size];
    int array_size = 0;

public:

    // Возвращаем элемент
    T get_elem (size_t index) const { return Books[index]; }

    // Добавляем элемент
    void Add(T n_el) { Books[array_size++] = n_el; }

    // Вывод индексов массива на экран
    void print() { for(int i = 0; i < array_size; i++) { cout << i << endl; } }

    int am_el() const { return array_size; }

    // Переопределим метод Iterator из базового класса Get_Iterator
    class Iterator<T> *GetIterator() override { return new ArrayIterator<T>(Books, array_size); }; // в данном случае не надо передавать итератору
    // адрес откуда брать элементы, т.к. имя массива уже является указателем на первый элемент массива
};


// Реализация "Итератора" для обхода вектора
template <typename T>
class VectorIterator : public Iterator<T>
{
private:
    const T *VecContainer; // указатель на вектор
    int pos;
    size_t Size;
public:
    VectorIterator(T *container, size_t Size) : VecContainer(container), pos(0), Size(Size) {}

    // Переопределяем методы из базового класса
    void First() override { pos = 0; }
    void Next() override { pos++; }
    bool isDone() const override { return (pos >= Size); }
    T GetCurrent() const override { return VecContainer[pos]; }
};

// Шаблонный класс "Вектор". Тоже будем класть в него книги. Интерфейс изменим
template <typename T>
class VecClass : public Get_Iterator<T>
{
private:
    vector<T> Ex_books;
    size_t vec_size = 0;
public:

    // Возвращаем количество элементов
    int return_amount_el() const { return Ex_books.size(); }

    // Проверка того, является ли вектор пустым
    bool isEmpty() const { int count_1 = 0; for(auto x: Ex_books) { count_1 += 1; } if(count_1 == 0) { return true; } else { return false; } }

    // Добавление элемента
    void Push(T new_el) { Ex_books.push_back(new_el); vec_size = Ex_books.size(); }

    // Возвращаем элемент
    T get_elem (size_t index) const { return Ex_books[index]; }

    class Iterator<T> *GetIterator() override { return new VectorIterator<T>(&Ex_books[0], vec_size); };  // в данной строчке кода передаем адрес
        // на первый элемент ветора, т.е указываем место итератору откуда брать элементы
};

// Паттерн "Декоратор"
template<typename T>
class Decorator : public Iterator<T>
{
protected:
    Iterator<T> *It; // создали указатель на базовый класс Iterator
public:
    Decorator(Iterator<T> *it) : It(it) {} // конструктор, в аргумент которого будет передаваться указатель на базовый класс Iterator.
    // Теперь It и it указывают на один и тот же базовый класс Iterator
    virtual ~Decorator() { delete It; }
    virtual void First() { It->First(); } // наследуем метод First из класса Iterator
    virtual void Next() { It->Next(); } // наследуем метод Next из класса Iterator
    virtual bool isDone() const { return It->isDone(); } // наследуем метод isDone из класса Iterator
    virtual T GetCurrent() const { return It->GetCurrent(); } // наследуем метод GetCurrent() из класса Iterator
};

// Паттерн "Адаптер"
template<typename ContainerType, typename ItemType> // шиблон. Благодарая ему можно будет подставлять любые типы контейнеров и типы данных
class Adapter : public Iterator<ItemType>
{
protected:
    ContainerType* container; // указатель на контейнер
    typename ContainerType::const_iterator It; //
public:
    Adapter(ContainerType* Container) : container(Container) { It = Container->begin(); }

    virtual ~Adapter() {};
    virtual void First() { It = container->begin(); }
    virtual void Next() { It++; }
    virtual bool isDone() const { return (It == container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};

#endif
