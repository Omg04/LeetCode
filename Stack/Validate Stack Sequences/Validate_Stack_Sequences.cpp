class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int>st;
        int i = 0,j = 0;
        while(i < pushed.size() || !st.empty()) {
            if(!st.empty() && popped[j] == st.top()) {
                st.pop();
                j++;
            }
            else {
                if(i < pushed.size()) {
                    st.push(pushed[i]);
                    i++;
                }
                else return false;
            }
        }
        return true;
    }
};