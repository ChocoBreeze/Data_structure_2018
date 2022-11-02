#include <stdio.h>
#include <stdlib.h>
#define SIZE_QUEUE 100	//the maximum size of the news_queue
#define CAPACITY 6		//the capacity of ZNN.com (per sec)
#define NUM_USER 20		//the number of users
#define NUM_LOOP 100	//the number of loops


//ContentFidelity is one of the types: video, image, text
typedef enum { Video, Image, Text } ContentFidelity;

typedef struct {
	unsigned int requestedBy;		// ��û��
	ContentFidelity fidelity;		// ǰ��
} news;

typedef struct {
	news queue[SIZE_QUEUE];
	unsigned int front;
	unsigned int rear;
} Queue;

typedef struct P { // �߰���
	int recently_request_time; 
	int wait_time;
	int content_score;
	int content_number;
} User;

User user_info[NUM_USER];	// �߰��� ��
Queue news_queue;
ContentFidelity currentFidelity = Video;


int is_full() {
	return ((news_queue.rear + 1) % SIZE_QUEUE == news_queue.front);
}

int is_empty() {
	return (news_queue.rear == news_queue.front);
}

int check_queue(int user_index) { // �ߺ��˻�
	if (news_queue.front <= news_queue.rear) {
		for (unsigned int i = news_queue.front + 1; i <= news_queue.rear; i++) {
			if (news_queue.queue[i].requestedBy == user_index) return 1;
		}
	}
	else {
		for (unsigned int i = news_queue.front + 1; i < SIZE_QUEUE; i++) {
			if (news_queue.queue[i].requestedBy == user_index) return 1;
		}
		for (unsigned int i = 0; i <= news_queue.rear; i++) {
			if (news_queue.queue[i].requestedBy == user_index) return 1;
		}
	}
	return 0;
}

void enqueue(int user_index,int nthLoop) {
	if (is_full()) { return; }
	printf(" %d,",user_index);
	news_queue.rear = (news_queue.rear + 1) % SIZE_QUEUE;
	news_queue.queue[news_queue.rear].requestedBy = user_index;
	news_queue.queue[news_queue.rear].fidelity = currentFidelity;
	user_info[user_index].recently_request_time = nthLoop;
}

void request(int nthLoop) { // ��û
	double k;
	printf(" >>>>Requesting(ENQUEUE):");
	for (int i = 0; i < NUM_USER; i++) {
		if (!check_queue(i)) {			// �ߺ� �˻縦 ����� ����ڵ� �� 50% Ȯ���� ��û
			if (rand() % 2 == 0) enqueue(i, nthLoop);
		}
	}
	printf("\n");
}

void setFidelity(int nthLoop) { // ǰ�� ����
	double sum = 0;
	if (news_queue.front <= news_queue.rear) {
		for (unsigned int i = news_queue.front + 1; i <= news_queue.rear; i++) {
			sum += nthLoop - user_info[news_queue.queue[i].requestedBy].recently_request_time;
		}
		if (!is_empty()) sum /= (news_queue.rear - news_queue.front);
	}
	else {
		for (unsigned int i = news_queue.front + 1; i < SIZE_QUEUE; i++) {
			sum += nthLoop - user_info[news_queue.queue[i].requestedBy].recently_request_time;
		}
		for (unsigned int i = 0; i <= news_queue.rear; i++) {
			sum += nthLoop - user_info[news_queue.queue[i].requestedBy].recently_request_time;
		}
		sum /= (SIZE_QUEUE + news_queue.rear - news_queue.front);
	}
	if (sum >= 3 && currentFidelity != 2) currentFidelity++;
	else if (sum <= 2 && currentFidelity != 0) currentFidelity--;
	printf("Average waiting time: %.6lf, Current Quality: ", sum);
	if (currentFidelity == 0) printf("Video\n");
	else if (currentFidelity == 1) printf("Image\n");
	else printf("text\n");
}

