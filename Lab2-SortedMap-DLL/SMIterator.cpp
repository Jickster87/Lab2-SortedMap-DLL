#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    currentElem = map.head;
}

void SMIterator::first(){
    currentElem = map.head;
}

void SMIterator::next(){
    if (!valid()) {
        throw exception();
    }
    currentElem = currentElem->next;
}

bool SMIterator::valid() const{
    return currentElem != nullptr;
}

TElem SMIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return currentElem->elem;
}
