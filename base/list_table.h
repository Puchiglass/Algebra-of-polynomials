#ifndef _LIST_TABLE_H_
#define _LIST_TABLE_H_
#include "table.h"

class ListTable :public Table
{
    List<TableString> data;
    virtual TableString* find_str(const std::string& key);
    ListIterator<TableString> cur_pos;
public:
    TableBody* find(const std::string& key);
    bool insert(const std::string& key, TableBody& data_);
    bool erase(const std::string& key);
 //   void print();

    bool empty()
    {
        return data_cnt == 0;
    }
    int get_data_count()
    {
        return data_cnt;
    }
    inline bool is_full() const
    {
        try {
            NodeList<TableString>* tmp = new NodeList<TableString>;
            delete tmp;
        }
        catch (...)
        {
            return true;
        }
        return false;
    }

    // go to first position of table, returns is_tab_ended()
    bool reset()
    {
        cur_pos = data.begin();
        return is_tab_ended();
    }
    // return cur_pos == data.end();
    bool is_tab_ended() const
    {
        return cur_pos == data.end();
    }
    // go to next position, returns is_tab_ended
    bool go_next()
    {
        if (!is_tab_ended())
            ++cur_pos;
        return is_tab_ended();
    }
    TableString* get_value()
    {
        if (is_tab_ended()) {
            return nullptr;
        }
        return &(*cur_pos);
    }


    ListTable() : data(), cur_pos(data.begin())
    {
        data_cnt = 0;
    }
    ListTable(std::vector<TableString> a) : data(a), cur_pos(data.begin())
    {
        data_cnt = a.size();
    }
    ~ListTable()
    {}
};
#endif