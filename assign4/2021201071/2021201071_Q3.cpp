#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
class Trie
{
public:
	unsigned long long int mark;
	Trie *array[2];
	Trie()
	{
		mark = 0;
		for (long long int i = 0; i < 2; i++)
		{
			array[i] = NULL;
		}
	}
};
unsigned long long int solve(unsigned long long int t, Trie *root)
{
	Trie *temp = root;
	unsigned long long int val = 0;
	for (long long int j = pow(2, 6) - 1; j >= 0; j--)
	{
		if ((t & (1ULL << j)))
		{
			if (temp->array[0] != NULL)
			{
				temp = temp->array[0];
				val += (1ULL << j);
			}
			else
			{
				temp = temp->array[1];
			}
		}
		else
		{
			if (temp->array[1] != NULL)
			{
				temp = temp->array[1];
				val += (1ULL << j);
			}
			else
			{
				temp = temp->array[0];
			}
		}
	}
	return val;
}
int main()
{
	unsigned long long int n, x, t, a, ans;
	long long q;
	cin >> n >> q;
	vector<unsigned long long int> v;
	for (long long int i = 0; i < n; i++)
	{
		cin >> a;
		v.push_back(a);
	}
	Trie *root = new Trie();
	for (long long int i = 0; i < n; i++)
	{
		Trie *curr = root;
		x = v[i];
		for (long long int j = pow(2, 6) - 1; j >= 0; j--)
		{
			if ((x & (1ULL << j)))
			{
				if (!(curr->array[1]))
					curr->array[1] = new Trie();
				curr = curr->array[1];
			}
			else
			{
				if (!(curr->array[0]))
					curr->array[0] = new Trie();
				curr = curr->array[0];
			}
		}
		curr->mark = 1;
	}
	while (q--)
	{
		cin >> t;
		ans = solve(t, root);
		cout << ans << endl;
	}
	return 0;
}