#include <iostream>
#include <fstream>

using namespace std;

// template <class myT>
struct NodeType {
    NodeType() {
        data = -1;
        next = nullptr;
        prev = nullptr;
    }

    int data;
    NodeType* next;
    NodeType* prev;
};

class List {
    public:
        List();
        void Insert(const int& item);
        void printForward(NodeType* head) const;
        
        NodeType* getFirstNode()const {return firstNode;}
        NodeType* getLastNode()const {return lastNode;}


    // private:
        int numNodes;
        NodeType *firstNode;
        NodeType *lastNode;
};

// constructor
List::List() {
    numNodes = 0;
    firstNode = nullptr;
    lastNode = nullptr;
}

void List::Insert(const int& item){
    // NodeType *current;
    // NodeType *beforeCurrent;

    // step 1: create a new node
    NodeType *newNode = new NodeType;
    newNode->data = item;               // store passed in item into the data

    // step 2: consider cases for inserting node
        // case 1: the linked list is empty
        if (firstNode == nullptr) {
            firstNode = newNode;        // since newNode is only node, 
            lastNode = newNode;         // it is both the first and the last node
        }
        // case 2: note empty
        else {
            lastNode->next = newNode;   // add node to the very end
            newNode->prev = lastNode;   // make it link back to previous node
            lastNode = newNode;         // set this new node to the last node (since it's at end of list)
        }
    numNodes++;                         // since we added, increment
}

void List::printForward(NodeType* head) const {
    if (head == lastNode) {
        cout << head->data;
        return;
    }
    else {
        cout << head->data << "->";
        printForward(head->next);
    }
}

NodeType*** createArr(int numberOfLists) {
    NodeType*** arr = new NodeType**[numberOfLists];
    for (int i = 0; i < numberOfLists; i++)
        arr[i] = new NodeType*[2];
    return arr;
}

int main (int argc, char *argv[]) {
    ifstream inputFile(argv[1]);    // input file is second command line argument
    int numberOfLists;
    inputFile >> numberOfLists;     // storing first element

    List l[numberOfLists];          // creating array of linked lists

    NodeType*** arr = createArr(numberOfLists); // creating the 2d array

    // populating 2d array


    // poulating linked lists
    int count = 0;
    while (count < numberOfLists) {
        int numItems;
        inputFile >> numItems;
        for (int i = 0; i < numItems+1; i++) {
            if (i == 0){ l[count].Insert(numItems);
                cout << numItems << " ";
            }
            
            else {
                int data; 
                inputFile >> data;
                cout << data << " ";
                l[count].Insert(data);
            }
            
        }
        cout << endl;
        count++;
    }

    for (int i = 0; i < numberOfLists; i++) {
        arr[i][0] = l[i].getFirstNode();
        arr[i][1] = l[i].getLastNode();
    }


    // for (int i = 0; i < numberOfLists; i++) {
    //     cout << ((l[i].getFirstNode())->data);
    // }
    for (int i = 0; i < numberOfLists; i++) {
        l[i].printForward(arr[i][0]);
        cout << endl;
    }
    
    

    return 0;
}
