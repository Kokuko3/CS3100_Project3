#include <iostream>
#include "sequence.h"

using namespace std;
int main(){
    Sequence test_sequence(5);  // create a Sequence of length 5 (indexes 0 through 4)
    test_sequence[0] = 1;
    test_sequence[1] = 2;
    test_sequence[2] = 3;
    test_sequence[3] = 4;
    test_sequence[4] = 5;
    // cout << "Size: " << test_sequence.size() << endl;
    // test_sequence.print(cout);
    // test_sequence.push_back(20);
    // test_sequence.print(cout);
    test_sequence.insert(5,6);
    test_sequence.print(cout);
    test_sequence.erase(2,1);
    test_sequence.print(cout);
}