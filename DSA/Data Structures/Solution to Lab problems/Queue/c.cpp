#include <iostream>
#include <queue>
#include <vector>

using namespace std;
class Node
{
public:
    int value;
    Node *next;

    Node(int value, Node *next = nullptr)
    {
        this->value = value;
        this->next = next;
    }
};

class Queue
{
private:
    Node *front;
    Node *rear;
    int size;

public:
    Queue()
    {
        this->front = nullptr;
        this->rear = nullptr;
        this->size = 0;
    }

    int get_size()
    {
        return this->size;
    }

    void enqueue(int value)
    {
        Node *newNode = new Node(value);
        if (front == nullptr)
        {
            front = newNode;
            rear = newNode;
            this->size++;
            return;
        }
        rear->next = newNode;
        rear = rear->next;
        this->size++;
    }

    void dequeue()
    {
        if (front == nullptr)
            return;
        Node *temp = front;
        front = front->next;
        this->size--;
        delete temp;
    }

    int peek()
    {
        if (front == nullptr)
            return INT_MIN;
        return front->value;
    }

    void print()
    {
        Node *currNode = this->front;

        while (currNode != nullptr)
        {
            cout << currNode->value << " -> ";
            currNode = currNode->next;
        }
        cout << '\n';
    }
};

pair<int, int> smallestSubsequence(Queue q, int target)
{
    int n = q.get_size();
    vector<int> prefixSum(n + 1);
    for (int i = 1; i <= n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + q.peek();
        q.dequeue();
    }

    int minLength = n;
    pair<int, int> minIndices = {0, n - 1};

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int sum = prefixSum[j] - prefixSum[i];
            if (sum >= target && (j - i) < minLength)
            {
                minLength = j - i;
                minIndices = {i, j - 1};
            }
        }
    }

    return {prefixSum[minIndices.first + 1] - prefixSum[minIndices.first], prefixSum[minIndices.second + 1] - prefixSum[minIndices.second]};
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);
    Queue q;
    int n, target;
    cin >> n >> target;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        q.enqueue(a);
    }

    auto result = smallestSubsequence(q, target);
    cout << result.first << " " << result.second << '\n';

    return 0;
}
