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
int GCD (int a,int b) {
    while(b!=0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(head->next == NULL) return head;
        ListNode * curr = head;
        while(curr->next != NULL) {
            ListNode * temp= new ListNode(GCD(curr->val,curr->next->val));
            temp->next = curr->next;
            curr->next = temp;
            curr = curr->next->next;
        }
        return head;
    }
};