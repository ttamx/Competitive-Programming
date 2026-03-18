#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n=30;
    cout << n << endl;
    vector<vector<bool>> bad(n,vector<bool>(n));
    vector<pair<int,int>> cands;
    auto ask=[&](vector<vector<int>> a){
        cands.clear();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(bad[i][j]){
                    assert(a[i][j]==0);
                }else{
                    assert(a[i][j]!=0);
                }
            }
        }
        cout << "QUERY" << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        int s,m;
        cin >> s >> m;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i][j]!=s){
                    bad[i][j]=true;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i][j]==s){
                    vector<pair<int,int>> q;
                    auto push=[&](int ii,int jj){
                        if(ii<0||ii>=n||jj<0||jj>=n||a[ii][jj]!=s)return;
                        q.emplace_back(ii,jj);
                        a[ii][jj]=-1;
                    };
                    push(i,j);
                    for(int k=0;k<q.size();k++){
                        auto [ii,jj]=q[k];
                        push(ii-1,jj);
                        push(ii,jj-1);
                        push(ii,jj+1);
                        push(ii+1,jj);
                    }
                    if(q.size()!=m){
                        for(auto [ii,jj]:q){
                            bad[ii][jj]=true;
                        }
                    }else{
                        cands.insert(cands.end(),q.begin(),q.end());
                    }
                }
            }
        }
        return make_pair(s,m);
    };
    vector<vector<int>> a(n,vector<int>(n));
    for(int i=0;i<3;i++){
        for(int j=0;j<15;j++){
            a[i][j]=i+1;
        }
        int idx=15;
        int add=0;
        for(int j=1;j<=5;j++){
            for(int k=0;k<j;k++){
                a[i][idx]=(i+1+add)%3+1;
                idx++;
            }
            add^=1;
        }
    }
    for(int i=3;i<n;i++){
        int c1=(4-i%3)%3;
        int c2=(5-i%3)%3;
        int l=15+i/3;
        for(int j=0;j<n;j++){
            a[i][j]=(j<l?c1:c2)+1;
        }
    }
    ask(a);
    assert(cands.size()<=24);
    vector<int> szs;
    for(int i=0;i<3;i++)szs.emplace_back(3);
    for(int i=0;i<3;i++)szs.emplace_back(2);
    for(int i=0;i<9;i++)szs.emplace_back(1);
    a.assign(n,vector<int>(n,0));
    int col=0;
    for(auto s:szs){
        if(s>cands.size()){
            continue;
        }
        for(int i=0;i<s;i++){
            auto [ii,jj]=cands.back();
            cands.pop_back();
            a[ii][jj]=col+1;
        }
        col=(col+1)%3;
    }
    ask(a);
    assert(cands.size()<=3);
    a.assign(n,vector<int>(n,0));
    for(int i=0;i<cands.size();i++){
        auto [ii,jj]=cands[i];
        a[ii][jj]=i+1;
    }
    ask(a);
    assert(cands.size()==1);
    auto [i,j]=cands[0];
    cout << "ANSWER" << endl;
    cout << i+1 << " " << j+1 << endl;
}