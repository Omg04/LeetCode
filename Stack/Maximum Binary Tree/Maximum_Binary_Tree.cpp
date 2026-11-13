class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
       stack<TreeNode*>st;
       TreeNode * root = new TreeNode();
       TreeNode * temp = nullptr;
       for(auto &num : nums) {
            TreeNode * curr = new TreeNode(num);
            if(!st.empty()) {
                if(st.top()->val>num) {
                    st.top()->right = curr;
                }
                else {
                    while(!st.empty() && st.top()->val<num) {
                        temp = st.top();
                        st.pop();
                    }
                    curr->left = temp;
                }
            }
        
            if(st.empty()) root = curr;
            else st.top()->right = curr;
            st.push(curr); 
       }
       return root;
    }
};