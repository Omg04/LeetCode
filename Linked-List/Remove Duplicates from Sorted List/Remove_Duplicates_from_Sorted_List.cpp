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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL) return head;
        ListNode* i = head; ListNode* j = head;
        while(j!=NULL) {
            if(i->val!=j->val) {
                i->next = j;
                i = j;
            }
            j = j->next;
        }
        i->next = NULL;
        return head;
    }
};