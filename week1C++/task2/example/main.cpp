#define  _CRT_SECURE_NO_WARNINGS 
#include"CString.h"
#include<iostream>
using namespace std;


void main()
{
	CNString str1("abc");
	CNString str2;
	cout << "���� = ������:" << endl;
	str2 = str1;
	str2.Show();
	CNString str3("efg");
	CNString str4;
	cout << "���� + ������" << endl;
	str4 = str1 + str3;
	str4.Show();
	CNString nstring1("abc");
	cout << "���� [] ������:" << endl;
	cout << nstring1[0] << endl;// ����Ļ��ʾa
	cout << nstring1[2] << endl; // ����Ļ��ʾc
	cout << "���� > ������:" << endl;
	if (str1>str3){
		cout << "str1>str3" << endl;
	}
	cout << "���� < ������:" << endl;
	if (str1<str3){
		cout << "str1<str3" << endl;
	}
	cout << "���� == ������:" << endl;
	if (str1 == str3){
		cout << "str1==str3" << endl;
	}
	system("pause");
}