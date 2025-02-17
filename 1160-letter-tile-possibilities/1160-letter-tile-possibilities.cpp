class Solution {
public:
    unordered_set<string> allPossible;
    void recusionAllPossible(unordered_map<int,bool>& visited,string currString,string& originalString){
        allPossible.insert(currString);
        cout<<currString<<endl;
        for(int i = 0;i < originalString.length();i++){
            if(!visited[i]){
                visited[i] = true;
                recusionAllPossible(visited,currString + originalString[i],originalString);
                visited[i] = false;
            }
        }
    }

    int numTilePossibilities(string tiles) {
        int len = tiles.size();
        unordered_map<int,bool> visited(len);
        string currString = "";
        recusionAllPossible(visited,currString,tiles);
        return allPossible.size() - 1;
    }
};