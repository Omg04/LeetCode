
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        int start_row = 0,start_column = 0;
        vector<vector<int>>Matrix(m, std::vector<int>(n, -1));
        while(start_row<=m || start_column<=n) {
            int i = start_row,j = start_column;
            while(j<n) {
                if(head)  {
                    Matrix[i][j] = head->val;
                    head = head->next;
                }
                else return Matrix;
                j++;
            }
            j--;i++;
            while(i<m) {
                if(head)  {
                    Matrix[i][j] = head->val;
                    head = head->next;
                }
                else return Matrix;
                i++;
            }
            i--;j--;
           
            while(j>=start_column) {
                if(head)  {
                    Matrix[i][j] = head->val;
                    head = head->next;
                }
                else return Matrix;
                j--;
            }
            j++;i--;
            while(i>start_row) {
                if(head)  {
                    Matrix[i][j] = head->val;
                    head = head->next;
                }
                else return Matrix;
                i--;
            }
            start_row++;start_column++;
            m--;n--;
        }
        return Matrix;
    }
};