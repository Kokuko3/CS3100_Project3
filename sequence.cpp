#include "sequence.h"


Sequence::Sequence(size_type sz)
{   
    numElts = sz;

    if(sz == 0){
        head = nullptr;
        tail = nullptr;
    } else { 
        head = new SequenceNode(); 
        tail = head;  
    } 

    for(int i=0; i < sz-1; i++){
        tail->next = new SequenceNode();
        tail->next->prev = tail;
        tail = tail->next;
    }
}

//TODO
Sequence::Sequence(const Sequence& s)
{
    
} 

Sequence::~Sequence()
{
    SequenceNode * current = head; 
    while (current != nullptr){ 
        SequenceNode * killMeNext = current->next; 
        delete current; 
        current = killMeNext; 
    } 
}

Sequence& Sequence::operator=(const Sequence& s)
{
    return *this;
}

Sequence::value_type& Sequence::operator[](size_type position){
    SequenceNode * current = head;
    for(unsigned int i = 0; i < position; i++){
        if(current == nullptr){
            throw exception();
        }
        current = current->next;
    }
    if(current == nullptr){
            cout << "There is no element: " << position << endl;
            throw exception();
    } else {
        return current->elt;   }
}

void Sequence::push_back(const value_type& value)
{
    tail->next = new SequenceNode();
    tail->next->prev = tail;
    tail = tail->next;
    tail->elt = value;
}

//TODO
void Sequence::pop_back()
{
    SequenceNode * to_delete = tail;
    if (head != nullptr){ 
        tail = tail->prev;
        delete to_delete;
    } 
}

//TODO
void Sequence::insert(size_type position, value_type value)
{
    throw exception();
}

const Sequence::value_type& Sequence::front() const
{
    if(head == nullptr){
        throw exception();
    }
    else{
        return head->elt;
    }
}

const Sequence::value_type& Sequence::back() const
{
    if(head == nullptr){
        throw exception();
    }
    else{
        return tail->elt;
    }
}

bool Sequence::empty() const
{
    bool empty = false;
    if(head == nullptr){
        empty = true;
    }
    return empty;
}

Sequence::size_type Sequence::size() const
{
    SequenceNode * current = head;
    int i = 0;
    while(current != nullptr){
        i++;
        current = current->next;
    }
    return i;
}

//TODO
void Sequence::clear()
{

}

//TODO
void Sequence::erase(size_type position, size_type count)
{
    throw exception();
}

void Sequence::print(ostream& os) const
{
    SequenceNode * current = head;
    while (current != nullptr){
        os << current -> elt << endl;
        current = current->next ;
    }
}

// Don't modify, do the output in the print() method
ostream& operator<<(ostream& os, const Sequence& s)
{
    s.print(os);
    return os;
}

