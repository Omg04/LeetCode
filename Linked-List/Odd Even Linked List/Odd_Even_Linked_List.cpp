class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode * curr = head;
        ListNode * Odd = new ListNode();ListNode * Oddtail = Odd;
        ListNode * Even = new ListNode();ListNode * Eventail = Even;
        int i = 1;

        while(curr) {
            if(i%2 != 0) {
                Oddtail->next = curr;
                curr = curr->next;
                Oddtail = Oddtail->next;
                Oddtail->next = NULL;
            }
            else {
                Eventail->next = curr;
                curr = curr->next;
                Eventail = Eventail->next;
                Eventail->next = NULL;
            }
            i++;
        }
        Oddtail->next = Even->next;
        return Odd->next;
    }
};