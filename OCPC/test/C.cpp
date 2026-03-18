#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string run_type;
    cin >> run_type;
    if(run_type=="first"){
        int n;
        cin >> n;
        vector<int> p(2*n);
        for(auto &x:p){
            cin >> x;
            x--;
        }
        vector<bool> vis(2*n);
        for(int i=0;i<2*n;i++){
            if(vis[i])continue;
            vector<int> c;
            for(int j=i;!vis[j];j=p[j]){
                vis[j]=true;
                c.emplace_back(j);
            }
            if(c.size()>n){
                int m=c.size()/2;
                cout << c[0]+1 << " " << c[m]+1 << endl;
                exit(0);
            }
        }
        cout << 1 << " " << 1 << endl;
    }else{
        int n,x,y;
        cin >> n >> x;
        while(true){
            cout << x << endl;
            cin >> y;
            if(x==y)break;
            x=y;
        }
    }
}