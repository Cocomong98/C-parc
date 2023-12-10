// BST의 시간 복잡도는 O(h) 
// 최소 h가 log2N이므로 BST의 최적 시간 복잡도는 O(log2N)

/*
노드의 높이 = h
밸런스 정보 = 왼쪽 높이 - 오른쪽 높이
빈 노드의 높이 = -1

AVL 트리는 이미 완성된 BST나 새로 만드는 트리에서만 가능하다
*/

// v - 넣을 키들의 배열 (넣을 값들의 모임)
// n - 배열의 크기 (넣을 개수)
tree bulidAVL(int* v, int n) {
    if(n <= 0) return nullptr;

    int mid = n/2;

    tree root = new TreeNode(v[mid]);

    root->left = bulidAVL(v, mid);
    root->right = bulidAVL(v+mid+1, n-mid+1);

    return root;
}