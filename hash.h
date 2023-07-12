#ifndef HASH_H
#define HASH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "user.h"
using namespace std;

enum EntryType { ACTIVE, EMPTY, DELETED };
const unsigned int primeNumbersArray[20] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23,29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

bool isPrime( int n );
int nextPrime( int n );

struct HashEntry
{
    User element;
    EntryType info;

    HashEntry( const User & e = User{ }, EntryType i = EMPTY )
        : element{ e }, info{ i } { }
        
    HashEntry( User && e, EntryType i = EMPTY )
        : element{ std::move( e ) }, info{ i } { }
};


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings


class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const User & x ) const
    {
        return isActive( findPos( x ) );
    }

    //function that returns the location of the user in the table (returns -1 if it doesn't exist)
    int search(const User& x){
        int locationOfUSer = findPos(x);
        if(isActive(locationOfUSer)){
            return locationOfUSer;
        }
        return -1;
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    bool insert( const User & x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }
    
    bool insert( User && x )
    {
            // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

            // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const User & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    void printArray(){
        for(int i = 0; i < array.size( ); i++){
            if(array[i].info == ACTIVE){

                array[i].element.getID().printEmailAdress();
                cout<<array[i].element.getUserName()<<endl;
                cout<<array[i].element.getPassword()<<endl;
                cout<<"-> "<<i<<endl<<endl;
            }
        }
    }


  private:
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const User & x ) const
    {
        int offset = 1;
        int keyOfX = KeyValue(x);
        int currentPos = hashValue(keyOfX);
        int keyOfElement = KeyValue(array[currentPos].element);

        while( array[ currentPos ].info != EMPTY &&
               keyOfElement != keyOfX )
        {
            currentPos += offset;  // Compute ith probe
            offset += 2;
            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    int KeyValue(const User & x ) const{
        int uniqueStringNumber = 0;
        for(int i = 0; i < x.getID().getName().size(); i++){
            char letter = toupper(x.getID().getName()[i]);
            uniqueStringNumber += primeNumbersArray[i] * letter - int('0');
        }
        return uniqueStringNumber;
    }

    int hashValue(int key) const{
        return key % array.size();
    }

    friend class ServerUser;
    friend class MailServer;
};

#endif