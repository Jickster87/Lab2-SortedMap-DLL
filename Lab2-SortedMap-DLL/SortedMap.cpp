#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    head = tail = nullptr;
    rel = r;
    totalPairs = 0;
}

TValue SortedMap::add(TKey k, TValue v) {
	//elem exists , replace old value
    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == k) {
            TValue oldVal = current->elem.second;
            current->elem.second = v;
            return oldVal;
        }
        current = current->next;
    }
    //elem doesn't exist
    TElem newElem = std::make_pair(k, v);
    Node * newNode = new Node(newElem);
    
    // Handle case where list is empty
    if (head == nullptr) {
        head = tail = newNode;
        totalPairs++;
        return NULL_TVALUE;
    }
    
    //go to correct spot in list
    current = head;
    while (current != nullptr && rel(current->elem.first, k)) {
        current = current->next;
    }
    
    //head, tail, or in between cases
    if (current == head) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (current == nullptr) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else {
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev != nullptr) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
        if (current == head) {
            head = newNode;
        }
    }
    
    totalPairs++;
    return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    Node * current = head;
    
    //go to correct spot in list
    while (current != nullptr && current->elem.first != k) {
        current = current->next;
    }
    //if current is null , elem not found case
    if (current == nullptr)
    {
       return NULL_TVALUE;
    }
    
    TValue removedValue = current->elem.second;
    //if it's first element (head) case
    if (current == head) {
       head = current->next;
       if (head != nullptr)
       {
           head->prev = nullptr;
       }
       else {
           tail = nullptr;
       }
    }
    //if it's last element (tail) case
    else if (current == tail)
    {
        tail = current->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    }
    //if it's a middle element in the list
    //link the neighbouring elements together bypassing the current
    //node you want to get rid of
    else
    {
       current->next->prev = current->prev;
       current->prev->next = current->next;

    }
    
    delete current;
    totalPairs--;
    return removedValue;
}

TValue SortedMap::search(TKey k) const {
    Node * current = head;
    while (current != nullptr) {
        if (current->elem.first == k) {
            return current->elem.second;
        }
        current = current->next;
    }
    return NULL_TVALUE;
}

int SortedMap::size() const {
    return totalPairs;
}

bool SortedMap::isEmpty() const {
    return totalPairs == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}
