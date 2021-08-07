#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct BSTNode BSTNode;
struct BSTNode {
    int val;
    struct BSTNode* l_child;
    struct BSTNode* r_child;
};

BSTNode* insert(BSTNode* root, int val) {
    //if BSTNode doesnt yet exist
    if(root==NULL) {
        root = malloc(sizeof(BSTNode));
        root->l_child = NULL;
        root->r_child = NULL;
        root->val = val;
        return root;
    }
    //if the BSTNode already exists, insert into correct subtree
    if(val < root->val) {
        root->l_child = insert(root->l_child, val);
        return root;
    } else if(val == root->val) {
        //ignore duplicate
        return root;
    } else {
        root->r_child = insert(root->r_child, val);
        return root;
    }
}

void delete(BSTNode* root) {
    //if root->l_child not null, call delete
    if(root->l_child) { delete(root->l_child); };
    //if root->r_child not null, call delete
    if(root->r_child) { delete(root->r_child); };
    free(root);
}


void print_in_reverse(BSTNode* root) {
    if(root == NULL) { return; }
    else {
        print_in_reverse(root->r_child);
        printf("%d\n", root->val);
        print_in_reverse(root->l_child);
    }
}

int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct BSTNode* root = NULL;
    int key;
    while(fscanf(fp, "%d\n", &key) != EOF) {
        root = insert(root, key);
    }


    fclose(fp);
    print_in_reverse(root);


    delete(root);
    return 0;
}
