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
// 리스트는 맨 앞의 헤드와 맨 뒤의 테일로 감싸져 있는 형태이다 
struct List
{
    Node* head; // 노드의 앞쪽 부분
    Node* tail; // 노드의 맨 뒷 부분
    int size; // 해도 되고 안 해도 됨
    List() { 
        // 헤드 부분을 담당할 노드 생성
        head = new Node{}; 
        // 꼬리 부분을 담당할 노드 생성
        tail = new Node{};
        // 헤드의 다음에 올 노드는 꼬리
        head->next = tail; 
        // 꼬리의 이전 노드는 헤드 
        tail->prev = head;
        // 이렇게 선언하면 헤드와 꼬리 이외의 노드는 리스트에 없음
        // 그래서 사이즈는 0 (사이즈에서 헤드와 꼬리는 제외함)
        size = 0;
    }
    ~List() {}
};

// 만든 노드와 리스트 객체로 불러옴
using pNode = Node*;
using pList = List*;

/* =========================================================================== */

// 해당 노드를 지우는 역할인 erase 
// x는 리스트의 시작점이다. (head를 가리키는 것)
void erase(pNode x){
    // 현재 노드의 이전 노드의 다음 = 이전 노드에서의 다음 노드를 가리키는 포인터를
    // 현재인 x가 아니라 그 다음 노드로 연결
    // 1 <-> 2(현위치) <-> 3의 구조에서 1->3, 1<-2 라는 구조로 바꿈 
    x->prev->next = x->next;
    x->next->prev = x->prev;
    delete x;
}

// 정해진 노드를 제외하는 함수
// 이걸 구현하기 위해서 erase와 find를 사용한다
// find로 찾은 값을 erase하면 될 듯
void pop(pList p, int value){
    pNode node = find(p, value);
    erase(node);
}

