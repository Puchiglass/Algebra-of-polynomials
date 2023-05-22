#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_


#include "table.h"
#include <iterator>
#include <ostream>
#include "table_string.h"
#include "stack.h"

enum RBTColor { Black, Red };

struct  RBTNode
{
    TableString* data;
    RBTColor color;
    RBTNode * left;
    RBTNode* right;
    RBTNode * parent;
    RBTNode(TableString* data_, RBTColor c, RBTNode* p, RBTNode*l, RBTNode*r) :
        data(data_), color(c), parent(p), left(l), right(r) { };
};

class RedBlackTree : public Table
{
private:
    void left_rotate(RBTNode* &root, RBTNode* x);
    void right_rotate(RBTNode* &root, RBTNode* y);
    void insert_in(RBTNode* &root, RBTNode* node);
    void insert_fix_up(RBTNode* &root, RBTNode* node);
    void destroy(RBTNode* &node);
    void remove(RBTNode*& root, RBTNode*node);
    void remove_fix_up(RBTNode* &root, RBTNode* node, RBTNode*parent);
    RBTNode* search(RBTNode*node, const std::string& key) const;
    
    // void pre_order(RBTNode* tree)const;
    // void in_order(RBTNode* tree)const;
    // void post_order(RBTNode* tree)const;

    int curr_pos;
    RBTNode *root;
    RBTNode *current;
    TStack<RBTNode*> st;
public:
    
    RedBlackTree(): curr_pos(0), root(nullptr), current(nullptr)
      {}

    ~RedBlackTree() {
        destroy(root);
    }


    TableString* find_str(const std::string& key);
    TableBody* find(const std::string& key);
    bool insert(const std::string& key, TableBody& data);
    bool erase(const std::string& key);
    bool is_full() const;
    bool reset();
    bool is_tab_ended() const;
    bool go_next();
    bool set_current_pos(int pos);
    int get_current_pos() const;
    TableString* get_value();

};

#endif // _RED_BLACK_TREE_H_