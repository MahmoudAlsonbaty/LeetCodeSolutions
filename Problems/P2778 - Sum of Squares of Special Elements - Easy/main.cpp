#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int sum = 0;
        for(int i = 0;i<nums.size();i++){
            if(nums.size()%(i+1) ==0) sum+= nums[i]*nums[i];
        }
        return sum;
    }
};
int main(){
    vector<int> arr = {2,7,1,19,18,3};
    auto answer = Solution().sumOfSquares(arr);

    std::cout << answer <<endl;
    return 0;
}
