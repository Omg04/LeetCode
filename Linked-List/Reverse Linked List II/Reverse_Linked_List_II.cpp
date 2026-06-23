class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left == right) return head;
        ListNode * dummy = NULL;
        for(int i = 1;i<left;i++) {
            dummy = dummy?dummy->next:head;
        } 
        ListNode * prev = NULL;
        ListNode * curr = dummy?dummy->next:head;
        ListNode * tail = curr;
        for(int i = left;i<=right;i++) {
            ListNode * Next = curr->next;
            curr -> next = prev;
            prev = curr;
            curr = Next;
        }
        if(dummy) dummy->next = prev;
        else head = prev;
        tail->next = curr;
        return head;
    }
};