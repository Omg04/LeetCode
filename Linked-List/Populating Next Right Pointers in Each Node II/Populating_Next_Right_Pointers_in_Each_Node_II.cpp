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
queue<Node *>open;
    Node* connect(Node* root) {
        if(!root) return root;
        open.push(root);
        open.push(NULL);
        Node * prev = NULL;
        while(!open.empty()) {
            Node * curr = open.front();
            open.pop();
            if(prev) prev->next = curr;
            if(curr) {
                if(curr->left) open.push(curr->left);
                if(curr->right) open.push(curr->right);
            }
            else {
                if(open.empty()) break;
                open.push(curr);
            }
            prev = curr;
        }
        return root;
    }
};