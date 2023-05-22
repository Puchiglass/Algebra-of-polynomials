

#ifndef __HASHTABLEDOUBLE_H__
#define __HASHTABLEDOUBLE_H__


#include "table.h"
#include "table_string.h"
#include <string>

class HashTableDouble : public Table
{
private:
    int default_size;//размер таблицы
   // int size;// количество эл-в в таблице
    int size_all_non_nullptr;//кол-во эл-в вместе с удаленными
    int* flag;//массив состояния элементов таблицы
    int curr_index;
    TableString** table;
    unsigned int Hash1(const std::string& key);
    unsigned int Hash2(const std::string& key);
public:
    HashTableDouble(int _size = 50)
    {
        curr_index = 0;
        default_size = _size;
       // size = 0;
        data_cnt = 0;
        size_all_non_nullptr = 0;
        table = new TableString * [default_size];
        flag = new int [default_size];
        for (int i = 0; i < default_size; i++)
        {
            flag[i] = 0;
            table[i] = nullptr;
        }
    }

    ~HashTableDouble()
    {
        for (int i = 0; i < default_size; i++)
                delete table[i];
        delete[] table;
    }

    inline int get_data_count() const
    {
        return data_cnt;
    }

    TableString* find_str(const std::string& key);
    bool insert(const std::string& key, TableBody& data);
    bool erase(const std::string& key);
    //void print();
    TableBody* find(const std::string& key);
    bool is_full() const;
    bool reset();
    bool is_tab_ended() const;
    bool go_next();
    TableString* get_value();
};


#endif