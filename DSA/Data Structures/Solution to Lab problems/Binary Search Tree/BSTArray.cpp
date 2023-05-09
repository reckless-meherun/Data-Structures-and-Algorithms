#include <bits/stdc++.h>
using namespace std;

class Student
{
public:
    string Name;
    int roll;
    string DateOfBirth;
    double cgpa;
    Student(string name, int roll, string DateOfBirth, double cgpa)
    {
        this->Name = name;
        this->roll = roll;
        this->DateOfBirth = DateOfBirth;
        this->cgpa = cgpa;
    }
    void DIsplay()
    {
        cout << "Name: " << Name << endl;
        cout << "Roll: " << roll << endl;
        cout << "Date of Birth: " << DateOfBirth << endl;
        cout << "CGPA: " << cgpa << endl;
    }
};

class TreeArrat
{
public:
    Student *tree[100000];
    int node_count = 0;
    void addnode(Student *s, int parent = 1)
    {
        if (tree[parent] == NULL)
        {
            tree[parent] = s;
            return;
        }

        if (tree[parent]->roll > s->roll)
        {
            if (tree[2 * parent] == NULL)
            {
                tree[2 * parent] = s;
                node_count++;
                return;
            }
            addnode(s, 2 * parent);
        }
        else
        {
            if (tree[(parent * 2) + 1] == NULL)
            {
                tree[(2 * parent) + 1] = s;
                node_count++;
                return;
            }
            addnode(s, (2 * parent) + 1);
        }
    }

    void preOrderTravarsal(int parent = 1)
    {
        if (tree[parent] != NULL)
        {
            cout << tree[parent]->roll << " ";
            preOrderTravarsal(parent * 2);
            preOrderTravarsal((parent * 2) + 1);
        }
    }
    void inOrderTravarsal(int parent = 1)
    {
        if (tree[parent] != NULL)
        {
            inOrderTravarsal(parent * 2);
            cout << tree[parent]->roll << " ";
            inOrderTravarsal((parent * 2) + 1);
        }
    }
    void postOrderTravarsal(int parent = 1)
    {
        if (tree[parent] != NULL)
        {

            postOrderTravarsal(parent * 2);

            postOrderTravarsal((parent * 2) + 1);
            cout << tree[parent]->roll << " ";
        }
    }
    int find_min(int parent = 1)
    {
        while (tree[parent] and tree[parent * 2] != NULL)
        {
            parent *= 2;
        }
        return parent;
    }

    void delnode(int val, int parent = 1)
    {
        if (tree[parent] == NULL)
        {
            return;
        }
        if (val < tree[parent]->roll)
        {
            delnode(val, parent * 2);
        }
        else if (val > tree[parent]->roll)
        {
            delnode(val, (parent * 2) + 1);
        }
        else
        {
            if (tree[parent * 2] == NULL) // if left null, bring from right
            {
                tree[parent] = tree[(parent * 2) + 1];
                // cout<<1<<endl;
                tree[(parent * 2) + 1] = NULL;
                node_count--;
                return;
            }
            else if (tree[(parent * 2) + 1] == NULL) // if right null, bring from left
            {
                tree[parent] = tree[parent * 2];
                // cout<<1<<endl;
                tree[(parent * 2)] = NULL;
                node_count--;
                return;
            }
            else // if none of the children are null, swap the parent with right successor
            {
                Student *s = tree[find_min(parent * 2 + 1)];
                tree[parent] = s;
                delnode(val, (parent * 2) + 1);
            }
        }
    }
    int search(int val, int par = 1)
    {
        if (tree[par] == NULL)
        {
            return -1;
        }
        if (val == tree[par]->roll)
        {
            return par;
        }
        if (val < tree[par]->roll)
        {
            search(val, par * 2);
        }
        else
        {
            search(val, (par * 2) + 1);
        }
    }
    bool isFull(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (tree[par * 2] == NULL and tree[par * 2 + 1] == NULL)
        {
            return true;
        }
        else if (tree[par * 2] == NULL or tree[par * 2 + 1] == NULL)
        {
            return false;
        }
        else
        {
            return (isFull(par * 2) & isFull(par * 2 + 1));
        }
    }
    void print_tree()
    {
        cout << "\n";
        for (int i = 0; i < 10; i++)
        {
            if (tree[i] != NULL)
                tree[i]->DIsplay();
            else
                cout << endl;
        }

        return;
    }
    bool isskewed(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (tree[par * 2] == NULL and tree[par * 2 + 1] == NULL)
        {
            return true;
        }
        if (tree[par * 2] != NULL and tree[par * 2 + 1] != NULL)
        {
            return false;
        }
        else if (tree[par * 2] == NULL)
        {
            return isskewed(par * 2 + 1);
        }
        else
        {
            return isskewed(par * 2);
        }
    }
    bool isskewed_left(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (tree[par * 2] == NULL and tree[par * 2 + 1] == NULL)
        {
            return true;
        }
        if (tree[par * 2 + 1] != NULL)
        {
            return false;
        }
        return isskewed_left(par * 2);
    }
    bool isskewed_right(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (tree[par * 2] == NULL and tree[par * 2 + 1] == NULL)
        {
            return true;
        }
        if (tree[par * 2] != NULL)
        {
            return false;
        }
        return isskewed_right(par * 2 + 1);
    }
    int depth()
    {
        int par = 1;
        int cnt = 0;
        while (tree[par * 2] != NULL)
        {
            par *= 2;
            cnt++;
        }
        return cnt;
    }
    bool isPerf(int d, int par = 1, int lev = 0)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (tree[par * 2] == NULL and tree[par * 2 + 1] == NULL)
        {
            return (d == lev);
        }
        if (tree[par * 2] == NULL or tree[par * 2 + 1] == NULL)
        {
            return false;
        }
        return (isPerf(d, par * 2, lev + 1) & isPerf(d, par * 2 + 1, lev + 1));
    }
    bool isperfect()
    {
        if (tree[1] == NULL)
        {
            return true;
        }
        int d = depth();
        return isPerf(d);
    }
    bool iscomplete(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        if (par > this->node_count)
        {
            return false;
        }
        return (iscomplete(par * 2) & iscomplete(par * 2 + 1));
    }
    int height(int par)
    {
        if (tree[par] == NULL)
        {
            return 0;
        }
        return 1 + max(height(par * 2), height(par * 2 + 1));
    }
    bool isbalanced(int par = 1)
    {
        if (tree[par] == NULL)
        {
            return true;
        }
        int lh, rh;
        lh = height(par * 2);
        rh = height(par * 2 + 1);
        return (abs(lh - rh) <= 1 and isbalanced(par * 2) and isbalanced(par * 2 + 1));
    }
};

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    TreeArrat t = TreeArrat();
    t.addnode(new Student("Meherun", 5, "27/09/2003", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("Tahsin", 2, "27/09/2003", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("Tasnia", 27, "27/09/2003", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("Jamal", 7, "27/09/2003", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("Himel", 13, "27/09/2003", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("Aniket", 48, "--/--/2002", 4.00));
    t.preOrderTravarsal(1);
    cout << endl;
    t.addnode(new Student("maisha", 63, "--/--/2002", 4.00));
    t.preOrderTravarsal();
    cout << endl;
    cout << t.isperfect() << endl;
    t.delnode(47);
    t.preOrderTravarsal();
    cout << endl;
    cout << t.isperfect() << endl;

    return 0;
}
