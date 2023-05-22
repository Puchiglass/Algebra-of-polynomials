#include "list_table.h"
//void insert(const std::string& key, TableBody& data)
bool ListTable::insert(const std::string& key, TableBody& data_)
{
    TableString* ts = find_str(key);
    if (ts != nullptr) {
        return false;
    }
    TableString tmp(key, data_);
    data.insert(data.begin(), tmp);
    data_cnt++;
    return true;
}
bool ListTable::erase(const std::string& key)
{
    ListIterator<TableString> it = data.begin();
    for (; it != data.end(); ++it) {
        if ((*it).key == key)
        {
            data_cnt--;
            data.erase(it);
            return true;
        }
    }
    return false;
}
TableBody* ListTable::find(const std::string& key)
{
    TableString* tmp = (*this).find_str(key);
    if (tmp == nullptr) {
        return nullptr;
    }
    else {
        return &(tmp->body);
    }
}
TableString* ListTable::find_str(const std::string& key)
{
    /*for (ListIterator<TableString> it = data.begin(); it != data.end(); ++it) {
        ;
    }
	if(it==data.end())
		return nullptr;
	else
		return &(*it);*/
    ListIterator<TableString> it = data.begin();
    for (; it != data.end(); ++it) {
        if ((*it).key == key)
            return &*it;
    }
    // for (TableString tmp : data) {
        // if (tmp.key == key) {
            // return &tmp;
        // }
    // }
    return nullptr;
}