#include "iostream"

using namespace std;

#define MAX_STR 11              //int������󲻻ᳬ��10λ��
#define MAX_INT 2147483647

////////////////////////////////////////////////
// input:     int���ͣ���Χ0��MAX_INT��
// input:     char*����
// output:    char*���ͣ�����Ϊ����n��ֵ
////////////////////////////////////////////////
char* itostr(int n, char* string)
{
	// string�ĳ���
	static int length = 0;

	// ������
	if (n < 0) {

	}

	// ��ȡ��λ�ϵ��ַ�c
	int n1 = n % 10;
	char c = n1 + '0';
	*(string + length) = c;

	length++;

	// �жϵݹ��Ƿ񵽴����һ��
	if (n1 == n) {
		*(string + length) = '\0';
		return string;
	}
	else
		return itostr(n / 10, string);

}

//////////////////////////////////////////////////
// Main Function
// ������������"001"��ԭ���ǵݹ麯����string��ֵ�͵��������˳��
//////////////////////////////////////////////////
int main()
{
	int n;
	char* string = itostr(100, new char);
	cout << string << endl;
	cin >> n;

	return 0;
}
