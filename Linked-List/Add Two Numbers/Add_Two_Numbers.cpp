/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
void fun(ListNode* L1,ListNode* L2,ListNode* result,int carry) {
    if (L1==NULL||L2==NULL) {
        if(L1!=NULL) {
            while(L1!=NULL) {
                int sum = L1->val+carry;
                carry = sum/10;
                ListNode*temp = new ListNode();
                temp->val = sum%10;
                result->next = temp;
                result=temp;
                L1 = L1->next;
            }
        }
        else {
            while(L2!=NULL) {
                int sum = L2->val+carry;
                carry = sum/10;
                ListNode*temp = new ListNode();
                temp->val = sum%10;
                result->next = temp;
                result=temp;
                L2 = L2->next;
            }
        }
        if (carry!=0) {
            ListNode*temp = new ListNode();
            temp->val = carry;
            result->next = temp;
        }
        return;
    }
        int sum = L1->val+L2->val+carry;
        carry = sum/10;
        ListNode*temp = new ListNode();
        temp->val = sum%10;
        result->next = temp;
        result=temp;
        fun(L1=L1->next,L2=L2->next,result,carry);
}
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode*result = new ListNode();
    fun(l1,l2,result,0);
    return result->next;
    }
};