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

// 헤드를 주고 맨 앞에 끼워넣기 O(n)-> list에 head만 있는 경우
void push_front(pList p, int value){
    // 새 노드를 만들고, 값에 value, next에 현재의 헤드를 넣는다 -> 그리고 그 노드를 리스트의 헤드 노드에 연결한다
    p->head = new Node(value, p->head);
}

/* =========================================================================== */

// 헤드를 주고 맨 뒤에 넣기 -> list에 head만 있는 경우
void push_back(pList p, int value) {
    // 노드 x는 헤드 값을 넣어 실행한 last함수의 결과값 (마지막 노드)이다
    pNode x = last(p->head);
    // 새 노드에 값과 next에 nulld을 넣고, 앞전에 찾은 마지막 노드인 x의 next에 넣어 잇는다
    x->next = new Node{value, nullptr};
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

// 시간 복잡도를 더 해결한 버전 O(1) -> list에 tail도 있는 경우 + last 불필요
void push_back(pList p, int value) {
    // 노드의 마지막의 다음을 나타내는 노드 (원래는 nullptr)에 새 노드를 연결하고 값을 할당
    p->tail->next = new Node{value};
    // 그 후 기존의 맨 끝 값이었던 p->tail에 새롭게 추가된 맨 끝 값인 p->tail->next를 할당해
    // 노드의 맨 뒤를 가리키는 p->tail을 최신화
    p->tail = p->tail->next;
}

// 간소화시킨 버전, 시간복잡도는 차이 없음
void push_back(pList p, int value) {
    p->tail = p->tail->next = new Node{value};
}

/* =========================================================================== */

// 헤드를 주고, 중간에 끼워넣기
// p는 노드들이 담긴 리스트의 이름, value는 중간에 끼울 노드에 담을 값, z는 노드를 찾을 key값
// value라는 값이 담긴 노드를 z값이 담긴 노드 위치에 넣기
// 결과적으로 이건 z로 찾은 노드의 앞에 새 노드를 만들어 끼우는 것이다. 그래야 z번째에 넣을 수 있으니까
void push_at(pList p, int value, int z) {
    // 받아온 노드의 리스트가 비어있거나, 맨 앞 노드의 데이터가 찾던 노드의 데이터일 경우 (더 찾을 필요가 없음)
    if(empty(p) || (p->head->data == z)) {
        // 해당 노드의 맨 앞에 value값이 담긴 노드를 이어 붙인다
        return push_front(p, value);
    }
    // 그렇지 않을 경우 (처음 만난 게 찾는 노드가 아닌 경우)

    // 헤드값을 x에 저장
    pNode x = p->head;
    // null값을 Prev에 저장
    // 헤드의 이전 값은 존재할 수 없으므로 null을 저장
    pNode prev = nullptr;
    // 현재 위치한 노드 값이 null이 아닐 경우 (마지막이 아닌 경우) 반복
    while (x!=nullptr) {
        // 현재 노드의 값과 찾으려는 z값이 일치할 경우, 
        if(x->data == z) {
            // 이 상태에서 prev는 현재 위치한 곳 (value가 z인 곳)의 이전 노드를 가리킨다
            // x는 현재 z값을 갖고 있는 노드를 가리킨다

            // prev->next로 이전 노드의 다음 노드에 새 노드를 파서 넣는다
            // 여기서 중요한 점은, 이전 노드-새 노드로 연결하고 새 노드의 next에 새 노드를 만들기 전 버전의
            // prev의 다음 노드를 넣어 순번이 자연스럽게 이어지게 한 것이다
            // 이게 가능한 이유는 = 을 기준으로 오른쪽을 왼쪽보다 먼저 계산하기 때문임
            prev->next = new Node{value, prev->next};
            // 다 끝났으니까 리턴
            return;
        }
        // 값을 비교해 같지 않았던 경우 (한 칸 뒤의 노드로 이동)
        // 이전 노드를 가리키는 값을 현재 노드값으로 변경
        prev = x;
        // 현재 노드값은 다음 노드값으로 변경 
        x = x->next;
    }
}

/* =========================================================================== */


