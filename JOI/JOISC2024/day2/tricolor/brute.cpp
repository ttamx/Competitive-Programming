#include<bits/stdc++.h>

using namespace std;

mt19937 rng(998244353);

const int S=6;
const int D=9;
const int M=27*27;

int decode[M];
int score,max_score;
int encode[M][D];
int pw[S];

int calc(){
    int res=0;
    vector<int> a,b,c;
    int pattern;
    function<bool(int,int)> check=[&](int x,int b){
        if(b<0)return decode[x]!=0;
        for(int i=0;i<3;i++)if(!check(pw[b]*i+x,b-1))return false;
        return true;
    };
    function<void()> gen=[&](){
        if(b.size()==S){
            int val=0,base=1;
            for(auto x:b){
                val+=x*base;
                base*=3;
            }
            if(decode[val]!=0){
                for(int x=val,b=S-1;;x/=3,b--){
                    if(!check(x,b))return;
                    if(x==0)break;
                }
                c[decode[val]]=10;
            }else{
                c[decode[val]]=1;
            }
            encode[pattern][decode[val]]=val;
            return;
        }
        for(int i=0;i<3;i++)if(i!=a[b.size()]){
            b.emplace_back(i);
            gen();
            b.pop_back();
        }
    };
    function<void()> brute=[&](){
        if(a.size()==S){
            c.assign(D,0);
            pattern=0;
            int base=1;
            for(auto x:a){
                pattern+=x*base;
                base*=3;
            }
            gen();
            for(auto x:c)res+=x;
            return;
        }
        for(int i=0;i<3;i++){
            a.emplace_back(i);
            brute();
            a.pop_back();
        }
    };
    brute();
    return res;
}

double rand_double(){
    double res=1;
    for(int i=0;i<3;i++)res*=1.0*(rng()%1024)/1024.0;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<S;i++)pw[i]=pw[i-1]*3;
    for(int i=0;i<M;i++){
        decode[i]=rng()%(D-1)+1;
    }
    score=max_score=calc();
    while(true){
        int idx=rng()%M;
        int val=rng()%D;
        int memo=decode[idx];
        decode[idx]=val;
        int new_score=calc();
        if(rand_double()<exp(6.0*(new_score-score))){
            score=new_score;
            if(score>max_score){
                printf("score : %d -> %d\n",max_score,score);
                max_score=score;
            }
            if(max_score==M*(10*D-9))break;
        }else{
            decode[idx]=memo;
        }
    }
    ofstream fout("tmp.txt");
    fout << "int decode[" << M << "] = {";
    for(int i=0;i<M;i++){
        if(i)fout << ",";
        if(i%27==0)fout << "\n\t";
        fout << decode[i];
    }
    fout << "\n};\n\n";
    fout << "int encode[" << M << "][" << D << "] = {";
    for(int i=0;i<M;i++){
        if(i)fout << ",";
        if(i%9==0)fout << "\n\t";
        fout << "{";
        for(int j=0;j<D;j++){
            fout << encode[i][j] << ",}"[j==D-1];
        }
    }
    fout << "\n};\n";
}