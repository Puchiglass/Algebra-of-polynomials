#ifndef _ARRAY_TABLE_H_
#define _ARRAY_TABLE_H_

// TODO: Memory allocation
#include "table.h"
#include "table_string.h"
#include <utility>

#define DEFAULT_SIZE 25

class ArrayTable : public Table
{
protected:
    TableString** tbl;
    int size;
    int curr_pos;

    void memory_allocator();
public:
    ArrayTable(int _size = DEFAULT_SIZE)
        : Table(), size(_size), curr_pos(0)
    {
        tbl = new TableString*[size];
        for (int i = 0; i < _size; i++) {
            tbl[i] = nullptr;
        }
    }
    virtual ~ArrayTable()
    {
        // Delete key - not  data
        for (int i = 0; i < size; i++) {
            delete  tbl[i];
        }
        delete [] tbl;
    }


    inline int get_size() const
    {
        return size;
    }
    
    virtual TableBody* find(const std::string& key);
    virtual TableString* find_str(const std::string& key);
    virtual bool insert(const std::string& key, TableBody& data);
    virtual bool erase(const std::string& key);
    virtual bool is_full() const;
    virtual bool reset();
    virtual bool is_tab_ended() const;
    virtual bool go_next();
    virtual bool set_current_pos(int pos);
    virtual int get_current_pos() const;
    virtual TableString* get_value();
};


#endif