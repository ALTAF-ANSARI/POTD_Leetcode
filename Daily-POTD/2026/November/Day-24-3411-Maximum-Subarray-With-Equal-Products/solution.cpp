class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n=nums.size();
        int count=min(n,2);
        for(int i=0;i<n;i++){
            bool valid=true;
            for(int j=i+1;j<n;j++){
                for(int k=i;k<j;k++){
                    if(gcd(nums[k],nums[j])!=1){
                        valid=false;
                        break;
                    }
                }
                if(!valid) break;
                count=max(count,j-i+1);
            }
        }
        return count;
    }
};