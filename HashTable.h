//
//  HashTable.h
//  Project5
//
//  Created by Kyle Lei on 25/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

template <typename T>
class HashTable {
    SortedList<SortedList<int>> buckets;
public:
    HashTable(int numBuckets){table=new T[numBuckets];}
    ~HashTable(){delete []table;}
    
    int hash(int,int)=0;
};

#endif /* HashTable_h */
