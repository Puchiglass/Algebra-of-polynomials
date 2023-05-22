#ifndef _TABLE_STRING_H_
#define _TABLE_STRING_H_

#include <ostream>
#include <string>

#include "polynom.h"

using std::string;

class TableString;


struct TableBody
{
    string poly_string; // строка полинома
    Polynom* poly; // указатель на полином
    TableBody() // конструктор по умолчанию
        : poly_string(), poly(nullptr)
    {}
    TableBody(const Polynom& poly_) // конструктор преобразования полинома в тело записи
    {
        poly = new Polynom(poly_);
        poly_string = poly_.str();
    }

    ~TableBody() = default;
};

class TableString
{
private:
    //private:
    string key; // Ключ записи
    TableBody body; // Тело записи
public:
    TableString() // Конструктор по умолчанию 
        :key("I"), body()
    {}

    TableString(string key_, TableBody& body_) // Конструктор инициализации
        : key(key_), body(body_)
    {
        const int k_MAX_NAME = 16;
        //const int k_MAX_POLY_STRING = 102;
        if (key_.size() > k_MAX_NAME)
            throw EqException(error_codes::k_OVERFLOW);
        for (int i = 0; i < key.size(); i++)
        {

            char c = key[i];
            if (c == 'I')
                throw EqException(error_codes::k_USING_RESERVED_NAME);
            if (c == 'd' && (key[i + 1] == 'x' || key[i + 1] == 'y' || key[i + 1] == 'z'))
                throw EqException(error_codes::k_USING_RESERVED_NAME);
            if (c >= '9' + 1 && c <= '9' + 7)
                throw EqException(error_codes::k_USING_PUNCTUATION_MARKS);
        }
    }

    TableString(const TableString& other) = default; // Конструктор копирования
    ~TableString() = default; // Деструктор

    TableString& operator=(const TableString& other) = default; // Оператор присваивания

    bool operator==(const TableString& other) // Оператор проверки на равенство
    {
        return key == other.key;
    }
    bool operator!=(const TableString& other) // Оператор проверки на неравенство
    {
        return key != other.key;
    }

    bool operator<(const TableString& other) // Оператор "меньше"
    {
        return key < other.key;
    }

    bool operator>(const TableString& other) // Оператор "больше"
    {
        return key > other.key;
    }

    inline string get_key() const // Получение ключа
    {
        return key;
    }

    inline Polynom* get_polynom() const // Получение указателя на полином
    {
        return body.poly;
    }

    void print(std::ostream& os) const // Простая печать строки
    {
        os << key << " " << body.poly_string << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const TableString* ts);

    friend class ArrayTable;
    friend class Table;
    friend class HashTableList;
    friend class HashTableDouble;
    friend class HashTableDouble;
    friend class Interface;
    friend class ListTable;
    friend class RedBlackTree;
    friend class SortTable;
};



#endif // 