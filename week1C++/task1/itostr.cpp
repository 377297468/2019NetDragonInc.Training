#include "stdafx.h"
#include "itostr.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

char * itostr(int n, char * string)
{
	//�ַ������±�
	static int i = 0;
	
	//�ж��Ƿ���
	if (n < 0)
	{
		string[i] = '-';
		n = abs(n);
		i++;
	}

	//�ݹ齫ÿ��λ����ֵ���ַ���
	if (n/10) 
	{
		itostr(n/10, string);
	}

	string[i] = n % 10 + '0';
	i++;
	string[i] = '\0';

	return string;
}

void itostrTest()
{
	char str[30];
	int n;
	printf("����������������������������\n");
	printf("��Test1������ת�ַ��� \n");
	printf("����������������������������\n");

	printf("��-> ������һ��������");
	scanf_s("%d", &n);
	printf("��\n");
	
	printf("��   ��������Ϊ��%d\n",n);
	printf("��   ִ��itostr(%d,str);\n", n);
	itostr(n, str);
	printf("��   ����ַ���str��%s\n", str);
	printf("��\n");
	printf("����������������������������\n");
	
	system("Pause");
}
