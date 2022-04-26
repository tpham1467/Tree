#include <bits/stdc++.h>
using namespace std;
int GetMid(int x, int y) { return x + (y - x) / 2; }
int n, st[1000];
void build(int a[], int v, int l, int r)
{
    if (l == r)
        st[v] = a[l];
    else
    {
        int mid = (l + r) / 2;
        build(a, v * 2 + 1, l, mid);
        build(a, v * 2 + 2, mid + 1, r);
        st[v] = st[v * 2 + 1] + st[v * 2 + 2];
    }
}
int GetMaxRange(int l,int r)
{
    
}
int main()
{
    int arr[] = {1, 3, 2, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    build(arr,0,0,n-1);
    for (int i = 0; i < n; i++)
    {
        cout<<st[i]<<endl;
    }
    
    return 0;
}