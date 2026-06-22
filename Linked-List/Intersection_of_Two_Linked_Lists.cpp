/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
       ListNode * A = headA;
       ListNode * B = headB;
       while(A != B) {
        A = (A == nullptr) ? headB : A->next;
        B = (B == nullptr) ? headA : B->next;
       }
       return A;
    }
};