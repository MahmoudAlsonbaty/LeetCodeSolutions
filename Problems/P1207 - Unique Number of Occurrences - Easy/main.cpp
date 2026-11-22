#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> freq;
        for(auto t:arr){
            freq[t]++;
        }
        unordered_map<int,int> freqOpposite;
        for(auto &[key,Value]:freq){
            if(freqOpposite.count(Value) != 0) return false;
            freqOpposite[Value] = key;
        }
        return true;
    }
};



int main(){
    // vector<int> arr = {1, 2, 2, 1, 1, 3};
    // vector<int> arr = {1, 2};
    vector<int> arr = {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0};
    auto answer = Solution().uniqueOccurrences(arr);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
