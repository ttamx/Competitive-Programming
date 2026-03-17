#include <bits/stdc++.h>

using namespace std;

const int N=1<<12;

int w[N];

int main(){
    int val;
    cin >> val;
    string s;
    for(int i=0;cin >> s;i++){
        cin >> s;
        int val=0;
        for(auto x:s){
            val*=16;
            if(isdigit(x)){
                val+=x-'0';
            }else{
                val+=x-'a'+10;
            }
        }
        w[i]=val;
    }
    cin >> w[N-1];
    int ip=0;
    int cnt=0;
    while(ip<((1<<12)-2)){
        int a=w[ip],b=w[ip+1];
        cerr << ip << " : " << (a>>4) << "," << (a&15) << " " << (b>>4) << "," << (b&15) << " " ;
        cerr << w[ip+2] << "\n";
        int t=w[b>>4]&(~(1<<(b&15)));
        w[b>>4]=t|((w[a>>4]>>(a&15)&1)<<(b&15));
        cerr << w[ip+2] << "\n";
        ip=w[ip+2];
        cnt++;
        if(cnt>=(1<<12)){
            cerr << "TLE";
            break;
        }
    }
    cout << (w[N-1]&1);
}