void provide(int nthLoop) {
	if (is_empty()) return;
	printf("Providing(DEQUEUE): ");
	int max = CAPACITY;
	while (1) {
		if (max < (3 - news_queue.queue[(news_queue.front + 1) % SIZE_QUEUE].fidelity)) break;
		news_queue.front = (news_queue.front + 1) % SIZE_QUEUE;
		printf("(%d,  ",news_queue.queue[news_queue.front].requestedBy);
		if (news_queue.queue[news_queue.front].fidelity == 0) printf("Video), ");
		else if (news_queue.queue[news_queue.front].fidelity == 1) printf("Image), ");
		else printf("text), ");
		max -= (3 - news_queue.queue[news_queue.front].fidelity);
		user_info[news_queue.queue[news_queue.front].requestedBy].wait_time += (nthLoop - user_info[news_queue.queue[news_queue.front].requestedBy].recently_request_time);
		user_info[news_queue.queue[news_queue.front].requestedBy].content_score += (3 - news_queue.queue[news_queue.front].fidelity);
		user_info[news_queue.queue[news_queue.front].requestedBy].content_number++;
	}
	printf("\n");
}

void printQueue() {
	printf("In the queue: [");
	if (news_queue.front <= news_queue.rear) {
		for (unsigned int i = news_queue.front + 1; i <= news_queue.rear; i++) {
			printf("(%d, ", news_queue.queue[i].requestedBy);
			if (news_queue.queue[i].fidelity == 0) printf("Video), ");
			else if (news_queue.queue[i].fidelity == 1) printf("Image), ");
			else printf("text), ");
		}
	}
	else {
		for (unsigned int i = news_queue.front + 1; i < SIZE_QUEUE; i++) {
			printf("(%d, ", news_queue.queue[i].requestedBy);
			if (news_queue.queue[i].fidelity == 0) printf("Video), ");
			else if (news_queue.queue[i].fidelity == 1) printf("Image), ");
			else printf("text), ");
		}
		for (unsigned int i = 0; i <= news_queue.rear; i++) {
			printf("(%d, ", news_queue.queue[i].requestedBy);
			if (news_queue.queue[i].fidelity == 0) printf("Video), ");
			else if (news_queue.queue[i].fidelity == 1) printf("Image), ");
			else printf("text), ");
		}
	}
	printf("]\n");
}

void printResult() {
	printf("******Result*****\n");
	printf("User\tAvg.wait        Avg.score\n");
	for (int i = 0; i < NUM_USER; i++) {
		printf("User%d:\t%.6lfs       %.6lf\n",i,(double)user_info[i].wait_time/user_info[i].content_number,(double)user_info[i].content_score/user_info[i].content_number);
	}
}

void main() {
	unsigned int nthLoop;
	for (nthLoop = 0; nthLoop < NUM_LOOP; nthLoop++) {
		printf("\n=======%d seconds======\n", nthLoop);
		//users can request contents every two loops
		if (nthLoop % 2 == 0) {
			setFidelity(nthLoop); // �ð��� ����
			request(nthLoop);	// �ð��� ����
		}
		printQueue();
		provide(nthLoop); // �ð��� ����
	}
	printResult();
}
#include <stdio.h>
#include <stdlib.h>
#define SIZE_QUEUE 100	//the maximum size of the news_queue
#define CAPACITY 6		//the capacity of ZNN.com (per sec)
#define NUM_USER 20		//the number of users
#define NUM_LOOP 100    //the number of loops


//ContentFidelity is one of the types: video, image, text
typedef enum { Video = 3, Image = 2, Text = 1 } ContentFidelity;

typedef struct {
	unsigned int requestedBy;
	ContentFidelity fidelity;
	double time;
} news;

typedef struct {
	news queue[SIZE_QUEUE];
	unsigned int front;
	unsigned int rear;
} Queue;

Queue news_queue;
Queue *q = &news_queue;

ContentFidelity currentFidelity = Video;
const char *fidel[] = { "Video","Image","text" };   //fidelity�� ���ڿ��� �ٲ��ִ� �Լ� 


