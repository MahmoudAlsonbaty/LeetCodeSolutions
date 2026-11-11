#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int getTimeSinceDay0(string date){
        //Day 0 is gonna be 1970/1/1
        //Leap year divisible by 4
        const int days[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
        int Year = stoi(date.substr(0,4));
        int Month = stoi(date.substr(5,2));
        int Day = stoi(date.substr(8,2));
        int totalDays = 0;
        for(int y = 1970;y<=Year;y++){
            bool leapYear = (y%4 == 0);
            if(y%100 ==0){
                leapYear = false;
                if(y%400==0){
                    leapYear = true;
                }
            }
            //Last Year
            if(y == Year){
                for(int m=1;m<Month;m++){
                    if(m==2 && leapYear){
                        totalDays+=29;
                    }else{
                        totalDays+=days[m];
                    }
                }
                totalDays+=Day;
            }else{
                for(int m=1;m<=12;m++){
                    if(m==2 && leapYear){
                        totalDays+=29;
                    }else{
                        totalDays+=days[m];
                    }
                }
            }
        }
        return totalDays;
    }
    int daysBetweenDates(string date1, string date2) {
        int daysInD1 = getTimeSinceDay0(date1);
        int daysInD2 = getTimeSinceDay0(date2);

        return abs(daysInD1-daysInD2);
    }
};

int main(){
string date1 = "2100-09-22";
string date2 = "1991-03-12";
    auto answer = Solution().daysBetweenDates(date1,date2);
    
    // for(int i = 0;i<answer.size();i++){
    //     cout << endl;
    //     for(int j = 0;j<answer[i].size();j++){
    //         cout<< answer[i][j];
    //     }
    // }
    std::cout << answer <<endl;
    return 0;
}
