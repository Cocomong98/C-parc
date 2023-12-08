# Binary Tree

바이너리 트리의 풀 노드 = 밑의 노드가 2개일 때

리프 노드 = 스스로가 마지막일 때 

level (root가 1부터 시작) = n이라 했을 때,

 각 단계에 있는 노드의 수(최대) = 2^(k-1)
 해당 단계까지 있는 모든 노드의 수 = 

완전히 꽉 찬 이진 트리 = full binary tree

그렇지 않은 것 = complete binary tree

컴플리트의 기준 : 왼->오로 채우는 순서. 끝까지 차있지는 않아도 이전 단계는 다 차있어야 함

생성할때도, 지울때도 이와 같음


# complete binay tree (CBT) 

CBT에 있는 노드들을 array에 나열할 수 있음 (순차적으로 꽉 차있으니까 가능)

여기서 index가 4인 값에 대해서 다룬다고 가정

 - 부모 노드 구하기
   - index(4) / 2 = 2 (2번째 index가 parnet node)
   - 값이 1인 경우, 현재 노드가 root라는 의미이다
 - 자녀 노드 (왼쪽) 구하기
   - index(4) * 2 = 8 (8번째 index가 child node)
   - 
 - 자녀 노드 (오른쪽) 구하기
   - index(4) * 2 + 1 = 9 (8번째 index가 child node)
   - 