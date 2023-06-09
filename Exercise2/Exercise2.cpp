#include <iostream>
#include<string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList { // membuat class Circular yang berisi public dan private dan ada metode / fungsi
private:
    Node* LAST;
public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** previous, Node** Imam);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() { //Program mencari Node
    Node* newNode = new Node();// menambahkan Node baru 
    cout << "\nEnter roll number: ";
    cin >> newNode->rollNumber;
    cout << "Enter name: ";
    cin >> newNode->name;

    if (listEmpty()) { // 1.Mencari tempat kosong buat newNode
        newNode->next = newNode;
        LAST = newNode;
    }
    else { 
        Node* current = LAST->next;// 2.Buat bidang berikut nya dari current hingga last
        Node* previous = NULL; 

        while (current != LAST && current->rollNumber < newNode->rollNumber) { //3.current akan mencari rollnumber 
            previous = current;
            current = current->next;
        }

        if (current == LAST && current->rollNumber < newNode->rollNumber) { //4.untnk memberhentikan current seketika current sudah menemukan rollNumber atau newNode
            newNode->next = current->next;
            current->next = newNode;
            LAST = newNode;
        }
        else { // Between two nodes
            newNode->next = current; //1.titik pertama node 
            if (previous == NULL) //2.memberikan previous NULL
                LAST->next = newNode;//3.mengulangi step sampi previouse sama dengan Last
            else
                previous->next = newNode;
        }
    }
    cout << "Record added successfully." << endl;
}
bool CircularLinkedList::search(int rollno, Node** previous, Node** Imam) { //mencari node
    *previous = LAST->next;  // untuk menjalankan previouse
    *Imam = LAST->next; // untunk menjalankan next
    while (*Imam != LAST) { 
        if (rollno == (*Imam)->rollNumber) {
            return true;
        }
        *previous = *Imam;
        *Imam = (*Imam)->next;
    }
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}
bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}
bool CircularLinkedList::delNode() { //write your answer here
    if (listEmpty()) {// 1.Mencari tempat kosong untuk di hapus
        cout << "List is empty. No records to delete." << endl;
        return false;
    }

    int rollno; // 2.mencari rollno yang ada di search untuk di hapus
    cout << "\nTekan Rollno untuk di hapus: ";
    cin >> rollno;

    Node* previous;
    Node* current;

    if (search(rollno, &previous, &current)) {
        if (LAST->next == LAST) { // 2.untuk menghapus LAST jika LAST tersebut KOSONG
            delete LAST;
            LAST = NULL;
        }
        else if (current == LAST) { // 3.untuk menghapus current jika current sama dengan LAST
            LAST = previous;
            previous->next = current->next;
            delete current;
        }
        else if (previous == LAST) { 
            LAST->next = current->next;
            delete current;
        }
        else { // Between two nodes
            previous->next = current->next;
            delete current;
        }

        cout << "Record with roll number " << rollno << " deleted successfully." << endl;
        return true;
    }
    else {
        cout << "Record with roll number " << rollno << " not found." << endl;
        return false;
    }
}
void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* currentNode = LAST->next;
        while (currentNode != LAST) {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}
int main() {
    CircularLinkedList obj;
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
            }
            case '2': {
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
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
    }
    return 0;
}