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

void erase(pNode x) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
    delete x;
}

void insert (pNode x, int value) {
    pNode node = new Node{value, x->prev, x};
    x->prev->next = node;
    x->prev = node;
}

void push_front(pList p, int value) {
    insert(begin(p), value);
}

// 맨 앞 노드 제거
void pop_front(pList p, int value) {
    // 비어있지 않으면
    if (!empty(p)) {
        // 시작 노드 제거
        erase (begin(p));
    }
}

// void push_back(pList p, int value) {
//     insert(end(p), value);
// }

// void pop_back(pList p, int value) {
//     if(!empty(p)) {
//         erase(end(p));
//     }
// }

/* =========================================================================== */

// 노드 x를 삭제
void erase(pNode x) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
    delete x;
}
// 아래의 erase가 위의 erase를 호출  

// 받은 리스트에서 정해진 노드를 삭제
void erase (pList p, pNode x) {
    if(x == end(p)) {
        // x가 마지막 노드이면 삭제하지 않음
        return;
    }
    // 그렇지 않으면 삭제
    erase(x);
}

// 이 위의 두 erase가 합쳐져 마지막 노드일 때는 삭제하지 않는 erase함수 완성

// 받은 리스트에서 정해진 노드를 삭제
void erase (pList p, pNode x) {
    if(x == end(p)) {
        // x가 마지막 노드이면 삭제하지 않음
        return;
    }
    // 그렇지 않으면 삭제
    x->prev->next = x->next;
    x->next->prev = x->prev;
    delete x;
}


/* =========================================================================== */
// 아예 여기서 마지막 노드면 지우지 않게 하기

// 노드 리스트 중 한 노드를 제거
void pop(pList p, int value){
    // p라는 이름의 노드 리스트 중, value값을 갖는 노드를 삭제
    erase(find(p, value));
}
// 이 경우는 지울 값이 tail값일 경우, 노드 리스트가 망가질 위험이 있다

// 개선 버전 2
void pop(pList p, int value){
    // 리스트까지 받아서 먼저 tail인지 확인 후, 삭제용 erase에 넘기는 
    erase(p, find(p, value));
}
// 이 경우는 지울 값이 tail값일 경우, 노드 리스트가 망가질 위험이 있다

// 개선 버전 1
void pop(pList p, int value){
    // pop할 노드를 find로 찾아서 node라는 포인터에 저장 (포인터 저장이라 node를 써도 원본이 건드려진다)
    pNode node = find(p, value);
    // 찾은 node값이 맨 마지막 값일 경우
    if(node == p->tail) {
        // 아무 일도 일어나지 않는다 ('ㅅ')
        return;
    }
    // 찾은 node값이 맨 마지막 값이 아닐 경우 
    // 찾은 값을 삭제한다
    erase(node);
}

/* =========================================================================== */

// 리스트에서 정해진 값을 가진 노드를 찾아서 주소값을 리턴
pNode find(pList p, int value){
    // 시작하는 위치를 x라 지정
    pNode x = begin(p);
    // x가 마지막이 아닐 때 까지 반복
    while(x != end(p)) {
        // 현위치의 데이터가 찾는 값과 일치하면
        if (x->data == value) {
            // 현위치 리턴 (주소값)
            return x;
        }
        // 못찾으면 x값을 다음 노드로 이전
        x = x->next;
    }
    // 모두 끝나면 x 리턴
    return x;
}

// 여기서 못찾는다 - while이 종료된 것이다 - while의 조건에 따라서 그 때 x의 값은 end(p)의 값일 것임

/* =========================================================================== */

// 마지막 노드일 경우만 제외하고 value와 일치하는 값을 갖는 노드를 모두 pop
void pop_all (pList p, int value) {
    // 찾는 value를 값으로 갖는 노드가 마지막 노드만 아니면 (마지막 노드 지우면 큰일남)
    while (find(p, value) != end(p)) {
        // 해당 노드 pop
        pop(p, value);
    }
}

void pop_all (pList p, int value) {
    for(pNode x = begin(p); x != end(p); x=x->next) {
        if (x->data == value) {
            // 이게 문제다. erase를 하면 지운 노드의 앞 뒤가 잘릴 수 있어서 pop으로 바꾸는 것이 더 좋음
            pNode temp = new Node;
            temp = x->prev;
            erase(p,x);
            x = temp;
        }
    }
}

/* =========================================================================== */

// 받은 노드 리스트의 절반 위치의 주소값을 반환하는 함수
pNode half(pList p) {
    pNode rabbit = begin(p);
    pNode turtle = begin(p);
    while(rabbit != end(p) || rabbit != last(p)) {
        rabbit = rabbit->next->next;
        turtle = turtle->next;
    }
    return turtle;
}