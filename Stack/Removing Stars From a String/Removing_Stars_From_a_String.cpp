class Solution {
public:
    string removeStars(string s) {
        string ans;
        for(auto ch : s) {
            if(ch != '*') ans.push_back(ch);
            else {
                if(ans.length() > 0) ans.pop_back();
            } 
        }
        return ans;
    }
};