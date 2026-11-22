#include <functional>
#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char,int> freqA;
        unordered_map<char,int> freqB;
        for(int i = 0;i<s.length();i++){
            freqA[s[i]]++;
        }
        for(int i = 0;i<t.length();i++){
            freqB[t[i]]++;
        }

        if(freqA.size() != freqB.size()) return false;
        for(const auto[key, Value]:freqA){
            if(freqB[key] != Value) return false;
        }
        return true;
    }
};



int main(){

    auto answer = Solution().isAnagram("ggii","eekk");
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    std::cout << answer <<endl;
    return 0;
}
