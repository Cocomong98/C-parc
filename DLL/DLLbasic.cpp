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

pNode begin(pList p) {
    // 시작하는 노드 (실제로 값이 담긴 노드)부터이므로 head의 다음에 올 노드를 리턴
    return p->head->next;
}
pNode end(pList p) {
    return p->tail;
}

// 이걸 활용한 기능들

// 리스트가 비었는지 확인하기
bool empty(pList p){
    // 시작과 끝이 같은 경우 비어있음
    // 이게 가능한 이유는 begin이 헤드가 아닌 헤드의 다음 노드를 가리키고 있기 때문이다
    return begin(p) == end(p);
}
// 이건 실제 사용되는 값의 마지막 노드를 리턴
pNode last(pList p){
    // 꼬리 값의 바로 앞 노드를 리턴
    return end(p)->prev;
}

/* =========================================================================== */

// 크기 재기 : 방법 1 - while 사용
int size(pList p){
    // 횟수를 담당할 변수 초기화
    int count=0;
    // 값이 시작되는 노드를 x에 저장함
    pNode x = begin(p);
    // x가 맨 끝 노드가 아닐때 까지 돌린다
    while(x != end(p)){
        // 횟수 증가
        count++;
        // 노드를 다음걸로 옮김
        x = x->next;
    }
    // 현재 노드가 마지막이면 바로 나옴 (그래서 맨 앞/맨 뒤를 제거한 개수를 알 수 있는 것이다)
    return count;
}

// 크기 재기 : 방법 2 - for 사용
int size(pList p){
    int count=0;
    // 위의 초기화 + 조건문 + 아닐 시 다음 노드 이동을 for문 하나에 다 담았음
    for (pNode x = begin(p); x!=end(p); x=x->next) {
        count++;
    }
    return count;
}

// 리스트와 찾을 값을 주고 찾기
pNode find(pList p, int value) {
    // 시작점을 x로 지정
    pNode x = begin(p);
    // x가 맨 끝이 아닐 때 까지 반복
    while(x != end(p)) {
        // x의 data가 찾던 value일 경우
        if(x->data == value) {
            // 해당 노드를 리턴
            return x;
        }
        // 아닐 경우 다음 노드로 이동
        x = x->next;
    }
    // 모든 게 끝나면 x를 리턴
    return x;
}

// 개선된 버전
// 이건 포인터 주소가 아닌, 직접적인 값인 int를 반환한다
int find(pList p, int value){
    // 이 방식은 while을 for로 바꾼 것과 동일
    for (pNode x = begin(p); x != end(p); x = x->next) {
        if (x->data == value) {
            // 리턴하는 값을 값이 담긴 포인터인 x로 반환하는 전과 달리
            // 실제 그 value값인 x->data를 반환한다
           return x->data; 
        }
    }
}