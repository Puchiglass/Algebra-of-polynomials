#include "hash_table_double.h"
#include "eq_exception.h"
#include "table_string.h"
#include "list.h"
#include "table.h"

unsigned int HashTableDouble::Hash1(const std::string& key)
{
    int hash_result = 0;
    int len = key.length();
    for (int i = 0; i < len; i++)
        hash_result = ((default_size - 1) * hash_result + key[i]) % default_size;
    hash_result = (hash_result * 2 + 1) % default_size;
    return hash_result;
}

unsigned int HashTableDouble::Hash2(const std::string& key)
{
    int hash_result = 0;
    int len = key.length();
    for (int i = 0; i < len; i++)
        hash_result = ((default_size + 1) * hash_result + key[i]) % default_size;
    hash_result = (hash_result * 2 + 1) % default_size;
    return hash_result;
}

TableString* HashTableDouble::find_str(const std::string& key)
{
    int k = 0;
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    while (k < default_size)
    {
        if (table[h1] == nullptr)
            return nullptr;
        if ((table[h1]->key == key) && (flag[h1] == 1))
            return table[h1];
        h1 = (h1 + h2) % default_size;
        k++;
    }
}

bool HashTableDouble::erase(const std::string& key)
{
    int k = 0;
    int f = 0;
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    while (k < default_size)
    {
        if (table[h1] == nullptr)
            return false;
        if ((table[h1]->key == key) && (flag[h1] == 1))
        {
            f = 1;
            break;
        }
        h1 = (h1 + h2) % default_size;
        k++;
    }
    if (f == 1)
    {
        flag[h1] = -1;
        data_cnt--;
        return true;
    }
    return false;
}

bool HashTableDouble::insert(const std::string& key, TableBody& data)
{
    if (is_full()) {
        throw EqException(error_codes::k_OUT_OF_MEMORY);
    }
    TableString* tm = find_str(key);
    if (tm != nullptr) {
        return false;
    }
    int i = 0;
    int h1 = Hash1(key);
    int h2 = Hash2(key);
    TableString* tmp = new TableString(key, data);
    int first_deleted = -1; // ���������� ������ ���������� (���������) �������
    while (first_deleted == -1 && flag[h1] != 0 && i < default_size)
    {
        if (table[h1]->key == key && flag[h1] == 1)
            return false; // ����� ������� ��� ����
        if (flag[h1] == -1) // ������� ����� ��� ������ ��������
            first_deleted = h1;
        h1 = (h1 + h2) % default_size;
        i++;
    }
    if (flag[h1] == 0) // ���� �� ������� ����������� �����, ������� ����� Node
    {
        table[h1] = tmp;
        flag[h1] = 1;
        size_all_non_nullptr++;
        data_cnt++;
    }
    else if(first_deleted!=-1)
    {
        table[first_deleted] = tmp;
        flag[first_deleted] == 1;
        data_cnt++;
    }
    return true;
}

bool HashTableDouble::is_full() const
{
    if (data_cnt > default_size/2)
        return true;
    else
    return false;
}

bool  HashTableDouble::is_tab_ended() const
{
    return curr_index >= default_size;
}

bool HashTableDouble::reset()
{
    curr_index = 0;
    return is_tab_ended();
}

bool HashTableDouble::go_next()
{
    curr_index= curr_index + 1;
    if (is_tab_ended()) {
        return false;
    }
    return true;
}

TableString* HashTableDouble::get_value()
{
    if (table[curr_index] == nullptr || flag[curr_index]!=1)
    {
        return nullptr;
    }
    return table[curr_index];
}

TableBody* HashTableDouble::find(const std::string& key)
{
    if ((*this).find_str(key)!= nullptr)
    return &(*this).find_str(key)->body;
    return nullptr;
}

