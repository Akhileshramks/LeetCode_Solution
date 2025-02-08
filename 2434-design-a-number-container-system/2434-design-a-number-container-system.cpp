class NumberContainers {
public:
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> number;
    unordered_map<int,int> index;
    NumberContainers() {
        
    }
    
    void change(int ind, int num) {
        number[num].push(ind);
        index[ind] = num;
    }
    
    int find(int num) {
        while(number[num].size() > 0 && index[number[num].top()] != num) number[num].pop();
        if(number[num].size() > 0) return number[num].top();
        return -1;
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */