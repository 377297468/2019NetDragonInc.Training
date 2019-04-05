#include "DLinkedList.h"
#include <iostream>
using namespace std;

ListNode::ListNode(const int x)
{
	data = x;
	prev = NULL;
	next = NULL;
}


DLinkedList::DLinkedList()
{
	_head = NULL;
	_tail = NULL;
}

DLinkedList::DLinkedList(DLinkedList & s)
{
	/*���ƶ���Ϊ������ʱ������������*/
	if (s._head == NULL)
	{
		_head = NULL;
		_tail = NULL;
		return;
	}
	ListNode* temp = s._head;
	while (temp)
	{
		/*�Ӹ��ƶ����ͷ��㿪ʼ��β�ڵ����������������β�����븴�ƶ���Ľڵ�����*/
		PushNode(temp->data);
		temp = temp->next;
	}
}

DLinkedList::~DLinkedList()
{
	/*���������ͷŽڵ�ռ�*/
	ListNode* begin = _head;
	while (begin != _tail)
	{
		_head = _head->next;
		delete begin;
		begin = _head;
	}
	_head = NULL;
	_head = NULL;
}

/*��β������һ���ڵ�*/
void DLinkedList::PushNode(const int x)
{
	if (_head == NULL)  /*�������ǿ�������Ϊβ������Ľڵ���ͷ���Ҳ��β�ڵ�*/
	{
		_head = new ListNode(x);
		_tail = _head;
	}
	else
	{
		_tail->next = new ListNode(x);
		_tail->next->prev = _tail;
		_tail = _tail->next;
	}

}
/*�̶�λ�ò���һ���ڵ㣨���Find��������ʹ�ã�*/
void DLinkedList::Insert(ListNode * pos, int data)
{
	if (pos == _tail)
	{
		/*����λ����β�ڵ�ʱ��ֱ����β�ڵ������½ڵ�*/
		PushNode(data);
	}
	else
	{
		ListNode* tar = Find(pos->data);
		if (tar != NULL)  /*�����ָ��λ���������д��ڵ���Ч�ڵ�*/
		{
			ListNode* newNode = new ListNode(data);
			newNode->next = tar->next;
			newNode->prev = tar;
			tar->next = newNode;
			tar->next->prev = newNode;
		}
	}

}
/*ɾ��ָ���ĵĽڵ�*/
void DLinkedList::Delete(const int x)
{
	/*����ǿ�����ʱ������ɾ������*/
	if (this->isEmpty() == false)
	{
		ListNode* target = NULL;
		if (_head->data == x)
		{
			/*ɾ����ָ���ڵ�Ϊͷ���*/
			target = _head;
			_head = _head->next;
			_head->prev = NULL;
			delete target;
		}
		if (_tail->data == x)
		{
			/*ɾ����ָ���ڵ�Ϊβ���*/
			target = _tail;
			_tail = _tail->prev;
			_tail->next = NULL;
			delete target;
		}
		target = Find(x);
		if (target != NULL)
		{
			/*ɾ����ָ���ڵ�Ϊ�����д��ڵ���Ч�ڵ�*/
			target->prev->next = target->next;
			target->next->prev = target->prev;
			delete target;
		}
	}

}

/*����ָ���Ľڵ�*/
ListNode * DLinkedList::Find(const int x)
{
	if (this->isEmpty() == true)
	{
		return NULL;
	}
	else
	{
		ListNode* begin = _head;
		while (begin != NULL)
		{
			if (begin->data == x)
			{
				return begin;
			}
			begin = begin->next;
		}
	}
	return NULL;
}
/*���������ð����������*/
void DLinkedList::AscendingOrder()
{
	ListNode* p;
	ListNode* q;

	for (p = _head; p->next != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (q->data < p->data)
			{
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}

bool DLinkedList::isEmpty()
{
	if (_head == NULL)
	{
		cout << "����Ϊ������" << endl;
		return true;
	}
	return  false;
}

void DLinkedList::show()
{
	ListNode* begin;
	for (begin = _head; begin != NULL; begin = begin->next)
	{
		cout << begin->data << " ";
	}
	cout << endl;
}


