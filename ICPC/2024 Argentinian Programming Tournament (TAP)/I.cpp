#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<char>> a(n,vector<char>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<set<int>> row(n),col(m);
    int tot=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                row[i].emplace(j);
                col[j].emplace(i);
                tot++;
            }
        }
    }
    if(tot<2){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << (a[i][j]=='.') << " \n"[j==m-1];
            }
        }
        exit(0);
    }
    if(tot>1){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(a[i][j]=='.'){
                    if(row[i].size()==1&&col[j].size()==1){
                        cout << "*";
                        exit(0);
                    }
                }
            }
        }
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        if(row[i].size()%2){
            cnt++;
        }
    }
    for(int i=0;i<m;i++){
        if(col[i].size()%2){
            cnt++;
        }
    }
    if(cnt>2){
        cout << "*";
        exit(0);
    }
    int si=-1,sj=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                if(row[i].size()%2||col[j].size()%2){
                    si=i,sj=j;
                    break;
                }
            }
        }
        if(si!=-1)break;
    }
    if(si==-1){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(a[i][j]=='.'){
                    si=i,sj=j;
                    break;
                }
            }
            if(si!=-1)break;
        }
    }
    vector<bool> brow(n),bcol(m);
    vector<vector<int>> ans(n,vector<int>(m));
    ans[si][sj]=1;
    int dir=row[si].size()%2;
    for(int t=2;t<=tot;t++){
        row[si].erase(sj);
        col[sj].erase(si);
        if(dir){
            bool found=false;
            auto it=col[sj].upper_bound(si);
            for(auto it2=it;it2!=col[sj].end();it2++){
                if(t==tot||row[*it2].size()>1){
                    si=*it2;
                    found=true;
                    break;
                }
            }
            if(!found){
                for(auto it2=it;it2!=col[sj].begin();){
                    it2--;
                    if(t==tot||row[*it2].size()>1){
                        si=*it2;
                        found=true;
                        break;
                    }
                }
            }
            assert(found);
        }else{
            bool found=false;
            auto it=row[si].upper_bound(sj);
            for(auto it2=it;it2!=row[si].end();it2++){
                if(t==tot||col[*it2].size()>1){
                    sj=*it2;
                    found=true;
                    break;
                }
            }
            if(!found){
                for(auto it2=it;it2!=row[si].begin();){
                    it2--;  
                    if(t==tot||col[*it2].size()>1){
                        sj=*it2;
                        found=true;
                        break;
                    }
                }
            }
            assert(found);
        }
        ans[si][sj]=t;
        dir^=1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << ans[i][j] << " \n"[j==m-1];
        }
    }
}