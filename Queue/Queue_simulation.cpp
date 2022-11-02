/* simulation.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100

typedef struct {
	int id;
	int arrival_time;
	int service_time;
} element;

typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
QueueType queue;

// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태입니다.\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태입니다.\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// [0..1] 사이의 난수 생성 함수
double random()
{
	return rand() / (double)RAND_MAX;
}

// 시뮬레이션에 필요한 여러가지 상태 변수
int duration = 10; // 시물레이션 시간 
double arrival_prob = 0.7; // 하나의 시간 단위에 도착하는 평균 고객의 수
int max_serv_time = 5; // 하나의 고객에 대한 최대 서비스 시간
int clock;

// 시뮬레이션의 결과
int customers;			// 전체고객수
int served_customers;	// 서비스받은 고객수
int waited_time;	// 고객들이 기다린 시간
int completely_finished_customers;	// 완전히 서비스를 끝낸 고객수	내가 추가함

// 랜덤 숫자를 생성하여 고객이 도착했는지 도착하지 않았는지를 판단
int is_customer_arrived()
{
	if (random() < arrival_prob)
		return TRUE;
	else return FALSE;
}
// 새로 도착한 고객을 큐에 삽입
void insert_customer(int arrival_time)
{
	element customer;

	customer.id = customers++;
	customer.arrival_time = arrival_time;
	customer.service_time = (int)(max_serv_time * random()) + 1;	// 1에서 max_serv_time+1까지의 시간
	enqueue(&queue, customer);
	printf("고객 %d이 %d분에 들어옵니다. 서비스시간은 %d분입니다.\n",
		customer.id, customer.arrival_time, customer.service_time);
}
// 큐에서 기다리는 고객을 꺼내어 고객의 서비스 시간을 반환한다.
int remove_customer()
{
	element customer;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	customer = dequeue(&queue);
	service_time = customer.service_time - 1;
	served_customers++;			// 서비스 받은 고객 수 증가
	waited_time += clock - customer.arrival_time;		//  대기시간 증가
	printf("고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n",
		customer.id, clock, clock - customer.arrival_time);
	return service_time;
}
// 통계치를 출력한다.
void print_stat()
{
	printf("서비스받은 고객수 = %d\n", served_customers);
	printf("완전히 서비스를 끝낸 고객수 = %d\n", completely_finished_customers);
	printf("전체 대기 시간 = %d분\n", waited_time);
	printf("1인당 평군 대기 시간 = %f분\n", (double)waited_time / served_customers);
	printf("아직 대기중인 고객수 = %d\n", customers - served_customers);
}
// 시뮬레이션 프로그램
void main()
{
	int service_time = 0;
	clock = 0;
	while (clock < duration) {		// duration이라는 시간제한 안에 어느 정도의 손님이 오는가?
		clock++;		// 전체 시간 증가
		printf("현재시각=%d\n", clock);
		if (is_customer_arrived()) {		// 고객확인
			insert_customer(clock);
		}
		if (service_time > 0)		// service_time이 남아있으면 방금까지 서비스받던 고객을 진행
			service_time--;
		else {
			if (clock != 1) completely_finished_customers++;
			service_time = remove_customer();	// service_time=0이면 다음 고객을 받고 다음 고객의 서비스 시간을 저장
		}
	}
	print_stat();
}