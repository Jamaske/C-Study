#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

int main() {
    int M, N, num_of_edges = 0;
    scanf("%d %d", &M, &N);
    vector<bool> visited(M, false);        // Marks visited nodes when doing dfs
    vector<vector<int>> adjacent(M);  // Adjacency "matrix"

    for (int i = 0; i < M; i++) {
        adjacent[i].reserve(M);
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            if (--x != i) {  // Add an edge for every color not in its own box
                num_of_edges++;
                adjacent[i].push_back(x);
            }
        }
    }

    int num_of_connected = 0;  // Number of connected components in the graph
    vector<int> stack(M * N);
    int top = 0;
    for (int i = 0; i < M; i++) {  // Simple dfs; count the number of connected components
        if (!visited[i] && !adjacent[i].empty()) {
            num_of_connected++;
            stack[top++] = i;
            while (top != 0) {
                int current_node = stack[--top];
                visited[current_node] = true;
                for (auto next_node : adjacent[current_node]) {
                    if (!visited[next_node]) {
                        stack[top++] = next_node;
                    }
                }
            }
        }
    }

    int answer = num_of_edges + max(0, num_of_connected - 1);
    printf("%d\n", answer);
    return 0;
}