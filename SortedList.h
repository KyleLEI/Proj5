//
//  SortedList.h
//  Project5
//
//  Created by Kyle Lei on 24/11/2016.
//  Copyright © 2016 LEI Zhao. All rights reserved.
//

#ifndef SortedList_h
#define SortedList_h
#include <cstddef>
#include <stdexcept>

template <typename T>
class Node {
public:
    T content;
    Node* next;
    Node* prev;
    
    Node(T in_content=0, Node* in_next=NULL, Node* in_prev=NULL):
    content(in_content), next(in_next), prev(in_prev){}
    Node(const Node& src):content(src.content),next(src.next),prev(src.prev){}
};

template <typename T>
class SortedList { //operator> and == needs overloading for user-defined classes
    Node<T>* head;
    Node<T>* tail;
    int size;
    
public:
    SortedList(): head(NULL),tail(NULL),size(0){};
    ~SortedList();
    
    T* insert(const T&);
    T* insertRaw(const T&);
    Node<T>* find(const T&);
    bool remove(const T&); //true for successful removal
    bool removeNode(Node<T>*);
    
    Node<T>* getHead() const{return head;}
    Node<T>* getTail() const{return tail;}
    int getSize() const{return size;}
    bool isEmpty() const{return size==0;}
    T& operator[](int);
    
private:
    void initialize(const T& input);
    inline void insertFront(Node<T>* toBeInserted, Node<T>* node);
};

template<typename T>
SortedList<T>::~SortedList(){
    if(isEmpty()) return;
    while(size>1){
        head=head->next;
        delete head->prev;
        --size;
    }
    delete head;
}

template<typename T>
void SortedList<T>::initialize(const T& input){
    head=new Node<T>(input,NULL,NULL);
    tail=head;
    tail->next=head;
    tail->prev=head;
    head->next=tail;
    head->prev=tail;
}

template<typename T>
T* SortedList<T>::insert(const T& input){
    ++size;
    if(head==NULL){initialize(input); return &head->content;}
    Node<T>* newNode=new Node<T>(input);
    
    for(Node<T>* node=head;node!=tail;node=node->next){
        if(node->content>input){
            insertFront(newNode, node);
            return &newNode->content;
        }
    }
    if(tail->content>input){
        insertFront(newNode, tail);
        return &newNode->content;
    }
    
    tail->next=newNode; //if larger than all existing nodes, insert at tail
    newNode->prev=tail;
    newNode->next=head;
    tail=newNode;
    return &newNode->content;
}

template<typename T>
T* SortedList<T>::insertRaw(const T& input){
    ++size;
    if(head==NULL){initialize(input); return &head->content;}
    Node<T>* newNode=new Node<T>(input);
    tail->next=newNode;
    newNode->prev=tail;
    newNode->next=head;
    tail=newNode;
    return &newNode->content;
}

template<typename T>
void SortedList<T>::insertFront(Node<T>* toBeInserted, Node<T>* node){
    if(node->prev!=NULL){
        Node<T>* oldprev=node->prev;
        oldprev->next=toBeInserted;
        toBeInserted->prev=oldprev;
        node->prev=toBeInserted;
        toBeInserted->next=node;
    }else{
        node->prev=toBeInserted;
        toBeInserted->next=node;
        head=toBeInserted;
    }
}

template<typename T>
Node<T>* SortedList<T>::find(const T& target){
    if(size==0) return NULL;
    for(Node<T>* node=head;node!=tail;node=node->next){
        if(node->content==target)
            return node;
    }
    if(tail->content==target)
        return tail;
    return NULL;
}

template<typename T>
bool SortedList<T>::remove(const T& target){
    if(size<=0) return false;
    Node<T>* node=find(target);
    if(node==NULL) return false;
    --size;
    
    if(node==head){
        Node<T>* newhead=head->next;
        delete head;
        head=newhead;
        if(newhead!=NULL) newhead->prev=tail;
        else tail=NULL;
        return true;
    }
    if(node==tail){
        Node<T>* newtail=tail->prev;
        delete tail;
        tail=newtail;
        if(newtail!=NULL) newtail->next=head;
        else head=NULL;
        return true;
    }
    node->prev->next=node->next;
    node->next->prev=node->prev;
    delete node;
    return true;
}

template <typename T>
bool SortedList<T>::removeNode(Node<T>* node) {
    if(size<=0) return false;
    if(node==NULL) return false;
    --size;
    
    if(node==head){
        Node<T>* newhead=head->next;
        delete head;
        head=newhead;
        if(newhead!=NULL) newhead->prev=tail;
        else tail=NULL;
        return true;
    }
    if(node==tail){
        Node<T>* newtail=tail->prev;
        delete tail;
        tail=newtail;
        if(newtail!=NULL) newtail->next=head;
        else head=NULL;
        return true;
    }
    node->prev->next=node->next;
    node->next->prev=node->prev;
    delete node;
    return true;
}

template<typename T>
T& SortedList<T>::operator[](int n){
    if(isEmpty()) throw std::runtime_error("accessing empty list\n");
    if(n<size/2){
        Node<T>* node=head;
        for(int i=0;i<n;++i)
            node=node->next;
        return node->content;
    }
    if(n<size){
        Node<T>* node=tail;
        for(int i=0;i<(size-n-1);++i)
            node=node->prev;
        return node->content;
    }
    return tail->content;
}

#endif /* SortedList_h */
