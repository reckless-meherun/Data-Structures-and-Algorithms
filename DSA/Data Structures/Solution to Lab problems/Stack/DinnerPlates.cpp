#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class DinnerPlates
{
public:
    int capacity;
    int top, rightmost_indx;

    DinnerPlates(int _capacity)
    {
        top = 0;
        rightmost_indx = 0;
        this->capacity = _capacity;
    }
    stack<int> s[20000];
    void push(int val)
    {
        // s.push_back(stack<int>());
        while (s[top].size() == capacity)
        {
            ++top;
            rightmost_indx++;
        }
        s[top].push(val);
    }

    int pop()
    {
        if (top == -1)
        {
            return -1;
        }
        top = rightmost_indx;
        while (s[top].size() == 0)
        {
            top--;
            if (top < 0)
                break;
        }
        if (top < 0)
        {
            top = -1; //**
            return -1;
        }

        int x = s[top].top();
        s[top].pop();
        return x;
    }

    int popAtStack(int index)
    {
        if (s[index].size() == 0)
        {
            return -1;
        }
        int x = s[index].top();
        s[index].pop();
        top = index;
        return x;
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
    // freopen("output.in", "w", stdout);

    // Your DinnerPlates object will be instantiated and called as such :

    DinnerPlates *obj = new DinnerPlates(10);
    obj->push(5);
    int param_2 = obj->pop();
    cout << param_2 << endl;
    // int param_3 = obj->popAtStack(0);
    // cout << param_3 << endl;

    return 0;
}