#pragma once

#include <deque>

template <class Item>
class List
{
    public:
        long Count() const { return static_cast<long>(_list.size()); };
        Item &Get(long index) const { return const_cast<Item &>(_list.at(index)); };
        Item &First() const { return _list.front(); };
        Item &Last() const { return _list.back(); };
        bool Includes(const Item& item) const;

        void Append(const Item& item) { _list.push_back(item); }
        void Prepend(const Item& item);

        void Remove(const Item &);

        void RemoveLast();
        void RemoveFirst();
        void RemoveAll();

        Item &Top() const;
        void Push(const Item&);
        Item &Pop();
    private:
        std::deque<Item> _list{};
};
