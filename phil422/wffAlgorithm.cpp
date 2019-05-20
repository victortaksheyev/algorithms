
#include <iostream>
#include <string>

const int NUM_OF_CONNECTIVES = 3;
const char connectives[NUM_OF_CONNECTIVES] = {'&', '|', '-'};



using namespace std;

int numConnectives(string wff, char operators[][2]);

int main() {
    string wff;
    char operators[10][2];

    cin >> wff;
    // cout << "the number of connectives is: " << numConnectives(wff, operators) << endl;
    for (int i = 0; i < numConnectives(wff, operators); i++) {
        cout << operators[i][0] << " ";
        cout << "index: " << operators[i][1];
    }
}


// A|B

// addParen()
// find the connective
// move one to the left and add parenths
// move one to the right and add parenths
// if there are already parenthesis, move 5 to the left/right

void addParen(string wff, char **operators, int numOpers) {
    int currentOperator = 0;
    if (currentOperator == numOpers+1) return;
    else {
        wff[operators[]]
    }
}

// scans wff and returns number of connectives
int numConnectives(string wff, char operators[][2]) {
    int count = 0;
    for (int i = 0; i < wff.length(); i++) {
        for (int j = 0; j < NUM_OF_CONNECTIVES; j++) {
            if (wff[i] == connectives[j]) {
                operators[count][0] = wff[i]; 
                operators[count][1] = i+48;    // storing the array at which the operator is at
                count++;
            }
        }
    }
    return count;
