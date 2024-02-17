#include <iostream>
#include "sequence.h"

using namespace std;
int main(){
    Sequence test_sequence(5);
    cout << "Size: " << test_sequence.size() << endl;
    test_sequence.insert(5,15);
    test_sequence.print(cout);
}