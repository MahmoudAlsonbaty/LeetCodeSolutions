#include <cmath>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i = 0;i<matrix.size()/2;i++){
            for(int j = i;j<matrix[0].size()-i-1;j++){
                //Do 4 rotations
                int n = matrix.size()-1;
                int first =  matrix[i][j];
                int second = matrix[j][n-i];
                int third = matrix[n-i][n-j];
                int fourth = matrix[n-j][i];
                // cout << matrix[i][j] << " ";
                matrix[j][n-i] = first;
                matrix[n-i][n-j] = second;
                matrix[n-j][i] = third;
                matrix[i][j] = fourth;
            }
        }
    }
};

int main(){
    vector<vector<int>> matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    // auto answer = Solution().rotate(matrix);
    Solution().rotate(matrix);
    for(int i = 0;i<matrix.size();i++){
        cout << endl;
        for(int j = 0;j<matrix[0].size();j++){
            cout<< matrix[i][j] << " ";
        }
    }
    // std::cout << matrix <<endl;
    return 0;
}
