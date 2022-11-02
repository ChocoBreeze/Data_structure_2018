/*
Student_info.txt
�й�	�̸�(��, �̸�) �� �������� �� txt ����
*/
#include<stdio.h>
#include<string.h>	// strlen()�Լ� ȣ�⿡ �̿�
#include<math.h>	// deviation�� ���̴� sqrt() �Լ� ȣ�⿡ �̿�
typedef struct student{ // student��� ����ü ������ ������
	char name[100];
	int student_number;
	int score;
}student;

double get_mean(student *student_info) {	//����� ���ϴ� �Լ�.
	int i;
	double sum = 0;
	for (i = 0; i < 100; i++) {
		sum += (student_info + i)->score; // ������ �� ����
	}
	sum /= 100; // �� ���� ������ ������ ��������
	return sum;
}

double get_deviation(student *student_info) { //ǥ�������� ���ϴ� �Լ�
	int i;
	double mean_score=0, mean_score_square=0;
	mean_score = get_mean(student_info); // ����� get_mean �Լ��� �̿��� ����.
	for (i = 0; i < 100; i++) {
		mean_score_square += ((student_info + i)->score)*((student_info + i)->score); // ������ ������ ���� �� ����.
	}
	mean_score_square /= 100; // �� ���� ������ ������ ���� ������ ��������
	return sqrt(mean_score_square - (mean_score*mean_score)); // ������ ��� - ����� �������� ǥ�������� ����.
}
int main() {
	FILE *file;
	student student_info[100]; // student �迭�� ����
	int i;
	fopen_s(&file, "Student_info.txt", "rt");
	if (file == NULL) {
		printf("Can not open the file!\n");
		return 1;
	}
	for(i=0;;i++) {
		char str[100];
		fgets(str, sizeof(str), file); // ���� �� �Է��� �޾���
		int str_length = strlen(str);
		if (feof(file)) break; // file�� ���� �̸� ��� break�� while���� ��������
		(student_info + i)->student_number = 0; //�й��� ������ ���� ���̱� ������ �ʱ�ȭ�� ����
		int k = 1000000000;
		for (int j = 0; j < 10; j++) {
			(student_info + i)->student_number += k*(str[j] - '0'); // �ϳ��ϳ� ���ؼ� student_number�� ������.
			k /= 10;
		}
		for (int j = 11; j <str_length; j++)	{
			(student_info + i)->name[j-11] = str[j];	// �й��� �Է��ϰ� ���Ŀ� \t�� ���� 11��° ���ں��� �̸��̹Ƿ� j=11���� �����ؼ� str�� ������ ���� �̸��� �ѱ��ھ� �־���
		}
		(student_info + i)->name[str_length - 12] = '\0'; // ������ ���ڿ� �ι��ڰ��ƴ� ���๮�ڰ� ���Ƿ� �ι��ڸ� �־���
		(student_info + i)->score = (rand() % 101); //������ ������ ������ �־���ϹǷ� rand()�� 101�� �����ԵǸ� 0~100 ���̿� ���ڰ� �������� ��.
	}
	printf("mean : %lf\n", get_mean(student_info)); // ����� �����
	printf("deviation : %lf\n", get_deviation(student_info));	// ǥ�������� �����
	for (i = 0;i<100; i++) {
		printf("%s %d\n",(student_info+i)->name,(student_info+i)->student_number);
	}
	fclose(file);
	return 0;
}