class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.length(),ans = 0;
        stack<char>st;
        for(int i = 0;i<n;i++) {
            if(s[i]=='(') st.push('(');
            else {
                 if(st.empty()) ans++;
                else st.pop();
            }
        }
        return ans + st.size();
    }
};