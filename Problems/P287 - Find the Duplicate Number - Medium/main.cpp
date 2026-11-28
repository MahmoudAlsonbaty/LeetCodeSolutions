#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        //We'll be using the tortoise and hare algorithm, Known as Floyd's Cycle finding
        int slow = 0; //Start at index 0: no value points to it, so it's outside the cycle
        int fast = 0;

        int i = 0;
        while(true){
            
            // cout << "["<<i<<"] ";
            i++;
            // cout << "Slow = "<<slow;
            // cout << ", Fast = "<<fast << endl;

            slow = nums[slow];
            fast = nums[nums[fast]];
            
            if(slow == fast) break; //It's guaranteed that there's a cycle so they must eventually meet
        }
        
            // cout << "["<<i<<"] ";
            i++;
            // cout << "Slow = "<<slow;
            // cout << ", Fast = "<<fast << endl;
            // cout << "NOW RESTARTING CYCLE" <<endl;
            slow = 0;
            while(true){
            
            // cout << "["<<i<<"] ";
            i++;
            // cout << "Slow = "<<slow;
            // cout << ", Fast = "<<fast << endl;

            slow = nums[slow];
            fast = nums[fast];

            if(slow == fast) break; //It's guaranteed that there's a cycle so they must eventually meet
        }
        // cout << "DONE"<<endl;
        //  cout << "["<<i<<"] ";
            i++;
            // cout << "Slow = "<<slow;
            // cout << ", Fast = "<<fast << endl;
        return slow;


    }
};



int main(){
    vector<int> nums = {1, 3, 4, 2, 2};
    auto answer = Solution().findDuplicate(nums);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    std::cout << answer <<endl;
    return 0;
}
