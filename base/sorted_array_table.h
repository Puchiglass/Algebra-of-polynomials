#ifndef _SORTED_ARRAY_TABLE_H_
#define _SORTED_ARRAY_TABLE_H_

#include "array_table.h"
#include "table_string.h"


class SortTable : public ArrayTable
{
private:
    void sort(TableString** unsrtd_table, int data_cnt);

public:
    SortTable(int size = DEFAULT_SIZE) : ArrayTable(size) {} ;
    SortTable& operator=(const SortTable& other);
    SortTable(const ArrayTable &other) { *this = other; }

    TableBody* find(const std::string& key);
    TableString* find_str(const std::string& key);
    bool insert(const std::string& key, TableBody& data);
    bool erase(const std::string& key);
};
#endif


