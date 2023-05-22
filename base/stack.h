#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
public:
    TStack(int _size = 10);
    TStack(const TStack<T>& s);
    ~TStack();
    void add(T tmp);

    //Changed in accordance with the coding rules

    T get_top();
    T info_top();
    bool is_empty();
    bool is_full();
    void set_size(int s);
    int get_size();
};
template <class T>
TStack<T>::TStack(const TStack<T>& s)
{
    size = s.size;
    pMem = new T[size];
    top = s.top;
    for (int i = 0; i <= top; i++)
        pMem[i] = s.pMem[i];
}
template <class T>
TStack<T>::TStack(int _size = 1)
{
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    pMem = new T[size];
}
template <class T>
TStack<T>:: ~TStack()
{
    delete[] pMem;
}
template <class T>
void TStack<T>::add(T tmp)
{
    if (top + 1 >= size)
        throw size;
    pMem[++top] = tmp;
}
template <class T>
T TStack<T>::get_top()
{
    if (is_empty() == true)
    {
        throw 0;
    }
    return (pMem[top--]);
}
template <class T>
T TStack<T>::info_top()
{
    if (is_empty() == true)
    {
        throw 0;
    }
    return (pMem[top]);
}
template <class T>
bool TStack<T>::is_empty()
{
    if (top == -1)
        return true;
    else {
        return false;
    }
}
template <class T>
bool TStack<T>::is_full()
{
    if (top == size - 1) {
        return true;
    }
    else {
        return false;
    }
}
template <class T>
void TStack<T>::set_size(int s)
{
    size = s;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    delete[] pMem;
    pMem = new T[size];
}
template <class T>
int TStack<T>::get_size()
{
    return size;
}
#endif