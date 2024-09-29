#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

class LinkedListNode {
public:
    int freq;
    unordered_set<string> st;
    LinkedListNode* prev;
    LinkedListNode* next;
    LinkedListNode(int f) : freq(f), prev(nullptr), next(nullptr) {}
};

class AllOne {
public:
    LinkedListNode* head;
    LinkedListNode* tail;
    unordered_map<string, LinkedListNode*> mpp;

    AllOne() {
        head = new LinkedListNode(0);  // Dummy head
        tail = new LinkedListNode(0);  // Dummy tail
        head->next = tail;
        tail->prev = head;
    }
    
    void inc(string key) {
        if (mpp.find(key) == mpp.end()) {
            if (head->next != tail && head->next->freq == 1) {
                head->next->st.insert(key);
                mpp[key] = head->next;
            } 
            else {
                LinkedListNode* newNode = new LinkedListNode(1);
                newNode->st.insert(key);
                newNode->next = head->next;
                head->next->prev = newNode;
                head->next = newNode;
                newNode->prev = head;
                mpp[key] = newNode;
            }
        } 
        else {
            LinkedListNode* node = mpp[key];
            int f = node->freq;
            node->st.erase(key);
            LinkedListNode* nextNode = node->next;
            
            if (nextNode != tail && nextNode->freq == f + 1) {
                nextNode->st.insert(key);
                mpp[key] = nextNode;
            } 
            else {
                LinkedListNode* newNode = new LinkedListNode(f + 1);
                newNode->st.insert(key);
                newNode->next = nextNode;
                nextNode->prev = newNode;
                node->next = newNode;
                newNode->prev = node;
                mpp[key] = newNode;
            }
            if (node->st.empty()) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                delete node;
            }

        }
    }

    void dec(string key) {
        if (mpp.find(key) == mpp.end()) return;

        LinkedListNode* node = mpp[key];
        int f = node->freq;
        node->st.erase(key);

        LinkedListNode* prevNode = node->prev; 
        if (f == 1) {
            mpp.erase(key);
        }
        else{
            if (prevNode != head && prevNode->freq == f - 1) {
                prevNode->st.insert(key);
                mpp[key] = prevNode;
            } 
            else {
                LinkedListNode* newNode = new LinkedListNode(f - 1);
                newNode->st.insert(key);
                newNode->next = node;
                node->prev = newNode;
                prevNode->next = newNode;
                newNode->prev = prevNode;
                mpp[key] = newNode;
            }
        }
        if (node->st.empty()) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
        }
    }

    string getMaxKey() {
        if (tail->prev == head) return "";  
        return *(tail->prev->st.begin()); 
    }

    string getMinKey() {
        if (head->next == tail) return ""; 
        return *(head->next->st.begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
