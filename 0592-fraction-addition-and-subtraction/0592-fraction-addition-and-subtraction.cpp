class Solution {
public:
    int gcd(int x,int y){
        if(y == 0) return x;
        return gcd(y,x%y);
    }
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