#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef pair<int,ll> pi;
#define INF 10000000000000

vector<vector<pi>> g;

ll dp[18][(1<<17)];

int n,m;

ll solve(int who,int mask){
    int see = 1 <<n;
    if(see-1 == mask){
        for(auto va:g[who])
            if(va.first == 0)
                return dp[who][mask] = va.second;
        return dp[who][mask] = INF;
    }
    if(dp[who][mask] != -1)return dp[who][mask];
    dp[who][mask] = INF;
    for(auto va:g[who]){
        if(!((mask>>(va.first))&1))
            dp[who][mask] = min(dp[who][mask],solve(va.first,mask|(1<<va.first))+va.second);
    }
    return dp[who][mask];
}

vector<int> nodes;
void getSol(int who,int mask){
    int see = 1 <<n;
    nodes.push_back(who);
    if(see-1 == mask) return;
    int next;
    ll ans = INF;
    for(auto va:g[who]){
        if(!((mask>>(va.first))&1))
            if(solve(va.first,mask|(1<<va.first))+va.second < ans)
                ans = solve(va.first,mask|(1<<va.first))+va.second,next = va.first;
    }
    getSol(next,mask|(1<<next));
}

int main() {
    memset(dp,-1,sizeof(dp));
    scanf(" %d %d",&n,&m);
    g.resize(n);
    while(m--){
        int from,to;ll cost;
        scanf(" %d %d %lld",&from,&to,&cost);
        --from,--to;
        g[from].push_back({to,cost});
        g[to].push_back({from,cost});
    }
    ll ans = solve(0,1);
    if(ans == INF) ans = -1;
    printf("%lld\n",ans);
    if(ans == -1) return 0;
    getSol(0,1);
    for(auto va:nodes)
        printf("%d ",va+1);
    puts("");
    return 0;
}
