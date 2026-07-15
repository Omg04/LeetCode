class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_map<int,int>table;
        for(auto &i : nums) table[i]++;
        int ans = 0;
        bool flag = false;
        while(head) { 
            if(!flag && table.contains(head->val)) {
                flag = true;
                ans++;
            }
            if(!table.contains(head->val)) flag = false;
            head = head->next;
        }
        return ans;
    }
};