class Solution {
public:
stack<int>st;
    vector<int> nextLargerNodes(ListNode* head) {
        int n = 0;
        ListNode * curr = head;ListNode * prev = NULL;
        while(curr) {
            n++;
            ListNode * temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        head = prev;
        vector<int>ans (n,0);
        n--;
        while(n>=0) {
            if(!st.empty() && st.top()>head->val) {
                ans[n] = st.top();
            }
            else {
                while(!st.empty() && st.top() <= head->val) st.pop();
                if(st.empty()) ans[n] = 0;
                else ans[n] = st.top();
            }
            st.push(head->val);
            head = head->next;
            n--;
        }
        return ans;
    }
};