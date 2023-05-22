#include "interface.h"
using std::string;
using std::cout;
using std::cin;
bool Interface::are_sure()
{
    int ans;
    std::cout << "PRESS Y IF YES, PRESS ANYTHING ELSE IF NO\n\n";
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
    string commands[k_com_num] = { "1. OPERATIONS WITH POLYNOMS", "2. OPERATIONS WITH TABLES", "0. EXIT" };
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
            cout << "YOU REALLY WANT TO EXIT?\n";
            if (are_sure())
            {
                std::cout << "GOODBYE, HAVE A NICE DAY!\n";
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
    string commands[k_com_num] = { "1. FIND ELEMENT", "2. INSERT ELEMENT", "3. DELETE ELEMENT", 
        "4. CHOOSE TABLE", "5. DISPLAY THE TABLE", "0. RETURN TO MAIN MENU" };
    int input;
    const int k_tables_num = 7;
    string tables[k_tables_num] = { "1. UNSORTED ARRAY TABLE",
        "2. SORTED ARRAY TABLE","3. LIST TABLE", "4. RED-BLACK TREE",
        "5. HASH TABLE (CHAIN METHOD)", "6. LIST HASH TABLE" ,"0. RETURN TO OPERATIONS WITH TABLES"};
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
                cout << "TABLE IS NOT CHOSEN!" << endl << "CHOOSE TABLE: \n" << endl;
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
                cout << endl << tables[0] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 2: {
                mode = Table_num::k_SORTED_ARRAY_TABLE;
                cout << endl << tables[1] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 3: {
                mode = Table_num::k_LIST_TABLE;
                cout << endl << tables[2] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 4: {
                mode = Table_num::k_RED_BLACK_TREE;
                cout << endl << tables[3] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 5: {
                mode = Table_num::k_CHAIN_HASH_TABLE;
                cout << endl << tables[4] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 6: {
                mode = Table_num::k_LIST_HASH_TABLE;
                cout << endl << tables[5] << " HAD CHOSEN" << endl << endl;
                if (input != 4)
                    goto inp;
                break;
            }
            case 0: {
                if (is_tab_not_chosen()) {
                    cout << "TABLE IS NOT CHOSEN!" << endl << "CHOOSE TABLE: \n" << endl;
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
//const int k_com_num = 5;
//string commands[k_com_num];
//int input;
//do {
//    input = _getch();
//} while (input);

////////////////////////////////////////////////////////
void Interface::polynom_menu()
{
    const int k_com_num = 2;
    string commands[k_com_num] = { "1. CALCULATE THE EXPRESSION", 
        "0. RETURN TO MAIN MENU" };
    int input;
    do {
        for (int i = 0; i < k_com_num; i++)
            std::cout << commands[i] << "\n";
        cout << endl;        
        input = _getch();
        input -= '0';
        switch (input)
        {
        //case 1: {
        //    string pol_str;
        //    std::cin >> pol_str;
        //    try { 
        //        Polynom tmp(pol_str); 
        //
        //    }
        //    catch (EqException eq)
        //    {
        //        print_error(eq);
        //    }

        //}
        case 1: {
            string expression;
            cout << "PRINT EXPTRESSION WITHOUT SPACES AND DELIMITERS\n";
            cout << "PRINT 0, IF YOU WANT TO RETURN TO OPERATIONS WITH TABLES" << endl;
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
            cout << "THE RESULT IS " << tmp << endl;
            cout << "DO YOU WANT TO SAVE THE POLYNOM?" << endl;
            if (are_sure())
            {
                TableBody save(tmp);
                cout << "PRESS THE NAME OF POLYNOM. DO NOT USE SUCH LETTERS: I,d,x,y,z. USE ONLY LETTERS";
                cout << "MAX LENGTH OF NAME IS 16 SYMBOLS" << endl;
                string name;
                cin >> name;
                for (int i = 0; i < Interface::k_table_size; i++)
                {
                    if (!tab[i]->insert(name, save)) {
                        cout << "INSERTION PROBLEM" << endl << endl;
                    }
                }
                cout << "SUCCESS" << endl << endl;
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
    cout << "ERROR NUMBER " << eq.get_error() << ". - " << eq.get_comment() << endl;
}
void Interface::find()
{
    string key;
    cout << "PRINT NAME OF POLYNOM" << endl << "PRINT 0, IF YOU WANT TO RETURN TO OPERATIONS WITH TABLES" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    TableBody* tmp = tab[mode]->find(key);
    if (tmp == nullptr) {
        cout << "THERE IS NO POLYNOM WITH THAT NAME" << endl << endl;
        return;
    }
    else {
        cout << (*tmp).poly_string << endl << endl;
    }
}
void Interface::insert()
{
    string key;
    cout << "PRINT NAME OF POLYNOM" << endl << "PRINT 0, IF YOU WANT TO RETURN TO OPERATIONS WITH TABLES" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    cout << "PRINT POLYNOM" << endl;
    string poly_;
    cin >> poly_;
    try { 
        Polynom p(poly_);
        try {
            TableBody tmp(p);
            for (int i = 0; i < 6; i++)
                if (!tab[i]->insert(key, tmp))
                {
                    cout << "A POLYNOM WITH THIS NAME IS ALREADY IN THE TABLE" << endl << endl;
                    return;
                }
            cout << "SUCCESS!" << endl << endl;
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
    cout << "PRINT NAME OF POLYNOM" << endl << "PRINT 0, IF YOU WANT TO RETURN TO OPERATIONS WITH TABLES" << endl;
    cin >> key;
    if (key == "0")
    {
        cout << endl;
        return;
    }
    for (int i = 0; i < k_table_size; i++)
        if (!tab[i]->erase(key))
        {
            cout << "THERE IS NO POLYNOM WITH THAT NAME" << endl << endl;
            return;
        }
    cout << "SUCCESS!" << endl << endl;
}
//choose redefine or use table's print
void Interface::print()
{
    tab[mode]->print(tab[mode]);
    cout << endl;
}