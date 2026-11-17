class Solution{
public:
    int minimumChanges(string s,int k){
        int n=s.size();
        vector<vector<int>>factors(n+1);
        for(int d=1;d<n;d++){
            for(int len=d*2;len<=n;len+=d){
                factors[len].push_back(d);
            }
        }
        vector<vector<int>>cost(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int len=j-i+1;
                int minCost=n;
                for(int d:factors[len]){
                    int changes=0;
                    for(int offset=0;offset<d;offset++){
                        int left=i+offset;
                        int right=j-d+1+offset;
                        while(left<right){
                            if(s[left]!=s[right]){
                                changes++;
                            }
                            left+=d;
                            right-=d;
                        }
                    }
                    minCost=min(minCost,changes);
                }
                cost[i][j]=minCost;
            }
        }
        const int INF=1e9;
        vector<vector<int>>dp(n+1,vector<int>(k+1,INF));
        dp[0][0]=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                for(int h=0;h<=i-2;h++){
                    if(dp[h][j-1]==INF)continue;
                    dp[i][j]=min(dp[i][j],dp[h][j-1]+cost[h][i-1]);
                }
            }
        }
        return dp[n][k];
    }
};