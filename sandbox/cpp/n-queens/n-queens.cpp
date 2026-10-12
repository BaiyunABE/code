#include <bits/stdc++.h>
using namespace std;

#define get(a, i) ((int)(((a) >> ((i) << 2)) & 0xf))
#define set(a, i, x)                          \
    do                                        \
    {                                         \
        (a) &= ~(0xfull << ((i) << 2));       \
        (a) |= ((uint64_t)(x) << ((i) << 2)); \
    } while (0)

class Solution
{
    vector<uint64_t> ans;
    uint64_t a;
    vector<bool> v;
    int n;

public:
    void arrangement_recursive_(int m)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i != j && abs(i - j) == abs(get(a, i) - get(a, j)))
                {
                    return;
                }
            }
        }
        if (m == n)
        {
            ans.push_back(a);
            return;
        }
        for (int i = 0; i < (m == 0 ? (n + 1) / 2 : n); i++)
        {
            if (v[i] == 0)
            {
                set(a, m, i);
                v[i] = true;
                arrangement_recursive_(m + 1);
                v[i] = false;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        this->n = n;
        v = vector<bool>(n, 0);
        arrangement_recursive_(0);

        int m = ans.size();
        for (int i = 0; i < m; i++)
        {
            a = ans[i];
            if (n % 2 == 1 && get(a, 0) == n / 2)
            {
                break;
            }
            for (int i = 0; i < n; i++)
            {
                int x = get(a, i);
                set(a, i, n - 1 - x);
            }
            ans.push_back(a);
        }

        sort(ans.begin(), ans.end());

        vector<vector<string>> sans;
        for (auto a : ans)
        {
            vector<string> sa;
            for (int i = 0; i < n; i++)
            {
                string s(n, '.');
                s[get(a, i)] = 'Q';
                sa.push_back(s);
            }
            sans.push_back(sa);
        }

        return sans;
    }
};

int main()
{
    int n;
    cin >> n;

    Solution s;
    auto ans = s.solveNQueens(n);
    for (auto a : ans)
    {
        for (auto s : a)
        {
            cout << s << endl;
        }
        cout << endl;
    }

    return 0;
}
