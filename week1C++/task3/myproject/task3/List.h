#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#include <iostream>
using namespace std;

////////////////////////////////////
// ����Ԫ����
////////////////////////////////////
template <typename T>
class DataType
{
public:
	bool b; //�Ƿ���������
	DataType* pre;
	DataType* next;

	DataType() {
		data = T(); pre = NULL; next = NULL; b = false;
	};
	DataType(T i) {
		data = i; pre = NULL; next = NULL; b = false;
	};
	~DataType() {
		data = NULL; pre = NULL; next = NULL; b = NULL;
	};

	T getData() { return data; }

	friend bool operator<(DataType& d1, DataType& d2) {
		if (d1.data < d2.data) return true;
		else return false;
	};
	friend bool operator>(DataType& d1, DataType& d2) {
		if (d1.data > d2.data) return true;
		else return false;
	};
	friend bool operator==(DataType& d1, DataType& d2) {
		if (d1.data == d2.data) return true;
		else return false;
	};
private:
	T data;
};

////////////////////////////////////////////////////////////////
// ˫�������࣬������Ĭ�Ϲ��캯������Ŀ����������������������
// ʵ������������ݡ��������򡢲���������ĳ���ڵ㼰ɾ��������ĳ
// ���ڵ�Ĳ�����
////////////////////////////////////////////////////////////////
template <typename T>
class List
{
public:
	DataType<T>* p;  //ָ��ǰ���ݵ�ָ��
	List() {
		p = NULL; head = NULL; tail = NULL; len = 0;
	};
	List(List<T>& b) {
		p = b.p; head = b.head; tail = b.tail; len = b.len;
	};
	~List() {
		p = NULL; head = NULL; tail = NULL;
		len = 0;
	};
	List& add(DataType<T>& d, const int i);//��ָ��λ��������ݣ�����ͷ����Ӧ��������1��β����Ӧlen+1
	List& add(DataType<T>& d); //��β��������ݡ�
	List& sortRise();  //��������
	DataType<T>* findByNum(const int i); //ͨ��λ��Ѱ��data����ָ����ʽ����
	int findTheNum(const T data); //ͨ�����ݵ����ݣ�DataType��˽�г�Աdata��ֵ),���Ҹ����ݵ�λ�ã����Ҳ�������0
	List& del(const int i);  //ɾ����i�����ݣ�ɾ����pָ����һ������
	List& del(DataType<T>& data); //ɾ����������Ϊdata�����ݣ����г���һ����ɾ��ȫ����
private:
	DataType<T>* head;
	DataType<T>* tail;
	int len;  //Ԫ�ص��ܸ���
	void QSortRise(DataType<T>* i, DataType<T>* j);//��i��j�����ݽ��п�������
};

/////////////////////////////
// ������ĳ�Ա��������
/////////////////////////////
template <typename T>
List<T>& List<T>::sortRise()
{
	QSortRise(head, tail);
	return *this;
}

// ��i��j�����ݽ��п�������
template <typename T>
void List<T>::QSortRise(DataType<T>* fst, DataType<T>* lst)
{
	DataType<T>* p = fst->next;
	if (!p) {
		cout << "Error" << endl;
		return;
	}
	p = fst;
	if (p == lst)  return;

	// ��ʼ��������
	DataType<T> *i, *j;
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
					DataType<T>* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType<T>* t;
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
					DataType<T>* t = i->next;
					i->next = j->next;  j->next = t;
					t = i->pre;
					i->pre = j->pre;  j->pre = t;
				}
				DataType<T>* t;
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

template <typename T>
DataType<T>* List<T>::findByNum(const int i)
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

template <typename T>
int List<T>::findTheNum(const T da)
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

template <typename T>
List<T>& List<T>::add(DataType<T>& data, int index)
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

template <typename T>
List<T>& List<T>::add(DataType<T>& data)
{
	return this->add(data, len + 1);
}

template <typename T>
List<T>& List<T>::del(int i)
{
	findByNum(i); //��pָ���i������
	DataType<T>* pp = p;
	len--;
	if (len == 0) {
		head = NULL; tail = NULL; p = NULL;
		pp->~DataType<T>();
		return *this;
	}
	if (p == head) {
		head = p->next;
		p = head; p->pre = NULL;
		pp->~DataType<T>();
	}
	else if (p == tail) {
		tail = p->pre;
		p = tail; p->next = NULL;
		pp->~DataType<T>();
	}
	else {
		p = p->next;  //ɾ����pָ����һ������
		p->pre = pp->pre;
		pp->pre->next = p;
		pp->~DataType<T>();
	}
	return *this;
}

template <typename T>
List<T>& List<T>::del(DataType<T>& dt)
{
	T d = dt.getData();
	int i = findTheNum(d);
	while (i != 0) {
		del(i);
		i = findTheNum(d);
	}
	return *this;
}


#endif