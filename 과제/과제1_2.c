#include<stdio.h>
#include<string.h> // strlen()�Լ� ȣ�⿡ �̿�
void reverse_recursion(char *s, int now, int length)
{
	if (length - 1 != now) reverse_recursion(s, now + 1, length); //���ڿ��� ������ ���ڿ� ������ ���ڿ� ������ �� �� �ٸ��� �ε����� 1���� ���� ���ȣ���� �Ѵ�.
	printf("%c", *(s + now));
}
int main()
{
	char string[100];
	scanf_s("%s", string,sizeof(string));	// �Ųٷ� �Է��� ���ڸ� �Է¹޴´�
	reverse_recursion(string, 0, strlen(string)); // �Ű������� ������ �ּ�, ó�� ��ġ, ������ ���̸� �ش�.
	return 0;
}