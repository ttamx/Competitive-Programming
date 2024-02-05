#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "library.cpp"
using namespace std;
void Solve(int N);

namespace {
struct Judge
{
	int N;
	int A[1002];
	int pos[1002];
	bool f[1002];
	int query_c;
	bool answered;
	void init()
	{
		query_c=0;
		int ret=scanf("%d",&N); ret++;
		answered=false;
		for(int i=0;i<N;i++)ret=scanf("%d",&A[i]),pos[A[i]]=i;
	}
	int query(const vector<int>& M)
	{
		if(query_c==20000)
		{
			puts("Wrong Answer [3]");
			exit(0);
		}
		if(int(M.size())!=N)
		{
			puts("Wrong Answer [1]");
			exit(0);
		}
		bool all_zero=true;
		for(int i=0;i<N;i++)
		{
			if(M[i]!=0&&M[i]!=1)
			{
				puts("Wrong Answer [2]");
				exit(0);
			}
			if(M[i]==1)all_zero=false;
		}
		if(all_zero)
		{
			puts("Wrong Answer [2]");
			exit(0);
		}
		memset(f,0,sizeof(f));
		for(int i=0;i<N;i++)if(M[i])f[pos[i+1]]=true;
		bool las=false;
		int r=0;
		for(int i=0;i<N;i++)
		{
			if(las==false&&f[i]==true)r++;
			las=f[i];
		}
		query_c++;
		return r;
	}
	void answer(const vector<int>& res)
	{
		bool f1=true,f2=true;
		if(int(res.size())!=N)
		{
			puts("Wrong Answer　[4]");
			exit(0);
		}
		if(answered)
		{
			puts("Wrong Answer [7]");
			exit(0);
		}
		answered=true;
		memset(f,0,sizeof(f));
		for(int i=0;i<N;i++)
		{
			if(res[i]<=0||res[i]>N)
			{
				puts("Wrong Answer [5]");
				exit(0);
			}
			if(f[res[i]])
			{
				puts("Wrong Answer [6]");
				exit(0);
			}
			f[res[i]]=true;
		}
		for(int i=0;i<N;i++)
		{
			f1&=A[i]==res[i];
			f2&=A[i]==res[N-i-1];
		}
		if(!f1&&!f2)
		{
			puts("Wrong Answer　[8]");
			exit(0);
		}
	}
	void end()
	{
		if(!answered)puts("Wrong Answer [7]");
		else printf("Accepted : %d\n",query_c);
	}
}judge;
}

int Query(const vector<int>& M)
{
	for(auto &x:M)cerr << x << " ";
	int res=judge.query(M);
	cerr << ": " << res << "\n";
	return res;
}
void Answer(const vector<int>& res)
{
	judge.answer(res);
}

int main()
{
	judge.init();
	Solve(judge.N);
	judge.end();
}
