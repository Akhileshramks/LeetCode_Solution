class Solution {
public:
    int gcd(int x,int y){
        if(y == 0) return x;
        return gcd(y,x%y);
    }
    vector<pair<int, int>> extract(string& s) {
        int n = s.size();
        int i = 0;
        vector<int> numArr;
        vector<int> denomArr;

        while (i < n) {
            int num = 0;
            bool isNegative = false;
            if (s[i] == '+') {
                i++;
            } else if (s[i] == '-') {
                isNegative = true;
                i++;
            }
            while (s[i] != '/') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            if (isNegative) {
                num = -num;
            }
            numArr.push_back(num);
            i++; // Skip the '/'
            int denom = 0;
            while (i < n && s[i] != '+' && s[i] != '-') {
                denom = denom * 10 + (s[i] - '0');
                i++;
            }
            denomArr.push_back(denom);
        }

        vector<pair<int, int>> extractArr;
        for (int i = 0; i < numArr.size(); i++) {
            extractArr.push_back({numArr[i], denomArr[i]});
        }
        return extractArr;
    }
    // string fractionAddition2(string expression) {
    //     int n = expression.size();
    //     int i =0 ;
    //     while(i<n){
    //         int sign = 1;
    //         if(expression[i] == '-' && expression[i] == '+'){
    //             sign = -1;
    //             continue;
    //         }
    //         int q2 = fractions[i].first;
    //         int d2 = fractions[i].second;
    //         int lcm = d1*d2/gcd(d1,d2);
    //         q1 = q1*lcm/d1 + q2*lcm/d2;
    //         d1 = lcm;
    //         if(abs(q1) == d1){
    //             return "1/1";
    //         }
    //         else if(q1 == 0){
    //             return "0/1";
    //         }
    //         else{
    //             return to_string(q1)+"/"+to_string(d1);
    //         }
    //     }
    // }
    // string fractionAddition(string expression) {
    //     vector<pair<int, int>> fractions;
    //     fractions = extract(expression);
    //     for(int i=0;i<fractions.size();i++){
    //         cout<<fractions[i].first<<" "<<fractions[i].second<<endl;
    //     }
    //     int q1 = fractions[0].first;
    //     int d1 = fractions[0].second;
    //     for(int i=1;i<fractions.size();i++){
    //         int q2 = fractions[i].first;
    //         int d2 = fractions[i].second;
    //         int lcm = d1*d2/gcd(abs(d1),abs(d2));
    //         q1 = q1 * (lcm / d1) + q2 * (lcm / d2);
    //         d1 = lcm;
    //     }
    //     if(q1 == 0){
    //         return "0/1";
    //     }
    //     else{
    //         int m = gcd(abs(q1),abs(d1));
    //         return to_string(q1/m)+"/"+to_string(d1/m);
    //     }
    // }
    string fractionAddition(string expression){
        int n = expression.size();
        int i =0 ;
        int numerator = 0;
        int denominator = 1;
        while(i<n){
            int sign = 1;
            int denom = 0;
            int num = 0;
            if(expression[i] == '-' || expression[i] == '+'){
                if(expression[i] == '-'){
                    sign = -1;
                } 
                i++;
            }
            if(isdigit(expression[i])){
                while(i<n && isdigit(expression[i])){
                    num = num*10+expression[i]-'0';
                    i++;
                }
                num *= sign;
            }
            if(expression[i] == '/'){
                i++;
                while(i<n && isdigit(expression[i])){
                    denom = denom*10+expression[i]-'0';
                    i++;
                }
            }
            numerator = numerator*denom + num*denominator;
            denominator = denominator * denom;
        }
        int factor = gcd(abs(numerator),abs(denominator));
        numerator = numerator/factor;
        denominator = denominator/factor;
        return to_string(numerator) + "/" + to_string(denominator);
    }
};