#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int maxSum = INT_MIN;

int findMaxPathSum(TreeNode* root) {
    if (!root) return 0;
    int left = max(0, findMaxPathSum(root->left));
    int right = max(0, findMaxPathSum(root->right));
    maxSum = max(maxSum, left + right + root->val);
    return root->val + max(left, right);
}

int maxPathSum(TreeNode* root) {
    findMaxPathSum(root);
    return maxSum;
}

int main() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    cout << maxPathSum(root) << endl;
    
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root->left;
    delete root;
    
    return 0;
}
