#include<iostream>
#include<string.h>
#include<fstream>
#include<climits>
#include<conio.h>
#include"Linked_List.h"

using namespace std;

const char *filePath = "Data.txt";

int PressNumber();
int MenuBox();
void FinishThisAction();
void Deploy(int key);

struct MEMBER
{
	int ID;
	string name;
	int age;
	int group_ID;
	
};
typedef struct MEMBER member;
		
bool operator == (member mem1, member mem2)
{
	return (mem1.ID == mem2.ID);
}

bool operator != (member mem1, member mem2)
{
	return (mem1.ID != mem2.ID);
}

bool Compare(member m1, member m2)
{
	return (m1.ID < m2.ID);
}

class List_of_Member 
{
	
	private:
		
		Linked_List <member> *memberList;
		
	public:
	
		List_of_Member();
	
		void AddMember();
	
		void EditMemberInformationViaID(int ID);
	
		void FindMemberByID(int ID);
	
		void DeleteMember(int ID);
		
		void NumberOfMember();
		
		void SortByID();
		
		void ViewDetail();
	
		~List_of_Member();
};

// Constructor
List_of_Member :: List_of_Member()
{
	memberList = new Linked_List <member>;
	
	ifstream input(filePath);
	member temp;
	while(!input.eof())
	{
		input >> temp.ID >> temp.age>> temp.group_ID;
		input.ignore();
		getline(input, temp.name);
		this->memberList->AddToTail(temp);
	}
	input.close();
}

// Xem thong tin cua tat ca cac thanh vien
void List_of_Member :: ViewDetail()
{
	node <member> *p = memberList->Begin();
	while(p != NULL)
	{
		member view = p->data;
		cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "ID: " << view.ID << endl;
		cout << "Name: " << view.name << endl;
		cout << "Age: " << view.age << endl;
		cout << "Group: " << view.group_ID << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
		p = p->pNext;
	}
}

// Them mot thanh vien moi
void List_of_Member :: AddMember()
{
	member newMember;
	
	cout << "ID: ";
	newMember.ID = PressNumber();
	cout << "Name: ";
	cin.ignore();
	getline(cin, newMember.name);
	cout << "Age: ";
	newMember.age = PressNumber();
	cout << "Group: ";
	newMember.group_ID = PressNumber();
	
	memberList->AddToTail(newMember);
}

// Sua thong tin mot thanh vien khi biet ID
void List_of_Member :: EditMemberInformationViaID(int ID)
{
	member traced;
	traced.ID = ID;
	node <member> *p = memberList->FindSingleElementByKey(traced);
	if(p == NULL)
	{
		cout << "No member having that ID!" << endl;
		return;
	}
	else
	{
		cout << "Input new data:" << endl;
		cout << "Name: ";
		cin.ignore();
		getline(cin, traced.name);
		cout << "Age: ";
		cin >> traced.age;
		cout << "Group: ";
		cin >> traced.group_ID;
		
		p->data = traced;
	}
}

// Xoa mot thanh vien
void List_of_Member :: DeleteMember(int ID)
{
	member traced;
	traced.ID = ID;
	memberList->Delete(traced);
}

// Tim mot thanh vien qua ID
void List_of_Member :: FindMemberByID(int ID)
{
	member traced;
	traced.ID = ID;
	node <member> *p = memberList->FindSingleElementByKey(traced);
	if(p == NULL)
	{
		cout << "No member having that ID!" << endl;
		return;
	}
	else
	{
		traced = p->data;
		cout << "Name: " << traced.name << endl;
		cout << "ID: " << traced.ID << endl;
		cout << "Age: " << traced.age << endl;
		cout << "Group: " << traced.group_ID << endl;
	}
}

// Tim mot thanh vien qua ID
void List_of_Member :: NumberOfMember()
{
	cout << "So thanh vien trong doi: " << memberList->Length() << endl;
}

//Sap xep cac thanh vien qua ID
void List_of_Member :: SortByID()
{
	memberList->Sort(Compare);
}

// Destructor
List_of_Member :: ~List_of_Member()
{
	ofstream output(filePath);
	
	node <member> *p = memberList->Begin();
	while(p != memberList->End())
	{
		member temp = p->data;
		output << temp.ID << " " << temp.age << " " << temp.group_ID << endl;
		output << temp.name << endl;
		p = p->pNext;
	}
	member temp = p->data;
	output << temp.ID << " " << temp.age << " " << temp.group_ID << endl;
	output << temp.name;
	
	output.close();
	
	memberList->Clear();
	delete  memberList;
	
}

// ============================================================================ PROGRAM ===============================================================================
// ==================================================================== VIT MEMBER MANAGEMENT =========================================================================

List_of_Member myList;

int main()
{
	const int EXIT_CODE = 8;
	int key;
	do{
		key = MenuBox();
		Deploy(key);
	}while(key != EXIT_CODE);
	return 0;
}

int PressNumber()
{
	int number;
	cin >> number;
	while(cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Yeu cau nhap vao so: ";
		cin >> number;
	}
	return number;
}

int MenuBox()
{
	cout << "==================== MENU ====================\n";
	cout << "1. Them thanh vien\n";
	cout << "2. Sua thong tin mot thanh vien\n";
	cout << "3. Tim kiem thong tin thanh vien\n";
	cout << "4. Xoa mot thanh vien khoi danh sach\n";
	cout << "5. So thanh vien trong doi\n";
	cout << "6. Xem thong tin tat ca thanh vien trong doi\n";
	cout << "7. Sap xep thanh vien theo ID\n";
	cout << "8. Thoat\n";
	int selection;
	do{
		cout << "Select: ";
		selection = PressNumber();
	}while(selection < 1 || selection > 8);
	return selection;
}

void FinishThisAction()
{
	cout << "Press any key to continue...";
	getch();
	cin.ignore();
	system("cls");
}

void Deploy(int key)
{
	switch(key)
	{
		case 1:{
			myList.AddMember();
			FinishThisAction();
			break;
		}
		
		case 2:{
			int ID = PressNumber();
			myList.EditMemberInformationViaID(ID);
			FinishThisAction();
			break;
		}
		
		case 3:{
			int ID = PressNumber();
			myList.FindMemberByID(ID);
			FinishThisAction();
			break;
		}
		
		case 4:{
			int ID = PressNumber();
			myList.DeleteMember(ID);
			FinishThisAction();
			break;
		}
		
		case 5:{
			myList.NumberOfMember();
			FinishThisAction();
			break;
		}
		
		case 6:{
			myList.ViewDetail();
			FinishThisAction();
			break;
		}
		
		case 7:{
			myList.SortByID();
			FinishThisAction();
			break;
		}
		
		default: break;
	}
}
