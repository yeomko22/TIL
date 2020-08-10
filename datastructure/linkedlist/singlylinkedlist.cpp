class MyLinkedList {
public:
    struct Node {
        int val;
        Node *next = NULL;
        Node(int val) : val(val) {}
    };
    Node *head=NULL;
    int size = 0;
    /** Initialize your data structure here. */
    MyLinkedList() {
        
    }
    
    void printSelf(string msg) {
        // Node *curNode = head;
        // cout << msg << ": ";
        // while (curNode) {
        //     cout << curNode->val;
        //     if (curNode->next) {
        //         cout << "<-";
        //     }
        //     curNode = curNode->next;
        // }
        // cout << endl;
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if (!head || index > size - 1) {
            return -1;
        }
        Node *curNode = head;
        while (index) {
            if (curNode==NULL) {
                break;
            }
            curNode = curNode->next;
            index--;
        }
        if (index) {
            return -1;
        }
        return curNode->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        Node *newNode = new Node(val);
        if (head) {
            newNode->next = head;
        }
        head = newNode;
        size++;
        printSelf("add at head");
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node *newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node *curNode = head;
            while (curNode->next) {
                curNode = curNode->next;
            }
            curNode->next = newNode;
        }
        size++;
        printSelf("add at tail");
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if (index==0) {
            addAtHead(val);
        } else if (index==size) {
            addAtTail(val);
        } else if (index > size + 1)  {
            cout << "add at index, invalid index!" << endl; 
        } else {
            Node *curNode = head;
            index--;
            while (index--) {
                curNode = curNode->next;
            }
            Node *newNode = new Node(val);
            newNode->next = curNode->next;
            curNode->next = newNode;
            size++;
        }
        printSelf("add at index");
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (index==0) {
            Node *target = head;
            head = head->next;
            delete target;
            size--;
        } else if (index > size - 1)  {
            cout << "delete at index, invalid index!" << endl; 
        } else {
            Node *curNode = head;
            index--;
            while (index--) {
                curNode = curNode->next;
            }
            Node *target = curNode->next;
            if (curNode->next) {
                curNode->next = curNode->next->next;
            }
            delete target;
            size--;
        }
        printSelf("delete at index");
    }
};
