class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int>st;
        for(auto & ch : operations) {
            if(ch == "D") st.push_back(st.back() * 2);
            else if(ch == "C") st.pop_back();
            else if(ch == "+") st.push_back(st[st.size()-1] + st[st.size()-2]);
            else st.push_back(stoi(ch));
        }
        int ans = 0;
        while(!st.empty()) {
            ans += st.back();
            st.pop_back();
        }
        return ans;
    }
};