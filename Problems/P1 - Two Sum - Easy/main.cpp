#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> solution;
        for(int i = 0;i<nums.size();i++){
            for(int j = i+1;j<nums.size();j++){
                if(nums[i]+nums[j] == target){
                    solution.push_back(i);
                    solution.push_back(j);
                    return solution;
                }
            }
        }
        return vector<int>{-1,-1};
    }
    
};

int main(){
    vector<int> example{3,2,4};
    vector<int> answer = Solution().twoSum(example,6);

    std::cout << answer[0] << " " << answer[1];
    return 0;
}
