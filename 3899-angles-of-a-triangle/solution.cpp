class Solution {
public:
    vector<double> internalAngles(vector<int>& sides) {
        sort(sides.begin(),sides.end());
        if(sides[0] + sides[1] <= sides[2]) return {};
        // a^2 = b^2 + c^2 - 2bc cosA
        // A = cos^-1(a^2 - b^2 - c^2 / 2bc)
        int a = sides[0], b = sides[1], c = sides[2];
        double A = ((acos((b*b + c*c - a*a)/(2.0*b*c)))/M_PI)*180;
        double B = ((acos((a*a + c*c - b*b)/(2.0*a*c)))/M_PI)*180;
        double C = ((acos((b*b + a*a - c*c)/(2.0*b*a)))/M_PI)*180;
        vector<double> res = {A,B,C};
        sort(res.begin(), res.end());
        return res;
    }
};