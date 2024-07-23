//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution
{
public:

    vector <int> search(string pat, string txt)
    {
        vector<int> mathes;

        for (int i = 0; i < txt.size() - pat.size(); ++i) {
            int j = 0;
            for (; j < (long long)pat.size() - 7; j += 8) {
                long long x, y;
                x = *(long long*)(&txt[i + j]);
                y = *(long long*)(&pat[j]);
                if (x != y) {
                    goto missmath;
                }

            }

            if (j + 3 < pat.size()) {
                if (*(int*)(&txt[i + j]) != *(int*)(&pat[j])) {
                    goto missmath;
                }
                j += 4;
            }

            if (j + 1 < pat.size()) {
                if (*(short*)(&txt[i + j]) != *(short*)(&pat[j])) { goto missmath; }
                j += 2;
            }
            if (j < pat.size()) {
                if (txt[i + j] != pat[j]) {
                    goto missmath;
                }
            }

            mathes.push_back(i + 1);
        missmath:
            {}
        }
        return mathes;
    }

};

//{ Driver Code Starts.
int main()
{
    int t = 1;

    while (t--)
    {
        string S = "geeksforgeeks", pat = "geek";
        Solution ob;
        vector <int> res = ob.search(pat, S);
        if (res.size() == 0)
            cout << -1 << endl;
        else {
            for (int i : res) cout << i << " ";
            cout << endl;
        }
    }
    return 0;
}

// Contributed By: Pranay Bansal

// } Driver Code Ends