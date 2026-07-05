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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        int i = 1;
        ListNode * dummyhead = head;ListNode * tail = head;
        while(dummyhead->next) {
            int length = 0;
            do {
                if(tail->next) {
                    tail = tail->next;
                    length++;
                }
                else break;
            } while(length<=i);
            ListNode * temp = dummyhead->next;
            
            if(length%2 == 0) {
                dummyhead->next = reverseBetween(dummyhead->next,1,length);
                dummyhead = temp;
                tail = dummyhead;
            } else dummyhead = tail;
            
            i++;
        }
        return head;
    }
};