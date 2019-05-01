 /*
    * Description: Linked list that can 
    * Input: formated input file passed as command line arg
    * Output: console input with choices/output of choices
*/

#include <iostream>
#include <iomanip>      // setw
#include <fstream>      // fstream

using namespace std;

const int BEGINNING = 0;
const int END = 1;

template <class myT>

// Struct for creating a node
struct NodeType {
    NodeType() {        // initializing to null
        data = -1;
        next = nullptr;
        prev = nullptr;
    }
    myT data;
    NodeType* next;
    NodeType* prev;
};

/*
    * class_identifier: contains methods for manipulating nodes along with first and last node data members
    * constructors: List()
    * public functions: void Insert(const int& item);
                        void printForward(NodeType<myT>* head) const;
                        void backwardsPrint(NodeType<myT>* tail) const;
                        int forwardSearch(const int& item, NodeType<myT>*** arr, int listIndex);
                        int backwardSearch(const int& item, NodeType<myT>* tail, NodeType<myT>* head);
                        void forwardDelete(NodeType<myT>* head, int index);
                        void backwardsDelete(NodeType<myT>* tail, int index, NodeType<myT>* head);
                        void mergeLists(int l1index, int l2index, NodeType<myT>*** arr);
                        void deleteList(NodeType<myT>* head);
                        void setFitstNode(NodeType<myT>* first) {this->firstNode = first;}
                        void setLastNode(NodeType<myT>* last) {this->lastNode = last;}
    * static members:   none
*/

template <class myT>
class List {
    public:
        List();
        void Insert(const int& item);
        void printForward(NodeType<myT>* head) const;
        void backwardsPrint(NodeType<myT>* tail) const;
        int forwardSearch(const int& item, NodeType<myT>*** arr, int listIndex);
        int backwardSearch(const int& item, NodeType<myT>* tail, NodeType<myT>* head);
        void forwardDelete(NodeType<myT>* head, int index);
        void backwardsDelete(NodeType<myT>* tail, int index, NodeType<myT>* head);
        void mergeLists(int l1index, int l2index, NodeType<myT>*** arr);
        void deleteList(NodeType<myT>* head);
        NodeType<myT>* getFirstNode()const {return firstNode;}
        NodeType<myT>* getLastNode()const {return lastNode;}
        void setFitstNode(NodeType<myT>* first) {this->firstNode = first;}
        void setLastNode(NodeType<myT>* last) {this->lastNode = last;}
    private:
        int numNodes;
        NodeType<myT> *firstNode;
        NodeType<myT> *lastNode;
};

// constructor
template <class myT>
List<myT>::List() {
    numNodes = 0;
    firstNode = nullptr;
    lastNode = nullptr;
}

