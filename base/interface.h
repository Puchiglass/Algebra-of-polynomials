#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "table.h"
#include "red_black_tree.h"
#include "polynom.h"
#include "array_table.h"
#include "list_table.h"
#include "sorted_array_table.h"
#include "hash_table_list.h"
#include "hash_table_double.h"
#include "eq_exception.h"
#include "postfix.h"
#include <conio.h>
class Interface
{
    enum Table_num
    {
        k_ARRAY_TABLE,
        k_SORTED_ARRAY_TABLE,
        k_LIST_TABLE,
        k_RED_BLACK_TREE,
        k_CHAIN_HASH_TABLE,
        k_LIST_HASH_TABLE,
        k_TABLE,
    };
    const int k_table_size;
    Table_num mode;
    // 0 Arr, 1 Sort, 2 List, 3 Tree, 4 Chain-Hash, 5 List-Hash
    Table** tab;
private:
    bool is_tab_not_chosen(); // Возвращает, была ли выбрана таблица
    bool are_sure(); // Спрашивает согласие пользователя
    void table_menu(); // Предоставляет пользователю выбор действий с таблицами
    void find(); // Находит элемент в таблице и показывает его на экране
    void insert(); // Вставляет элемент во все таблицы и показывает, была ли успешна вставка
    void erase(); // Удаляет элемент из всех таблиц и показывает, было ли успешно удаление
    void polynom_menu(); // Предоставляет пользователю выполнить вычисление выражения с полиномами
    void print(); // Выводит на экран текущую таблицу целиком
    void print_error(EqException eq); // Выводит на экран номер и название исключения
public:
    Interface() :mode(Table_num::k_TABLE), k_table_size/*(4)*/(6) // Конструктор по умолчанию
    {
        tab = new Table * [k_table_size];
        tab[0] = new ArrayTable;
        tab[1] = new SortTable;
        tab[2] = new ListTable;
        tab[3] = new RedBlackTree;
        //////////////////////////////////////////////////
        tab[4] = new HashTableDouble;
        tab[5] = new HashTableList(100);
    }
    void menu(); // Главное меню. Из него можно выйти из программы и войти в меню операций с таблицами или выполнить вычисления с полиномами
};
#endif