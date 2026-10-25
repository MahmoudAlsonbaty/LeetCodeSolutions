#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int sum = 0;
        unordered_map<char,int> values = {
            {'I',1},
            {'V',5},
            {'X',10},
            {'L',50},
            {'C',100},
            {'D',500},
            {'M',1000},
        };

        for(int i = 0;i<s.size();i++){
            char c = s[i];
            int val = values[c];
            if (i > 0){       
                if(c == 'V'){
                    if(s[i-1] == 'I'){
                        val -= 1;
                        sum -= 1; // Because in the previous run we counted I
                    }
                }else if(c == 'X'){
                    if(s[i-1] == 'I'){
                        val -= 1;
                        sum -= 1; // Because in the previous run we counted I
                    }
                }else if(c == 'L'){
                    if(s[i-1] == 'X'){
                        val -= 10;
                        sum -= 10; // Because in the previous run we counted X
                    }
                }else if(c == 'C'){
                    if(s[i-1] == 'X'){
                        val -= 10;
                        sum -= 10; // Because in the previous run we counted X
                    }
                }else if(c == 'D'){
                    if(s[i-1] == 'C'){
                        val -= 100;
                        sum -= 100; // Because in the previous run we counted C
                    }
                }else if(c == 'M'){
                    if(s[i-1] == 'C'){
                        val -= 100;
                        sum -= 100; // Because in the previous run we counted C
                    }
                }
            }
            sum += val;
        }

        return sum;
    }
};

int main(){
    int answer = Solution().romanToInt("MCDLXXVI");
    std::cout << answer ;
    return 0;
}
