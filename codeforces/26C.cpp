#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,a,b,c;
    cin >> n >> m >> a >> b >> c;
    if(n*m%2==1){
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<string> ans(n,string(m,'-'));
    if(n%2==1){
        for(int j=0;j+1<m;j++){
            if(ans[n-1][j]=='-'&&ans[n-1][j+1]=='-'){
                if(a==0)return void(cout << "IMPOSSIBLE\n");
                a--;
                ans[n-1][j]=ans[n-1][j+1]=(a%2?'c':'d');
            }
        }
    }
    if(m%2==1){
        for(int i=0;i+1<n;i++){
            if(ans[i][m-1]=='-'&&ans[i+1][m-1]=='-'){
                if(b==0)return void(cout << "IMPOSSIBLE\n");
                b--;
                ans[i][m-1]=ans[i+1][m-1]=(b%2?'e':'f');
            }
        }
    }
    a/=2,b/=2;
    for(int i=0;i+1<n;i+=2){
        for(int j=0;j+1<m;j+=2){
            int t=(i/2+j/2)%2;
            if(ans[i][j]=='-'){
                if(c>0){
                    c--;
                    ans[i][j]=ans[i][j+1]=ans[i+1][j]=ans[i+1][j+1]=(t?'a':'b');
                }else if(a>0){
                    a--;
                    ans[i][j]=ans[i][j+1]=(t?'g':'h');
                    ans[i+1][j]=ans[i+1][j+1]=(t?'i':'j');
                }else if(b>0){
                    b--;
                    ans[i][j]=ans[i+1][j]=(t?'k':'l');
                    ans[i][j+1]=ans[i+1][j+1]=(t?'m':'n');
                }else{
                    return void(cout << "IMPOSSIBLE\n");
                }
            }
        }
    }
    for(auto x:ans)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}