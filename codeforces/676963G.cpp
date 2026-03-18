#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;

ll dpc[N][5],dpg[N][5];
ll pc[N],pg[N];

void runcase(){
    int g,c;
    cin >> g >> c;
    if(g==0&&c==0){
        cout << "GG\n";
        return;
    }
    int len=0;
    while(len<N&&(pc[len]<c||pg[len]<g))len++;
    string ans="";
    for(;len>0;len--){
        while(g>0&&g>=dpg[len][3]){
            ans.push_back('G');
            g-=dpg[len][3];
        }
        while(c>0&&c>=dpc[len][2]){
            ans.push_back('C');
            c-=dpc[len][2];
        }
        ans.push_back("TA"[len%2]);
    }
    assert(g==0&&c==0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dpc[0][0]=dpg[0][0]=1;
    for(int i=1;i<N;i++){
        for(int j=0;j<5;j++){
            dpc[i][j]=dpc[i-1][j];
            dpg[i][j]=dpg[i-1][j];
        }
        if(i%2){ // A
            dpc[i][2]+=dpc[i-1][1];
            dpg[i][1]+=dpg[i-1][0];
            dpg[i][3]+=dpg[i-1][2];
        }else{ // T
            dpc[i][1]+=dpc[i-1][0];
            dpg[i][2]+=dpg[i-1][1];
        }
        pc[i]=pc[i-1]+dpc[i][2];
        pg[i]=pg[i-1]+dpg[i][3];
    }
    int t;
    cin >> t;
    while(t--)runcase();
}