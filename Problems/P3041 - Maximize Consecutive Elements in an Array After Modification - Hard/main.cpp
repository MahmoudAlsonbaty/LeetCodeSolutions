#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int l = 0;
        int maxConsec =1;
        vector<int> longestSeq(nums.size(),1);
        for(int i = 1;i<nums.size();i++){
            //Add the number?
            if(nums[i] - nums[i-1] == 1){// We can add 1 to the number
                longestSeq[i] = longestSeq[i-1]+1;
                maxConsec = max(maxConsec,longestSeq[i]);
                continue;
            }else if(nums[i] - nums[i-1] == 2){// We can add 1 to the past number
                nums[i-1]++;
                longestSeq[i] = longestSeq[i-1]+1;
                maxConsec = max(maxConsec,longestSeq[i]);
                continue;
            }else if(nums[i] - nums[i-1] == 0){
                //Increase the current by 1 and keep it
                // nums[i]++;
                longestSeq[i] = longestSeq[i-1];
                maxConsec = max(maxConsec,longestSeq[i]);
                continue;
            }else{
                longestSeq[i] =1;
            }
            //The difference isn't 1
        }
        return maxConsec;
    }
};



int main(){
    // vector<int> nums = {2, 1, 5, 1, 1};
    vector<int> nums = {8,10,6,12,9,12,2,3,13,19,11,18,10,16};
    auto answer = Solution().maxSelectedElements(nums);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
