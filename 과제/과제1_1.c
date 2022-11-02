/*
Student_info.txt
학번	이름(성, 이름) 의 형식으로 된 txt 파일
*/
#include<stdio.h>
#include<string.h>	// strlen()함수 호출에 이용
#include<math.h>	// deviation에 쓰이는 sqrt() 함수 호출에 이용
typedef struct student{ // student라는 구조체 형식을 선언함
	char name[100];
	int student_number;
	int score;
}student;

double get_mean(student *student_info) {	//평균을 구하는 함수.
	int i;
	double sum = 0;
	for (i = 0; i < 100; i++) {
		sum += (student_info + i)->score; // 점수를 다 더함
	}
	sum /= 100; // 다 더한 점수를 개수로 나누어줌
	return sum;
}

double get_deviation(student *student_info) { //표준편차를 구하는 함수
	int i;
	double mean_score=0, mean_score_square=0;
	mean_score = get_mean(student_info); // 평균은 get_mean 함수를 이용해 구함.
	for (i = 0; i < 100; i++) {
		mean_score_square += ((student_info + i)->score)*((student_info + i)->score); // 점수의 제곱의 합을 다 더함.
	}
	mean_score_square /= 100; // 다 더한 점수의 제곱의 합을 개수로 나누어줌
	return sqrt(mean_score_square - (mean_score*mean_score)); // 제곱의 평균 - 평균의 제곱으로 표준편차를 구함.
}
int main() {
	FILE *file;
	student student_info[100]; // student 배열을 만듬
	int i;
	fopen_s(&file, "Student_info.txt", "rt");
	if (file == NULL) {
		printf("Can not open the file!\n");
		return 1;
	}
	for(i=0;;i++) {
		char str[100];
		fgets(str, sizeof(str), file); // 한줄 씩 입력을 받아줌
		int str_length = strlen(str);
		if (feof(file)) break; // file의 끝에 이를 경우 break로 while문을 빠져나옴
		(student_info + i)->student_number = 0; //학번은 합으로 구할 것이기 때문에 초기화를 해줌
		int k = 1000000000;
		for (int j = 0; j < 10; j++) {
			(student_info + i)->student_number += k*(str[j] - '0'); // 하나하나 곱해서 student_number에 더해줌.
			k /= 10;
		}
		for (int j = 11; j <str_length; j++)	{
			(student_info + i)->name[j-11] = str[j];	// 학번을 입력하고 난후에 \t이 오고 11번째 문자부터 이름이므로 j=11에서 시작해서 str의 끝까지 수행 이름을 한글자씩 넣어줌
		}
		(student_info + i)->name[str_length - 12] = '\0'; // 마지막 문자에 널문자가아닌 개행문자가 들어가므로 널문자를 넣어줌
		(student_info + i)->score = (rand() % 101); //점수는 랜덤한 점수를 넣어야하므로 rand()를 101로 나누게되면 0~100 사이에 숫자가 랜덤으로 들어감.
	}
	printf("mean : %lf\n", get_mean(student_info)); // 평균을 출력함
	printf("deviation : %lf\n", get_deviation(student_info));	// 표준편차를 출력함
	for (i = 0;i<100; i++) {
		printf("%s %d\n",(student_info+i)->name,(student_info+i)->student_number);
	}
	fclose(file);
	return 0;
}