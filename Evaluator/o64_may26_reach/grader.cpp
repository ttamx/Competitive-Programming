#include "reach.cpp"
#include <cstdio>
#include <cassert>
#include <cstdlib>

int main()
{
	int n, q;
	assert(2 == scanf("%d %d", &n, &q));

	initialize(n);

	for(int i = 0; i< q; i++)
	{
		int cmd; 
		assert(1 == scanf("%d", &cmd));

		if(cmd == 1)
		{
			int u, v;
			assert(2 == scanf("%d %d", &u, &v));

			add_arc(u, v);
		}
		else if(cmd == 2)
		{
			int u, v, t;
			assert(3 == scanf("%d %d %d", &u, &v, &t));

			bool result = is_reachable(u, v, t);
			
			if(result) printf("1\n");
			else printf("0\n");
		}
		else
		{
			fprintf(stderr, "Wrong input: command not 1 or 2\n");
			exit(1);
		}
	}
}
