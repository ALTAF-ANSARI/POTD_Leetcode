class Solution {
public:
    bool canAliceWin(int n) {
        int steps=0;
        if(n<10){
            return false;
        }
        int stones=10;
        while(n>=0){
            n-=stones;
            steps++;
            stones--;
            if(n<stones){
                break;
            }
        }
        if(steps%2==0){
            return false;
        }
        return true;
    }
};