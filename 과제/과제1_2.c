#include<stdio.h>
#include<string.h> // strlen()함수 호출에 이용
void reverse_recursion(char *s, int now, int length)
{
	if (length - 1 != now) reverse_recursion(s, now + 1, length); //문자열의 마지막 문자와 지금의 문자와 같은지 비교 후 다르면 인덱스를 1증가 시켜 재귀호출을 한다.
	printf("%c", *(s + now));
}
int main()
{
	char string[100];
	scanf_s("%s", string,sizeof(string));	// 거꾸로 입력할 문자를 입력받는다
	reverse_recursion(string, 0, strlen(string)); // 매개변수로 문자의 주소, 처음 위치, 문자의 길이를 준다.
	return 0;
}