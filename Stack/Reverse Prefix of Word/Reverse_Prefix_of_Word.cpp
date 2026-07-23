class Solution {
public:
    string reversePrefix(string word, char ch) {
        vector<char>st;
        bool flag = false;
        int i = 0;
        for(i;i<word.length();i++) {
            st.push_back(word[i]);
            if(word[i] == ch) {
                flag = true;
                break;
            }
        }
        if(!flag) return word;
        string ans = "";
        while(!st.empty()) {
            ans += st.back();
            st.pop_back();
        }
        i++;
        for(i;i<word.length();i++) ans += word[i];
        return ans;
    }
};