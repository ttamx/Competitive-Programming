#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n,m;
    cin >> n >> m;
    if(n==1){
        cout << n*m << "\n";
        cout << "1 1 |\n";
        cout << m-1 << "\n";
        cout << string(m-1,'R') << "\n";
        return;
    }
    if(m==1){
        cout << n*m << "\n";
        cout << "1 1 -\n";
        cout << n-1 << "\n";
        cout << string(n-1,'D') << "\n";
        return;
    }
    vector<pair<int,char>> op;
    op.emplace_back(m-1,'L');
    for(int i=2;i<=n-1;i++){
        op.emplace_back(1,'D');
        op.emplace_back(1,'R');
        op.emplace_back(1,'D');
        op.emplace_back(1,'L');
        op.emplace_back(1,'U');
        op.emplace_back(m-1,'R');
        op.emplace_back(m-1,'L');
    }
    op.emplace_back(1,'D');
    op.emplace_back(1,'R');
    op.emplace_back(1,'U');
    op.emplace_back(1,'L');
    op.emplace_back(1,'D');
    op.emplace_back(m-1,'R');
    string ans="";
    for(auto [c,x]:op){
        for(int i=0;i<c;i++){
            ans.push_back(x);
        }
    }
    cout << n*m-1 << "\n";
    cout << "1 " << m << " |\n";
    cout << ans.size() << "\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}