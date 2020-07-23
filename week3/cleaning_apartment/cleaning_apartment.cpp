#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n+1,vector<int> (n+1,0));
    for (int i = 0; i < m; ++i) {
        int from,to;
        cin >> from >> to;
        matrix[from][to] = 1;
        matrix[to][from] = 1;
    }
    vector<vector<int>> classes;
    for(int i = 1; i <= n;++i){
        vector<int> add;
        for(int j = 0; j < n;++j)
            add.push_back(i*n-j);
        classes.push_back(add);
        add.clear();
        for(int j = n-1; j > -1;--j){
            for(int k = i*n-j+1; k <= i*n;++k){
                add.push_back(-(i*n-j));
                add.push_back(-(k));
                if(add.size())
                    classes.push_back(add);
                add.clear();
            }
        }
        //cout << "wtf" << "\n";
        for(int k = n-1; k > 0;--k){
            for(int j = 1; j <= n;++j){
                if(j == i || matrix[i][j] == 1) continue;
                add.push_back(-(i*n-k));
                add.push_back(-(j*n-(k-1)));
                classes.push_back(add);
                add.clear();
            }
        }

    }
    for(int i = n-1; i > -1;--i){
        vector<int> add;
        for(int j = 1;j <= n;++j){
            add.push_back(j*n-i);
        }
        classes.push_back(add);
        add.clear();
    }
    for(int i = 1; i <= n;++i){
        vector<int> add;
        for(int j = n-1; j > 0;--j){
            for(int k = i+1;k <= n;++k){
                add.push_back(-(i*n-j));
                add.push_back(-(k*n-j));
                classes.push_back(add);
                add.clear();
            }
        }
    }
    cout << classes.size() << " " << n*n << "\n";
    for(auto &va:classes){
        for(auto &ve:va)
            cout << ve << " ";
        cout << "0\n";
    }
    return 0;
}
