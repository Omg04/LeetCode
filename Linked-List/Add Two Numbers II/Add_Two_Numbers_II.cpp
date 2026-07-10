class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1->val == 0) return l2;
        if(l2->val == 0) return l1;
        int carry = 0;
        stack<int>L1;stack<int>L2;
        while(l1 || l2) {
            if(l1) {
                L1.push(l1->val);
                l1 = l1->next;
            }
            if(l2) {
                L2.push(l2->val);
                l2 = l2->next;
            }
        }
        ListNode * ans = new ListNode(0);
        while(!L1.empty() || !L2.empty()) {
            int sum = 0;
            if(!L1.empty()) {
                sum = L1.top();
                L1.pop();
            }
            if(!L2.empty()) {
                sum += L2.top();
                L2.pop();
            }
            sum += carry;
            ans->val = sum % 10;
            carry = sum/10;
            ans = new ListNode(0,ans);
        }
        if(carry) ans->val = carry;
        if(ans->val) return ans;
        return ans->next;
    }
};