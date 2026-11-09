#include <iostream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double sol = numeric_limits<double>::lowest();
        long int sum =0;
        int left= 0;
        for(int i = 0;i<nums.size();i++){
            sum+=nums[i];
            if(i-left+1 < k){
                continue;
            }else{
                sol = max(double(sol),double(sum)/(i-left+1));
                sum-= nums[left];
                left++;
            }
        }

        return sol;
    }
};


int main(){
    vector<int> test = {1,12,-5,-6,50,3};
    auto answer = Solution().findMaxAverage(test,4);

    std::cout << answer <<endl;
    return 0;
}