// inserts node, taking into consideration different possible areas of insertion
template <class myT>
void List<myT>::Insert(const int& item){

    // step 1: create a new node
    NodeType<myT> *newNode = new NodeType<myT>;
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

// prints linked list in the forward direction
template <class myT>
void List<myT>::printForward(NodeType<myT>* head) const {
    if (head == nullptr){return;}           // if empty list, don't do anything
    if (head == lastNode) {                 // continue to last node
        cout << head->data;                 // print the last node without the ->
        return;
    } else {
        cout << head->data << "->";         // print all elements it encouters
        printForward(head->next);           // recurse
    }
}

// prints linked list in the backward direction
template <class myT>
void List<myT>::backwardsPrint(NodeType<myT>* tail) const {
    if (tail == nullptr) {return;}          // if empty list, don't do anything
    if (tail == firstNode) {                // continue to the first (which in this case is last) node
        cout << tail->data;                 // print that node without the ->
        return;
    } else {
        cout << tail->data << "->";         // print all elements it encounters
        backwardsPrint(tail->prev);         // recurse
    }
}

// searches in the forward direction for the item the user specifies
template <class myT>
int List<myT>::forwardSearch(const int& item, NodeType<myT>*** arr, int listIndex) {
    NodeType<myT>* currNode = arr[listIndex][0];    // setting the current node to the head of the desired linked list
    int index = 0; 
    while (currNode != nullptr) {                   // continue until we're at the end of the list
        if (currNode->data == item) {               // if we found it
            return index;                           // return the index
        } else {
            currNode = currNode->next;              // increment the loop
            index++;                                // add to the index
        }
    }
    // the item is not in the list
    cout << "ERROR: item not found";                // print out error statement
    return -1;
}

// searches in backward direction for the item the user specifies
template <class myT>
int List<myT>::backwardSearch(const int& item, NodeType<myT>* tail, NodeType<myT>* head) {
    int index = 0; 
    if (tail->data == item) {                               // if found
        return index;
    } else if (tail == head) {                              // if we traversed entire array (no item)
        cout << "ERROR: item not found";
        return -1;
    } else {
        return backwardSearch(item, tail->prev, head) + 1;  // incrementing the index
    }
    
}

// traverses linked list in forward direction and deleted element at index
// assuming no invalid index is given
template <class myT>
void List<myT>::forwardDelete(NodeType<myT>* head, int index) {
    NodeType<myT>* curr;
    NodeType<myT>* prev;
    if (head == nullptr) {  // empty list
        cout << "ERROR: list is empty" << endl;
        return;
    } else if (index == 0) {                                    // first node is the one to be deleted
        curr = head;
        firstNode = firstNode->next;                            // move to next element
        if (firstNode!=nullptr) firstNode->prev = nullptr;      // set its previous to null (making it the first element)
        numNodes--;                                             
        cout << "Deleted Item: " << curr->data << endl;         // confirm to user
        delete curr;
    } else {                                                    // element is either in the body of linked list or the last item
        curr = head;
        int count = 0;
        while (count < index) {                                  // find the element iteratively
            count++;
            curr = curr->next;
        }
        if (curr->next == nullptr) {                             // if its the last item
            prev = curr->prev;
            prev->next = nullptr;                               // setting it to be the last (pointing to null instead of last item)
            lastNode = prev;
            cout << "Deleted Item: " << curr->data << endl;
            delete curr;
            numNodes--;
            
        } else {                                                // if its somethere in the list
            prev = curr->prev;                                  // initializing previous reference point
            prev->next = curr->next;                            // set the prev to point to the current next, skipping the current
            curr->next->prev = prev;                            // set the next link to point back to the previous, skipping the current
            cout << "Deleted Item: " << curr->data << endl;
            delete curr;
            numNodes--;
        }
    }
}

// recursively searches for user's index and deletes it from the linked list
// assuming no invalid index is given
template <class myT>
void List<myT>::backwardsDelete(NodeType<myT>* tail, int index, NodeType<myT>* head) {
    NodeType<myT>* curr;
    NodeType<myT>* next;
    if (head == nullptr) {                                      // empty list
        cout << "ERROR: list is empty" << endl;
        return;
    }
    if (index==0) {                                             // first node is the one to be deleted
        curr = tail;
        lastNode = lastNode->prev;
        if (lastNode!=nullptr) lastNode->next = nullptr;        // make the node before last the first node (last in proper direction)
        numNodes--;
        cout << "Deleted Item: " << curr->data << endl;
        delete curr;
        return;
    }
    if (index == 1) {                                           // once we find the list
        curr = tail->prev;
        if (curr->prev == nullptr) {                            // if its the last item
            next = curr->next;
            next->prev = nullptr;                               // setting that node to be the last
            firstNode = next;
            cout << "Deleted Item: " << curr->data << endl;
            delete curr;
            numNodes--;
        } else {                                                // if its somethere in the list
            next = curr->next;                                  // initializing previous reference point
            next->prev = curr->prev;                            // set the prev to point to the current next, skipping the current
            // if (curr->next != nullptr) {
            curr->prev->next = next;                            // set the next link to point back to the previous, skipping the current
            cout << "Deleted Item: " << curr->data << endl;
            delete curr;
            numNodes--;
        }
    }
    else {
        backwardsDelete(tail->prev, index-1, head);             // recurse
    }
}

template <class myT>
void List<myT>::mergeLists(int l1index, int l2index, NodeType<myT>*** arr) {
    if (l1index == l2index) {                                   // if merging itself into itself
        cout << "Merged List " << l1index << " and " << l2index << endl; 
        return;                                                 // don't do anything
    }
    if (arr[l1index][0]!=nullptr && arr[l2index][0]!=nullptr){  // prevent empty lists from being merged into
        NodeType<myT>* temp = arr[l1index][1];
        arr[l1index][1]->next = arr[l2index][0];                // connect the two linked lists
        arr[l1index][1]->next->prev = temp;
        arr[l1index][1] = arr[l2index][1];                      // set the end of the first linked list to the end of the second linked list
        arr[l2index][0] = nullptr;                              // set the start of the second linked list to null
        arr[l2index][1] = nullptr;                              // set the end of the second linked list to NULL
        cout << "Merged List " << l1index << " and " << l2index << endl;
    } else {
        cout << "ERROR: One of your lists is empty!" << endl;
    }
}

template <class myT>
void List<myT>::deleteList(NodeType<myT>* head) {
    if (head==NULL){                                        // if at the last item     
        return;                                             // end recursion
    } else {
        deleteList(head->next);                             // recurse
        delete head;                                        // delete the nodes
    }
}

 /*
    * function_identifier:  dynamically allocates 2d array of pointers to Nodes
    *                       Node at 0th index is head of the linked list
    *                       Node at 1st index is tail of the linked list
    * parameters:           number of lists to make
    * return value:         the array
*/
template <class myT>
NodeType<myT>*** createArr(int numberOfLists) {
    NodeType<myT>*** arr = new NodeType<myT>**[numberOfLists];
    for (int i = 0; i < numberOfLists; i++)
        arr[i] = new NodeType<myT>*[2];
    return arr;
}

 /*
    * function_identifier:  provides console output for the menu
    * parameters:           none
    * return value:         none
*/
void menu() {
    cout << left << setw(25)<< "List Commands "  << "(0)" << endl;
    cout << left << setw(25)<< "Forward Search "  << "(1)" << endl;
    cout << left << setw(25)<< "Backwards Search "  << "(2)" << endl;
    cout << left << setw(25)<< "Forward Delete Index "  << "(3)" << endl;
    cout << left << setw(25)<< "Backward Delete Index "  << "(4)" << endl;
    cout << left << setw(25)<< "Merge Lists "  << "(5)" << endl;
    cout << left << setw(25)<< "Delete Lists "  << "(6)" << endl;
    cout << left << setw(25)<< "Forward Print Lists"  << "(7)" << endl;
    cout << left << setw(25)<< "Backward Print Lists"  << "(8)" << endl;
    cout << left << setw(25)<< "Exit Program"  << "(9)" << endl;
    cout << endl;
}

/*
    * function_identifier:  creates linked list by inserting the data into the nodes
    * parameters:           input file stream, number of lists, array of linked lists
    * return value:         none
*/
template <class myT>
void inputData(ifstream& inputFile, int numberOfLists, List<myT>l[]) {
    int count = 0;
    while (count < numberOfLists) {
        int numItems;
        inputFile >> numItems;
        for (int i = 0; i < numItems+1; i++) {
            if (i == 0){ l[count].Insert(numItems);
            } else {
                myT data; 
                inputFile >> data;
                l[count].Insert(data);
            }
        }
        count++;
    }
}

/*
    * function_identifier:  calls functions that create the linked lists
    *                       provides console output to the user
    * parameters:           command line arguments
    * return value:         0
*/
int main (int argc, char *argv[]) {
    ifstream inputFile(argv[1]);                            // input file is second command line argument
    int numberOfLists;
    inputFile >> numberOfLists;                             // storing first element

    List<int>l[numberOfLists];                              // creating array of linked lists

    NodeType<int>*** arr = createArr<int>(numberOfLists);   // creating the 2d array
    
    inputData(inputFile, numberOfLists, l);                 // poulating linked lists
    
    for (int i = 0; i < numberOfLists; i++) {               // populating nodes with initial (nullptr) values
        arr[i][0] = l[i].getFirstNode();
        arr[i][1] = l[i].getLastNode();
    }

    // creating the menu
        cout << "Available Options: " << endl << endl;
        menu();
        while (true) {
            int input;
            cout << "Enter Command: ";
            cin >> input;
            switch(input) {
                    case 0: 
                        menu();
                        break;
                    case 1:     // forward search                           
                        int listIndex;
                        int toSearchFor;
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "Enter Item to search for: ";
                        cin >> toSearchFor;
                        cout << "Item Found at Index: " << l[listIndex].forwardSearch(toSearchFor, arr, listIndex) << endl;
                        cout << endl;
                        break;
                    case 2:     // backward search
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "Enter Item to search for: ";
                        cin >> toSearchFor;
                        cout << "Item Found at Index: " << l[listIndex].backwardSearch(toSearchFor, arr[listIndex][1], arr[listIndex][0]) << endl;
                        cout << endl;
                        break;
                    case 3:     // forward delete index
                        int index;
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "Enter Index: ";
                        cin >> index;
                        l[listIndex].forwardDelete(arr[listIndex][0], index);
                        
                        arr[listIndex][0] = l[listIndex].getFirstNode();    // update the list
                        arr[listIndex][1] = l[listIndex].getLastNode();
                        cout << endl;
                        break;
                    case 4:     // backward delete index
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "Enter Index: ";
                        cin >> index;
                        l[listIndex].backwardsDelete(arr[listIndex][1], index, arr[listIndex][0]);

                        arr[listIndex][0] = l[listIndex].getFirstNode();    // update the list
                        arr[listIndex][1] = l[listIndex].getLastNode();
                        cout << endl;
                        break;
                    case 5:     // merge
                        int secondIndex;
                        cout << "Enter List Index to Merge Into (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "Enter Second List Index to Merge (Available 0-" << numberOfLists-1<< "): ";
                        cin >> secondIndex;
                        l[listIndex].mergeLists(listIndex, secondIndex, arr);
                        l[listIndex].setFitstNode(arr[listIndex][0]);
                        l[listIndex].setLastNode(arr[listIndex][1]);

                        l[secondIndex].setFitstNode(arr[secondIndex][0]);
                        l[secondIndex].setLastNode(arr[secondIndex][1]);
                        cout << endl;
                        break;
                    case 6:     // delete
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        l[listIndex].deleteList(arr[listIndex][0]);
                        for (int i = listIndex; i < numberOfLists-1; i++) {        // update the list
                            arr[i][0] = arr[i+1][0];
                            arr[i][1] = arr[i+1][1];
                        }
                        numberOfLists--;   
                        for (int i = 0; i < numberOfLists; i++) {
                            l[i].setFitstNode(arr[i][0]);
                            l[i].setLastNode(arr[i][1]);
                        }   
                        cout << "Deleted List " << listIndex << endl;
                        cout << endl; 
                        break;
                    case 7:     // forward print list
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "List: " << listIndex << endl;
                        l[listIndex].printForward(arr[listIndex][0]);
                        cout << endl << endl;
                        break;
                    case 8:     // backward print list
                        cout << "Enter List Index (Available 0-" << numberOfLists-1<< "): ";
                        cin >> listIndex;
                        cout << "List: " << listIndex << endl;
                        l[listIndex].backwardsPrint(arr[listIndex][1]);
                        cout << endl << endl;
                        break;
                    case 9:     // exit the program
                        for (int i = 0; i < numberOfLists; i++) {
                            cout << "List: " << i << endl;
                            l[i].printForward(arr[i][0]);
                            cout << endl;
                        }
                        cout << endl << "Hasta la vista, baby!" << endl;
                        return 0;
                        break;
                    default: break;
            }
        }
    return 0;
}