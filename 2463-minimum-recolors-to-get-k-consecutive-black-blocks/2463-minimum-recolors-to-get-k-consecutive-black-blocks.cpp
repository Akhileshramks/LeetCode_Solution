class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.length();
        int turn = 0;
        for(int i = 0;i < k;i++){
            if(blocks[i] == 'W') turn++;
        }
        int mini = turn;
        for(int i = k;i < n;i++){
            if(blocks[i] == 'W') turn++;
            if(blocks[i - k] == 'W') turn--;
            mini = min(turn,mini);
        }
        return mini;
    }
};