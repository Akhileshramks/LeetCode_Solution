class Solution {
public:
    vector<int> diffWays(string exp) {
        vector<int> result;
        if(exp.size() == 0) return {};
        if (exp.size() == 1) return {stoi(exp)};
        if (exp.length() == 2 && isdigit(exp[0])) {
            result.push_back(stoi(exp));
            return result;
        }
        for (int i = 0; i < exp.size(); i++) {
            char c = exp[i];
            if (c == '*' || c == '-' || c == '+') {
                vector<int> leftResults = diffWays(exp.substr(0, i));
                vector<int> rightResults = diffWays(exp.substr(i + 1));
                for (int left : leftResults) {
                    for (int right : rightResults) {
                        if (c == '*') result.push_back(left * right);
                        else if (c == '-') result.push_back(left - right);
                        else if (c == '+') result.push_back(left + right);
                    }
                }
            }
        }
        return result;
    }
    vector<int> diffWaysToCompute(string expression) {
        return diffWays(expression);
    }
};
