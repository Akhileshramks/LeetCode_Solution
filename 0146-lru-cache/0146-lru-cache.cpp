class Node{
    public:
        int key;
        int val;
        Node* next = NULL;
        Node* prev = NULL;

        Node(int k,int v){
            key = k;
            val = v;
        }
        
};
void addNode(Node* node,Node* head){
    node->next = head->next;
    node->next->prev = node;
    head->next = node;
    node->prev = head;
}
void deleteNode(Node* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
class LRUCache {
public:
    int capacity;
    unordered_map<int,Node*> mpp;
    Node* head = new Node(-1,-1);
    Node* tail = new Node(-1,-1);
    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(mpp.find(key) == mpp.end()) return -1;
        Node* node = mpp[key];
        deleteNode(node);
        addNode(node,head);
        return node->val;
    }
    
    void put(int key, int value) {
        
        Node* node;
        if(mpp.find(key) == mpp.end()){
            if(mpp.size() == capacity){
                Node* del = tail->prev;
                deleteNode(del);
                mpp.erase(del->key);
                delete(del);
            }
            node = new Node(key,value);
            mpp[key] = node;
        }
        else{
            node = mpp[key];
            node->val = value;
            deleteNode(node);
        }
        addNode(node,head);
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */