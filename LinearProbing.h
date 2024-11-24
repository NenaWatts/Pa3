#pragma once
#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <utility>
#include "Employee.h"
#include "utils.h"

using namespace std;

// this inplementation follows Figure 5.14 in textbook for quadratic probing
template <typename HashedObj>
class ProbingHash
{
public:
    explicit ProbingHash(int size = 101) : array(nextPrime(size)), currentSize{ 0 }
    {
        makeEmpty();
    }

    bool contains(const HashedObj& x) const
    {
        return isActive(findPos(x));
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (auto& entry : array)
            entry.info = EMPTY;
        // Figure 5.15 in textbook for quadratic probing
    }

    bool insert(const HashedObj& x)
    {
        int currPos = findPos(x);
        if (isActive(currPos))
        {
            return false;
        }
        array[currPos].element = x;
        array[currPos].info = ACTIVE;
        
        if (++currentSize > array.size() / 2)
        {
            rehash();
        }

        //Figure 5.17 in textbook for quadratic probing
        return false;
    }

    bool insert(HashedObj&& x)
    {
        int currPos = findPos(x);
        if (isActive(currPos))
        {
            return false;
        }
        array[currPos].element = std::move(x);
        array[currPos].info = ACTIVE;

        if (++currentSize > array.size() / 2)
        {
            rehash();
        }
        // Figure 5.17 in textbook for quadratic probing
        // this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
        return false;
    }

    bool remove(const HashedObj& x)
    {
        int currPos = findPos(x);
        if (!isActive(currPos))
        {
            return false;
        }
        array[currPos].info = DELETED;
        return true;
        // Figure 5.17 in textbook for quadratic probing
        
    }

    double readLoadFactor()
    {
        return loadFactor();
    }

    double readCurrentSize()
    {
        return currentSize;
    }

    double readArraySize()
    {
        return array.size();
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj{ }, EntryType i = EMPTY)
            : element{ e }, info{ i } { }

        HashEntry(HashedObj&& e, EntryType i = EMPTY)
            : element{ std::move(e) }, info{ i } { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj& x) const
    {
        int offset = 1;
        int currPos = myhash(x) % array.size();
        while (array[currPos].info != EMPTY && array[currPos].element != x)
        {
            currPos += offset;
            offset += 2;
            if (currPos >= array.size())
            {
                currPos -= array.size();
            }
        }
        return currPos;
         
        //Figure 5.16 in textbook for quadratic probing,
        // we need a version of linear probing that finds the position with the linear probing resolution
        return currPos;
    }

    void rehash()
    {
        vector<HashEntry> oldarr = array;

        array.resize(nextPrime(2 * oldarr.size()));
        for (auto& entry : array)
        {
            entry.info = EMPTY;
        }
        currentSize = 0;
        for (auto& entry : oldarr)
        {
            if (entry.info == ACTIVE)
            {
                insert(std::move(entry.element));
            }   
            
        }
        //Figure 5.22 in textbook for qudratic probing
    }

    size_t myhash(const HashedObj& x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % array.size();
    }


    double loadFactor()
    {
        int count = 0;
        for (auto& entry : array)
        {
            if (entry.info == ACTIVE)
            {
                ++count;
            }
        }
        // defined on Page 198 of textbook
        return static_cast<double>(count)/array.size();
    }
};

#endif
