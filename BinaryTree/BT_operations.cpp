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

tree maximunBT (tree node) {
    // 빈 노드일 경우 예외처리 해 주는 줄
    if(node == nullptr) return node;

    // 최대함수 카운트하기 위해 일단은 루트 값으로 초기화시켜둠
    tree max = node;

    // 재귀함수를 사용해 좌우로 한번씩 다 돌려보기
    tree x = maximunBT(node -> left);
    tree y = maximunBT(node -> right);

    // 재귀를 통해 찾은 값과 기존의 max를 비교해 큰 값만 찾기
    if(x->key > max->key) max=x;
    if(y->key > max->key) max=y;

    // 최종 결과물 반환
    return max;
}
// 하지만 이 코드에는 문제가 있음 

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


/*
    10
   /  \
  5    15
 / \   / \
3   8 12  20
*/
// 찾는 key값이 나오기까지의 경로를 vector에 담아두었다가 리턴하는 함수
// 함수 자체의 리턴은 true(경로를 찾음) / false(경로를 못찾음)이고, 실제 경로는 vec에 저장됨
// root는 사용할 트리의 루트, x는 사용할 트리 이름, vector는 트리를 담을 벡터
bool findpath(tree root, tree x, vector<int>& vec) {

    // root가 null일 때 (값이 없을 때) false 반환하기 -> key값을 아예 갖고 있지 않기 때문
    if (root == nullptr) return false;

    // 일단 벡터에 키값 넣기 (push_back함수 사용)
    vec.push_back(root->key);

    // 넣은 값이 찾는 값인 경우 -> true 반환 
    if(root->key == x->key) return true;
    
    // 넣은 값이 찾는 값이 아닌 경우 -> 다음 노드로 재귀를 사용해 이동
    // 좌로 현재 노드의 왼쪽 자녀 노드 주고 이동 / 오른쪽 자녀 노드 주고 이동
    // or 연산자를 넣었으므로 둘 중 하나면 true여도 true = 당연함
    if(findpath(root->left, x, vec) || findpath(root->right, x, vec)){
        // 위의 항목이 false일 경우 해당 창은 자동으로 if(false)가 되므로 작동될 일 없음
        // 이건 위의 항목에서 찾아서 재귀로 나올때를 위해서 true로 만들어둔 것
        return true;
    }
    // 위가 false인 경우 = 재귀로 찾았는데도 없다 = 현재 노드 방향에서는 못찾는다
    else{
        // 저장한 값을 벡터에서 빼기
        vec.pop_back();
        // false 반환하기
        // 여기서 false인거면 그냥 전체에서 못 찾은거임
        return false;
    }
}

// root의 밑에 있는 주어진 두 개의 tree(node) 값의 가장 가까운 공통된 조상 노드를 찾는 과정
tree LCA(tree root, tree p, tree q){
    // root로 시작하는 tree가 비어있으면 없는거니까 null 반환
    if(empty(root)) return nullptr;

    // case 1
    // 혹시 지금의 위치가 찾으려는 두 위치와 하나라도 일치 = 지금의 위치가 LCA
    if (root == p || root == q) return root;

    // case 2
    // 받은 수인 p,q가 모두 root의 값보다 크다 -> 현재 두 노드가 오른쪽 서브트리에 있다
    if(p->key > root->key && q->key > root->key) {
        // 때문에 root의 위치를 연결된 오른쪽 서브트리로 옮기고 다시 LCA 실행
        root = LCA(root->right,p,q);
    }

    // case 3
    // 아닌 경우 (왼쪽 서브트리)
    else if(p->key < root->key && q->key < root->key){
        // root의 위치를 연결된 왼쪽으로 바꾸고 LCA 실행
        root = LCA(root -> left,p,q);
    }

    // result
    // 아닌 경우 -> 그때부터 갈라진다 = 지금의 위치가 공통 조상이다
    // 그래서 마지막으로 옮겨진 root의 위치가 공통 조상이 된다
    return root;
}

int main() {
    return;
}