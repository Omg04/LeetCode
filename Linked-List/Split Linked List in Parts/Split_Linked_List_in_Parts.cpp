class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*>parts;
        int n = 0;
        ListNode * curr = head;
        while(curr) {
            n++;
            curr = curr->next;
        }
        curr = head;
        int Node = n/k;

        if(k>=n) {
            int counter = 0;
            while(curr) {
                counter++;
                ListNode * temp = curr->next;
                curr->next = NULL;
                parts.push_back(curr);
                curr = temp;
            }
            for(int i = counter;i<k;i++) parts.push_back(nullptr);
            return parts;
        }

        for(int i = 0;i<n%k;i++) {
            int counter = 1;
            while(counter<Node+1) {
                counter++;
                curr = curr->next;
            }
            ListNode * temp = curr->next;
            curr->next = nullptr;
            parts.push_back(head);
            head = temp;
            curr = head;
        }
        for(int i = k - (n%k);i>0;i--) {
            int counter = 1;
            while(counter<Node) {
                counter++;
                curr = curr->next;
            }
            ListNode * temp = curr->next;
            curr->next = nullptr;
            parts.push_back(head);
            head = temp;
            curr = head;
        }
        return parts;
    }
};