#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        bool ans;
        string w1 = "";
        string w2 = "";
        for(auto t:word1){
            w1.append(t);
        }
        for(auto t:word2){
            w2.append(t);
        }
        
        return (w1 == w2);
    }
};

int main(){
    // auto answer = Solution().createGrid(3,3);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    // std::cout << matrix <<endl;
    return 0;
}
