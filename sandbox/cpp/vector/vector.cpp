#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;
    for (int i = 0; i < 1000; i++) {
        v.push_back(0);
        cout << v.size() << "\t" << v.capacity() << endl;
    }
    return 0;
}