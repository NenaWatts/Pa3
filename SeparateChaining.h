#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
public:
    explicit ChainingHash(int size = 101) : currentSize{ 0 }
    {
        {theLists.resize(101); }
    }

    bool contains(const HashedObj& x) const
    {
        auto& chooseList = theLists[myhash(x)];
        return find(begin(chooseList), end(chooseList), x) != end(chooseList);
        // Figure 5.9 in textboo
    }

   void makeEmpty()
    {
        for (auto& thisL : theLists)
        {
            thisL.clear();
        }
        
        //Figure 5.9 in textbook
    }

    bool insert(const HashedObj& x)
    {
        auto& chooseList = theLists[myhash(x)];
        if (find(begin(chooseList), end(chooseList), x) != end(chooseList))
        {
            return false;
        }
        chooseList.push_back(x);
        if (++currentSize > theLists.size())
        {
            rehash();
        }

        // TODO: refer to Figure 5.10 in textbook
        // this "insert" function accepts Lvalues
        return true;
    }

    bool insert(HashedObj&& x)
    {
        auto& chooseList = theLists[myhash(x)];
        if (find(begin(chooseList), end(chooseList), x) != end(chooseList))
        {
            return false;
        }
         if (++currentSize > theLists.size())
        {
            rehash();
        }
        chooseList.push_back(std::move(x));

       
        // TODO: this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
        return true;
    }

    bool remove(const HashedObj& x)
    {
        auto& chooseList = theLists[myhash(x)];
        auto itr = find(begin(chooseList), end(chooseList), x);
        if (itr == end(chooseList))
        {
            return false;
        }
        chooseList.erase(itr);
        --currentSize;
        return true;
        // TODO: refer to Figure 5.9 in textbook
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
        return theLists.size();
    }
    //enum EntryType { ACTIVE, EMPTY, DELETED };
private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int currentSize;

    void rehash()
    {
        vector<list<HashedObj>> oldL = theLists;
        
        theLists.resize(nextPrime(2 * theLists.size()));
        
        for (auto& chooseList : theLists)
        {
            chooseList.clear();
        }
        currentSize = 0;
        for (auto& chooseList : oldL)
        {
            for (auto&x : chooseList)
            {
                insert(std::move(x));
            }
        }
        
    }

    size_t myhash(const HashedObj& x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

    double loadFactor() const
    {
        return static_cast<double>(currentSize) / theLists.size();
    }
       
};

#endif
