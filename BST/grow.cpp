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

/*
BST의 특징
 - 왼쪽의 모든 서브트리는 parent보다 작다
 - node를 기준으로 왼쪽은 작고 오른쪽은 크다
 - 같은 값은 존재할 수 없다

 search
 size
 height
 min/max
 successor
 predesessor

 BT에서의 find 시간복잡도 -> O(n)
 BST에서의 find 시간복잡도 -> O(n)은 worst case, 보통은 O(h)이므로 더 효율적이다

 grow(insert)
 trim(delete)
 BT to BST convert
 LCA
*/

// find를 사용하기 

// 특정 노드가 (key값을 가진 노드가) tree에 존재하는지 알아내는 함수
bool containsIteration(tree node, int key) {
    if(node == nullptr) return false;

    // 노드 전체에 대해 반복하기
    while(node) {
        // 현재 위치가 찾고자 하는 값 = key값이 현재 tree에 있음 = true 반환
        if(key == node->key) return true;

        // 만약 현재 키 값이 노드의 값보다 크다 (오른쪽으로 이동해야 함)
        if (key > node->key) {
            node = node->right;
        }
        else {
            node = node->left;
        }

        // 다 했는데도 없다
        return false;
    }
}
// 딱 봐도 비효율적

// 이건 재귀를 써서 효율적으로 개선
bool contains (tree node, int key){
    // 이건 동일 
    if(node == nullptr) return false;
    // 이것도 동일 (while이 없음)
    if(key == node->key) return true;

    // 현재보다 크면 오른쪽
    if(key > node->key) {
        contains(node->right, key);
    }
    // 아니면 왼쪽
    return contains(node->left, key);
}
// 이게 더 효율적

tree grow(tree node, int key) {
    // 호출 시에 받아온 node가 null이다 = 새로 만든다는 뜻 (그게 root가 될거니까) = 그래서 new
    if (node == nullptr) return new tree(key);

    // null이 아닐 경우
    // 받아온 key를 현 위치의 key와 비교해서 동작
    if(key < node->key) {
        // = 은 오->왼 순서로 실행된다
        // grow를 재귀로 부를 때 넘겨주는 node->left는 null상태이므로 key값이 담기게 잘 생성되고
        // 돌아와서 node->left에 저장해주므로 연결된다
        // 사실 최초 한 번은 이렇게 안 해줘도 되지만, 그 후로부터는 root에 계속 갱신되는 그림이라 이게 나음
        node->left = grow(node->left, key);
    }
    else if (key > node->key) {
        node->right = grow(node->right, key);
    }

    return node;
}

tree trim(tree node, int key) {
    if(node == nullptr) return node;

    // 지울 노드가 현재 노드보다 작음
    if (key < node->key) {
        // 위치를 왼쪽 자녀 노드로 바꾸고 다시 호출
        node->left = trim(node->left, key);
    }
    // 지울 노드가 현재 노드보다 큼
    else if (key > node->key) {
        // 재귀로 trim을 오른쪽 노드에 다시 돌리기. 반환값은 현재 노드의 오른쪽 가지로 연결
        node->right = trim(node->right, key);
    }
    // 여기까지의 과정은 다른 것들과 동일한 과정

    // 현재 위치와 지울 노드가 동일한 경우 (이제 이 밑에서 trim 실행)
    else {

        // case 1 : 지울 노드가 leaf node 인 경우 -> 지우고 null을 반환해서 연결 (지운 상태로 두면 됨)
        // leaf node인지 확인
        if(node -> right == nullptr && node ->left == nullptr){
            // 노드 지우기
            delete node;
            // null 반환
            return nullptr;
        }

        // case 2 : 지울 노드의 자녀 노드가 한 개 밖에 없는 경우 -> 지울 노드 값을 temp에 저장했다가 (자녀 노드의 위치를 위해서)
        // 리턴시킬 때 temp 사용해 자녀 노드를 부모 노드와 연결시키고 temp 삭제
        // 왼쪽 노드만 있는 경우
        else if(node -> right == nullptr){
            // 현재 노드를 temp에 저장 (왼쪽 자녀노드만 있는)
            tree temp = node;
            // 노드의 위치를 왼쪽 자녀 노드로 이동
            node = node -> left;
            // temp삭제 (현재 노드가 있는 위치. tree가 포인터형이라 이게 가능)
            delete temp;
            // node 반환 (왼쪽 자녀 노드로 덮어씌워진 노드 반환)
            return node;
        }
        // 오른쪽 노드만 있는 경우
        else if(node -> left == nullptr){
            // 노드값 저장
            tree temp = node;
            // 자녀 노드값을 노드에 저장
            node = node -> right;
            // 삭제
            delete temp;
            // 리턴
            return node;
        }

        // case 3 : 지울 노드의 자녀 노드가 두 개인 경우
        // case1,2가 아닌 경우 3이므로 else만 사용해도 됨
        // predesessor : 삭제하려는 노드보다 작은 값 중에서 가장 큰 노드 
        // 삭제하려는 노드의 왼쪽 자식 트리중 가장 오른쪽에 위치한 노드
        // successor : 삭제하려는 값보다 가장 큰 값 중 가장 작은 노드
        // 삭제하려는 노드의 오른쪽 자식 트리 중 가장 왼쪽에 위치한 노드

        //pred와 succ가 필요한 이유는, 삭제하고 그 두개를 찾아서 삭제하기 전 노드에 연결시켜 주어야 하기 때문이다
        else{
            if(height(node -> left) < height(node -> right)){
                tree suc = succ(node);
                node -> key = suc -> key;
                node -> right = trim(node -> right, suc -> key);
            }
            else{
                tree pre = pred(node);
                node -> key = pre -> key;
                node -> left = trim(node -> left, pre -> key);//node의 왼쪽부터 시작해서 지우고 와라~ pre나 suc은 one child이다.
            }
        }
    }
}

int main(){
    // 트리 생성 전 초기화
    tree root = nullptr;
    // 초기 생성값을 5로 설정하기 위해서 정함
    int key = 5;

    // 최초 생성
    root = grow(root, key);
    cout << root->key << '\n';
    root = grow(root, 9);
}