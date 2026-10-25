#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int begin = 0;
        
        long long numberOfSubarrays = 0;
        for(int i = 0;i<nums.size();i++){ 
            if(nums[i] > maxK || nums[i] < minK){
                long long n = i - begin;
                long long elements = ((long long)n*((long long)n+1))/(long long)2;
                numberOfSubarrays += elements;
                begin = i+1;
            }else if (i+1 == nums.size()){
                if(nums[i] <= maxK && nums[i] >= minK){
                    i++;
                    long long n = i - begin;
                    long long elements = ((long long)n*((long long)n+1))/(long long)2;
                    numberOfSubarrays += elements;
                }
            }else{
                continue;
            }
            // for(int j = i;j<nums.size();j++){ 
            //     bool stop = false;
            //     for(int m = j;m<=j;m++){ 
            //         if(nums[m] > maxK){
            //             stop = true;
            //             break;
            //         }
            //         if(nums[m] < minK){
            //             stop = true;
            //             break;
            //         }
            //     }
            //     if(!stop){
            //         numberOfSubarrays++;
            //     }else{
            //         break;
            //     }   
            // }    
        }
        return numberOfSubarrays;
    }
};

int main(){
    vector<int> example = {1,4,7,3};
    auto answer = Solution().countSubarrays(example,1,5);

    std::cout << answer <<endl;
    return 0;
}
