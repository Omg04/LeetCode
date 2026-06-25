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
        if(head == NULL || head->next == NULL) return head;
        ListNode * temp = head;ListNode * i = head;ListNode * prev;
        bool flag = true,k = false;
        while(i != NULL) {
            if(i->next) {
                if(i->val != i->next->val) {
                    if(flag) {
                        cout<<i->val<<endl;
                        temp->val = i->val;
                        prev = temp;
                        temp = temp->next;
                        k = true;
                    }
                    else flag = !flag;
                }
                else flag = false;
            }
            else if(flag) {
                temp->val = i->val;
                prev = temp;
                temp = temp->next;
                k = true;
            }
            i = i->next;
        }
        prev->next = NULL;
        if(k) return head;
        return NULL;
    }
};