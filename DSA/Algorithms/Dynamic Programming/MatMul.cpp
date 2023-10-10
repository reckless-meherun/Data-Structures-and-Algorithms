#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[1010][1010] = {{1, 1}, {2, 2}};
int B[1010][1010] = {{1, 1}, {2, 2}};

vector<vector<int>> matMul(int A[1010][1010], int B[1010][1010], int p, int q, int s, int r)
{
    vector<vector<int>> C(p, vector<int>(r, 0));
    if (q != s)
    {
        cout << "Multiplication not possible\n";
    }
    else
    {
        for (int i = 0; i < p; i++)
        {
            for (int j = 0; j < r; j++)
            {
                for (int k = 0; k < q; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    return C;
}

void printMatrix(vector<vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    printMatrix(matMul(A,B,2,2,2,2));
    //matMul(A, B, 2, 2, 2, 2);
    return 0;
}