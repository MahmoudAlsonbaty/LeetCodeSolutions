#include <cstddef>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string removeStars(string s) {
        int deleted = 0;
        string empty= "";
        size_t starsExist = s.find('*');
        while(starsExist != s.npos){
            //Count the stars
            int counter = 0;
            int StartingPos = starsExist;
            while (s[StartingPos] == '*') {
                counter++;
                StartingPos++;
            }
            s.erase(s.begin()+starsExist,s.begin()+starsExist+counter);//remove stars
            s.erase(s.begin()+starsExist-counter,s.begin()+starsExist);//remove letters
            starsExist = s.find('*');
        }
        return s;
    }
};

int main(){

    auto answer = Solution().removeStars("ABCDE**");
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
