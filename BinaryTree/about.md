# Binary Tree

트리 예시

        A
       / \
      B   C
     / \
    D   E


용어 정리
 - child : 어떤 노드의 하위에 있는 노드 
   - ex) B는 A의 자식 노드이다
  
 - parent : 어떤 노드의 상위에 있는 노드
   - ex) A는 B의 부모 노드이다
  
 - sibling : 같은 부모 노드를 가진 두 노드 
   - ex) B와 C는 A의 자녀 노드이고, 형제 노드이다
  
 - degree : 어떤 노드가 가진 자녀 노드의 수
   - ex) A노드의 degree는 2이다 (B,C)
  
 - leaf nodes : degree가 0인 노드
   - ex) D는 leaf node이다 (자녀가 없으므로)
  
 - level : 트리의 깊이. root가 1이다
   - ex) 이 트리의 level은 3까지 있다
  
 - internal node : leaf node를 제외한 나머지 노드들 (자녀가 1개라도 있는)
   - ex) A,B는 internal node이다

 - height : 높이. 해당 노드의 밑에 몇 층의 노드가 있는지 나타낸다. (leaf node -> root node)
   - 0으로 시작한다
   - root노드의 height는 tree의 height이다.
   - tree의 height가 1인 노드는 0이다. (root만 있음)
   - ex) C의 height는 0, B의 height는 1, A의 height는 2이다

 - depth : 깊이. 해당 노드의 위에 몇 층의 노드가 있는지 나타낸다. (root node -> leaf node)
   - 0으로 시작한다
   - ex) C의 depth는 1, A의 height는 0, D의 depth는 2이다

 - height : 높이. 해당 노드의 밑에 몇 층의 노드가 있는지 체크
   - ex) B의 height는 1, A의 height는 2이다