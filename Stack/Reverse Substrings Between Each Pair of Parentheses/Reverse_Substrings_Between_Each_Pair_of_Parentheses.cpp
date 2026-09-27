class Solution {
public:
    string reverseParentheses(string s) {
        stack<char>st;
        for(auto ch : s) {
            if(ch != ')') st.push(ch);
            else {
                string temp = "";
                while(!st.empty() && st.top() != '(')  {
                    temp += st.top();
                    st.pop();
                }
                st.pop();
                // cout<<temp<<endl;
                for(auto c : temp) st.push(c);
            }
        }
        s = "";
        while(!st.empty()) {
            s += st.top();
            st.pop();
        }
        return string(s.rbegin(), s.rend());
    }
};