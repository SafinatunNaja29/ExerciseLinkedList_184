#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;

    Node(int rollNumber, string name) {
        this->rollNumber = rollNumber;
        this->name = name;
        next = NULL;
    }
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** previous, Node** current);
    bool listEmpty();
    bool delNode();
    void traverse();

};

void CircularLinkedList::addNode() { //membuat procedure untuk menambahkan data nilai dan nama
    int rollno;
    string name;
    Node* newNode = new Node(rollno, name);     //membuat node baru
    newNode->rollNumber = rollno;  
    newNode->name = name;  

    if (LAST == NULL) {         
        LAST = newNode;
        newNode->next = newNode;
    }
    else {
        Node* temp = LAST;      
        while (temp->next != LAST) //temp tidak sama dengan last maka akan lanjut
        newNode->next = LAST->next;
        LAST->next = newNode;       //step 4a. membuat point akhir ke new node

        if (rollno > LAST->rollNumber) {    //jika nilai lebih besar dari last maka akan mengisi ulang nilai
            LAST = newNode;
        }
    }
}


bool CircularLinkedList::search(int rollNumber, Node** safina, Node** naja) {
    *safina = LAST->next;       //previous = safina
    *naja = LAST->next;         //current = naja

    while (*naja != LAST) {
        if (rollNumber == (*naja)->rollNumber) {
            return true;
        }
        *safina = *naja;
        *naja = (*naja)->next;
    }

    if (rollNumber == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;    //lanjut ke langkah berikutnya jika last bernilai 0
}

bool CircularLinkedList::delNode() { //membuat konstruktor untuk menghapus node
    Node* safina, * naja;
    safina = naja = NULL;       //step 1a. Mark LAST as NULL

    if (naja == LAST) {     //current sama dengan LAST
        Node* temp = LAST;
        while (temp->next != LAST) {
            temp = temp->next;      //step 4b.Make previous point to current
        }
        temp->next = LAST->next;
        LAST = LAST->next;
    }
    else {
        safina->next = naja->next;  //jika previous dan current sudah berisi data maka lanjut 
    }
    delete naja;    //untuk menghapus node yg diinginkan
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* currentNode = LAST->next;
        while (currentNode != LAST) {
            cout << currentNode->rollNumber << "   " << currentNode->name << endl;
            currentNode = currentNode->next;
        }
        cout << LAST->rollNumber << "   " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    CircularLinkedList list;
    int ch, rollNumber;
    string name;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-5): ";

            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                cout << "Enter rollNumber and name: ";
                cin >> rollNumber >> name;
                list.addNode();
                break;
            }
            case '2': {
                cout << "Enter rollNumber of node to delete: "; // mencari node yang didelete 
                cin >> rollNumber;
                if (list.delNode()) {
                    cout << "Node deleted successfully." << endl;
                }
                else {
                    cout << "Node not found." << endl;
                }
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                if (list.listEmpty()) { 
                    cout << "List is empty." << endl;
                }
                else {
                    cout << "List is not empty." << endl;
                }
                break;
            }
            case 5: {
                cout << "Exiting program." << endl;
                exit(0);
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
        cout << endl;
    }
    return 0;
}