class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
       ListNode * dummy_less = new ListNode();
       ListNode * dummy_greater = new ListNode();
       ListNode * tail_less = dummy_less;
       ListNode * tail_greater = dummy_greater;
       ListNode * curr = head;
       while(curr) {
        if(curr->val<x) {
            tail_less->next = curr;
            tail_less = curr;
        }
        else {
            tail_greater->next = curr;
            tail_greater = curr;
        }
        curr = curr->next;
       }
       tail_less->next = dummy_greater->next;
       tail_greater->next = NULL;
       return dummy_less->next;
    }
};