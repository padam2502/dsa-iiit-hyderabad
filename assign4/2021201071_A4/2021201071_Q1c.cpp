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
char T[MAX_N];                          // the input string, up to 100K characters
long long int n;                        // the length of input string
long long int RA[MAX_N], tempRA[MAX_N]; // rank array and temporary rank array
long long int SA[MAX_N], tempSA[MAX_N];
long long int Phi[MAX_N], PLCP[MAX_N],LCP[MAX_N]; // suffix array and temporary suffix array
long long int c[MAX_N];                 // for counting/radix sort
void countingSort(long long int k)
{                                               // O(n)
    long long int i, sum, maxi = max(300LL, n); // up to 255 ASCII chars or length of n
    memset(c, 0, sizeof c);                     // clear frequency table
    for (i = 0; i < n; i++)                     // count the frequency of each integer rank
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++)
    {
        long long int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) // shuffle the suffix array if necessary
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++) // update the suffix array SA
        SA[i] = tempSA[i];
}
void constructSA()
{ // this version can go up to 100000 characters
    long long int i, k, r;
    for (i = 0; i < n; i++)
        RA[i] = T[i]; // initial rankings
    for (i = 0; i < n; i++)
        SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1)
    {                           // repeat sorting process log n times
        countingSort(k);        // actually radix sort: sort based on the second item
        countingSort(0);        // then (stable) sort based on the first item
        tempRA[SA[0]] = r = 0;  // re-ranking; start from rank r = 0
        for (i = 1; i < n; i++) // compare adjacent suffixes
            tempRA[SA[i]] =     // if same pair => same rank r; otherwise, increase r
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++) // update the rank array RA
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break; // nice optimization trick
    }
}
void computeLCP()
{
    long long  i, L;
    Phi[SA[0]] = -1;            // default value
    for (i = 1; i < n; i++)     // compute Phi in O(n)
        Phi[SA[i]] = SA[i - 1]; // remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++)
    { // compute Permuted LCP in O(n)
        if (Phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        } // special case
        while (T[i + L] == T[Phi[i] + L])
            L++; // L increased max n times
        PLCP[i] = L;
        L = max(L - 1, 0LL); // L decreased max n times
    }
    for (i = 0; i < n; i++)   // compute LCP in O(n)
        LCP[i] = PLCP[SA[i]]; // put the permuted LCP to the correct position
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
    string ww=s;
    reverse(s.begin(),s.end());
    s = ww + "$"+s;

    for (long long int i = 0; i < s.size(); i++)
    {
        T[i] = s[i];
    }
    n = s.size();
    constructSA();
    computeLCP();
    // getline(T)
    // n = (int)strlen(); // input T as per normal, without the ‘$’
    // T[n++] = '$';
    // for (long long int i = 0; i < n; i++)
    // {
    //     // if (SA[i] < ans)
    //     // //cout<<SA[i]<<"  "<<s.substr(SA[i],n);
    //     // {
    //     //     cout << s.substr(SA[i], ans);
    //     //     cout << endl;
    //     //     break;
    //     // }
    //     cout<<SA[i]<<" "<<LCP[i]<<endl;
    // }
    long long anslength=0;
    long long Position=0;
    for(long long i=1;i<n;++i)
    {
        //Note that Len=Length of Original String +"#"+ Reverse String
        if((LCP[i]>anslength))
        {
            //Note Actual Len=Length of original Input string .
            if((SA[i-1]<ans && SA[i]>ans)||(SA[i]<ans && SA[i-1]>ans))
            {
                 //print :Calculating Longest Prefixes b/w suffixArray[i-1] AND  suffixArray[i]


                anslength=LCP[i];
              //print The Longest Prefix b/w them  is ..
              //print The Length is :longestlength:=LCP[i];
                Position=SA[i];
            }
        }
    }
    //cout<<anslength;
    cout << s.substr(Position, anslength);
    //     cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n";
    //  cout << "CPU-TIME START " << start << "\n";
    //  cout << "CPU-TIME END " << end << "\n";
    //  cout << "CPU-TIME END - START " << end - start << "\n";
    //  cout << "TIME(SEC) " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n";

    // printf("%2d\t%s\n", SA[i], T + SA[i]);
    return 0;
}