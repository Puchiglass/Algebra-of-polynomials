#include "hash_table_list.h"
#include "eq_exception.h"
#include "list.h"
#include "table_string.h"


unsigned int HashTableList::Hash(const std::string& key)
{
    unsigned long hashval = 0;
    int len = key.length();
    for (int i = 0; i < len; i++) {
        hashval = (hashval << 3) + key[i];
    }
    return hashval % size;
}

TableString* HashTableList::find_str(const std::string& key)
{
    int index = Hash(key);
    for (ListIterator<TableString*> it = table[index]->begin();
        it != table[index]->end(); ++it)
    {
        if ((*it)->get_key() == key) {
            curr_pos = it;
            return (*it);
        }
    }
    return nullptr;
}

TableBody* HashTableList::find(const std::string& key)
{
    TableString* tmp = (*this).find_str(key);
    if (tmp == nullptr) {
        return nullptr;
    }
    else {
        return &tmp->body;
    }
}


bool HashTableList::insert(const std::string& key, TableBody& data)
{
    if (is_full()) {
        throw EqException(error_codes::k_OUT_OF_MEMORY);
    }

    TableString* tmp = find_str(key);
    if (tmp != nullptr) {
        return false;
    }
    else {
        int index = Hash(key);
        ListIterator<TableString*> it =  table[index]->begin();
        TableString* tmp = new TableString(key, data);
        table[index]->insert(it, tmp);
        data_cnt++;
    }
    return true;
}


bool HashTableList::erase(const std::string& key)
{
    int index = Hash(key);

    if ((*this).find_str(key) == nullptr) {
        return false;
    }
    else {
        table[index]->erase(curr_pos);
        data_cnt--;
        return true;
    }
}

bool HashTableList::is_full() const
{
    try {
        TableString* pNode = new TableString();
        delete pNode;
    }
    catch(...) {
        return true;
    }
    
    return false;
}

bool HashTableList::is_tab_ended() const
{
    return curr_index >= size;
}

bool HashTableList::reset()
{
    curr_pos = table[0]->begin();
    curr_index = 0;
    curr_pos_num = 0;
    return is_tab_ended();
}

bool HashTableList::go_next()
{
    if (is_tab_ended()) {
        return true;
    }

    int p_curr_index = curr_index;
    if ( ++curr_pos == table[curr_index]->end()) {
        curr_index++;

        if (is_tab_ended()) {
            return true;
        }

        if (table[curr_index]->get_size() == 0) {
            return is_tab_ended();
        }
        curr_pos_num++;
        curr_pos = table[curr_index]->begin();
    }
    else {
        curr_pos_num++;
    }

    return is_tab_ended();
}

bool HashTableList::set_current_pos(int pos)
{
    if(!((pos > -1) && (pos < data_cnt))) {
        return false;
    }

    int cnt = 0;
    for((*this).reset(); !(*this).is_tab_ended(); (*this).go_next()) {
        if(cnt == pos) {
            break;
        }
        else {
            cnt++;
        }
    }
    return true;
}

TableString*  HashTableList::get_value()
{
    if (table[curr_index]->get_size() == 0) {
        return nullptr;
    }

    return (*curr_pos);
}

int HashTableList::hash_string(const std::string &key)
{
    return Hash(key);
}


int HashTableList::get_current_pos() const
{
    return curr_pos_num;
}
