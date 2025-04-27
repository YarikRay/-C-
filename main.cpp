#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "template.h"

using namespace std;

// Перечисляемый тип способов написания
enum class WriteWay : int
{
    WriteAll,
    LetterByLetter,
    Sentences,
    None
};

enum class TypeOfBook : int
{
    squarebook,
    linebook,
    ringbook
};

enum class FormatOfBook : int
{
    A5,
    A4,
    A3
};

class WriteStrategy
{
public:
    virtual ~WriteStrategy() {}
    virtual void Write() = 0;
};

// Реализуем классы-наследники
class WriteAllStrategy : public WriteStrategy
{
    void Write() { cout << "Write all text..." << endl; }
};
class LetterByLetterStrategy : public WriteStrategy
{
    void Write() { cout << "Write smth letter by letter..." << endl; }
};
class SentencesStrategy : public WriteStrategy
{
    void Write() { cout << "Write smth by sentence..." << endl; }
};

// Реализуем паттерн Фабричный Метод
WriteStrategy* CreateWriteStrategy(WriteWay writeway)
{
    WriteStrategy* pwritestrategy = nullptr;
    if(writeway == WriteWay::LetterByLetter)
    {
        pwritestrategy = new LetterByLetterStrategy;
    }
    else if(writeway == WriteWay::Sentences)
    {
        pwritestrategy = new SentencesStrategy;
    }
    else if(writeway == WriteWay::WriteAll)
    {
        pwritestrategy = new WriteAllStrategy;
    }
    else { pwritestrategy = nullptr; }
    return pwritestrategy;
}

class ExerciseBook
{
private:
    TypeOfBook type;
    FormatOfBook format_book;

    WriteStrategy* pStrategy; // указатель на базовый класс с целью дальнейшего использования его интерфейса
    void DoWriteUsingStrategy()
    {
        if(pStrategy == nullptr)
        {
            cout << "No strategy was found";
            return;
        }
        else
        {
            pStrategy->Write();
        }
    }

public:

    int page = 0;
    string format = "A5";

    ExerciseBook(int x);

    ExerciseBook(TypeOfBook tbook, FormatOfBook fbook) : type(tbook), format_book(fbook), pStrategy(nullptr) {}
    //ExerciseBook(FormatOfBook fbook) : format_book(fbook) {}
    virtual ~ExerciseBook()
    {
        if(pStrategy != nullptr)
        {
            delete pStrategy;
        }
    };

    // Общие методы
    virtual int open_page(int page) { return page; }
    virtual string tell_format() { return format; }

    virtual void printype() = 0;
    int write_smth(int page) {

        printype();
        DoWriteUsingStrategy();
        return page; };

    TypeOfBook Get_Type() { return type; }
    FormatOfBook Get_Format() { return format_book; }
    bool Is_Open() { return true; }

    virtual void Open()
    {
        if(Is_Open())
        {
            cout << "Book is open" << endl;
        }
    }


    //Метод для тетради в клеточку
    virtual void get_squares() { cout << "Amount of squares: "; }
    //Метод для тетради в линейку
    virtual void get_lines() { cout << "Amount of lines: "; }
    //Метод для тетради в кольцах
    virtual void get_amount_pages() { cout << "Amount of pages: "; }

    void SetStrategy(WriteStrategy* pwritestrategy) { pStrategy = pwritestrategy; }
};

// Конструктор(параметризованный)
ExerciseBook::ExerciseBook(int x) : page(x)
{
}

class SquareBook : public ExerciseBook
{
public:
    int how_much_squares = 38; // сколько клеточек на одной странице

    SquareBook() : ExerciseBook(TypeOfBook::squarebook, FormatOfBook::A5)
    {
        SetStrategy(CreateWriteStrategy(WriteWay::WriteAll));
        cout << "SquareBook is open" << endl;
    };

    ~SquareBook();
    void printype() {cout << "That's a squarebook" << endl;}

