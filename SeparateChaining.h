#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
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
    explicit ChainingHash( int size = 101 ) : currentSize{ 0 }
      { theLists.resize( 101 ); }

    bool contains( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.9 in textbook
        return false;
    }

    void makeEmpty( )
    {
        // TODO: refer to Figure 5.9 in textbook
    }

    bool insert( const HashedObj & x )
    {
        // TODO: refer to Figure 5.10 in textbook
        // this "insert" function accepts Lvalues
        return false;
    }
    
    bool insert( HashedObj && x )
    {
        // TODO: this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
        return false;
    }

    bool remove( const HashedObj & x )
    {
        // TODO: refer to Figure 5.9 in textbook
        return false;
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

  private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int currentSize;

    void rehash( )
    {
        // TODO: refer to Figure 5.22 in textbook
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % theLists.size( );
    }

    double loadFactor()
    {
        // TODO: compute the load factor of hash table, defined on Page 198 of textbook
        return 0.0;
    }
};

#endif
