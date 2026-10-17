class Solution {
public:
    string makeGood(string s) {
        stack<char>st;
        for(auto & ch : s) {
            if(st.size() == 0) {
                st.push(ch);
                continue;
            }
            if(int(ch) >= 97) {
                if(int(st.top()) == int(ch) - 32) st.pop();
                else st.push(ch);
            } 
            else {
                if(int(st.top()) == int(ch) + 32) st.pop();
                else st.push(ch);
            }
        }
        int n = st.size();
        string ans(n, ' ');
        for(int i = n - 1;i>=0;i--) {
            ans[i] = st.top();
            st.pop();
        }
        return ans;
    }
};