#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<vector<int>> g;
ll dp[100005];
ll dist[100005];

ll solve(int p, int dad){
    if(dp[p] != -1) return dp[p];
    ll ans1 = dist[p];
    for(auto va:g[p])
        if(va != dad)
            for(auto ve:g[va])
                if(ve != p)
                    ans1 += solve(ve,va);
    ll ans2 = 0;
    for(auto va:g[p])
        if(va != dad)
            ans2 += solve(va,p);
    dp[p] = max(ans2,ans1);
    return dp[p];
}

int main() {
    memset(dp,-1,sizeof(dp));
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    int n;
    scanf(" %d",&n);
    g.resize(n);
    for(int i = 0; i < n;++i)
        scanf(" %lld",&dist[i]);
    for(int i = 0; i < n-1;++i){
        int a,b;
        scanf(" %d %d",&a,&b);
        --a,--b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    printf("%lld\n",solve(0,-1));
    return 0;
}
