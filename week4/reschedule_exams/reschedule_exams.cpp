#include <bits/stdc++.h>
using namespace std;


class TwoSAT{

public:
    vector<int> topo;
    vector<vector<int>> g;
    vector<vector<int>> gReverse;
    vector<int> marked;
    int n, m;

    void topoSort(int p){
        marked[p] = 1;
        for(auto va:gReverse[p])
            if(!marked[va])
                topoSort(va);
        topo.push_back(p);
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

    vector<bool> solution;
    bool solve(vector<vector<int>> &graph) {
        n = (int)graph.size()-1;
        g = graph;
        gReverse.resize(g.size());
        marked.resize(g.size(),0);
        SCC.resize(g.size(),-1);
        color.resize(g.size(),-1);
        solution.resize(g.size(),false);
        for(int i = 1; i <= n; ++i){
            for(auto va:g[i])
                gReverse[va].push_back(i);
        }
        n = n>>1;
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
        }
        if(!posi){return false;}
        for(int i = 1; i <=n;++i)
            if(SCC[i] < SCC[i+n])
                solution[i] = true;
        return true;
    }
};

int n, m;

int translate(int see){
    if(see < 0)
        return (-see)+n;
    return see;
}
int other(int x){
    if(x > n)
        return x-n;
    return x+n;
}

char colors[1004];

int red(int x){
    return x*3-2;
}

int blue(int x){
    return x*3-1;
}

int green(int x){
    return x*3;
}

char color(int x){
    if(x%3 == 1)
        return 'R';
    else if(x%3 == 2)
        return 'B';
    return 'G';
}

int main() {
    scanf(" %d %d",&n,&m);
    for(int i = 1; i <= n;++i)
        scanf(" %c",&colors[i]);
    n *= 3;
    vector<vector<int>> g((n<<1)+1);
    for(int i = 1; i <= n/3;++i){
        if(colors[i] == 'R'){
            g[red(i)].push_back(other(red(i)));
            g[other(blue(i))].push_back(green(i));
            g[other(green(i))].push_back(blue(i));
            g[blue(i)].push_back(other(green(i)));
            g[green(i)].push_back(other(blue(i)));
        }
        else if(colors[i] == 'B'){
            g[blue(i)].push_back(other(blue(i)));
            g[other(green(i))].push_back(red(i));
            g[other(red(i))].push_back(green(i));
            g[green(i)].push_back(other(red(i)));
            g[red(i)].push_back(other(green(i)));
        }
        else{
            g[green(i)].push_back(other(green(i)));
            g[other(blue(i))].push_back(red(i));
            g[other(red(i))].push_back(blue(i));
            g[blue(i)].push_back(other(red(i)));
            g[red(i)].push_back(other(blue(i)));
        }
    }
    for(int i = 0; i < m;++i){
        int a,b;
        scanf(" %d %d",&a,&b);
        g[green(a)].push_back(other(green(b)));
        g[red(a)].push_back(other(red(b)));
        g[blue(a)].push_back(other(blue(b)));
        g[green(b)].push_back(other(green(a)));
        g[red(b)].push_back(other(red(a)));
        g[blue(b)].push_back(other(blue(a)));
    }
    TwoSAT cr;
    if(cr.solve(g)){
        for(int i = 1; i <= n;++i){
            if(cr.solution[i])
                printf("%c",color(i));
        }
    }
    else puts("Impossible");
    return 0;
}
