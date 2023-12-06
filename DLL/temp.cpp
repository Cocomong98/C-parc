#include <iostream>
using namespace std;

int main() {
    // N이라는 정수 선언
    int N;
    // N에 입력
	cin >> N;
    // 11개의 정수값을 갖는 배열 a를 선언 (레퍼런스인가?)
	int* a = new int[N];
    // N만큼 반복
	for (int i = 0; i < N; i++) {
        // 그 N만큼 입력
		cin >> a[i];
	}
    // 정수 key선언 (찾으려고 하는 정수)
	int key;
    // key 입력
	cin >> key;
    // 개수를 셀 count변수 선언
	int count = 0;
    // N번만큼 반복
	for (int i = 0; i < N; i++) {
        // 배열 안에 담긴 값이 key와 같을 때마다
		if (a[i] == key) {
            // count에 1씩 더하기
			count++;
		}
	}
    // 구한 count 출력하기
	cout << count;
}