#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    // 갖고 있는 데이터
    int key;
    // 왼쪽 자식 노드
    TreeNode* left;
    // 오른쪽 자식 노드
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

// 가장 작은 노드의 주소만 반복하는 거라서 값을 따로 보낼 건 없음 (key없는 거 보면 대충 답 나옴)
tree minimum(tree node) {
    // 지금 위치보다 작은 노드가 없음 -> 지금 노드가 최소니까 반환
    if(node->left == nullptr) return node;
    // 그렇지 않으면 다시 재귀
    return minimum(node->left);
}

// 미니멈과 원리는 동일
tree maximum(tree node) {
    // 지금 노드보다 큰 노드가 없음 -> 지금 노드가 최대니까 반환
    if (node->right == nullptr) return node;
    // 그렇지 않으면 재귀
    return maximum(node->right);
}

// succ는 successor를 뜻함
// succ는 현재 위치한 노드의 오른쪽 노드(이것보다 큰 노드) 값의 최소값을 찾는 기능임
// 즉, 전체 노드를 크기순으로 나열했을 때 지금 노드의 바로 뒤에 오는 노드를 찾는 것
tree succ(tree node) {
    // 노드가 빈 노드가 아니고, 오른쪽이 비어있지 않은 경우에만 실행
    if (node != nullptr && node->right != nullptr) {
        // 오른쪽 노드에서 최소를 찾음
        return minimum(node->right);
    }
    // 노드가 비어있거나 오른쪽이 비어있다면 null 반환 (succ가 없다는 뜻)
    return nullptr;
}

// pred는 predessessor를 뜻함
// pred는 현재 위치한 노드의 왼쪽 노드 값들 중 최대값을 찾는 것
tree pred(tree node) {
    // 현재 노드가 비어있지 않고, 왼쪽 노드가 비이었지 않은 경우에만 가능 (당연)
    if(node != nullptr && node->left != nullptr) {
        // 왼쪽 노드를 주고 최소값을 찾음
        return maximum(node->left);
    }
    // 못찾으면 없는거니까 null 반환
    return nullptr;
}
// pred와 succ의 시간 복잡도는 통상적으로 O(logN), 최악의 경우에는 O(n)