class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int>table;table.reserve(nums.size());
        for(auto num : nums) table.insert(num);
        ListNode dummy(0);
        ListNode * dummy_tail = &dummy;
        while(head) {
            if(!table.count(head->val)) {
                dummy_tail->next = head;
                dummy_tail = dummy_tail->next;
            }
            head = head->next;
        }
        dummy_tail->next = nullptr;
        return dummy.next;
    }
};