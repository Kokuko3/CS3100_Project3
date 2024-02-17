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

    for(unsigned int i=0; i < sz-1; i++){
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
    clear();
}


//TODO
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
    } 
    else {
        return current->elt;   
    }
}




void Sequence::push_back(const value_type& value)
{
    if(size() > 0){
        tail->next = new SequenceNode();
        tail->next->prev = tail;
        tail = tail->next;
        tail->elt = value;
        numElts++;
    } else {
        tail = new SequenceNode();
        head = tail;
        tail->elt = value;
        numElts++;
    }
}





void Sequence::pop_back()
{
    SequenceNode * to_delete = tail;
    if (head != nullptr){ 
        tail = tail->prev;
        tail->next = nullptr;
        delete to_delete;
    } 
    else if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    numElts--;
}




void Sequence::insert(size_type position, value_type value)
{
    if(position > size() || position < 0){
        cout << "No element " << position << endl;
        throw exception();
    }
    SequenceNode * new_node = new SequenceNode();
    SequenceNode * current = head;
    new_node->elt = value;
    if(size() == 0 || position == size()){
        push_back(value);
        delete new_node;
    }
    else if(position == 0){
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    else {
        for(unsigned int i = 0; i < position-1; i++){
            current = current->next;
        }
        current->next->prev = new_node;
        new_node->next = current->next;
        new_node->prev = current;
        current->next = new_node;
    }
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
    return numElts;
}





void Sequence::clear()
{
    SequenceNode * current = head; 
    while (current != nullptr){ 
        SequenceNode * killMeNext = current->next; 
        delete current; 
        current = killMeNext;
    }
    head = nullptr;
    tail = nullptr;
    numElts = 0;
}




//TODO
void Sequence::erase(size_type position, size_type count)
{   
    
}




void Sequence::print(ostream& os) const
{
    SequenceNode * current = head;
    if(head == nullptr){
        os << "There are not elements in the list.";
    }
    while (current != nullptr){
        os << current -> elt << " ";
        current = current->next ;
    }
    os << endl;
}




// Don't modify, do the output in the print() method
ostream& operator<<(ostream& os, const Sequence& s)
{
    s.print(os);
    return os;
}

