#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x){
    return rng()%x;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

double rand_double(){
    double res=1;
    for(int t=0;t<3;t++){
        res=(res*rnd(1024))/1024;
    }
    return res;
}

void gencase(int test_num){
    cout << test_num << endl;
    string name=to_string(test_num);
    if(name.size()<2)name='0'+name;
    ifstream fin("../test/"+name+".in");
    ofstream fout("sol/output_"+name+".txt");
    int n,m,k,full_score;
    fin >> n >> m >> k >> full_score;
    vector<int> h(k),w(k),v(k),a(k),b(k);
    vector<vector<int>> id(11);
    vector<vector<int>> cnt(n+2,vector<int>(m+2));
    vector<vector<int>> qs(n+2,vector<int>(m+2));
    for(int i=0;i<k;i++){
        fin >> h[i] >> w[i] >> v[i];
        id[v[i]].emplace_back(i);
    }
    for(int t=10;t>=1;t--){
        cout << "computing level " << t << endl;
        sort(id[t].begin(),id[t].end(),[&](int i,int j){
            return h[i]*w[i]>h[j]*w[j];
        });
        for(auto idx:id[t]){
            tuple<int,int,int> res(1e9,0,0);
            for(int i=0;i+h[idx]<=n;i++){
                for(int j=0;j+w[idx]<=m;j++){
                    int val=qs[i+h[idx]][j+w[idx]]-qs[i+h[idx]][j]-qs[i][j+w[idx]]+qs[i][j];
                    res=min(res,{val,i,j});
                }
            }
            int _;
            tie(_,a[idx],b[idx])=res;
            for(int i=0;i<h[idx];i++){
                for(int j=0;j<w[idx];j++){
                    cnt[a[idx]+i+1][b[idx]+j+1]=1;
                }
            }
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    qs[i][j]=cnt[i][j]+qs[i-1][j]+qs[i][j-1]-qs[i-1][j-1];
                }
            }
        }
    }
    cout << endl;
    for(int t=1;t<=10;t++){
        for(auto i:id[t]){
            fout << i+1 << " " << a[i] << " " << b[i] << "\n";
        }
    }
}

int main(){
    for(int i=1;i<=10;i++)gencase(i);
}