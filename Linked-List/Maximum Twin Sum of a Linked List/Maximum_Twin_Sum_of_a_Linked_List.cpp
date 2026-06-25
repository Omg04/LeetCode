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
ListNode *  reverse(ListNode * curr,ListNode * prev) {
    if(curr->next == NULL) {
        curr->next = prev;
        return curr;
    }
    ListNode * next = curr->next;
    curr->next = prev;
    return reverse(next,curr); 
}
    int pairSum(ListNode* head) {
        if(head->next->next == NULL) return head->val + head->next->val;
        int sum = INT_MIN;
        ListNode * slow = head;ListNode * fast = head;
        
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode * temp = slow->next;
        slow->next = NULL;
        temp = reverse(temp,NULL);

        while(head && temp) {
            sum = max(sum,head->val + temp->val);
            head = head->next;
            temp = temp->next;
        }
        return sum;
    }
};