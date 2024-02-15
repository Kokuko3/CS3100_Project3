#include <iostream>
#include "sequence.h"

using namespace std;
int main(){
    Sequence test_sequence(3);
    test_sequence[0] = 1;
    test_sequence[1] = 2;
    test_sequence[2] = 3;
    test_sequence.push_back(20);
    cout << "Size: " << test_sequence.size() << endl;
    test_sequence.pop_back();
    cout << "Size: " << test_sequence.size() << endl;

}