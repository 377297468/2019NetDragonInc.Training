#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

struct ListNode
{
	ListNode(const int x);
	int data;      /*�ڵ������*/
	ListNode* prev;		/*�ڵ��ǰ��ָ��*/
	ListNode* next;		/*�ڵ�ĺ��ָ��*/
};

class DLinkedList
{
private:
	ListNode* _head;	/*ָ�������ͷ�ڵ�*/
	ListNode* _tail;	/*ָ�������β�ڵ�*/
public:
	DLinkedList();					/*��Ĺ��캯��*/
	DLinkedList(DLinkedList& s);	/*��Ŀ�������*/
	~DLinkedList();					/*�����������*/

public:
	/*��β������һ���ڵ�*/
	void PushNode(const int x);

	/*�̶�λ�ò���һ���ڵ�*/
	void Insert(ListNode* pos, int data);

	/*ɾ��ָ���ĵĽڵ�*/
	void Delete(const int x);

	/*����ָ���Ľڵ�*/
	ListNode* Find(const int x);

	/*�����������������*/
	void AscendingOrder();

	/*�ж��б��Ƿ�Ϊ��*/
	bool isEmpty();

	void show(); /*��ӡ�б�����*/

};


#endif
