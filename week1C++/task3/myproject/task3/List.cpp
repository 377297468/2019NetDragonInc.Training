#include "DataType.h"
#include "List.h"

#include <iostream>

using namespace std;

List::List()
{
	p = NULL; head = NULL; tail = NULL; len = 0;
}

List::List(List& b)
{
	p = b.p; head = b.head; tail = b.tail; len = b.len;
}

List::~List()
{
	p = NULL; head = NULL; tail = NULL;
	len = 0;
}

List& List::sortRise()
{
	QSortRise(head, tail);
	return *this;
}

// ��i��j�����ݽ��п�������
void List::QSortRise(DataType* fst, DataType* lst)
{
	DataType* p = fst->next;
	if (!p) {
		cout << "Error" << endl;
		return;
	}
	p = fst;
	if (p == lst)  return;

	// ��ʼ��������
	DataType *i, *j;
	i = fst; j = lst;
	while (true) {
		if (i == j)
			break;
		while (true) {
			if (*j < *p) {
				// ��i,j��ָ�����������е�λ�ý��������Ž���i��jָ��
				// ע���Ƿ�Ҫ����ͷβָ�뼰fst\lstָ��
				if (i == head) {
					head = j;
					fst = j;
				}
				else {
					if (i == fst) fst = j;
					i->pre->next = j;
				}
				if (j == tail) {
					tail = i; lst = i;
				}
				else {
					if (lst == j) lst = i;
					j->next->pre = i;
				}
				if (i->next == j) {
					i->next = j->next; j->next = i;
					j->pre = i->pre; i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType* t;
				t = i;  i = j;	j = t;
				break;  //����j��ѭ������ʼi��ѭ��
			}
			else {
				j = j->pre;
				if (i == j) break;  //����j��ѭ����Ȼ�������һ�˿���
			}
		}
		while (true) {
			if (i == j)  break;
			if (*i > *p) {
				if (i == head) {
					head = j;
					fst = j;
				}
				else {
					if (i == fst) fst = j;
					i->pre->next = j;
				}
				if (j == tail) {
					tail = i; lst = i;
				}
				else {
					if (lst == j)  lst = i;
					j->next->pre = i;
				}
				if (i->next == j) {
					i->next = j->next; j->next = i;
					j->pre = i->pre; i->pre = j;
				}
				else {
					i->next->pre = j;
					j->pre->next = i;
					DataType* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType* t;
				t = i;  i = j;	j = t;
				break;  //����i��ѭ������ʼj��ѭ��
			}
			else {
				i = i->next;
				if (i == j)	break;
			}
		}
	}
	// һ�˿��Ž�������ʼ��pָ��ǰ���������п���
	if (p != lst && p->next != NULL)
		this->QSortRise(p->next, lst);
	if (p != fst && p->pre != NULL)
		this->QSortRise(fst, p->pre);
}

DataType* List::findByNum(const int i)
{
	// λ��i������Χ
	if (i > len || i < 1) {
		cout << i << " is too big or too small." << endl;
		return NULL;
	}
	// ��ǰ������
	if (i < len / 2) {
		p = head;
		for (int j = 1; j < i; j++)
		{
			if (i == j)  return p;
			p = p->next;
		}
	}
	// �Ӻ���ǰ��
	else {
		p = tail;
		for (int j = len; j > 0; j--)
		{
			if (i == j)  return p;
			p = p->pre;
		}
	}
	return p;
}

int List::findTheNum(const int da)
{
	p = head;
	int i = 1;
	while (p)
		if (p->getData() == da)
			return i;
		else
			if (p != tail) {
				p = p->next;
				i++;
			}
			else	return 0; //�Ҳ���������ֵΪ0
}

List& List::add(DataType& data, int index)
{
	if (index > len + 1) {
		cout << "Error! The index number is too big." << endl;
		return *this;
	}
	else if (index < 1) {
		cout << "Error! The index number cna't bee negative." << endl;
		return *this;
	}
	// �������Ϊ��
	if (len == 0) {
		head = &data;
		tail = &data;
		p = &data;
		len++;
		data.b = true;
		return *this;
	}
	// ���data�Ƿ��Ѿ���ӽ�������
	else if (data.b == true) {
		cout << "This data has aleady in the List." << endl;
		return *this;
	}
	// ����ĩβ����data
	if (index == len + 1) {
		tail->next = &data;
		data.pre = tail;
		data.next = NULL;
		tail = &data;
		len++;
		data.b = true;
		return *this;
	}
	// �ڵ�index������ǰ�����data
	else
	{
		int half = len / 2;
		if (index <= half) {
			p = head;
			for (int j = 1; j <= half; j++) {
				if (index == j) break;
				p = p->next;
			}
		}
		else {
			p = tail;
			for (int j = len; j > half; j--) {
				if (index == j)  break;
				p = p->pre;
			}
		}
		if (index != 1) {
			data.pre = p->pre;
			p->pre->next = &data;
		}
		else { //���������ǰ��ʱ
			head = &data;
			data.pre = NULL;
		}
		p->pre = &data;
		data.next = p;
		len++;
		data.b = true;
		return *this;
	}
}

List& List::add(DataType& data)
{
	return this->add(data, len + 1);
}

List& List::del(int i)
{
	findByNum(i); //��pָ���i������
	DataType* pp = p;
	len--;
	if (len == 0) {
		head = NULL; tail = NULL; p = NULL;
		pp->~DataType();
		return *this;
	}
	if (p == head) {
		head = p->next;
		p = head; p->pre = NULL;
		pp->~DataType();
	}
	else if (p == tail) {
		tail = p->pre;
		p = tail; p->next = NULL;
		pp->~DataType();
	}
	else {
		p = p->next;  //ɾ����pָ����һ������
		p->pre = pp->pre;
		pp->pre->next = p;
		pp->~DataType();
	}
	return *this;
}

List& List::del(DataType& dt)
{
	int d = dt.getData();
	int i = findTheNum(d);
	while (i != 0) {
		del(i);
		i = findTheNum(d);
	}
	return *this;
}
