#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        string res = "";
        int columns = encodedText.length()/rows;
        vector<vector<char>> arr;
        int counter = 0;
        for(int i = 0;i<rows;i++){
            arr.push_back(vector<char>());
            for(int j = 0;j<columns;j++){
                arr[i].push_back(encodedText[counter]);
                counter++;
            }
        }
        for(int i = 0;i < columns;++i){
            int r = 0, c = i;
            while (r < rows && c < columns) {
                res.push_back(arr[r][c]);
                r++;
                c++;
            }
        }
        while (!res.empty() && res.back() == ' ') {
            res.pop_back();
        }
        return res;
    }
};


int main(){

    auto answer = Solution().decodeCiphertext("ch   ie   pr",3);

    std::cout << answer <<endl;
    return 0;
}