class Solution {
public:
    int maxDiff(int num) {
        string n = to_string(num);
        char x1 = '9';
        char y1 = '9';
        int len = n.size();
        for(int i = 0;i < len;i++){
            if(n[i] == x1) continue;
            else{ y1 = n[i];break; }
        }
        char x2 = '0';
        char y2 = n[0];
        for(int i = 0;i < len;i++){
            if(n[i] == n[0] || n[i] == x2) continue;
            else { y2 = n[i];break; }
        }
        if(y2 == n[0]) x2 = '1';
        string a = n,b = n,c = n;
        for(int i = 0;i < len;i++){
            if(a[i] == y1) a[i] = x1;
            if(b[i] == y2) b[i] = x2;
            if(c[i] == n[0]) c[i] = '1';
        }
        cout<<a<<" "<<b;
        return stoi(a) - min(stoi(b),stoi(c));
    }
};

/*

54222 - 94222 - 1422


*/