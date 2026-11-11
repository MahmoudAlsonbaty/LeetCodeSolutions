#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> sol = {};
        for(int i =0;i<nums1.size();i++){
            auto loc = find(nums2.begin(),nums2.end(),nums1[i]);
            bool found = false;
            while (loc!=nums2.end()) {
                if(*loc > nums1[i]){
                    sol.push_back(*loc);
                    found = true;
                    break;
                }else{
                    loc++;
                }
            }
            if(!found) sol.push_back(-1);
        }
        return sol;
    }
};

int main(){
vector<int> nums1 = {2, 4};
vector<int> nums2 = {1, 2, 3, 4};
    auto answer = Solution().nextGreaterElement(nums1,nums2);
    
    for(int i = 0;i<answer.size();i++){
        cout << endl;
        cout<< answer[i];
    }
    // std::cout << answer <<endl;
    return 0;
}
