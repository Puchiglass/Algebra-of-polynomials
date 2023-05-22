#include "red_black_tree.h"
#include "eq_exception.h"
#include "table_string.h"
#include <new>
#include <string>
#include <type_traits>

void RedBlackTree::left_rotate(RBTNode* &root, RBTNode* x) {
    RBTNode*y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else {
        if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
};

bool RedBlackTree::insert(const std::string& key, TableBody& data)
{
    if(find_str(key) != nullptr) {
        return false;
    }
    TableString* tmp = new TableString(key, data);
    RBTNode *z = new RBTNode(tmp, Red, nullptr, nullptr, nullptr);
    insert_in(root, z);
    data_cnt++;
    return true;
};


void RedBlackTree::insert_in(RBTNode* &root, RBTNode* node)
{
    RBTNode *x = root;
    RBTNode *y = nullptr;
    while (x != nullptr)
    {
        y = x;
        if (node->data->key > x->data->key) {
            x = x->right;
        }
        else {
            x = x->left;
        }
    }
    node->parent = y;
    if(y!=nullptr) {
        if (node->data->key > y->data->key) {
            y->right = node;
        }
        else {
            y->left = node;
        }
    }
    else {
        root = node;
    }
    node->color = Red;
    insert_fix_up(root, node);
};


void RedBlackTree::insert_fix_up(RBTNode* &root, RBTNode* node)
{
    RBTNode*parent;
    parent = node->parent;
    while (node != RedBlackTree::root  && parent->color == Red) {
        RBTNode*gparent = parent->parent;
        if (gparent->left == parent) {
            RBTNode*uncle = gparent->right;
            if (uncle != nullptr && uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            }
            else {
                if (parent->right == node) {
                    left_rotate(root, parent);
                    std::swap(node, parent);
                }
                right_rotate(root, gparent);
                gparent->color = Red;
                parent->color = Black;
                break;
            }
        }
        else {
            RBTNode*uncle = gparent->left;
            if (uncle != nullptr && uncle->color == Red) {
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            }
            else {
                if (parent->left == node) {
                    right_rotate(root, parent);
                    std::swap(parent, node);
                }
                left_rotate(root, gparent);
                parent->color = Black;
                gparent->color = Red;
                break;
            }
        }
    }
    root->color = Black;
}

void RedBlackTree::destroy(RBTNode* &node) 
{
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}


bool RedBlackTree::erase(const std::string& key)
{
    RBTNode *deletenode = search(root, key);
    if (deletenode != nullptr) {
        remove(root, deletenode);
        return true;
    }
    else {
        return false;
    }
}

void RedBlackTree::remove(RBTNode*&root, RBTNode*node)
{
    RBTNode *child, *parent;
    RBTColor color;
    if (node->left != nullptr && node->right != nullptr) {
        RBTNode *replace = node;
        replace = node->right;
        while (replace->left != nullptr) {
            replace = replace->left;
        }
        if (node->parent != nullptr) {
            if (node->parent->left == node) {
                node->parent->left = replace;
            }
            else {
                node->parent->right = replace;
            }
        }

        else {
            root = replace;
        }
        
        child = replace->right;
        parent = replace->parent;
        color = replace->color;
        
        if (parent == node) {
            parent = replace;
        }
        else {
            if (child != nullptr) {
                child->parent = parent;
            }
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        if (color == Black) {
            remove_fix_up(root, child, parent);
        }

        delete node;
        data_cnt--;
        return;
    }
    if (node->left != nullptr) {
        child = node->left;
    }
    else {
        child = node->right;
    }

    parent = node->parent;
    color = node->color;
    if (child)  {
        child->parent = parent;
    }

    if (parent) {
        if (node == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
    }
    else {
        RedBlackTree::root = child;        
    }

    if (color == Black) {
        remove_fix_up(root, child, parent);
    }
    data_cnt--;
    delete node;
}

void RedBlackTree::remove_fix_up(RBTNode* &root, RBTNode* node, RBTNode*parent)
{
    RBTNode* othernode;
    if (root == nullptr) {
        return;
    }
    while ((!node) || node->color == Black && node != RedBlackTree::root) {
        if (parent->left == node) {
            othernode = parent->right;
            if (othernode->color == Red) {
                othernode->color = Black;
                parent->color = Red;
                left_rotate(root, parent);
                othernode = parent->right;
            }
            else {
                if (!(othernode->right) || othernode->right->color == Black) {
                    othernode->left->color=Black;
                    othernode->color = Red;
                    right_rotate(root, othernode);
                    othernode = parent->right;
                }
                othernode->color = parent->color;
                parent->color = Black;
                othernode->right->color = Black;
                left_rotate(root, parent);
                node = root;
                break;
            }
        }
        else {
            othernode = parent->left;
            if (othernode->color == Red)
            {
                othernode->color = Black;
                parent->color = Red;
                right_rotate(root, parent);
                othernode = parent->left;
            }
            if ((!othernode->left || othernode->left->color == Black)
                && (!othernode->right || othernode->right->color == Black))
            {
                othernode->color = Red;
                node = parent;
                parent = node->parent;
            }
            else {
                if (!(othernode->left) || othernode->left->color == Black) {
                    othernode->right->color = Black;
                    othernode->color = Red;
                    left_rotate(root, othernode);
                    othernode = parent->left;
                }
                othernode->color = parent->color;
                parent->color = Black;
                othernode->left->color = Black;
                right_rotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node) {
        node->color = Black;
    }
}

TableString* RedBlackTree::find_str(const std::string& key)
{
    RBTNode* tmp = search(root, key);
    if (tmp != nullptr) {
        return tmp->data;
    }
    else {
        return nullptr;
    }

}

TableBody* RedBlackTree::find(const std::string& key)
{
    TableString* tmp = (*this).find_str(key);
    if (tmp == nullptr) {
        return nullptr;
    }
    else {
        return &tmp->body;
    }
}

RBTNode* RedBlackTree::search(RBTNode* node, const std::string& key) const
{
    if (node == nullptr || node->data->key == key) {
        return node;
    }
    else
        if (key > node->data->key)
            return search(node->right, key);
        else
            return search(node->left, key);
}

void RedBlackTree::right_rotate(RBTNode*&root, RBTNode*y) {
    RBTNode*x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    }
    else {
        if  (y == y->parent->right) {
            y->parent->right = x;
        }
        else {
            y->parent->left = x;
        }
    }
    x->right = y;
    y->parent = x;
};

bool RedBlackTree::is_full() const
{
    try {
        TableString* ts = new TableString();
        RBTNode* rbtnode = new RBTNode(ts, Black, nullptr, nullptr, nullptr);
        delete rbtnode;
    }
    catch(...) {
        return  false;
    }
    return true;
}

bool RedBlackTree::reset()
{
    RBTNode* node = current = root;
    while (!st.is_empty()) {
        st.get_top();
    }

    curr_pos = 0;
    while(node != nullptr) {
        st.add(node);
        current = node;
        node = node->left;
    }
    return is_tab_ended();
}

bool RedBlackTree::go_next()
{
    if (!is_tab_ended() && (current != nullptr)) {
        RBTNode* node = current = current->right;
        st.get_top();
        while(node != nullptr) {
            st.add(node);
            current = node;
            node = node->left;
        }
        if ((current == nullptr) && !st.is_empty()) {
            current = st.info_top();
        }
        curr_pos++;
        return is_tab_ended();
    } 
    return is_tab_ended();
}

bool RedBlackTree::is_tab_ended() const
{
    return curr_pos >= data_cnt;
}

TableString* RedBlackTree::get_value()
{
    return current->data;
}

int RedBlackTree::get_current_pos() const
{
    return curr_pos;
}

bool RedBlackTree::set_current_pos(int pos)
{
    if (!((pos > -1) && (pos < data_cnt))) {
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

// void RedBlackTree::preOrder() {
//     if (root == nullptr)
//         cout << "empty RedBlackTree\n";
//     else
//         preOrder(root);
// };
         
// void RedBlackTree::preOrder(RBTNode* tree)const {
//         if (tree != nullptr) {
//             cout << tree->key << " ";
//             preOrder(tree->left);
//             preOrder(tree->right);
//         }
//     }

// void RedBlackTree::inOrder() {
//     if (root == nullptr)
//         cout << "empty RedBlackTree\n";
//     else
//         inOrder(root);
// };
         
// void RedBlackTree::inOrder(RBTNode* tree)const {
//     if (tree != nullptr) {
//         inOrder(tree->left);
//         cout << tree->key << " ";
//         inOrder(tree->right);
//     }
// }

// void RedBlackTree::postOrder() {
//     if (root == nullptr)
//         cout << "empty RedBlackTree\n";
//     else
//         postOrder(root);
// };
        
// void RedBlackTree::postOrder(RBTNode* tree)const {
//     if (tree != nullptr) {
//         postOrder(tree->left);
//         postOrder(tree->right);
//         cout << tree->key << " ";
//     }
// }

