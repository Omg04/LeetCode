/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool fun(ListNode *&i,ListNode* j) {
        if(j->next==NULL) {
            if(j->val == i->val) return true;
            return false;
        }
        if(fun(i,j->next)) {
            i = i->next;
            if(i->val == j->val) return true;
            return false;
        }
        return false;
    }
    bool isPalindrome(ListNode* head) {
        ListNode* i = new ListNode();ListNode* j = new ListNode();
        i = head;j= head ;
        return fun(i,j);
    }
};