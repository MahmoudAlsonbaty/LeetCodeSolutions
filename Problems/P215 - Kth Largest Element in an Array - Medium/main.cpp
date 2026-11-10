#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return *(nums.end()-k);
    }
};

int main(){
    vector<int> list{1,3,3,4,2,2,6,5,5};
    auto answer = Solution().findKthLargest(list,4);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
