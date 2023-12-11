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

// LL case
// 사용할 tree 가져온다
tree rotateLL(tree A) {
    // 이건 돌기 전 연결부를 뜻한다
    tree B = A->left;

    // 여기서부터 도는 것
    A->left = B->right;
    // root를 바꾼다
    B->right = A;
    return B;
}

// RR case
tree rotateRR(tree A) {
    // 돌기전 (이걸로 인해서 RR이 성립)
    tree B = A->right;

    // 
    A->rigth = B->left;
    B->left = A;

    return B;
}

// LR case (RR-LL) 
tree rotateLR (tree A) {
    // B는 A의 아래에 있고, 근데 왜 C는 언급을 안하지?
    tree B = A->left;

    A->left = rotateRR(B);
    return rotateLL (A);
}

// RL case (LL-RR)
tree rotateRL(tree A) {
    tree B = A->rignt;
    
    A->right = rotateLL(B)
    return rotateRR(A);
}

tree bulidAVL(int* v, int n) {
    // 넣을 수가 없으면 null 반환
    if(n <= 0) return nullptr;

    // 중앙 값은 당연히 넣을 수의 절반
    int mid = n/2;

    // 넣을 노드를 새로 만들기 -> 처음 들어온거라면 지금 만들어지는게 root이다
    tree root = new TreeNode(v[mid]);

    root->left = bulidAVL(v, mid);
    root->right = bulidAVL(v+mid+1, n-mid+1);

    return root;
}