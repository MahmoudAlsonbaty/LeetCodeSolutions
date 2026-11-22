#include <cstddef>
#include <functional>
#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> sol;
        vector<string> sorted = strs;
        for(auto &t:sorted){
            sort(t.begin(),t.end());
        }
        hash<string>stringHash;
        unordered_map<size_t,vector<string>> hashes;
        
        for(int i = 0;i<strs.size();i++){
            hashes[stringHash(sorted[i])].push_back(strs[i]);
        }
        int i =0;
        for(auto &[key, Value]:hashes){
            sol.push_back({});
            for(auto t:Value){
                sol[i].push_back(t);
            }
            i++;
        }
        return sol;
    }
};



int main(){
vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto answer = Solution().groupAnagrams(strs);
    
    cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    // std::cout << answer <<endl;
    return 0;
}
