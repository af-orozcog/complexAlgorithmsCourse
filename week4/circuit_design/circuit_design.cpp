#include <bits/stdc++.h>
using namespace std;

vector<int> topo;
vector<vector<int>> g;
vector<vector<int>> gReverse;
vector<int> marked;
int n, m;

int translate(int see){
    if(see < 0)
        return (-see)+n;
    return see;
}

void topoSort(int p){
    marked[p] = 1;
    for(auto va:gReverse[p])
        if(!marked[va])
            topoSort(va);
    topo.push_back(p);
}

int other(int x){
    if(x > n)
        return x-n;
    return x+n;
}
vector<int> SCC;
vector<int> color;

void dfs(int i, int sc){
    SCC[i] = sc;
    for(auto va:g[i]){
        if(SCC[va] == -1)
            dfs(va,sc);
    }
}

int main() {
    scanf(" %d %d",&n,&m);
    g.resize((n+4)<<1);
    gReverse.resize((n+4)<<1);
    marked.resize((n+4)<<1,0);
    SCC.resize((n+4)<<1,-1);
    color.resize((n+4)<<1,-1);
    for (int i = 0; i < m; ++i){
        int a,b;
        scanf(" %d %d",&a,&b);
        int opA = translate(-a),opB = translate(-b);
        a = translate(a);
        b = translate(b);
        g[opA].push_back(b);
        g[opB].push_back(a);
        gReverse[b].push_back(opA);
        gReverse[a].push_back(opB);
    }
    for(int i = 1; i <= (n<<1);++i)
        if(!marked[i]) topoSort(i);
    int SC = -1;
    reverse(topo.begin(),topo.end());
    for(auto va:topo){
        if(SCC[va] == -1)
            dfs(va,++SC);
    }
    bool posi = 1;
    for(int i = 1; i <= n && posi;++i){
        if(SCC[i] == SCC[i+n]) posi = 0;
        //printf("%d %d %d\n",i,SCC[i],SCC[i+n]);
    }
    if(!posi){puts("UNSATISFIABLE");return 0;}
    puts("SATISFIABLE");
    for(int i = 1; i <=n;++i)
        printf("%d ",(SCC[i] < SCC[i+n]?i:-i));
    puts("");
    return 0;
}
