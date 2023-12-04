#include <stdio.h>
using namespace std;

// DLL이 SLL과 다른 점은 prev 추가로 앞-뒤 모두 이동이 가능하다는 점이다

// 여기서 노드의 틀을 선언 (담을 값, 이전 노드, 다음 노드)
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int d = 0, Node* p = nullptr,
                    Node* x = nullptr)
        { data = d; prev = p; next = x; }
    ~Node() {}
};

// 노드들이 들어갈 리스트 선언 (첫 좌표, 마지막 좌표)
struct List
{
    Node* head;
    Node* tail;
    int size; // 해도 되고 안 해도 됨
    List() { head = new Node{}; tail = new Node{};
            head->next = tail; tail->prev = head;
            size = 0;
    }
    ~List() {}
};

// 만든 노드와 리스트 객체로 불러옴
using pNode = Node*;
using pList = List*;

// 헤드를 주고 맨 앞에 끼워넣기
void push_front(pList p, int value){
    // 새 노드를 만들고, 값에 value, next에 현재의 헤드를 넣는다 -> 그리고 그 노드를 리스트의 헤드 노드에 연결한다
    p->head = new Node(value, p->head);
}

// 헤드를 주고 맨 뒤에 넣기
void push_back(pList p, int value) {
    // 노드 x는 헤드 값을 넣어 실행한 last함수의 결과값 (마지막 노드)이다
    pNode x = last(p->head);
    // 새 노드에 값과 next에 nulld을 넣고, 앞전에 찾은 마지막 노드인 x의 next에 넣어 잇는다
    x->next = new Node{value, nullptr};
}

void push_back(pList p, int value) {
    p->tail->next = new Node{value};
    p->tail = p->tail->next;
}
// 첫 노드를 받아 마지막 노드를 반환하는 last
pNode last(pNode head) {
    // 받아온 노드 Head를 x에 할당
    pNode x = head;
    // x의 다음에 올 노드가 null일 때 까지 (현재 있는 노드가 마지막 노드일때까지) 반복
    while (x->next!=nullptr)
        // 노드를 한 칸씩 이동
        x = x->next;
    // 찾아낸 마지막 노드를 반환
    return x;
}