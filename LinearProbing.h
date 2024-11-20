#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

// this inplementation follows Figure 5.14 in textbook for quadratic probing
template <typename HashedObj> 
class ProbingHash
{
  public:
    explicit ProbingHash( int size = 101 ) : array( nextPrime( size ) ), currentSize{ 0 }
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.16 in textbook for quadratic probing
        return false;
    }

    void makeEmpty( )
    {
        // TODO: refer to Figure 5.15 in textbook for quadratic probing
    }

    bool insert( const HashedObj & x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
        return false;
    }
    
    bool insert( HashedObj && x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
        // this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
        return false;
    }

    bool remove( const HashedObj & x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
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
        return array.size();
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.16 in textbook for quadratic probing,
        // we need a version of linear probing that finds the position with the linear probing resolution
        return 0;
    }

    void rehash( )
    {
        // TODO: refer to Figure 5.22 in textbook for qudratic probing
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }


    double loadFactor()
    {
        // TODO: compute the load factor of hash table, defined on Page 198 of textbook
        return 0.0;
    }
};

#endif
