#include "interface.h"
using std::string;
using std::cout;
using std::cin;
bool Interface::are_sure()
{
    int ans;
    std::cout << "press y if yes, press anything else if no\n\n";
    ans = _getch();
    if (ans == 'Y' || ans == 'y')
        return true;
    else
        return false;
}
bool Interface::is_tab_not_chosen()
{
    return mode == Table_num::k_TABLE;
}
void Interface::menu()
{
    const int k_com_num = 3;
    string commands[k_com_num] = { "1. operations with polynoms", "2. operations with tables", "0. exit" };
    int input;
    do {
        for (int i = 0; i < k_com_num; i++)
            std::cout << commands[i] << endl;
        cout << endl;
        input = _getch();
        input -= '0';
        switch (input) {
        case 1: {
            polynom_menu();
            break;
        }
        case 2: {
            table_menu();
            break;
        }
        case 0: {
            cout << "you really want to exit?\n";
            if (are_sure())
            {
                std::cout << "goodbye!\n";
                return;
            }
            break;
        }
        }
    } while (true);
}
void Interface::table_menu()
{
    const int k_com_num = 6;
    string commands[k_com_num] = { "1. find element", "2. insert element", "3. delete element", 
        "4. choose table", "5. display the table", "0. return to main menu" };
    int input;
    const int k_tables_num = 7;
    string tables[k_tables_num] = { "1. unsorted array table",
        "2. sorted array table","3. list table", "4. red-black tree",
        "5. hash table (using chain)", "6. list hash table" ,"0. return to operations with tables" };
    int local_input;
    do {
        for (int i = 0; i < k_com_num; i++)
            cout << commands[i] << "\n";
        cout << "\n";
        input = _getch();
        input -= '0';
        if (is_tab_not_chosen())
            if (input != 4 && input > 0 && input < 6)
            {
                cout << "table is not chosen!" << endl << "choose table: \n" << endl;
                goto choose_tab;
            }
 inp:       switch (input)
        {
        case 1: {
            Interface::find();
            break;
        }
        case 2: {
            Interface::insert();
            break;
        }
        case 3: {
            Interface::erase();
            break;
        }
 choose_tab:       case 4: {
            for (int i = 0; i < k_tables_num; i++)
                std::cout << tables[i] << "\n";
            do {
                local_input = _getch();
            } while (local_input - '0' < 1 || local_input - '0' > 6);
            local_input -= '0';//
            switch (local_input)
            {
            case 1: {
                mode = Table_num::k_ARRAY_TABLE;
                cout << endl << tables[0] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 2: {
                mode = Table_num::k_SORTED_ARRAY_TABLE;
                cout << endl << tables[1] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 3: {
                mode = Table_num::k_LIST_TABLE;
                cout << endl << tables[2] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 4: {
                mode = Table_num::k_RED_BLACK_TREE;
                cout << endl << tables[3] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 5: {
                mode = Table_num::k_CHAIN_HASH_TABLE;
                cout << endl << tables[4] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 6: {
                mode = Table_num::k_LIST_HASH_TABLE;
                cout << endl << tables[5] << " had chosen" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 0: {
                if (is_tab_not_chosen()) {
                    cout << "table is not chosen!" << endl << "choose table: \n" << endl;
                    goto choose_tab;
                }
                break;
            }
            }
            break;
        }
        case 5: {
            print();
            break;
        }
        case 0: {
            return;
        }
        }
    } while (input != '0');
}
////////////////////////////////////////////////////////
void Interface::polynom_menu()
{
    const int k_com_num = 2;
    string commands[k_com_num] = { "1. calculate the expression", 
        "0. return to the main menu" };
    int input;
    do {
        for (int i = 0; i < k_com_num; i++)
            std::cout << commands[i] << "\n";
        cout << endl;        
        input = _getch();
        input -= '0';
        switch (input)
        {
        case 1: {
            string expression;
            cout << "print exptression without spaces and delimiters\n";
            cout << "print 0, if you want to return to operations with tables" << endl;
            cin >> expression;
            if (expression == "0")
            {
                cout << endl;
                return;
            }
            try { TPostfix postfix; 
            postfix.set_infix(expression);
            postfix.to_postfix();
            Polynom tmp = postfix.calculate(tab);
            cout << "the result is " << tmp << endl;
            cout << "do you want to save the polynom?" << endl;
            if (are_sure())
            {
                TableBody save(tmp);
                cout << "press the name of polynom. do not use such letters: i,d,x,y,z. use only letters";
                cout << "max length of name is 16 symbols" << endl;
                string name;
                cin >> name;
                for (int i = 0; i < Interface::k_table_size; i++)
                {
                    if (!tab[i]->insert(name, save)) {
                        cout << "insertion problem" << endl << endl;
                    }
                }
                cout << "success" << endl << endl;
                return;
            }
            }
            catch (EqException eq) {
                print_error(eq);
            }
            break;
        }
        case 0: {
            return;
        }
        }
    } while (input != 0);
}

void Interface::print_error(EqException eq)
{
    cout << "error number " << eq.get_error() << ". - " << eq.get_comment() << endl;
}
void Interface::find()
{
    string key;
    cout << "print name of polynom" << endl << "print 0, if you want to return to operations with tables" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    TableBody* tmp = tab[mode]->find(key);
    if (tmp == nullptr) {
        cout << "there is no polynom with that name" << endl << endl;
        return;
    }
    else {
        cout << (*tmp).poly_string << endl << endl;
    }
}
void Interface::insert()
{
    string key;
    cout << "print name of polynom" << endl << "print 0, if you want to return to operations with tables" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    cout << "print polynom" << endl;
    string poly_;
    cin >> poly_;
    try { 
        Polynom p(poly_);
        try {
            TableBody tmp(p);
            for (int i = 0; i < 6; i++)
                if (!tab[i]->insert(key, tmp))
                {
                    cout << "a polynom with this name is already in the table" << endl << endl;
                    return;
                }
            cout << "success!" << endl << endl;
        }
        catch (EqException eq)
        {
            print_error(eq);
        }
    }
    catch (EqException eq)
    {
        print_error(eq);
    }
}
void Interface::erase()
{
    string key;
    cout << "print name of polynom" << endl << "print 0, if you want to return to operations with tables" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    for (int i = 0; i < k_table_size; i++)
        if (!tab[i]->erase(key))
        {
            cout << "there is no polynom with that name" << endl << endl;
            return;
        }
    cout << "success!" << endl << endl;
}
//choose redefine or use table's print
void Interface::print()
{
    tab[mode]->print(tab[mode]);
    cout << endl;
}