    void get_squares() { ExerciseBook::get_squares(); cout << how_much_squares << endl; }
    int open_page(int page) { cout << "A squarebook is opened on page: " << ExerciseBook::open_page(page) << endl; return ExerciseBook::open_page(page); }
    int write_smth(int page) { cout << "Writing something on the page " << ExerciseBook::write_smth(page) << endl; return ExerciseBook::write_smth(page); }
    string tell_format() { cout << "The format is: " << ExerciseBook::tell_format() << endl; return ExerciseBook::tell_format(); }
    void Open() { ExerciseBook::Open(); }

};

// Деструктор класса SquareBook
SquareBook::~SquareBook() { cout << "Close the book with squares" << endl; }


class LineBook : public ExerciseBook
{
public:
    int how_much_lines = 12; // сколько линий на одной странице

    LineBook() : ExerciseBook(TypeOfBook::linebook, FormatOfBook::A5)
    {
        SetStrategy(CreateWriteStrategy(WriteWay::LetterByLetter));
        cout << "LineBook is open" << endl;
    }
    ~LineBook();

    void printype() {cout << "That's a linebook" << endl;}
    void get_lines() { ExerciseBook::get_lines(); cout << how_much_lines << endl; }
    int open_page(int page) { cout << "A linebook is opened on page: " << ExerciseBook::open_page(page) << endl; return ExerciseBook::open_page(page); }
    int write_smth(int page) { cout << "Writing something on the page " << ExerciseBook::write_smth(page) << endl; return ExerciseBook::write_smth(page); }
    string tell_format() { cout << "The format is: " << ExerciseBook::tell_format() << endl; return ExerciseBook::tell_format(); }
    void Open() { ExerciseBook::Open(); }
};

// Деструктор класса SquareBook
LineBook::~LineBook() { cout << "Close the book with lines" << endl; }

class RingBook : public ExerciseBook
{
public:
    int how_much_pages = 48; // сколько страниц в одной тетради

    RingBook():  ExerciseBook(TypeOfBook::ringbook, FormatOfBook::A5)
    {
        SetStrategy(CreateWriteStrategy(WriteWay::Sentences));
        cout << "RingBook is open" << endl;
    };
    //RingBook() : ExerciseBook(FormatOfBook::A5) {};

    ~RingBook();

    void printype() {cout << "That's a ringbook" << endl;}
    void get_amount_pages() { ExerciseBook::get_amount_pages(); cout << how_much_pages << endl; }
    int open_page(int page) { cout << "A ringbook is opened on page: " << ExerciseBook::open_page(page) << endl; return ExerciseBook::open_page(page); }
    int write_smth(int page) { cout << "Writing something on the page " << ExerciseBook::write_smth(page) << endl; return ExerciseBook::write_smth(page); }
    string tell_format() { cout << "The format is: " << ExerciseBook::tell_format() << endl; return ExerciseBook::tell_format(); }
    void Open() { ExerciseBook::Open(); }
};

// Деструктор класса SquareBook
RingBook::~RingBook() { cout << "Close the ringbook " << endl; }

// Класс декоратор для тетрадей конкретного типа
class Dec : public Decorator<ExerciseBook*>
{
private:
    TypeOfBook booktype;

public:
    Dec(Iterator<ExerciseBook*> *it, TypeOfBook type ) : Decorator<ExerciseBook*>(it), booktype(type) {};


    void First() // данный метод необходим для того, чтобы декоратор нашел первый подходящий элемент
    {
        It->First(); // перешли на первый элемент коллекции
        while(!It->isDone() && It->GetCurrent()->Get_Type() != booktype) // до тех пор пока не найдет подходящий
        {
            It->Next();
        }
    }
    void Next() // после первого найденного элемента надо двигаться дальше до тех пор, пока не обойдем весь контейнер
    {
        do
        {
            It->Next();

        } while(!It->isDone() && It->GetCurrent()->Get_Type() != booktype);

    }
};

