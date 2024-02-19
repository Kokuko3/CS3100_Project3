#include "sequence.h"

//----------------------------------------------------------------
// Mason McDaniel
// Project 3: Linked Sequence Data Structure
//    FILE: Sequence.cpp
//    Sequence class is implemented as a doubly linked list that supports random access like an array,
//    but also allows dynamic insertion and removal of new elements.
//----------------------------------------------------------------

// -----------------------------------------------
// Constructor for Sequence Class
//      Input: sz -- size of the sequence
// -----------------------------------------------
Sequence::Sequence(size_type sz)
{

    numElts = sz;

    if (sz == 0)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = new SequenceNode();
        tail = head;
    }

    // Attach each node to the list and link it to the previous node's
    for (unsigned int i = 0; i < sz - 1; i++)
    {
        tail->next = new SequenceNode();
        tail->next->prev = tail;
        tail = tail->next;
    }
}

// -----------------------------------------------
// Copy Constructor for Sequence Class
//      Input: s -- sequence to copy
// -----------------------------------------------
Sequence::Sequence(const Sequence &s)
{
    if(s.size() == 0){
        head = nullptr;
        tail = nullptr;
    }
    else if (s.size() == 1){
        SequenceNode * current = s.head;
        head = new SequenceNode();
        tail = head;
        head->elt = current->elt;
    }
    else {
        SequenceNode * current = s.head;
        head = new SequenceNode();
        tail = head;
        head->elt = current->elt;
        current = current->next;
        while (current != nullptr){
            tail->next = new SequenceNode();
            tail->next->elt = current->elt;
            tail->next->prev = tail;
            tail = tail->next;
            current = current->next;
        }
    }
}

// -----------------------------------------------
// Destructor for Sequence Class
//      Destroys all items in the sequence and releases
//      the memory associated with the sequence
// -----------------------------------------------
Sequence::~Sequence()
{
    clear();
}

// -----------------------------------------------
// Override operator =
//      Override's the = operator to allow for a sequence
//      to be replaced by a deep copy.
// -----------------------------------------------
// TODO
Sequence &Sequence::operator=(const Sequence &s)
{
    return *this;
}

// ---------------------------------------------------------------------------
// Override operator []
//      Inputs: position -- The position of the item in the list.
//          Must satisfy condition: position >= 0 && position <= last_index().
//      Returns: A reference to the item at index position in the sequence.
//          throws an exception if the position is outside the bounds of the sequence
// --------------------------------------------------------------------------
Sequence::value_type &Sequence::operator[](size_type position)
{

    // Local variables
    SequenceNode *current = head;

    // Walk through the list until current points at position
    for (unsigned int i = 0; i < position; i++)
    {
        if (current == nullptr)
        {
            throw exception();
        }
        current = current->next;
    }

    // Exception if outside the list
    if (current == nullptr || position < 0)
    {
        cout << "There is no element: " << position << endl;
        throw exception();
    }
    else
    {
        return current->elt;
    }
}

// ---------------------------------------------------------------------------
// push_back() -- grows the sequence by adding values to the end.
//      Inputs: value -- The value of item is append to the sequence.
// --------------------------------------------------------------------------
void Sequence::push_back(const value_type &value)
{
    // Connects the node to the position after
    // tail and makes that node the new tail.
    if (size() > 0)
    {
        tail->next = new SequenceNode();
        tail->next->prev = tail;
        tail = tail->next;
        tail->elt = value;
        numElts++;
    }

    // If there is only one node, point head and tail at that node.
    else
    {
        tail = new SequenceNode();
        head = tail;
        tail->elt = value;
        numElts++;
    }
}

// ---------------------------------------------------------------------------
// pop_back -- grows the sequence by adding values to the end.
//      Inputs: value -- The value of item is append to the sequence.
// --------------------------------------------------------------------------
void Sequence::pop_back()
{
    SequenceNode *to_delete = tail;
    if (head != nullptr)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete to_delete;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    numElts--;
}

// ---------------------------------------------------------------------------
// Insert -- The data is inserted at the designated position,
//           and the remaining items in the sequence are shifted to the right.
//      Inputs:
//          position -- The position of the item in the list.
//              Must satisfy condition: position >= 0 && position <= last_index().
//
//          value -- the value (elt) to be added to the sequence node inserted.
// --------------------------------------------------------------------------
void Sequence::insert(size_type position, value_type value)
{
    // Exception if position is out of range.
    if (position > size() || position < 0)
    {
        cout << "No element " << position << endl;
        throw exception();
    }

    // Create node to be added and a pointer to itterate.
    SequenceNode *new_node = new SequenceNode();
    SequenceNode *current = head;

    // Assign value to new element
    new_node->elt = value;

    // If no items in the list or at the end, push_back.
    if (size() == 0 || position == size())
    {
        push_back(value);
        delete new_node;
    }

    // If first item, change it to be new head node.
    else if (position == 0)
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }

    // Move to position and insert the node there.
    else
    {
        for (unsigned int i = 0; i < position - 1; i++)
        {
            current = current->next;
        }
        current->next->prev = new_node;
        new_node->next = current->next;
        new_node->prev = current;
        current->next = new_node;
    }
}

