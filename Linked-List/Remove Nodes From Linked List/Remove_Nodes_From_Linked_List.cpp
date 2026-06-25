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
void fun(ListNode *& prev,ListNode*j,int &max ) {
    if(j->next == NULL) {
        max = j->val;
        return;
    }
    fun(prev->next,j->next,max);
    if (j->val>=max) {
        max = j->val;
        return;
    }
    else prev->next = j->next;
    return;
}
    ListNode* removeNodes(ListNode* head) {
        ListNode * prev = head;ListNode*j =head;int max = 0;
        fun(prev,j->next,max);
        if(head->val<head->next->val) return head->next;
    return head;
    }  
};