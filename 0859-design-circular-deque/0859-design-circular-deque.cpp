class Node {
public:
    int val;
    Node* next;
    Node* prev;

    Node(int m) {
        val = m;
        next = NULL;
        prev = NULL;
    }
};

class MyCircularDeque {
public:
    int size;
    Node* front;
    Node* end;
    int count = 0;

    MyCircularDeque(int k) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        size = k;
        front = NULL;
        end = NULL;
    }

    bool insertFront(int value) {
        if (count < size) {
            Node* newNode = new Node(value);
            if (isEmpty()) { 
                front = end = newNode;
            } 
            else {
                newNode->next = front;
                front->prev = newNode;
                front = newNode;
            }
            count++;
            return true;
        }
        return false;
    }

    bool insertLast(int value) {
        if (count < size) {
            Node* newNode = new Node(value);
            if (isEmpty()) {
                front = end = newNode;
            } 
            else {
                end->next = newNode;
                newNode->prev = end;
                end = newNode;
            }
            count++;
            return true;
        }
        return false;
    }

    bool deleteFront() {
        if (!isEmpty()) {
            Node* delNode = front;
            if (count == 1) {
                front = end = NULL;
            } 
            else {
                front = front->next;
                front->prev = NULL;
            }
            delete delNode;
            count--;
            return true;
        }
        return false;
    }

    bool deleteLast() {
        if (!isEmpty()) {
            Node* delNode = end;
            if (count == 1) {
                front = end = NULL;
            } 
            else {
                end = end->prev;
                end->next = NULL;
            }
            delete delNode; 
            count--;
            return true;
        }
        return false;
    }

    int getFront() {
        if (!isEmpty()) {
            return front->val;
        }
        return -1;
    }

    int getRear() {
        if (!isEmpty()) {
            return end->val;
        }
        return -1;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == size;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
