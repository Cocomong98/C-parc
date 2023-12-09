#include <iostream>
using namespace std;

struct TreeNode {
    // 
    int key;
    TreeNode* left;
    TreeNode* right;

    // 생성자: 키 값과 왼쪽, 오른쪽 서브트리의 포인터를 매개변수로 받아 초기화
    TreeNode(int k, TreeNode* l, TreeNode* r) {
        key = k; left = l; right = r;
    }
    // 생성자: 키 값만을 매개변수로 받고, 왼쪽과 오른쪽 서브트리의 포인터를 nullptr로 초기화
    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}

    // 소멸자: 특별한 동작이 정의되어 있지 않음
    ~TreeNode(){}
};
using tree = TreeNode*;

/*
LVR : inorder
LRV : postorder
VLR : preorder
*/

// LVR
void inorder(tree root) {
    if (root == nullptr) return;

    inorder(root -> left); // 왼쪽 노드 방문
    cout << root -> key; // 방문 : 저장하거나 출력
    inorder(root -> right); // 오른쪽 노드 방문
}

// LRV
void postorder(tree root){
    if(root == nullptr) return;

    postorder(root -> left);
    postorder(root -> right);
    cout << root -> key;
}