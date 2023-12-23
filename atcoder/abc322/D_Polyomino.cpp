#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a[4][4],b[4][4];
    vector<int> v[3];
    int sum=0;
    auto encode=[&](){
        int res=0;
        for(int i=0;i<16;i++)res|=a[i>>2][i&3]<<i;
        while((res&15)==0)res>>=4;
        while((res&4369)==0)res>>=1;
        return res;
    };
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                char c;
                cin >> c;
                a[j][k]=(c=='#');
                sum+=(c=='#');
            }
        }
        for(int d=0;d<4;d++){
            int res=encode();
            for(int j=0;j<4;j++){
                int res2=res;
                for(int k=0;k<4;k++){
                    v[i].emplace_back(res2);
                    res2<<=4;
                    if(res2>65535)break;
                }
                res<<=1;
                if(res&4369)break;
            }
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    b[j][k]=a[k][3-j];
                }
            }
            swap(a,b);
        }
    }
    if(sum!=16)return void(cout << "No\n");
    for(auto x:v[0])for(auto y:v[1])for(auto z:v[2])if((x|y|z)==65535)return void(cout << "Yes\n");
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}