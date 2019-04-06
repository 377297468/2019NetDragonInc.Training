#ifndef _LIST_H_
#define _LIST_H_

#define MAX 999999  //�������󳤶�

class DataType;

////////////////////////////////////////////////////////////////
// ˫�������࣬������Ĭ�Ϲ��캯������Ŀ����������������������
// ʵ������������ݡ��������򡢲���������ĳ���ڵ㼰ɾ��������ĳ
// ���ڵ�Ĳ�����
////////////////////////////////////////////////////////////////
class List
{
public:
	DataType* p;  //ָ��ǰ���ݵ�ָ��
	List(void);
	List(List& b);
	~List();
	List& add(DataType& d, const int i);//��ָ��λ��������ݣ�����ͷ����Ӧ��������1��β����Ӧlen+1
	List& add(DataType& d); //��β��������ݡ�
	List& sortRise();  //��������
	DataType* findByNum(const int i); //ͨ��λ��Ѱ��data����ָ����ʽ����
	int findTheNum(const int data); //ͨ�����ݵ����ݣ�DataType��˽�г�Աdata��ֵ),���Ҹ����ݵ�λ�ã����Ҳ�������0
	List& del(const int i);  //ɾ����i�����ݣ�ɾ����pָ����һ������
	List& del(DataType& data); //ɾ����������Ϊdata�����ݣ����г���һ����ɾ��ȫ����
private:
	DataType* head;
	DataType* tail;
	int len;  //Ԫ�ص��ܸ���
	void QSortRise(DataType* i, DataType* j);//��i��j�����ݽ��п�������
};

#endif // !_LIST_H_