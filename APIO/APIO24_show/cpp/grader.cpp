#include <bits/stdc++.h>
#include "Alice.cpp"
#include "Bob.cpp"

void error(const std::string &info){
    std::cout << info << std::endl;
    exit(0);
}

class AliceGrader{
	int n;
	long long X;
	std::vector<std::pair<int,int>> V;
public:
	void Main(){
		std::cin >> X;
		if(X < 1 || X > 1000000000000000000ll){
			error("Error: input value X is invalid.");
		}
		n = -1;
		V = Alice();
		if(n == -1){
			error("Error: function setN() is not called by function Alice().");
		}
		if(V.size() != n - 1){
			error("Error: number of edges returned by Alice() is not n-1.");
		}
		for(int i = 0;i < n - 1;++i){
			if(V[i].first <= 0 || V[i].first > n || V[i].second <= 0 || V[i].second > n){
				error("Error: edges returned by Alice() have invalid node.");
			}
		}
		std::cout << n << std::endl;
		for(int i = 0;i < n - 1;++i){
			std::cout << V[i].first << " " << V[i].second << std::endl;
		}
	}
	long long setN(int N){
		if(n != -1){
			error("Error: function setN() is called twice by function Alice().");
		}
		if(N < 2 || N > 5000){
			error("Error: value N in function setN() is invalid.");
		}
		n = N;
		return X;
	}
}aliceGrader;

class BobGrader{
	int n, m;
	long long X;
	std::vector<std::pair<int,int>> V;
public:
	void Main(){
		std::cin >> n >> m;
		if(n < 2 || n > 5000){
			error("Error: input value n is invalid.");
		}
		if(m < n - 1 - (n - 2) / 2 || m > n - 1){
			error("Error: input value m is invalid.");
		}
		V.resize(m);
		for(int i = 0;i < m;++i){
			std::cin >> V[i].first >> V[i].second;
			if(V[i].first <= 0 || V[i].first > n || V[i].second <= 0 || V[i].second > n){
				error("Error: input edges have invalid node.");
			}
		}
		X = Bob(V);
		if(X < 1 || X > 1000000000000000000ll){
			error("Error: value X returned by Bob() is invalid.");
		}
		std::cout << X << std::endl;
	}
}bobGrader; 

long long setN(int N){
	return aliceGrader.setN(N);
}

int main(){
	int T;
	std::cin >> T;
	if(T == 1){
		aliceGrader.Main();
	}
	else if(T == 2){
		bobGrader.Main();
	}
	else{
		error("Error: input value T is invalid.");
	}
	return 0;
}