// ---------------------------------------------------------------------------
// front -- rerturns the element at the head of the sequence
//      Returns: value -- The value of item at head of sequence.
// --------------------------------------------------------------------------
const Sequence::value_type &Sequence::front() const
{
    if (head == nullptr)
    {
        throw exception();
    }
    else
    {
        return head->elt;
    }
}

// ---------------------------------------------------------------------------
// back -- rerturns the element at the tailof the sequence
//      Returns: value -- The value of item at tail of sequence.
// --------------------------------------------------------------------------
const Sequence::value_type &Sequence::back() const
{
    if (head == nullptr)
    {
        throw exception();
    }
    else
    {
        return tail->elt;
    }
}

// ---------------------------------------------------------------------------
// empty -- returns whether the sequence is empty or not
//      Returns: bool -- True if sequence empty, false if not.
// --------------------------------------------------------------------------
bool Sequence::empty() const
{
    bool empty = false;
    if (head == nullptr)
    {
        empty = true;
    }
    return empty;
}

// ---------------------------------------------------------------------------
// size -- returns the size of the sequence
//      Returns: numElts -- the number of elements in the sequence.
// --------------------------------------------------------------------------
Sequence::size_type Sequence::size() const
{
    return numElts;
}

// ---------------------------------------------------------------------------
// clear -- clears all elements in the sequence
//      Returns: numElts -- the number of elements in the sequence.
// --------------------------------------------------------------------------
void Sequence::clear()
{
    // Point current at head
    SequenceNode *current = head;
    // iterate through sequence and delete all nodes
    while (current != nullptr)
    {
        SequenceNode *to_kill_next = current->next;
        delete current;
        current = to_kill_next;
    }
    // Set sequence header
    head = nullptr;
    tail = nullptr;
    numElts = 0;
}

// ---------------------------------------------------------------------------
// Erase -- removes specified elements of a Sequence
//      Inputs:
//          position -- The position of the first element in the list.
//              Must satisfy condition: position >= 0 && position <= last_index().
//
//          count -- How many elements need to be erased.
// --------------------------------------------------------------------------
void Sequence::erase(size_type position, size_type count)
{

    // Throw error if position is outside of the seqeunce
    if (position > size() || position < 0)
    {
        cout << "No element " << position << endl;
        throw exception();
        // Throw error if no elements in the seqeunce
    }
    //Nothing in list
    else if (size() == 0)
    {
        cout << "No elements to erase" << endl;
        throw exception();
    }
    else
    {
        //If there is only one element in the list to be deleted.
        if(position == 0 && count == 1){
            SequenceNode * to_delete = head;
            head = head->next;
            head->next->prev = nullptr;
            delete to_delete;
        } 
        
        else{

            // Point start at head
            SequenceNode *start = head;

            // Move start to position
            for (unsigned int i = 0; i < position; i++)
            {
                if (start->next == nullptr)
                {
                    cout << position << " is outside of the sequence" << endl;
                    throw exception();
                }
                else
                {
                    start = start->next;
                }
            }

            // Point end at start
            SequenceNode *end = start;

            // Move end to 'count' positions away from start.
            // break if there is nothing else left in the list.
            for (unsigned int i = 0; i < count - 1; i++)
            {
                if (end->next == nullptr)
                {
                    break;
                }
                else
                {
                    end = end->next;
                }
            }

            // Now that start and end are in place, connect the rest of the list together.
            
            //If removing all items in the list
            if(position == 0 && count == size()){
                clear();
                
            }
            else{
                // If starting at the beginning of the list:
                if (position == 0)
                {
                    head = end->next;
                    end->next->prev = nullptr;
                }

                // If there are still items left at the end after the erase:
                else if (end->next != nullptr)
                {
                    start->prev->next = end->next;
                    end->next->prev = start->prev;
                }

                // If there are no elements left at the end of erase:
                else
                {
                    tail = start->prev;
                    start->prev->next = nullptr;
                }

                while (start != end)
                {
                    if (end->next == nullptr)
                    {
                        break;
                    }
                    SequenceNode *to_kill_next = start->next;
                    delete start;
                    start = to_kill_next;
                }
                delete start;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// print -- print all elements in the sequence.
//      Input: os -- ostream to print to.
// ---------------------------------------------------------------------------
void Sequence::print(ostream &os) const
{
    SequenceNode *current = head;
    if (head == nullptr)
    {
        os << "There are no elements in the list.";
    }
    while (current != nullptr)
    {
        os << current->elt << " ";
        current = current->next;
    }
    os << endl;
}

// Don't modify, do the output in the print() method
ostream &operator<<(ostream &os, const Sequence &s)
{
    s.print(os);
    return os;
}
