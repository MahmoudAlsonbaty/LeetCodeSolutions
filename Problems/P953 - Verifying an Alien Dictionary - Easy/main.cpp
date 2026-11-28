#include <iostream>
#include <bits/stdc++.h>
#include <TestCase.h>
using namespace std;

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        for (size_t i = 1; i < words.size(); i++) {
            if (std::lexicographical_compare(
            words[i].begin(), words[i].end(),
            words[i-1].begin(), words[i-1].end(),
            [&order](unsigned char c1, unsigned char c2) {
                return find(order.begin(),order.end(),c1) < find(order.begin(),order.end(),c2);
                // return std::tolower(c1) < std::tolower(c2);
            }
            )) return false;
        }
        return true;
    }
};



int main(){
vector<string> words = {"hello", "leetcode"};
string order = "hlabcdefgijkmnopqrstuvwxyz";
    auto answer = Solution().isAlienSorted(words,order);
    
    // cout2DVector(&answer);   // vector<vector<T>>
    // coutVector(&answer);     // vector<T>
    coutBool(&answer); //True or False
    // std::cout << answer <<endl;
    return 0;
}
