class Solution {
public:
    TreeNode* node = nullptr; // To store the lowest common ancestor

    // Helper function to find LCA
    bool LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return false; // Base case: null node

        // Check if the current node is either p or q
        bool isCurrentNode = (root == p || root == q);

        // Recursively search in the left and right subtrees
        bool left = LCA(root->left, p, q);
        bool right = LCA(root->right, p, q);

        // If p and q are found in different branches, root is the LCA
        if (left && right || (isCurrentNode && (left || right))) {
            node = root;
        }

        // Return true if current node is p or q, or if either subtree contains p or q
        return isCurrentNode || left || right;
    }

    // Main function to find the lowest common ancestor
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        LCA(root, p, q); // Trigger the recursive search
        return node; // Return the stored LCA
    }
};
