#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int k;
    string encoded_string;
    bool test;

public:
    string decodeString(string s)
    {
        k = 0;
        encoded_string = "";
        test = false;
        string ans = "";
        for (auto c : s)
        {
            if (c >= '0' && c <= '9')
            {
                k *= 10;
                k += (c - '0');
            }
            else if (c == '[')
            {
                test = true;
            }
            else if (c == ']')
            {
                while (k--)
                {
                    ans += encoded_string;
                }
                k = 0;
                encoded_string = "";
                test = false;
            }
            else
            {
                if (test)
                {
                    encoded_string += c;
                }
                else
                {
                    ans += c;
                }
            }
        }
        return ans;
    }
};

int main()
{
    Solution s;
    string ans = s.decodeString("3[a]2[bc]");
    cout << ans << endl;
    return 0;
}