int user[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };      //������û�ݺ� üũ���ִ� �迭 
int count[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };     //��������Ƚ�� ���ִ� �迭 
double timeadd[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //�����������ð�  �����ִ� �迭 
double scoreadd[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //������������ �����ִ� �迭 

int sizeque() {     //ť�� ������ �����ִ� �Լ� 
	int n;
	if ((q->rear) >= (q->front))
		n = (q->rear) - (q->front);
	else
		n = SIZE_QUEUE - ((q->front) - (q->rear));

	return n;
}

void request() {
	int i;
	printf(" >>>>Requesting(ENQUEUE):");
	for (i = 0; i<NUM_USER; i++)
	{
		if (user[i] == 1) continue;

		if (rand() % 2 == 0)                              //50�ۼ�Ʈ Ȯ���� ť push 
		{
			q->rear = (q->rear + 1) % SIZE_QUEUE;              //��û�� ť �ڷ���� 
			q->queue[q->rear].requestedBy = i;
			q->queue[q->rear].fidelity = currentFidelity;
			q->queue[q->rear].time = 0;
			printf(" %d,", i);
			user[i] = 1;                                  //�ݺ�X 
		}
	}
	printf("\n");
}

void setFidelity() {
	double timesum = 0.0;                             //��մ��ð� ���ϱ� 
	int i = 1;
	int n, m;
	n = m = sizeque();
	while (n--)
	{
		timesum += q->queue[(q->front + i) % SIZE_QUEUE].time;
		i++;
	}
	if (m == 0)
		timesum = 0;
	else
		timesum /= m;

	if (timesum <= 2 && currentFidelity <= 2)             //��մ��ð������� �������ϱ� 
	{
		if (currentFidelity == 1)
			currentFidelity = Image;
		else
			currentFidelity = Video;
	}
	else if (timesum >= 3 && currentFidelity >= 2)
	{
		if (currentFidelity == 3)
			currentFidelity = Image;
		else
			currentFidelity = Text;
	}
	printf("Average waiting time: %lf, Current Quality: %s\n", timesum, fidel[3 - currentFidelity]);
}

void provide() {
	int i = 1;
	int n;
	int sum = 0;
	printf("Providing(DEQUEUE): ");

	while (1)
	{
		sum += q->queue[(q->front + 1) % SIZE_QUEUE].fidelity;               //����ť���� pop �ؼ� 6�� �Ѵ��� Ȯ��
		if (sum>CAPACITY) break;
		q->front = (q->front + 1) % SIZE_QUEUE;
		if (q->queue[q->front].fidelity == 0) break;
		printf(" (%d, %s),", q->queue[q->front].requestedBy, fidel[3 - (q->queue[q->front].fidelity)]);

		timeadd[q->queue[q->front].requestedBy] += q->queue[q->front].time;     //�������ð�,����Ƚ��,��������  
		count[q->queue[q->front].requestedBy]++;
		scoreadd[q->queue[q->front].requestedBy] += q->queue[q->front].fidelity;
		q->queue[q->front].time = 0;
		user[q->queue[q->front].requestedBy] = 0;    //�ݺ�X 
	}


	for (n = sizeque(); n>0; n--)              //���ð� 
	{
		q->queue[(q->front + i) % SIZE_QUEUE].time++;
		i++;
	}

	printf("\n");

}

void printQueue() {
	printf("In the queue:");
	printf("[");
	int m = sizeque();
	int i = 1;

	while (m--)
	{
		printf(" (%d, %s),", q->queue[q->front + i].requestedBy, fidel[3 - (q->queue[q->front + i].fidelity)]);
		i++;
	}
	printf("]\n");

}

void printResult() {
	printf("\n******Result*****\nUser	Avg.wait	Avg.score\n");
	int i;
	for (i = 0; i<NUM_USER; i++)
	{
		printf("User%d:\t%.6lfs       %.6lf\n", i, timeadd[i] / count[i], scoreadd[i] / count[i]);
	}
}

void main() {
	unsigned int nthLoop;
	for (nthLoop = 0; nthLoop < NUM_LOOP; nthLoop++) {
		printf("\n=======%d seconds======\n", nthLoop);
		//users can request contents every two loops
		if (nthLoop % 2 == 0) {
			setFidelity();
			request();
		}
		printQueue();
		provide();
	}

	printResult();
}