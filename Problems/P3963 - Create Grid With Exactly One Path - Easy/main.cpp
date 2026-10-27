#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> sol;
        for(int i = 0;i<m;i++){
            sol.push_back("");
            for(int j = 0;j<n;j++){
                if(i == 0){
                    sol[i].push_back('.');
                    continue;
                }
                if(j == n-1){
                    sol[i].push_back('.');
                    continue;
                }
                sol[i].push_back('#');
            }
        }
        return sol;
    }

};

int main(){
    auto answer = Solution().createGrid(3,3);
    
    for(int i = 0;i<answer.size();i++){
        cout << endl;
        for(int j = 0;j<answer[i].size();j++){
            cout<< answer[i][j];
        }
    }
    // std::cout << matrix <<endl;
    return 0;
}
