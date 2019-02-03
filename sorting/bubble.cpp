// bubble sort

#include <iostream>

using namespace std;

int main() {
    int nums[1000];
    int length = 0;
    
    while (cin >> nums[length])
        length++;

    bool swap = true;
    // dismissing bubble on last term(s) since they're sorted
    int j = 1;
    while (swap) {
        swap = false;
        for (int i = 0; i < length - j; i++) {
            if (nums[i] > nums[i+1]) {
                int temp;
                temp = nums[i];
                nums[i] = nums[i+1];
                nums[i+1] = temp;
                swap = true;
            }
        }
        j++;
    }
    
    for (int i = 0; i < length; i++) {
        cout << nums[i] << endl;
    }
    
    return 0;
}
