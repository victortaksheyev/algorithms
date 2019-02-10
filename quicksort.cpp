#include <iostream>

using namespace std;

bool isXHere (int numbers[], int L, int U, int x);
int sum (int numbers[], int L, int U);

int main() {
    
    int numbers[7] = {10, 20, 30, 1, 3, 4, 5};
    
    /*
    1.base case
    2.recursive case
    */

    cout << isXHere(numbers, 0, 6, 4) << endl;
    cout << sum(numbers, 0, 7) << endl;
    return 0;
}

    
bool isXHere (int numbers[], int L, int U, int x) {
    // base case
    if (L == U) { // if there is 1 item in subarray
        if (numbers[L] == x) return true;
        else return false;
    } else {
        int mid = (L+U)/2;
        if(isXHere(numbers, L, mid, x)) return true;
        else return isXHere(numbers, mid+1, U, x);   
    }
}

int sum (int numbers[], int L, int U) {
    // base case
    if (L == U) { // this means we have 1 item in the group
        return numbers[L];
    } else {
        int mid = (L+U)/2;
        return sum(numbers, L, mid) + sum(numbers, mid+1, U);
    }
}