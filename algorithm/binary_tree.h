#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#define MAX_SON_NUM 2

template <class node_data>
class TreeNode {
public :
    TreeNode();
    ~TreeNode();
private :
    TreeNode<node_data> *son[MAX_SON_NUM];
    TreeNode<node_data> *father;
};


#endif
