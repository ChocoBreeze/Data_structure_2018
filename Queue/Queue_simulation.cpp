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

// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		fprintf(stderr, "ť�� ��ȭ�����Դϴ�.\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q)) {
		fprintf(stderr, "ť�� ��������Դϴ�.\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// [0..1] ������ ���� ���� �Լ�
double random()
{
	return rand() / (double)RAND_MAX;
}

// �ùķ��̼ǿ� �ʿ��� �������� ���� ����
int duration = 10; // �ù����̼� �ð� 
double arrival_prob = 0.7; // �ϳ��� �ð� ������ �����ϴ� ��� ������ ��
int max_serv_time = 5; // �ϳ��� ������ ���� �ִ� ���� �ð�
int clock;

// �ùķ��̼��� ���
int customers;			// ��ü������
int served_customers;	// ���񽺹��� ������
int waited_time;	// �������� ��ٸ� �ð�
int completely_finished_customers;	// ������ ���񽺸� ���� ������	���� �߰���

// ���� ���ڸ� �����Ͽ� ������ �����ߴ��� �������� �ʾҴ����� �Ǵ�
int is_customer_arrived()
{
	if (random() < arrival_prob)
		return TRUE;
	else return FALSE;
}
// ���� ������ ������ ť�� ����
void insert_customer(int arrival_time)
{
	element customer;

	customer.id = customers++;
	customer.arrival_time = arrival_time;
	customer.service_time = (int)(max_serv_time * random()) + 1;	// 1���� max_serv_time+1������ �ð�
	enqueue(&queue, customer);
	printf("���� %d�� %d�п� ���ɴϴ�. ���񽺽ð��� %d���Դϴ�.\n",
		customer.id, customer.arrival_time, customer.service_time);
}
// ť���� ��ٸ��� ������ ������ ������ ���� �ð��� ��ȯ�Ѵ�.
int remove_customer()
{
	element customer;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	customer = dequeue(&queue);
	service_time = customer.service_time - 1;
	served_customers++;			// ���� ���� ���� �� ����
	waited_time += clock - customer.arrival_time;		//  ���ð� ����
	printf("���� %d�� %d�п� ���񽺸� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
		customer.id, clock, clock - customer.arrival_time);
	return service_time;
}
// ���ġ�� ����Ѵ�.
void print_stat()
{
	printf("���񽺹��� ������ = %d\n", served_customers);
	printf("������ ���񽺸� ���� ������ = %d\n", completely_finished_customers);
	printf("��ü ��� �ð� = %d��\n", waited_time);
	printf("1�δ� �� ��� �ð� = %f��\n", (double)waited_time / served_customers);
	printf("���� ������� ������ = %d\n", customers - served_customers);
}
// �ùķ��̼� ���α׷�
void main()
{
	int service_time = 0;
	clock = 0;
	while (clock < duration) {		// duration�̶�� �ð����� �ȿ� ��� ������ �մ��� ���°�?
		clock++;		// ��ü �ð� ����
		printf("����ð�=%d\n", clock);
		if (is_customer_arrived()) {		// ����Ȯ��
			insert_customer(clock);
		}
		if (service_time > 0)		// service_time�� ���������� ��ݱ��� ���񽺹޴� ������ ����
			service_time--;
		else {
			if (clock != 1) completely_finished_customers++;
			service_time = remove_customer();	// service_time=0�̸� ���� ������ �ް� ���� ������ ���� �ð��� ����
		}
	}
	print_stat();
}