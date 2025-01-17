//
//	priority.h
//
//  Finn Le Var
//
#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

//
// Header only priority vector class
//
// T    is the data type that we're storing
// TNum is the data type that we're using as our priority
//
// TODO : Maybe replace all the throws with returns
// TODO : let us pass a custom sorting function, in case we want to sort backwards or something
//
template <typename T, typename TNum>
class CPriorityVector
{
private:

    // Our vector, priority and the element
    std::vector<std::pair<TNum, T>> m_items;

public:

    //
    // Nested iterator class so that when iterating over our priority vector it
    // only returns the actual item we're storing and not the whole pair that also
    // contains the priority
    //
    class CPriorityVectorIterator
    {
    private:

        // The iterator
    	typename std::vector<std::pair<TNum, T>>::iterator it_;

    public:

        // Aliases for readability
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        CPriorityVectorIterator(typename std::vector<std::pair<TNum, T>>::iterator it) : it_(it) {}

        //
        // Overload the dereference operator so that we only return the item and not the whole pair
        //
        reference operator*() const
        {
            // Item is the second item of our pair
            return it_->second;
        }

        //
        // Overload the increment operators
        //
        CPriorityVectorIterator& operator++()
        {
            ++it_;
            return *this;
        }

        CPriorityVectorIterator operator++(int)
        {
            CPriorityVectorIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        //
        // Overload the equality operators
        //
        bool operator==(const CPriorityVectorIterator& other) const { return it_ == other.it_; }
        bool operator!=(const CPriorityVectorIterator& other) const { return it_ != other.it_; }
    };

    //
    // Prints all the elements in our list, only used for printable types
    //
    void print() const
    {
        // TODO : Add check to see if item is printable

        for (const auto& [priority, item] : m_items)
        {
            std::cout << "Priority : " << priority << ", Item : " << item << "\n";
        }
    }

    //
    // Adds an item with a given priority to our list and inserts it at the right position
    //
    void push(const T& _item, TNum _priority)
    {
		auto pair = std::make_pair(_priority, _item);

        // Lambda to check two elements priorities against each other
        auto check = [](const auto& a, const auto& b)
        {
	        return a.first > b.first;
        };

		// Find the correct position for the new item with its priority
		auto pos = std::lower_bound(m_items.begin(), m_items.end(), pair, check);

		m_items.insert(pos, pair);
    }

    //
    // Removes the element at the top of our list
    //
    void pop()
    {
        // Remove the top item
        if (!m_items.empty())
            m_items.erase(m_items.begin());
    }

    //
    // Gets and returns the item at the given index
    //
    const T& at(size_t _index) const
    {
        if (_index >= m_items.size())
            throw std::out_of_range("Index out of range");

        return m_items.at(_index).second;
    }

    //
    // Gets and returns the element at the top of our list
    //
    const T& top() const
    {
        if (m_items.empty())
            throw std::runtime_error("CPriorityVector is empty");

        return m_items.front().second;
    }

    //
    // Removes the element at the given index
    //
    void erase(size_t _index)
    {
        if (_index >= m_items.size())
            throw std::out_of_range("Index out of range");

        m_items.erase(m_items.begin() + _index);
    }

    //
    // Removes all elements with the given priority
    //
    void erase_priority(TNum _priority)
    {
        // Lambda to check if the given item has the given priority
        auto check = [_priority](const std::pair<TNum, T>& _item)
        {
        	return _item.first == _priority;
        };

        // Find then remove them
        m_items.erase(std::remove_if(m_items.begin(), m_items.end(), check), m_items.end());
    }

    //
    // Returns true if our list is empty
    //
    bool empty() const
    {
        return m_items.empty();
    }

    //
    // Returns the size of our list
    //
    size_t size() const
    {
        return m_items.size();
    }

    //
    // Clears our list
    //
    void clear()
    {
        m_items.clear();
    }

    //
    // Iterator functions so that we can use a foreach loop
    //
    // TODO : Add a const iter for CPriorityVectorIterator, and add a non const version for the pair iter
    //

    // Iterator that only returns the item that we're storing
    CPriorityVectorIterator begin() { return CPriorityVectorIterator(m_items.begin()); }
    CPriorityVectorIterator end()   { return CPriorityVectorIterator(m_items.end()); }

    // Iterator that returns the whole pair of the priority and the item
    auto pair_begin() { return m_items.begin(); }
    auto pair_end()   { return m_items.end(); }

};

// Create an alias for readability
template<typename T, typename TNum>
using TPriority = CPriorityVector<T, TNum>;
