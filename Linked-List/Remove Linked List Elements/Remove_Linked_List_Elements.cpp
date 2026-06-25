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
    ListNode* removeElements(ListNode* head, int val) {
        if (head ==NULL) return head;
        ListNode * temp_head = new ListNode();
        ListNode * temp = new ListNode();
        temp_head = head;
        temp = head->next;
        while(temp!=NULL) {
            if(temp->val == val) {
                temp_head->next = temp->next;
                temp = temp->next;
            }
            else {
                temp_head = temp_head->next;
                temp = temp->next;
            }
        }
        if (head->val==val) head = head->next;
        return head;
    }
};