#pragma once

#include <iterator.hpp>
#include <list.hpp>

template <class Item>
class NullIterator : public Iterator<Item>
{
    public:
        NullIterator() { };
        
        void First() override { };
        void Next() override { };
        bool IsDone() const override { return true; };
        Item CurrentItem() const override { return nullptr; };
};