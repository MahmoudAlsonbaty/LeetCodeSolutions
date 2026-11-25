#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    static bool customSort(int first, int second){
        // bool done = false;
        // int copyFirst = first;
        // int copySecond = second;
        // vector<int> fi;
        // while(copyFirst%10 >=0){
        //     if(copyFirst == 0) break;
        //     fi.push_back(copyFirst%10);
        //     copyFirst /= 10;
        // } 
        // vector<int> sec;
        // while(copySecond%10 >=0){
        //     if(copySecond == 0) break;
        //     sec.push_back(copySecond%10);
        //     copySecond /= 10;
        // }
        // int i = 0;
        // while(true){
        //     if(fi.size() > i && sec.size() > i){
        //         if(*(fi.end()-1-i) > *(sec.end()-1-i)){
        //             return true;
        //         }else if(*(fi.end()-1-i) == *(sec.end()-1-i)){
        //             i++;
        //             continue;
        //         }else{return false;}
        //     }else{


        //         if(fi.size() > i){
        //             if(*(fi.end()-1-i) == 0 ){
        //                 return false;
        //             }else{
        //                 return true;
        //             }
        //         }else {
        //             if(*(sec.end()-1-i) == 0 ){
        //                 return false;
        //             }else{
        //                 return true;
        //             }
        //         }
        //     }

        // }
            string x = to_string(first), y = to_string(second);
            return x + y > y + x;
    }


    string largestNumber(vector<int>& nums) {
        // unordered_map<int,vector<int>> brokenDown;
        // string sol;
        // int i = 0;
        // for(auto t:nums){
        //     vector<int> numberBrokenDown;
        //     int num =t;
        //     while(num%10 >0){
        //     numberBrokenDown.push_back(num/10);
        //     num /= 10;
        //     }
        //     reverse(numberBrokenDown.begin(),numberBrokenDown.end());
        //     brokenDown[i] = numberBrokenDown; 
        //     i++;
        // }
        // unordered_map<int,bool> used;
        // for(int j = 0;j<nums.size();j++){
        //     int selected;
        //     bool found = false;
        //     int number = 0;
        //     int index = 0;
        //     int localMax = -1;
        //     while(!found){
        //         if(localMax == brokenDown[number][index]){
        //             number = 0;
        //             localMax = -1;
        //             index++;
        //         }
        //         if(!used[nums[number]])localMax = max(localMax,brokenDown[number][index]);
        //         number++;
        //         if(number == nums.size()){
        //             selected = nums[number];
        //             used[nums[number]] = true;
        //             found = true;
        //             break;
        //         }
        //     }
        //     sol += to_string(selected);

        // }
        sort(nums.begin(),nums.end(),customSort);
        string sol = "";
        for(auto t:nums){
            sol+= to_string(t);
        }
    

        return sol;

    }
};



int main(){
    // vector<int> nums = {10, 2};
    vector<int> nums = {3, 30, 34, 5, 9};
    // vector<int> nums = {8308,8308,830};
    auto answer = Solution().largestNumber(nums);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // coutBool(&answer); //True or False
    std::cout << answer <<endl;
    return 0;
}
