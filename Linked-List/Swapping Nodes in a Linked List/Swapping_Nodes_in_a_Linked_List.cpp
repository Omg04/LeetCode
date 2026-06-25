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
    ListNode* swapNodes(ListNode* head, int k) {
        if(head == NULL || head->next == NULL) return head;
        long long n = 0;
        ListNode * temp = head;
        while(temp!=NULL) {
            n++;
            temp = temp->next;
        }
        ListNode * i = head;ListNode * j = head; 
        int x=1,y = 1;
        for(int z = 0;z<n;z++) {
            if(x==k && y == n-k+1) break;
            if(x!=k) {
                i = i->next;
                x++;
            }
            if(y!=n-k+1) {
                j = j->next;
                y++;
            }
        }
        swap(i->val,j->val);
        return head;
    }
};