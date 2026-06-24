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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *head = new ListNode();
        ListNode *temp = new ListNode();
        temp = head;
        while(list1!=NULL && list2 != NULL) {
            if(list1->val<=list2->val) {
                ListNode *ptr = new ListNode(list1->val);
                temp->next = ptr;
                temp = ptr;
                list1 = list1->next;
            }
            else {
                ListNode *ptr = new ListNode(list2->val);
                temp->next = ptr;
                temp = ptr;
                list2 = list2->next;
            }
        }   
        if(list1!=NULL) {
            temp->next = list1;
        }
        else if(list2!=NULL) {
            temp->next = list2;
        }
        return head->next;
    }
};