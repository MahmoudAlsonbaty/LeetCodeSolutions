#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        //We'll be using the tortoise and hare algorithm, Known as Floyd's Cycle finding
        int slow = 1; //We'll offset by 1 because the array is 1 indexed
        int fast = 1;

        int i = 0;
        while(true){
            
            cout << "["<<i<<"] ";
            i++;
            cout << "Slow = "<<slow;
            cout << ", Fast = "<<fast << endl;

            if(slow == nums[slow-1] && slow < nums.size()) slow = nums[slow];
            else slow = nums[slow-1];

            if(fast == nums[nums[fast-1]-1] &&nums[fast-1] < nums.size() ) fast = nums[nums[fast-1]];
            else fast = nums[nums[fast-1]-1];
            
            if(slow == fast) break; //It's guaranteed that there's a cycle so they must eventually meet
        }
        
            cout << "["<<i<<"] ";
            i++;
            cout << "Slow = "<<slow;
            cout << ", Fast = "<<fast << endl;
            cout << "NOW RESTARTING CYCLE" <<endl;
            slow = 1;
            while(true){
            
            cout << "["<<i<<"] ";
            i++;
            cout << "Slow = "<<slow;
            cout << ", Fast = "<<fast << endl;

            if(slow == nums[slow-1] && slow+1 < nums.size()) slow = nums[slow];
            else slow = nums[slow-1];

            if(slow == fast) break; //It's guaranteed that there's a cycle so they must eventually meet
        }
        cout << "DONE"<<endl;
         cout << "["<<i<<"] ";
            i++;
            cout << "Slow = "<<slow;
            cout << ", Fast = "<<fast << endl;
        return 9999;


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
