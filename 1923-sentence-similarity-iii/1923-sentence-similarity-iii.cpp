class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> s1,s2;
        stringstream ss1(sentence1), ss2(sentence2);
        string word;
        while(ss1 >> word) s1.push_back(word);
        while(ss2 >> word) s2.push_back(word);

        int n1 = s1.size();
        int n2 = s2.size();

        if(n1 > n2) return  areSentencesSimilar(sentence2, sentence1);

        int start = 0;
        int end1 = n1 - 1;
        int end2 = n2 - 1;

        while(start < n1 && s1[start] == s2[start]) start++;
        while(end1 >= 0 && s1[end1] == s2[end2]) end1--,end2--;

        return end1 < start;

    }
};