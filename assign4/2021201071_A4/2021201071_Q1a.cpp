#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdio>
#include <fstream>
#include <ctime>
using namespace std;
#define MAX_N 10000010                  // second approach: O(n log n)
char T[MAX_N];
                          // the input string, up to 100K characters
long long int n;                        // the length of input string
long long int Rankarr[MAX_N];
long long int tempRankarr[MAX_N]; // Rankarrnk array and temporary rank array
long long int SA[MAX_N];
long long int tempSA[MAX_N]; // suffix array and temporary suffix array
long long int c[MAX_N];                 // for counting/radix sort
void countingSort(long long int k)
{                                               // O(n)
    long long int i;
    long long int sum;
    long long int maxi = max(300LL, n); // up to 255 ASCII chars or length of n
    memset(c, 0, sizeof c);                     // clear frequency table
    for(i = 0;i<n;i++)
    {
        c[i+k<n ? Rankarr[i + k] : 0]++;
    }                     // count the frequency of each integer Rankarrnk
        
    for (i = sum = 0; i < maxi; i++)
    {
        long long int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) // shuffle the suffix array if necessary
        tempSA[c[SA[i] + k < n ? Rankarr[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++) // update the suffix array SA
        SA[i] = tempSA[i];
}
void constructSA()
{ // this version can go up to 100000 characters
    long long int i, k, r;
    for (i = 0; i < n; i++)
        Rankarr[i] = T[i]; // initial rankings
    for (i = 0; i < n; i++)
        SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1)
    {                           // repeat sorting process log n times
        countingSort(k);        // actually radix sort: sort based on the second item
        countingSort(0);        // then (stable) sort based on the first item
        tempRankarr[SA[0]] = r = 0;  // re-ranking; start from rank r = 0
        for (i = 1; i < n; i++) // compare adjacent suffixes
            tempRankarr[SA[i]] =     // if same pair => same rank r; otherwise, increase r
                (Rankarr[SA[i]] == Rankarr[SA[i - 1]] && Rankarr[SA[i] + k] == Rankarr[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++) // update the rank array RA
            Rankarr[i] = tempRankarr[i];
        if (Rankarr[SA[n - 1]] == n - 1)
            break; // nice optimization trick
    }
}
int main()
{
    // clock_t start, end;
    // start = clock();
    //     std::ifstream infile("input.txt");
    //   if (!infile.is_open()) {
    //       return;
    //   }
    string s;
    cin >> s;
    long long ans = s.size();
    //s.push_back('$');
    s = s + s;

    for (long long int i = 0; i < s.size(); i++)
    {
        T[i] = s[i];
    }
    n = s.size();
    constructSA();
    // getline(T)
    // n = (int)strlen(); // input T as per normal, without the ‘$’
    // T[n++] = '$';
    for (long long int i = 0; i < n; i++)
    {
        if (SA[i] < ans)
        //cout<<SA[i]<<"  "<<s.substr(SA[i],n);
        {
            cout << s.substr(SA[i], ans);
            cout << endl;
            break;
        }
    }
    //     cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n";
    //  cout << "CPU-TIME START " << start << "\n";
    //  cout << "CPU-TIME END " << end << "\n";
    //  cout << "CPU-TIME END - START " << end - start << "\n";
    //  cout << "TIME(SEC) " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n";

    // printf("%2d\t%s\n", SA[i], T + SA[i]);
    return 0;
}