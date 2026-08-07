#pragma once

#include <iterator.hpp>
#include <list.hpp>

template <class Item>
class ListIterator : public Iterator<Item>
{
    public:
        ListIterator(const List<Item>* aList) : _aList(aList) {};
        
        virtual void First() { index = 0; if( IsDone() ) return; _current = _aList->Get(index); };
        virtual void Next() { index++; if( IsDone() ) return; _current = _aList->Get(index); };
        virtual bool IsDone() const { return _aList->Count() == index; };
        virtual Item CurrentItem() const { return _current; };
    private:
        long index = 0;
        Item _current = nullptr;
        const List<Item> *_aList;
};