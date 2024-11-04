#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    vector<string> a(6);
    for(auto &x:a){
        cin >> x;
    }
    bool ans[2]={false,false};
    for(int t=0;t<2;t++){
        for(int i=0;i<7;i++){
            for(int j=0;j<3;j++){
                bool ok=true;
                for(int k=0;k<4;k++){
                    if(a[j+k][i]!="CF"[t]){
                        ok=false;
                    }
                }
                if(ok){
                    ans[t]=true;
                }
            }
        }
    }
    vector<vector<int>> mx(2,vector<int>(4,-1));
    for(int t=0;t<2;t++){
        for(int i=0;i<6;i++){
            for(int j=0;j<4;j++){
                bool ok=true;
                for(int k=0;k<4;k++){
                    if(a[i][j+k]!="CF"[t]){
                        ok=false;
                    }
                }
                if(ok){
                    mx[t][j]=max(mx[t][j],i);
                }
            }
        }
        for(int i=3;i<6;i++){
            for(int j=0;j<4;j++){
                bool ok=true;
                for(int k=0;k<4;k++){
                    if(a[i-k][j+k]!="CF"[t]){
                        ok=false;
                    }
                }
                if(ok){
                    mx[t][j]=max(mx[t][j],i);
                }
            }
            for(int j=0;j<4;j++){
                bool ok=true;
                for(int k=0;k<4;k++){
                    if(a[i-k][j+3-k]!="CF"[t]){
                        ok=false;
                    }
                }
                if(ok){
                    mx[t][j]=max(mx[t][j],i);
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        if(mx[0][i]>mx[1][i])ans[0]=true;
        else if(mx[0][i]<mx[1][i])ans[1]=true;
        else if(mx[0][i]!=-1)ans[0]=ans[1]=true;
    }
    if(ans[0]&&ans[1]){
        cout << "?\n";
    }else if(ans[0]){
        cout << "C\n";
    }else if(ans[1]){
        cout << "F\n";
    }else{
        cout << "0\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}