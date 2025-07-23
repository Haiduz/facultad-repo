#include<stdlib.h>
#include<stdio.h>

typedef struct _BstNode{
    int data;
    struct _BstNode* left, *right;
}BstNode;

typedef BstNode* BstSet;

BstSet bst_create(){ return NULL; }

int bst_search(BstSet root,int searched){   
    if(root == NULL) return 0;
    if(root->data == searched){
        return 1;
    }else if(root->data < searched){
        return bst_search(root->left, searched);
    }else{
        return bst_search(root->right, searched);
    }

}

BstSet bst_add(BstSet root,int in_data){
    if(bst_search(root, in_data)) return root;
    if(root == NULL){
        BstNode* new_node = malloc(sizeof(BstNode));
        new_node->data = in_data;
        new_node->left = new_node->right = NULL;
        return new_node;
    }else if(root->data <= in_data){
        root->right = bst_add(root->right, in_data);
    }else{
        root->left = bst_add(root->left, in_data);
    }
    return root;
}

// el inorder agrega de menor a mayor xdd

void print_bst(BstSet root){
    if(root == NULL) return;
    print_bst(root->left);
    printf("%d ", root->data);
    print_bst(root->right);
}

BstSet bst_copy(BstSet root){
    if(root == NULL) return root;
    BstSet new_tree = malloc(sizeof(BstNode));
    new_tree->data = root->data;
    new_tree->left = bst_copy(root->left);
    new_tree->right = bst_copy(root->right);
    return new_tree;
}

int main(){
    BstSet tree = bst_create();
    tree = bst_add(tree, 1);
    tree = bst_add(tree, 3);
    tree = bst_add(tree, 2);
    tree = bst_add(tree, 10);
    tree = bst_add(tree, 1);
    puts(" ");
    print_bst(tree);
    BstSet tree1 = bst_copy(tree);
    puts(" ");
    print_bst(tree1);    
    return 0;               
}