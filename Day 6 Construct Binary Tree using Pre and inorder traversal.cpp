#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

unordered_map<int, int> inorderMap;
int preorderIndex = 0;

TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, int left, int right) {
    if (left > right) return nullptr;
    int rootValue = preorder[preorderIndex++];
    TreeNode* root = new TreeNode(rootValue);
    int inorderIndex = inorderMap[rootValue];
    root->left = buildTreeHelper(preorder, inorder, left, inorderIndex - 1);
    root->right = buildTreeHelper(preorder, inorder, inorderIndex + 1, right);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); i++) {
        inorderMap[inorder[i]] = i;
    }
    return buildTreeHelper(preorder, inorder, 0, inorder.size() - 1);
}

void printInOrder(TreeNode* root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    TreeNode* root = buildTree(preorder, inorder);
    printInOrder(root);
    cout << endl;
    
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;
    
    return 0;
}
