#include <stdio.h>
#include <omp.h> // 0단계: 헤더 추가

int main() {
    int n = 1000000;
    int data[1000000];
    for(int i=0; i<n; i++) data[i] = i % 100;

    int sum = 0;
    int max_val = 0;
    double start, end;

    // --- 여기부터 병렬화 시작 ---
    start = (omp_get_wtime() ); // 시작 시간 측정
    

    // 문제: 아래 지시어를 완성하여 sum과 max_val을 병렬로 계산하세요.
    #pragma omp parallel for reduction(+:sum) reduction(max_max_val)
    for (int i = 0; i < n; i++) {
        sum += data[i];
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }

    end = (omp_get_wtime() ); // 종료 시간 측정
    // --- 여기까지 병렬화 끝 ---

    printf("Sum: %d, Max: %d, Time: %f\n", sum, max_val, end - start);
    return 0;
}
