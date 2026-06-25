class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        vector<int>list;
        ListNode * temp = new ListNode();
        temp = head;
        while(temp!=NULL) {
            list.push_back(temp->val);
            temp = temp->next;
        }
        temp = head;
        for(int i=list.size()-1;i>=0;i--) {
            temp->val = list[i];
            temp = temp->next;
        }
        return head;
    }
};