// Класс декоратор для тетрадей конкретного цвета
class Dec_1 : public Decorator<ExerciseBook*>
{
private:
    FormatOfBook formatbook;
public:
    Dec_1(Iterator<ExerciseBook*> *it, FormatOfBook fb) : Decorator<ExerciseBook*>(it), formatbook(fb) {};
    // Та же реализация
    void First()
    {
        It -> First();
        while(!It->isDone() && It->GetCurrent()->Get_Format() != formatbook)
        {
            It->Next();
        }
    }
    void Next()
    {
        do
        {
            It -> Next();
        } while(!It->isDone() && It->GetCurrent()->Get_Format() != formatbook);
    }
};

// Класс декоратор для открытых тетрадей
class Dec_2 : public Decorator<ExerciseBook*>
{
private:
    bool opened;
public:
    Dec_2( Iterator<ExerciseBook*> *it, bool open ) : Decorator<ExerciseBook*>(it), opened(open) {};

    void First()
    {
        It -> First();
        while(!It->isDone() && It->GetCurrent()->Is_Open() != opened)
        {
            It->Next();
        }
    }
    void Next()
    {
        do
        {
            It -> Next();
        }while(!It->isDone() && It->GetCurrent()->Is_Open() != opened);
    }
};

// Реализация фабричного метода
ExerciseBook* CreateBook(int x, int page)
{
    ExerciseBook* pNewExerciseBook = nullptr;



    if(x == 1)
    {
        pNewExerciseBook = new SquareBook;
        pNewExerciseBook->open_page(page);
        pNewExerciseBook->write_smth(page);
        pNewExerciseBook->tell_format();
        pNewExerciseBook->get_squares();
    }
    else if(x == 2)
    {
        pNewExerciseBook = new LineBook;
        pNewExerciseBook->open_page(page);
        pNewExerciseBook->write_smth(page);
        pNewExerciseBook->tell_format();
        pNewExerciseBook->get_lines();
    }
    else
    {
        pNewExerciseBook = new RingBook;
        pNewExerciseBook->open_page(page);
        pNewExerciseBook->write_smth(page);
        pNewExerciseBook->tell_format();
        pNewExerciseBook->get_amount_pages();
    }
    return pNewExerciseBook;
}

