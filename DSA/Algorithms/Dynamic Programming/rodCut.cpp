#include <bits/stdc++.h>
using namespace std;

int cutRod(vector<int> &price, int n)
{
    if (n == 0)
        return 0;
    int q = -(1000000 + 9);
    for (int i = 1; i <= n; i++)
        q = max(q, price[i] + cutRod(price, n - i));
    return q;
}

void inputPrice(int n, vector<int> &price)
{
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        price.push_back(x);
    }
}

int topDownMem_Aux(vector<int> &price, int n, int r[])
{
    if (r[n] >= 0)
        return r[n];
    int q;
    if (n == 0)
        q = 0;
    else
        q = -(1000000 + 9);

    for (int i = 1; i <= n; i++)
    {
        q = max(q, price[i] + topDownMem_Aux(price, n - i, r));
    }
    r[n] = q;
    return q;
}

int topDownMem(vector<int> &price, int n)
{
    int r[1000000];
    for (int i = 0; i <= n; i++)
    {
        r[i] = -(1000000 + 9);
    }
    return topDownMem_Aux(price, n, r);
}

int bottomUp(vector<int> &price, int n)
{
    int r[1000000];
    int s[1000000];
    r[0] = 0;
    int q;
    for (int j = 1; j <= n; j++)
    {
        q = -(1000000 + 9);
        for (int i = 1; i <= j; i++)
        {
            if(q<(price[i]+r[j-i]))
            {
                q = price[i]+r[j-i];
                s[j]=i;
            }
        }
        r[j] = q;
    }
    
    cout<<"printing solution for bottom up\n";
    cout<<r[n]<<endl;
    while(n>0)
    {
        cout<<s[n]<<" ";
        n = s[n]-n;
    }
    return r[n];
}

void outputPrice(int n, vector<int> &price)
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " " << price[i] << endl;
    }
}

int main()
{
    vector<int> price;
    int n;
    cin >> n;
    price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    clock_t start, end;

    start = clock();
    cout << cutRod(price, n);
    cout<<endl;
    end = clock();
    cout<<"Time for recursion : "<< double(end - start)*1000 <<"ms"<<endl;

    start = clock();
    cout << topDownMem(price, n);
    cout<<endl;
    end = clock();
    cout<<"Time for topDownMemo : "<< double(end - start)*1000 <<"ms"<<endl;

    start = clock();
    bottomUp(price, n);
    end = clock();
    cout<<"Time for bottomUp : "<< double(end - start)*1000 <<"ms"<<endl;
    return 0;
}