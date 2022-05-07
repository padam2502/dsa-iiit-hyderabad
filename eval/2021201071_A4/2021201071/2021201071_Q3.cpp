#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <math.h>
#include<fstream>
using namespace std;

vector<string> split_string(string);

class Trie

{

public:

        unsigned long long int mark;

        Trie* array[2];

        Trie()

        {

            mark=0;

        for( long long int i=0;i<2;i++)

        {

            array[i]=NULL;

        }

        }

};

unsigned long long int solve(unsigned long long int t,Trie *root)

{

    Trie *temp=root;

    unsigned long long int val=0;

    for(long long int j=pow(2,6)-1;j>=0;j--)

    {

        if((t & (1ULL <<j)))

        {

            if(temp->array[0]!=NULL)

            {

                temp=temp->array[0];

                val+=(1ULL <<j);

            }

            else

            {

                temp=temp->array[1];

            }

        }

        else

        {

            if(temp->array[1]!=NULL)

            {

                temp=temp->array[1];

                val+=(1ULL <<j);

            }

            else

            {

                temp=temp->array[0];

            }

        }

    }

    return val;

}
vector<int> maxXor(vector<int> arr, vector<int> queries) {
    // solve here
    unsigned  long long int n,x,t,a,ans;
Trie* root=new Trie();

     for( long long int i=0;i<arr.size();i++)

    {

        Trie* curr=root;

        x=arr[i];

        for( long long int j=pow(2,6)-1;j>=0;j--)

        {

            if((x & (1ULL <<j)))

            {

                if(!(curr->array[1])) 

                curr->array[1]=new Trie();

            curr=curr->array[1];

            }

            else

            {

                if(!(curr->array[0])) 

                curr->array[0]=new Trie();

            curr=curr->array[0];

            }

        }

        curr->mark=1;

    }
    vector<int>re;
   for(long long i=0;i<queries.size();i++)

    {

        t=queries[i];

        ans=solve(t,root);

        re.push_back(ans);

    }
    return re;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(m);

    for (int i = 0; i < m; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<int> result = maxXor(arr, queries);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