// Функция, демонстрирующая взаимозависимость
void WriteEmAll(Iterator<ExerciseBook*> *it, int page)
{
    for(it->First(); !it->isDone(); it->Next())
    {
        ExerciseBook* currentBook = it->GetCurrent();
        currentBook->write_smth(page);
        currentBook->Open();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    wcout << "What exercisebook do you wanna create: 1 - squarebook, 2 - linebook, 3 - ringbook: ";
    int choice = 0;
    int page = 0;
    cin >> choice;
    cout << "Enter the page: ";
    cin >> page;

    ExerciseBook* pNewExerciseBook = CreateBook(choice, page);
    delete pNewExerciseBook;

    cout << "-------------------------------------------------------" << endl;


    ArrayClass<ExerciseBook*> s_array; // создали контейнер класса ArrayClass (т.е. массив)
    int amount = 0;
    cout << "Enter amount of elements: ";
    cin >> amount;
    for(size_t i = 0; i < amount; i++)
    {
        int choice_book = rand()%3 + 1;
        // Заполнение контейнера случайными значениями
        ExerciseBook* pNewBook = CreateBook(choice_book, page);
        s_array.Add(pNewBook);
    }

    // Продемонстрируем метод print()
    cout << "Write indexes: " << endl;
    s_array.print();

    // Обход массива, используя паттерн "Итератор". Используем метод GetIterator.
    //Iterator<ExerciseBook*> *pit_1 = new ArrayIterator<ExerciseBook*>(&s_array);
    Iterator<ExerciseBook*> *pit_1 = s_array.GetIterator();
    WriteEmAll(pit_1, page);
    delete pit_1;
    cout << "--------------------------------------------------------" << endl;
    // Обход массива, исользуя Декоратор. Фильтруем по формату, по типу тетради(клеточка, линейка...), открыта ли она
    cout << "If squarebooks exist, they're A5, opened, write them all" << endl;
    // параметр s_array.GetIterator() передает итератор в указатель it конструктора
    Iterator<ExerciseBook*> *pdec = new Dec(s_array.GetIterator(), TypeOfBook::squarebook); // тетрадки в клеточку
    Iterator<ExerciseBook*> *pdec_1 = new Dec_1(s_array.GetIterator(), FormatOfBook::A5); // тетрадки формата А5
    Iterator<ExerciseBook*> *pdec_2 = new Dec_2(s_array.GetIterator(), true); // тетради открыты
    WriteEmAll(pdec, page); // проверка первого декоратора
    WriteEmAll(pdec_1, page); // проверка второго декоратора
    WriteEmAll(pdec_2, page); // проверка третьего декоратора
    delete pdec;
    delete pdec_1;
    delete pdec_2;
    cout << endl;


    VecClass<ExerciseBook*> s_vec; // создали контейнер класса VecClass (т.е. вектор)

    cout << "Enter amount of elements: ";
    //int amount = 0;
    cin >> amount;
    for(size_t i = 0; i < amount; i++)
    {
        int choice_book_1 = rand()%3 + 1;
        s_vec.Push(CreateBook(choice_book_1, page));
    }

    cout << "Vector's empty? " << s_vec.isEmpty() << endl;
    cout << "Size: " << s_vec.return_amount_el();

    cout << endl;

    // Обход вектора, используя паттерн "Итератор"
    Iterator<ExerciseBook*> *pit_2 = s_vec.GetIterator();
    WriteEmAll(pit_2, page);
    delete pit_2;

    cout << "---------------------------------------------" << endl;
    cout << "If linebook exist, they're A5, opened, write them all" << endl;
    // Обход вектора, используя декоратор. Фильтруем по цвету, тетрадки должны быть в клеточку, и они должы быть открыты
    Iterator<ExerciseBook*> *pdec_vec = new Dec(s_vec.GetIterator(), TypeOfBook::linebook); // тетрадки в линейку
    Iterator<ExerciseBook*> *pdec_vec_1 = new Dec_1(s_vec.GetIterator(), FormatOfBook::A5); // тетрадки формата A5
    Iterator<ExerciseBook*> *pdec_vec_2 = new Dec_2(s_vec.GetIterator(), true); // тетрадки открыты
    WriteEmAll(pdec_vec, page); // если есть тетрадка в линейку, написать в ней
    WriteEmAll(pdec_vec_1, page); // если есть тетрадка формата A5, написать в ней
    WriteEmAll(pdec_vec_2, page); // если тетрадка открыта, написать в ней
    delete pdec_vec;
    delete pdec_vec_1;
    delete pdec_vec_2;

    cout << endl;

    // Создание еще одного вектора для демонстрации паттерна "Адаптер"
    vector<ExerciseBook*> adapt_vect;
    for(int i = 0; i < 3; i++)
    {
        int choice_book_2 = rand()%3 + 1;
        ExerciseBook* create_book = CreateBook(choice_book_2, page);
        adapt_vect.push_back(create_book);
    }

    // Реализация Адаптера
    cout << "----------------------------------------------" << endl;
    cout << "Writing only in SquareBook" << endl;
    Iterator<ExerciseBook*> *AdapterIterator = new Adapter<vector<ExerciseBook*>, ExerciseBook*>(&adapt_vect);
    Iterator<ExerciseBook*> *DecoratorAdapterIt = new Dec(AdapterIterator, TypeOfBook::squarebook); // отфильтруем наш вектор по тетрадямм в кольцах
    WriteEmAll(DecoratorAdapterIt, page);

    delete DecoratorAdapterIt;
    return 0;
}
