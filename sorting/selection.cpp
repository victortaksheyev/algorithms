// selection sort

#include <iostream>

using namespace std;

int main() {
    int nums[1000];
    int length = 0;
    
    while (cin >> nums[length])
        length++;

    int smallestI;
    
    for (int i = 0; i < length; i++) {
        smallestI = i;
        // i + 1 because starting at i would be comparing itself
        for (int j = i+1; j < length; j++) {
            if (nums[j] < nums[smallestI]) {
                smallestI = j;
            }
        }
        int temp;
        temp = nums[smallestI];
        nums[smallestI] = nums[i];
        nums[i] = temp;
    }
    
    for (int i = 0; i < length; i++) {
        cout << nums[i] << endl;
    }
    
    return 0;
}
