#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main()
{

	int decimal = 300;				// 테스트할 10진수 숫자 변수에 넣기
	char hexadeciaml[20] = { 0, };	// 16진수로 변환을 담을 배열 초기화
	char newone[20] = { 0, };
	char sixteen[99] = { '0', 'x', };
	int num = 0;

	int position = 0;				// 배열 인덱스를 0으로 초기화

	while (1)
	{
		int mod = decimal % 16;		// 16으로 나눈 나머지를 mod 변수에 저장
		if (mod < 10)
		{
			hexadeciaml[position] = 48 + mod;	// ASCII 코드 48는 문자 '0'
		}
		else
		{
			hexadeciaml[position] = 65 + (mod - 10);	// ASCII 코드 65는 문자 '65'
		}

		decimal = decimal / 16;							// 16으로 다시 나눌 몫을 구하기

		position++;

		if (decimal == 0)								// 더이상 나눌 몫이 없으면 while문 종료
			break;
	}

	// 배열의 요소를 역순으로 새로 저장
	for (int i = position - 1; i >= 0; i--)
	{
		for (int j = 0; j < position; j++)
		{
			newone[j] = hexadeciaml[i];
		}
	}

	strcat(sixteen, newone); // 배열 이어붙히기

	printf("16진수는 : ");

	for (int k = 0; k < position+2; k++)
	{
		printf("%c", sixteen[k]);
	}
	printf("\n");
	printf("16진수를 입력해주세요.");
	scanf("%x", &num);

	int original = num; //원본 데이터
	int cryptograph = 0;  //암호화 데이터
	int decrypt = 0;        //복화화 데이터
	int key = 0x394A38C9;       //암호화와 복호화에 사용할 키
	printf("원본 데이터: %#X \n", original);
	cryptograph = original ^ key; //암호화
	printf("암호화 데이터: %#X \n", cryptograph);
	decrypt = cryptograph ^ key; //복호화
	printf("복호화 데이터: %#X \n", decrypt);
	
	return 0;
}