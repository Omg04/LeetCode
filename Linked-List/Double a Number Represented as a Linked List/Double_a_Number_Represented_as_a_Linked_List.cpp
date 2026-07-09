class Solution {
public:
    ListNode* doubleIt(ListNode* head) {
        if(head->val >= 5) head = new ListNode(0,head);
        ListNode * curr = head;
        while(curr) {
            curr->val = (curr->val<<1) % 10;
            if(curr->next && curr->next->val >= 5) curr->val += 1;
            curr = curr->next;
        }
        return head;
    }
};