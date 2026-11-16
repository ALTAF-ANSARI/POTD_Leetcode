class Solution {
public:
    int digitsum(int n){
        int sum=0;
        while(n>0){
            int rem=n%10;
            sum+=rem;
            n/=10;
        }
        return sum;
    }
    string digitSum(string s, int k) {
        while(s.size()>k){
            string altaf="";
            for(int i=0;i<s.size();i+=k){
                int sum=0;
                for(int j=i;j<min(i+k,(int)s.size());j++){
                    sum+=s[j]-'0';
                }
                altaf+=to_string(sum);
            }
            s=altaf;
        }
        return s;
    }
};