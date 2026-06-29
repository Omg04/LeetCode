class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int>ans(2,-1);
        int Min = INT_MAX;
        int Max = INT_MAX;
        int curr = 1;
        ListNode * temp = head;
        while(temp->next->next) {
            if(temp->val<temp->next->val && temp->next->val>temp->next->next->val || temp->val>temp->next->val && temp->next->val<temp->next->next->val) {
                if(curr<Max) {
                    Max = curr;
                    Min = curr;
                }
                else {
                    int t = min(curr-Min,curr - Max);
                    ans[0] = ans[0] == -1?t:min(t,ans[0]);
                    ans[1] = max(curr-Max,curr-Min);
                    Min = curr;
                }
            }
            temp = temp->next;
            curr++;
        }
        return ans;
    }
};