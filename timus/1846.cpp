#include <iostream>
#include <map>
#include <set>

using namespace std;

#define ll long long

class Function
{
private:
    int base_function(int a, int b)
    {
        return a + b;
    }

    int GCD(int a, int b)
    {
        if (a > b) swap(a, b);
        while (a)
        {
            b %= a;
            swap(a, b);
        }

        return b;
    }

public:

    int operator()(int a, int b)
    {
        return GCD(a, b);
    }
};

template <class Type>
class SegmentTree
{
private:
    int _size;
    Type* data;
    Function function;

    void build(int left, int right, Type* info, int v = 1)
    {
        if (left == right)
        {
            data[v] = info[left];
            return;
        }
        int mid = (right + left) / 2;
        build(left, mid, info, 2 * v);
        build(mid+1, right, info, 2 * v + 1);
        data[v] = function(data[2 * v + 1], data[2 * v]);
    }

    Type get(int start, int end, int left, int right, int v)
    {
        if (start <= left && right <= end)
            return data[v];
        int mid = (left + right) / 2;
        Type tmp;
        bool used = 0;
        if ((start <= left && left <= end)  || (start <= mid && mid <= end) ||  (left <= start && start <= mid))
        {
            tmp = get(start, end, left, mid, 2 * v);
            used = 1;
        }
        if ((start <= right && right <= end) || (start <= mid+1 && mid+1 <= end) || (mid+1 <= start && start <= right))
            tmp = used ? function(tmp, get(start, end, mid + 1, right, 2 * v + 1)) : get(start, end, mid + 1, right, 2 * v + 1);
        return tmp;
    }

    Type update(int pos, Type value, int left, int right, int v)
    {
        if (left == right && left == pos)
        {
            data[v] = value;
            return value;
        }
        if (left > pos) return data[v];
        if (right < pos) return data[v];
        int mid = (left + right) / 2;
        data[v] = function(update(pos, value, left, mid, 2*v), update(pos, value, mid+1, right, 2 * v + 1));
        return data[v];
    }

public:
    SegmentTree(int size, Function func)
            :_size(size), data(new Type[4 * size]{ 0 }), function(func)
    {}

    SegmentTree(int size, Type* info, Function func): SegmentTree(size, func)
    {
        build(0, _size - 1, info);
    }

    Type get(int start, int end)
    {
        return get(start, end, 0, _size - 1, 1);
    }

    Type update(int pos, Type value)
    {
        return update(pos, value, 0, _size - 1, 1);
    }

    void print(int v, string sep)
    {
        if (v >= 4*_size || data[v] == 0) return;
        print(2 * v, sep + "   ");
        cout << sep << v << "(" << data[v] << ")" << '\n';
        print(2 * v + 1, sep + "   ");
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, size = 0;
    cin >> q;
    SegmentTree<int> tree(q, Function());
    map<int, set<int>> pos;
    while (q--)
    {
        char type;
        int val;
        cin >> type >> val;
        switch (type)
        {
            case '+':
                cout << tree.update(size, val) << '\n';
                pos[val].insert(size++);
                break;

            case '-':
                size--;
                int last = tree.get(size, size);
                if (last == val)
                {
                    pos[last].erase(size);
                    last = tree.update(size, 0);
                    cout << (last ? last : 1 ) << '\n';
                    break;
                }
                int posval = *pos[val].begin();
                int ans = tree.update(posval, last);
                cout << (ans ? ans : 1) << '\n';
                tree.update(size, 0);
                pos[val].erase(posval);
                pos[last].erase(size);
                pos[last].insert(posval);
        }
    }

    return 0;
}