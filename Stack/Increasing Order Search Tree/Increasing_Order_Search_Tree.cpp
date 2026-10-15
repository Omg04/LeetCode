/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
TreeNode * Root = NULL;
TreeNode * temp = NULL;
void fun(TreeNode * node) {
    if(!node) return;
    if(node->left) fun(node->left);
    if(!Root) {
        Root = node; 
        temp = Root;
        if(node->right) fun(node->right);
        return;
    }

    temp->right = node;
    temp = temp->right;
    temp->left = NULL;
    if(node->right) fun(node->right);
}
    TreeNode* increasingBST(TreeNode* root) {
        fun(root);
        return Root;
    }
};