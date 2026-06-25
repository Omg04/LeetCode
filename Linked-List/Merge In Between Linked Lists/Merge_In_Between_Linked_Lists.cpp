class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode * slow = list1;
        int i = 1;
        while(i<a) {
            slow = slow->next;
            i++;
        }
        ListNode * fast = slow->next;
        slow->next = list2;
        while(i<b) {
            fast = fast->next;
            i++;
        }
        slow = list2;
        while(slow->next!=nullptr) slow = slow->next;
        slow->next = fast->next;
        return list1;
    }
};