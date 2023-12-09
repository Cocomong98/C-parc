#include <iostream>
#include <queue>
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
DFS : depth first search : 깊이 기반 탐색

LVR : inorder
LRV : postorder
VLR : preorder
*/

// LVR
void inorder(tree root) {
    if (root == nullptr) return;

    inorder(root -> left); // 왼쪽 노드 방문
    cout << root -> key << '\n'; // 방문 : 저장하거나 출력
    inorder(root -> right); // 오른쪽 노드 방문
}

// LRV
void postorder(tree root){
    if(root == nullptr) return;

    postorder(root -> left);
    postorder(root -> right);
    cout << root -> key;
}

/*
BFS : 너비 기반 탐색

levelorder
*/

void levelorder(tree root, vector<int>& vec){
    if(empty(root)) return;
    // 들어온 root가 null이 아니면 바로 queue에 넣음
    queue<tree> que;
    if (!root) return;
    que.push(root);
    tree now = nullptr;

    // 가져온 queue
    while(que.empty()){
        // queue.front를 꺼내 방문하기 (처음 과정이라면 root에 방문)
        now = que.front();
        // left가 null이 아니면 queue에 넣기 
        vec.push_back(now -> key);
        if(now -> left != nullptr) {
            que.push(now -> left);
        }
        // right가 null이 아니면 queue에 넣기
        if(now -> right != nullptr) {
            que.push(now -> right);
        }
        // queue.pop으로 삭제 (queue.front로 꺼낸 값)
        que.pop();
    }
    //queue가 vector형식으므로 같은 level에 있는 노드들을 한번씩 다 방문하는 것임
    // FBT라면 1단계에 1, 2단계에 2, 3단계에 4개씩 담길 것임
}

int main() {
    // 왼쪽 부분 선언하고 1이라는 값 넣기
    tree left = new TreeNode(1);
    // 오른쪽 부분 선언하고 3이라는 값 넣기
    tree right = new TreeNode(3);
    // 중앙 부분 선언하고 2라는 값과 왼쪽,오른쪽에 올 부분 넣기 (완성)
    tree root = new TreeNode(2,left,right);
    inorder(root);
}