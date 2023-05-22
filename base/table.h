#ifndef _TABLE_H_
#define _TABLE_H_


#include "polynom.h"
#include "table_string.h"
#include <ostream>
#include <string>

#define DEFAULT_SIZE 100

using std::cout;

class Table
{
protected:
    //quantity of elements
    int data_cnt;
public:
    Table() : data_cnt(0) {}
    virtual ~Table() {}

    virtual bool insert(const std::string& key, TableBody& data) = 0;
    virtual bool erase(const std::string& key) = 0;
    inline virtual bool is_full() const = 0;
    virtual TableBody* find(const std::string& key) = 0;
    virtual TableString* find_str(const std::string& key) = 0;


    // HOW TO PRINT: print_header(); print other TableString's
    void print_header()
    {
        ///
        /// | - 179
        /// - - 196
        const char vert = 179, horiz = 196;
        const char left_up = 192, up = 193, rigth_up = 217;
        const char left_down = 218, down = 194, rigth_down = 191;
        const string name = "NAME OF POLYNOM ", stroka = "POLYNOM";
        //console length = 120
        cout << left_down;
        for (int i = 1; i < 17; i++)
            cout << horiz;
        cout << down;
        for (int i = 18; i < 119; i++)
            cout << horiz;
        cout << rigth_down;
        cout << '\n';
        cout << vert;
        cout << name << vert;
        cout << stroka;
        for (int i = 0; i < 101 - stroka.size(); i++)
            cout << ' ';
        cout << vert;
        cout << '\n';
        cout << left_up;
        for (int i = 1; i < 17; i++)
            cout << horiz;
        cout << up;
        for (int i = 18; i < 119; i++)
            cout << horiz;
        cout << rigth_up;
        cout << '\n';
    }


    // Set to first record
    // Return is_tab_ended
    virtual bool reset() = 0;

    virtual bool is_tab_ended() const = 0;

    // Next record
    // Return is_tab_ended
    virtual bool go_next() = 0;

    // Get value of current iterable record
    inline virtual TableString* get_value() = 0;

    inline virtual bool empty() const
    {
        return data_cnt == 0;
    }

    inline virtual int get_data_count() const
    {
        return data_cnt;
    }

    void print(Table* tab)
    {
        print_header();
        bool b;
        for (tab->reset(); !tab->is_tab_ended(); tab->go_next()) {
            cout << tab->get_value();
        }
       /* cout << "Table printing" << std::endl;
        for (tab.reset(); !tab.is_tab_ended(); tab.go_next()) {
            cout << " Key" << tab.get_value()->key << " Val "
                << tab.get_value()->body.poly_string << std::endl;
        }*/
    }

};

#endif // _TABLE_H_