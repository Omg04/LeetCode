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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head->next==NULL) return head->next;
        ListNode *i = head;
        int k = 0;
        while(i != NULL) {
            k++;
            i = i->next;
        }
        i = head;
        n = k-n;
        if(n == 0) return head->next;
        for(int j = 1;j<n;j++) {
            i = i->next;
        }
        if(i->next!=NULL) i->next = i->next->next;
        else i->next = NULL;
        return head;
    }
};