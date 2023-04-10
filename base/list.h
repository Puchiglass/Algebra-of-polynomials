#ifndef LIST_H_
#define LIST_H_


#include <vector>


template <class T>
struct NodeList
{
    T key = T();
    NodeList* pNext = nullptr;
};

template <class T>
class List;

template <class T>
class ListIterator;

template <class T>
class ListIterator
{
private:
    friend class List<T>;
    NodeList<T>* prev_ptr;
    NodeList<T>* ptr;

    ListIterator(NodeList<T>* ptr1) : ptr(ptr1), prev_ptr(ptr)
    {}
public:
    ListIterator() : prev_ptr(nullptr), ptr(nullptr)
    {}
    ListIterator(const ListIterator& it) : ptr(it.ptr), prev_ptr(it.prev_ptr)
    {}

    bool operator==(const ListIterator& it) const
    {
        return (ptr == it.ptr);
    }

    bool operator!=(const ListIterator& it) const
    {
        return (ptr != it.ptr);
    }

    T& operator*() const
    {
        return ptr->key;
    }

    ListIterator& operator++()
    {
        prev_ptr = ptr;
        if (ptr == nullptr)
            return *this;
        ptr = ptr->pNext;
        return *this;
    }
};

template <class T>
class List
{
private:
    int size;
    NodeList<T>* pFirst;
    NodeList<T>* pLast;
public:
    List() : size(0), pFirst(nullptr), pLast(nullptr) {}

    using iterator = ListIterator<T>;
    iterator begin() const
    {
        return iterator{ pFirst };
    }

    iterator end() const
    {
        return iterator{ nullptr };
    }

    iterator insert(iterator iter, const T& val)
    {
        if (iter.ptr == pFirst) {
            add(val);
            return iterator{ nullptr };
        }

        NodeList<T>* tmp = new NodeList<T>();
        tmp->key = val;
        tmp->pNext = iter.ptr;
        iter.prev_ptr->pNext = tmp;
        iter.ptr = tmp;
        return iter;
    }

    void erase(iterator iter)
    {
        NodeList<T>* tmp = pFirst;
        NodeList<T>* prev;
        int pos = 0;
        while (tmp != iter.ptr) {
            prev = tmp;
            tmp = tmp->pNext;
            pos++;
        }
        if (pos == 0) {
            pFirst = pFirst->pNext;
            delete tmp;
            size--;
        }
        else {
            prev->pNext = tmp->pNext;
            delete tmp;
            size--;
        }
    }

    void erase_first_found(T p_)
    {
        NodeList<T>* p;
        p->key = p_;
        NodeList<T>* pCurrent = pFirst;
        NodeList<T>* prevCurrent = nullptr;
        for (; pCurrent->key != p->key; prevCurrent = pCurrent, pCurrent = pCurrent->pNext)
            ;
        if (pCurrent == nullptr) {
            return;
        }
        else {
            prevCurrent->pNext = pCurrent->pNext;
            delete pCurrent;
        }
    }

    void erase_list()
    {
        NodeList<T>* pCurrent = pFirst;
        while (pCurrent != nullptr) {
            pCurrent = pCurrent->pNext;
            delete  pFirst;
            pFirst = pCurrent;
        }
        size = 0;
    }

    List(T* arr) : size(0), pFirst(nullptr), pLast(nullptr)
    {
        if (arr == nullptr)
            throw(EqException(error_codes::k_EMPTY));
        for (int i = 0; i < sizeoff(arr) / sizeoff(arr[0]); i++) {
            add(arr[i]);
        }
    }

    List(std::vector<T>& v) : size(0), pFirst(nullptr), pLast(nullptr)
    {
        for (T tmp : v) {
            add(tmp);
        }
    }
    

    T& operator[](int index)
    {
        int n = 0;

        NodeList<T>* pCurrent = pFirst;
        while (pCurrent != nullptr) {
            if (index == n) {
                return pCurrent->key;
            }
            pCurrent = pCurrent->pNext;
            n++;
        }
    }

    inline bool operator==(const List& other)
    {
        if (size != other.size) {
            return false;
        }

        if (this == &other) {
            return true;
        }

        iterator it1 = this->begin();
        iterator it2 = other.begin();

        for (; it1 != this->end(); ++it1, ++it2) {
            if (it1.ptr->key != it2.ptr->key) {
                return false;
            }
        }
        return true;
    }

    inline bool operator!=(const List& other)
    {
        return !(*this == other);
    }

    List(List&& list) noexcept
    {
        size = list.size;
        pFirst = list.pFirst;
        pLast = list.pLast;

        list.pFirst = nullptr;
        list.pLast = nullptr;
        list.size = 0;
    }

    List& operator=(List&& list) noexcept
    {
        if (this != &list) {
            while (pFirst != nullptr) {
                NodeList<T>* tmp = pFirst;
                pFirst = pFirst->pNext;
                delete tmp;
            }

            size = list.size;
            pFirst = list.pFirst;
            pLast = list.pLast;

            list.size = 0;
            list.pFirst = nullptr;
            list.pLast = nullptr;
        }
        return *this;
    }

    List(const List& other)
    {
        pFirst = nullptr;
        pLast = nullptr;
        size = 0;

        if (other.pFirst == nullptr) {
            return;
        }

        pFirst = new NodeList<T>();
        pFirst->key = other.pFirst->key;
        NodeList<T>* pCurrent = pFirst;
        size = 1;

        for (NodeList<T>* pTmp = other.pFirst->pNext;
            pTmp != nullptr; pTmp = pTmp->pNext) {
            pCurrent->pNext = new NodeList<T>();
            pCurrent = pCurrent->pNext;
            pCurrent->key = pTmp->key;
            size++;
        }
        pCurrent->pNext = nullptr;
        pLast = pCurrent;
    }

    void clear()
    {
        NodeList<T>* pCurrent = pFirst;
        while (pCurrent != nullptr) {
            pCurrent = pCurrent->pNext;
            delete  pFirst;
            pFirst = pCurrent;
        }
        size = 0;
    }

    ~List()
    {
        erase_list();
    }

    List& operator=(const List& other)
    {
        if (this == &other) {
            return *this;
        }
        List tmp(other);
        std::swap(tmp, *this);
        return *this;
    }

    NodeList<T>* add(T item)
    {
        if (pLast == nullptr) {
            NodeList<T>* tmp = new NodeList<T>();
            pLast = tmp;
            pLast->key = item;
            pFirst = pLast;
        }
        else {
            NodeList<T>* tmp = new NodeList<T>();
            pLast->pNext = tmp;
            pLast = tmp;
            pLast->key = item;
        }
        pLast->pNext = nullptr;
        size++;
        return pLast;
    }

    NodeList<T>* get_node(int index) const
    {
        if (index == size - 1) {
            return pLast;
        }
        else if (index == 0) {
            return pFirst;
        }
        else {
            NodeList<T>* ptr = pFirst;
            while (index) {
                ptr = ptr->pNext;
                index--;
            }
            return ptr;
        }
    }

    inline int get_size() const
    {
        return size;
    }

    inline bool is_empty() const
    {
        return (size == 0);
    }
};

#endif