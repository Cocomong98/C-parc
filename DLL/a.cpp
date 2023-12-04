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

// 맨 앞으로 보내는 기능은 push_front => 리스트와 값을 불러옴
void push_front(pList p, int value){
    // 리스트의 제일 앞쪽에 새로운 리스트를 넣고, 
    p->head = new Node(value, p->head);
}

void push_back (pList p, int value) {
    pNode x = next(p->head);
    x-> next = new Node{ value, nullptr};
}