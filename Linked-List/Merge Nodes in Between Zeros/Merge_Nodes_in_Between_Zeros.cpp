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
    ListNode* mergeNodes(ListNode* head) {
        ListNode * slow = head;ListNode * fast = head;
        int sum = 0;
        while(fast->next!=nullptr) {
            sum += fast->val;
            if(fast->next->val == 0) {
                slow->next->val = sum;
                sum = 0;
                slow = slow->next;
            }
            fast = fast->next;
        }
        slow->next = nullptr;
        return head->next;
    }
};