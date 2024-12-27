#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>> tree;
unordered_set<string> guessSet;
int result = 0;

int countCorrectGuesses(int node, int parent) {
    int count = 0;
    for (int neighbor : tree[node]) {
        if (neighbor == parent) continue;
        if (guessSet.count(to_string(node) + "," + to_string(neighbor))) {
            count++;
        }
        count += countCorrectGuesses(neighbor, node);
    }
    return count;
}

void dfs(int node, int parent, int correctGuesses, int k) {
    if (correctGuesses >= k) result++;
    for (int neighbor : tree[node]) {
        if (neighbor == parent) continue;
        int nextCorrectGuesses = correctGuesses;
        if (guessSet.count(to_string(node) + "," + to_string(neighbor))) 
            nextCorrectGuesses--;
        if (guessSet.count(to_string(neighbor) + "," + to_string(node))) 
            nextCorrectGuesses++;
        dfs(neighbor, node, nextCorrectGuesses, k);
    }
}

int countPossibleRoots(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
    int n = edges.size() + 1;
    tree.assign(n, vector<int>());
    for (auto& edge : edges) {
        tree[edge[0]].push_back(edge[1]);
        tree[edge[1]].push_back(edge[0]);
    }
    for (auto& guess : guesses) {
        guessSet.insert(to_string(guess[0]) + "," + to_string(guess[1]));
    }
    int initialCorrectGuesses = countCorrectGuesses(0, -1);
    dfs(0, -1, initialCorrectGuesses, k);
    return result;
}

int main() {
    vector<vector<int>> edges = {{0,1},{1,2},{1,3},{4,2}};
    vector<vector<int>> guesses = {{1,3},{0,1},{1,0},{2,4}};
    int k = 3;
    
    cout << countPossibleRoots(edges, guesses, k) << endl;
    
    return 0;
}
