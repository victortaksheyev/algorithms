//
//  main.cpp
//  philChecker
//
//  Created by Victor Taksheyev on 2/4/19.
//  Copyright © 2019 Victor Taksheyev. All rights reserved.
//

#include <iostream>
#include <string>

int WAYS_TO_WRITE = 0;

using namespace std;

void algorithm(int& WAYS_TO_WRITE, string formula);
void findConnectives(string formula);

int main() {
    string formula = "-PvQ";
    
    algorithm(WAYS_TO_WRITE, formula);
    findConnectives(formula);
    
    return 0;
}


void algorithm(int& WAYS_TO_WRITE, string formula) {
    int count = 0;
    for (int i = 0; i < formula.length(); i++) {
        count++;
    }
//    cout << count;
}

void findConnectives(string formula) {
    int connectives;
    int len = formula.length();
    string connectivesArr[len][2];
    
    
    
    for (int i = 0; i<len; i++) {
        for (int j =0; j<2; j++) {
            connectivesArr[i][j] = "x";
        }
    }
    for (int i = 0; i < len; i++) {
        if (formula[i] == '-' || formula[i] == '&' || formula[i] == 'v') {
            connectives++;
            connectivesArr[i][0] = to_string(i); // inputs the index of connective
            connectivesArr[i][1] = formula[i]; // inputs the connective
        }
    }
    
    for (int i = 0; i<len; i++) {
        for(int j =0; j<2; j++) {
            cout << connectivesArr[i][j] << " ";
        }
        cout << endl;
    }
    
}


