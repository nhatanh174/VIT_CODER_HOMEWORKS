// Demo danh sach lien ket don va mot so thao tac co ban

#include<cstdlib>

template <typename dataType>
struct node
{
	dataType data;
	node *pNext;
};

template <typename dataType>
struct list
{
	node <dataType> *pHead;
	node <dataType> *pTail;
};

template <typename dataType>
class Linked_List
{
	private:
		
		list <dataType> *myList;
		int numberOfElement;
		
		node <dataType> *GetNode(dataType singleElement)
		{
			node <dataType> *p = new node <dataType>;
			p->data = singleElement;
			p->pNext = NULL;
			return p;
		};
		
	public:
		
		Linked_List();
		
		void AddToTail(dataType singleElement);
		
		void Delete(dataType key);
		
		int Length();
		
		bool Empty();
		
		void Clear();
		
		void Sort(bool (*compare) (dataType singleElement1, dataType singleElement2));
		
		node <dataType> *Begin();
		
		node <dataType> *End();
		
		node <dataType> * FindSingleElementByKey(dataType key);
		
		~Linked_List();
		
};


// Constructor
template <typename dataType>
Linked_List <dataType> :: Linked_List()
{
	this->myList = new list <dataType>;
	this->myList->pHead = this->myList->pTail = NULL;
	this->numberOfElement = 0;
};


// Them 1 phan tu vao cuoi danh sach
template <typename dataType>
void Linked_List <dataType> :: AddToTail(dataType singleElement)
{
	node <dataType> *p = GetNode(singleElement);
	if(this->myList->pHead == NULL)
	{
		this->myList->pHead = this->myList->pTail = p;
	}
	else{
		this->myList->pTail->pNext = p;
		this->myList->pTail = p;
	}
	this->numberOfElement ++;
};


// Xoa 1 phan tu giong voi key trong danh sach
template <typename dataType>
void Linked_List <dataType> :: Delete(dataType key)
{
	node <dataType> *p = this->myList->pHead;
	node <dataType> *q = new node <dataType>;
	q->pNext = p;
	while(p->data != key)
	{
		p = p->pNext;
		q = q->pNext;
		if(p == NULL)
		{
			return;
		}
	}
	if(p == this->myList->pHead)
	{
		this->myList->pHead = p->pNext;
	}
	if(p == this->myList->pTail)
	{
		this->myList->pTail = q;
	}
	q->pNext = p->pNext;
	p->pNext = NULL;
	free(p);
	this->numberOfElement --;
};


// Tra ve do dai cua danh sach
template <typename dataType>
int Linked_List <dataType> :: Length()
{
	return this->numberOfElement;
};


// Check xem danh sach co phan tu nao hay khong
template <typename dataType>
bool Linked_List <dataType> :: Empty()
{
	if(this->numberOfElement == 0)
	{
		return true;
	}
	return false;
};


// Xoa het phan tu cua danh sach
template <typename dataType>
void Linked_List <dataType> :: Clear()
{
	while(this->myList->pHead != NULL)
	{
		node <dataType> *p = this->myList->pHead;
		this->myList->pHead = this->myList->pHead->pNext;
		p->pNext = NULL;
		free(p);
	}
};

// Sap xep cac phan tu cua danh sach theo thu tu xac dinh
template <typename dataType>
void Linked_List <dataType> :: Sort(bool (*Compare) (dataType singleElement1, dataType singleElement2))
{
	node <dataType> *p = this->myList->pHead;
	while(p != this->myList->pTail)
	{
		node <dataType> *q = p->pNext;
		while(q != NULL)
		{
			if(!(*Compare)(p->data, q->data))
			{
				dataType temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
			q = q->pNext;
		}
		p = p->pNext;
	}
}

// Tim phan tu thong qua key
template <typename dataType>
node <dataType> * Linked_List <dataType> :: FindSingleElementByKey(dataType key)
{
	node <dataType> *p = this->myList->pHead;
	while(p != NULL)
	{
		if(p->data == key)
		{
			return p;
		}
		p = p->pNext;
	}
	return NULL;
}


// Tra ve node dau tien cua danh sach
template <typename dataType>
node <dataType> * Linked_List <dataType> :: Begin()
{
	return this->myList->pHead;
}


// Tra ve node dau tien cua danh sach
template <typename dataType>
node <dataType> * Linked_List <dataType> :: End()
{
	return this->myList->pTail;
}


// Distructor
template <typename dataType>
Linked_List <dataType> :: ~Linked_List()
{
	free(this->myList);
};
