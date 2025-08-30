class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        for(int i = 0;i < n;i++){
            unordered_set<char> row;
            unordered_set<char> col;
            for(int j = 0;j < m;j++){
                if(board[i][j] != '.'){
                    if(row.find(board[i][j]) != row.end()) return false;
                    row.insert(board[i][j]);
                }
                if(board[j][i] != '.'){
                    if(col.find(board[j][i]) != col.end()) return false;
                    col.insert(board[j][i]);
                }
            }
        }
        for(int i = 0;i < 9;i+= 3){
            for(int j = 0;j < 9;j+= 3){
                unordered_set<char> sq;
                for(int k = i;k < i + 3;k++){
                    for(int l = j;l < j + 3;l++){
                        if(board[k][l] == '.') continue;
                        if(sq.find(board[k][l]) != sq.end()) return false;
                        sq.insert(board[k][l]);
                    }
                }
            }
        }
        return true;
    }
};