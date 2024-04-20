#include<bits/stdc++.h>

using namespace std;

mt19937 rng(0);

int main(){
    auto gen=[&](int testcase){
        cout << "TEST CASE #" << testcase << endl;
        string name=to_string(testcase);
        if(name.size()==1)name="0"+name;
        ifstream fin("input/"+name+".in");
        ofstream fout("output/output_"+name+".txt");
        int n,m;
        fin >> n >> m;
        vector<vector<int>> a;
        for(int j=1;j<=m;j++){
            vector<int> v(n);
            for(auto &x:v)fin >> x;
            int r;
            fin >> r;
            if(r)a.emplace_back(v);
        }
        int tot=a.size();
        vector<vector<pair<vector<int>,vector<int>>>> c(n+1);
        for(int i=0;i<a.size();i++){
            int cnt=accumulate(a[i].begin(),a[i].end(),0);
            c[cnt].emplace_back(a[i],vector<int>{i});
        }
        auto check=[&](const vector<int> &a,const vector<int> &b){
            int cnt=0;
            for(int i=0;i<n;i++)if(a[i]!=b[i]&&++cnt>1)return false;
            return true;
        };
        vector<pair<vector<int>,vector<int>>> vec,prime;
        bool done=false;
        while(!done){
            done=true;
            vector<vector<pair<vector<int>,vector<int>>>> nc(n+1);
            vector<vector<bool>> ok(n+1);
            for(int i=0;i<=n;i++)ok[i].assign(c[i].size(),false);
            for(int i=0;i<=n;i++){
                for(int j=0;j<c[i].size();j++){
                    auto [x,ix]=c[i][j];
                    if(i<n){
                        for(int k=0;k<c[i+1].size();k++){
                            auto [y,iy]=c[i+1][k];
                            if(check(x,y)){
                                vector<int> z(n,-1);
                                for(int i=0;i<n;i++)if(x[i]==y[i])z[i]=x[i];
                                auto iz=ix;
                                for(auto ii:iy)iz.emplace_back(ii);
                                nc[i].emplace_back(z,iz);
                                ok[i][j]=ok[i+1][k]=true;
                            }
                        }
                    }
                    if(!ok[i][j])vec.emplace_back(c[i][j]);
                    else done=false;
                }
            }
            swap(c,nc);
        }
        for(auto [v,iv]:vec){
            vector<int> tmp;
            for(int i=0;i<n;i++){
                if(v[i]==0)tmp.emplace_back(-i-1);
                if(v[i]==1)tmp.emplace_back(i+1);
            }
            sort(iv.begin(),iv.end());
            prime.emplace_back(tmp,iv);
        }
        sort(prime.begin(),prime.end());
        prime.erase(unique(prime.begin(),prime.end()),prime.end());
        int p=prime.size();
        vector<int> state(p),cnt(m);
        int score=0;
        auto rand_double=[&](){
            double res=1;
            for(int i=0;i<3;i++)res*=1.0*(rng()%1024)/1024.0;
            return res;
        };
        while(score<tot){
            int i=rng()%p;
            int new_score=score;
            if(state[i]){
                for(auto j:prime[i].second){
                    if(--cnt[j]==0)new_score--;
                }
            }else{
                for(auto j:prime[i].second){
                    if(++cnt[j]==1)new_score++;
                }
            }
            state[i]^=1;
            if(rand_double()<exp(6.0*(new_score-score))){
                score=new_score;
                continue;
            }
            state[i]^=1;
        }
        vector<vector<int>> ans;
        for(int i=0;i<p;i++)if(state[i])ans.emplace_back(prime[i].first);
        fout << ans.size() << "\n";
        int sum=ans.size()-1;
        for(auto v:ans){
            fout << v.size();
            for(auto x:v)fout << " " << x;
            fout << "\n";
            sum+=v.size()-1;
        }
        cout << "SIZE = " << sum << "\n";
    };
    for(int i=1;i<=10;i++)gen(i);
}