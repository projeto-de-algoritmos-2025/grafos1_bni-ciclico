/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int DFS(struct TreeNode* node, int* maxsum) {
	if (node == NULL) return 0;
	int l_sum = DFS(node->left, maxsum);
	int r_sum = DFS(node->right, maxsum);
	l_sum = l_sum > 0 ? l_sum : 0;
	r_sum = r_sum > 0 ? r_sum : 0;
	int newpath = (node->val + l_sum + r_sum);
	*maxsum = newpath > *maxsum ? newpath : *maxsum;
	return node->val + (l_sum > r_sum ? l_sum : r_sum);
}

int maxPathSum(struct TreeNode* root) {
	int maxsum = INT_MIN;
	DFS(root, &maxsum);
	return maxsum;
}
