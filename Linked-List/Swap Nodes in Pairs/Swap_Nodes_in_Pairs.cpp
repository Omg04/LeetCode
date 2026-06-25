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
    void fun(ListNode * i,ListNode * j) {
        if(j->next==NULL) {ListNode * temp = new ListNode(i->val);i->val=j->val;j->val = temp->val;return;}
        else if(i->next==NULL) return;
        ListNode * temp = new ListNode(i->val);i->val=j->val;j->val = temp->val;
        i = j->next;if(i->next!=NULL) j=i->next;else return;
        fun(i,j);
    }
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL || head->next==NULL) return head;
        ListNode * i = new ListNode();
        ListNode * j = new ListNode();
        i = head;j = head->next;
        fun(i,j);
        return head;
    }
};