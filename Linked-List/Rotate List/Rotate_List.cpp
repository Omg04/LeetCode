
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL || head->next == NULL) return head;
        ListNode * l = head;
        int length = 1;
        while(l->next) {
            length++;
            l = l->next;
        }
        k %= length;
        if(k == 0) return head;
        l->next = head;
        l = head;

        for(int i = 1;i<length-k;i++) {
            l = l->next;
        }
        head = l->next;
        l->next = NULL;
        return head;
    }
};