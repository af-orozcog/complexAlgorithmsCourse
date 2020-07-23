#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    int posi = 1;
    for (int i = 0; i < m; ++i) {
        int f,t;
        cin >> f >> t;
        g[f].push_back(t);
    }
    vector<vector<int>> clausses;
    for(int i = 1; i <= n;++i){
        for(int j = 0; j < g[i].size();++j){
            vector<int> add1(3,0),add2(3,0),add3(3,0);
            add1[0] = -(i*3),add1[1] = -(g[i][j]*3);
            add2[0] = -(i*3-1),add2[1] = -(g[i][j]*3-1);
            add3[0] = -(i*3-2),add3[1] = -(g[i][j]*3-2);
            clausses.push_back(add1);
            clausses.push_back(add2);
            clausses.push_back(add3);
        }
        vector<int> add1(4,0),add2(3,0),add3(3,0),add4(3,0);
        add1[0] = (i*3-2),add1[1] = (i*3-1),add1[2] = (i*3);
        add2[0] = -(i*3-2),add2[1] = -(i*3-1);
        add3[0] = -(i*3-2),add3[1] = -(i*3);
        add4[0] = -(i*3-1), add4[1] = -(i*3);
        clausses.push_back(add1);
        clausses.push_back(add2);
        clausses.push_back(add3);
        clausses.push_back(add4);
    }
    cout << clausses.size() << " " << n*3 << "\n";
    for(auto &va:clausses){
        for(auto &ve:va)
            cout << ve << " ";
        cout << "\n";
    }
    return 0;
}
