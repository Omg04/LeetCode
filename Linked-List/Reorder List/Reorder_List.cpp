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
ListNode* reverse(ListNode*head) {
    ListNode*prev = NULL;
    ListNode * i = head;
    ListNode *j=i->next;
    while(j!=NULL) {
        j = i->next;
        i->next = prev;
        prev = i;
        if(j == NULL) return i;
        i = j;
    }
    return i;
}
void merge(ListNode * &head,ListNode * S_head) {
    ListNode * i = head;
    ListNode * temp = NULL;
    while(S_head!=NULL) {
        ListNode *j= S_head->next;
        temp = i->next;
        i->next = S_head;
        i = i->next;
        i->next = temp;
        i = i->next;
        S_head = j;
    }
    return;
}
    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL) return;
        ListNode * i = head;ListNode * temp = head;
        while(i!=NULL) {
            if(i->next == NULL || i->next->next==NULL) break;
            i = i->next->next;
            temp = temp->next;
        }
        ListNode * S_head = temp->next;
        temp->next = NULL;
        S_head = reverse(S_head);
        merge(head,S_head);
        return;
    }
};