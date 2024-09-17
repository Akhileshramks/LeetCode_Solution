class MedianFinder {
public:
    priority_queue<int,vector<int>,greater<int>> right;
    priority_queue<int> left;
    MedianFinder() {
        
    }
    void addNum(int num) {
        if(left.empty() || left.top() > num) left.push(num);
        else right.push(num);
        if(left.size()+1 < right.size()){
            left.push(right.top());
            right.pop();
        }
        if(left.size() > right.size()+1){
            right.push(left.top());
            left.pop();
        }
    }
    
    double findMedian() {
        if(left.size() == right.size()) return (double)((left.top()+right.top())/2.0);
        else return left.size()>right.size() ? left.top() : right.top();
    }
};

/*
left -> maxHeap right->minHeap

1,5,2,4,3

left -> 1 2

right -> 5 4 3
*/