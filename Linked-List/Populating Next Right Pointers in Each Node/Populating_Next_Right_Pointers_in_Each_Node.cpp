/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:

int count = 0;
queue<Node*>open;

void fun(vector<Node*>&traverse) {
    if(open.empty()) return;
    Node * curr = open.front();
    traverse.push_back(curr);
    open.pop();
    count--;
    if(curr->left) open.push(curr->left);
    if(curr->right) open.push(curr->right);
    if(count == 0) {
        for(int i = 0;i<traverse.size()-1;i++) traverse[i]->next = traverse[i+1];
        traverse.clear();
        count = open.size();
    }
    fun(traverse);
}
    Node* connect(Node* root) {
        if(root == NULL) return root;
        open.push(root);
        count++;
        vector<Node*>traverse;
        fun(traverse);
        return root;
    }
};