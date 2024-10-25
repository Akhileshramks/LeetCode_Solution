class nAryTree{
    public:
        unordered_map<string,nAryTree*> sub;
        bool end = false;
};
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        vector<string> res;
        nAryTree* root = new nAryTree();
        for(auto &s : folder){
            nAryTree* tempRoot = root;
            string fold;
            stringstream ss(s);
            getline(ss,fold,'/');
            while(getline(ss,fold,'/')){
                if(tempRoot->sub.find(fold) == tempRoot->sub.end()){
                    tempRoot->sub[fold] = new nAryTree();
                }
                tempRoot = tempRoot->sub[fold];
            }
            tempRoot->end = true;
        }
        for(string &s : folder){
            bool flag = false;
            nAryTree* tempRoot = root;
            string fold;
            stringstream ss(s);
            getline(ss,fold,'/');
            while(getline(ss,fold,'/')){
                tempRoot = tempRoot->sub[fold];
                if(tempRoot->end == true && ss.rdbuf()->in_avail() != 0){
                    flag = true;
                    break;
                };
            }
            if(!flag) res.push_back(s);
        }
        return res;
    }
};