#include "sorted_array_table.h"
#include "eq_exception.h"
#include "table_string.h"
#include <algorithm>

#include <cstddef>
#include <string>

void SortTable::sort(TableString** unsrtd_table, int data_cnt)
{
    std::sort(unsrtd_table[0], unsrtd_table[data_cnt - 1]);
}

TableString* SortTable::find_str(const std::string& key)
{
    int i, i1 = 0, i2 = data_cnt -1;

    while(i1 <= i2) {
        i = (i1 + i2) >> 1;

        if (tbl[i]->key == key) {
            i1 = i + 1;
            i2 = i;
            break;
        }

        if (tbl[i]->key > key) {
            i2 = i - 1;
        }
        else {
            i1 = i + 1;
        }
    }
    if ((i2 < 0) || (tbl[i2]->key < key))  {
        i2++;
    }
    curr_pos = i2;
    if ((i2 < data_cnt) && (tbl[i]->key == key)) {
        return tbl[i2];
    }
    return nullptr;
}

TableBody* SortTable::find(const std::string& key)
{
    TableString* tmp = (*this).find_str(key);
    if (tmp == nullptr) {
        return nullptr;
    }
    else {
        return &tmp->body;
    }
}





bool SortTable::insert(const std::string& key, TableBody& data)
{
    if (is_full()) {
        throw (EqException(error_codes::k_OUT_OF_MEMORY));
    }

    TableString* tmp = find_str(key);
    if (tmp != nullptr) {
        return false;
    }
    else {
        for (int i = data_cnt; i > curr_pos; i--) {
            tbl[i] = tbl[i-1];
        }
        tbl[curr_pos] = new TableString(key, data);
        data_cnt++;
        return true;
    }
}

bool SortTable::erase(const std::string& key)
{
    TableString* tmp = find_str(key);
    if (tmp == nullptr) {
        return false;
    }
    else {
        for (int i = curr_pos; i < data_cnt; i++) {
            tbl[i] = tbl[i + 1];
        }
        tbl[--data_cnt] = nullptr;
        return true;
    }
}


SortTable& SortTable::operator=(const SortTable &other)
{
    if (tbl != nullptr) {
        for (int i = 0; i < data_cnt; i++) {
            delete tbl[i];
        }
        delete [] tbl;
        tbl = nullptr;
    }
    size = other.get_size();
    data_cnt = other.data_cnt;
    tbl = new TableString*[size];
    for (int i = 0; i < data_cnt; i++) {
        tbl[i] = other.tbl[i];
    }
    sort(tbl, data_cnt);
    curr_pos = 0;
    return *this;


}