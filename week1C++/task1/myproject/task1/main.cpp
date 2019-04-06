#include <iostream>

using namespace std;

#define MAX_STR 11 //int������󲻻ᳬ��10λ��

////////////////////////////////////////////////
// input:n       int���ͣ���Χ0��MAX_INT
// input:string  char*����,����ַ���
// output:       char*���ͣ���intת��Ϊstring
////////////////////////////////////////////////
char* itostr(int n, char* string)
{
	// �ַ����ĳ���
	static int length = 0;

	// ��¼��ǰ�ݹ�Ĳ���
	static int static_i = 0;
	static_i++;
	int current_i = static_i;

	// ������
	if (n < 0) {
		n = -n;
		*string = '-';
		length++;
	}

	// ��ȡ��λ�ϵ�����
	int n1 = n % 10;

	// �ݹ�Ѹ�λ����д��string
	if (n != n1)
		itostr(n / 10, string);

	// �Ѹ�λ��д��string
	*(string + length) = n1 + '0';
	length++;

	// �ƺ���
	// �ݹ鵽�����һ��ʱ
	if (n == n1)
		*(string + length) = '\0';
	// �ݹ���������ص��˱��ʱ
	if (current_i == 1) {
		length = 0;
		static_i = 0;
	}
	
	return string;
}

//////////////////////////////////////////////////
// Main Function
// ������������"001"��ԭ���ǵݹ麯����string��ֵ�͵��������˳��
//////////////////////////////////////////////////
int main()
{
	int n;
	char* string = new char[MAX_STR];

	while (true) {
		for (int i = 0; i <= MAX_STR; i++)
			*(string + i) = 0;
		cout << "������int���͵�������";
		cin >> n;
		cout << "������������ǣ�" << itostr(n,string) << endl << endl;
	}

	delete string;
	return 0;
}
