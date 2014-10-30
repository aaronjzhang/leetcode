/**
 * Defintion for binary tree
 *
 */
#include <stdlib.h>
#include <queue>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	bool isSymmetric(TreeNode *root) {
		if( !root ){
			return true;
		}
		return isSymmetric( root->left, root->right );	
	}

	bool isSymmetric( TreeNode* left, TreeNode *right ){
		if( left == NULL && right == NULL ){
			return true;
		}

		if( left && right )
		{
			return ( left->val == right->val ) && isSymmetric( left->left, right->right ) && isSymmetric( left->right, right->left );
		}
		return false;
	}

	bool isSymmetricByIterator( TreeNode *root ){
		std::queue<TreeNode*> left_q, right_q;
		left_q.push( root->left );
		right_q.push( root->right );
		for( ;; ){

			if( left_q.empty() && right_q.empty() ){
				return true;
			}


			TreeNode *node1 = left_q.front();
			left_q.pop();

			TreeNode *node2 = right_q.front();
			right_q.pop();

			if( node1 == NULL && node2 == NULL ){
				continue;
			}

			if( node1 && node2 ){
				if( node1->val == node2->val ){
					left_q.push( node1->left );
					left_q.push( node1->right );

					right_q.push( node2->right );
					right_q.push( node2->left );
					continue;
				}
			}
			return false;
		}
	}
};
