#include <iostream>
#include <string>

using namespace std;

/*************************************************************************
* This is the list class which is used for organizing 
* the list of student names.
* This is a singly linked list.
* 
* ListNode class is the structure of ever node in 
* the linked list. 
*
* next is the pointer to the next node of the list
* name is the name of every student
* netid is the unique netid of every student
*
**************************************************************************/

class List
{
	private:
	class ListNode
	{
		public:

		//Constructs list node with given data
		ListNode(std::string a_name);
		
		ListNode* next;
        std::string m_sName;
        bool leader;
        
        // Set Leader
        void setLeader(bool value);

        //Get Leader
        bool getLeader();
	};

	ListNode* head;
    ListNode* tail;
	int length;

	public:

	// Default constructor 
	// Empty List with head pointing to NULL
	List();

	//Returns length
	int getLength();

    //Print list
    void print();

	// Inserts a new node at the back of the list. 
	void insertBack(std::string a_name);

	// Reorganizes the list of student names according
	// to given pattern in question
	void reorganizeList();

};

//Constructor for list node
//Nobody is a leader by default
List::ListNode::ListNode(std::string a_name)
{
	m_sName = a_name;
	leader = false;
	next = NULL;
}

//Default constructor for list
List::List()
{
	length = 0;
	head = NULL;
    tail = NULL;
}

//Return length
int List::getLength()
{
	return length;
}

//Set leader as true or false
void List::ListNode::setLeader(bool value)
{
	leader = value;
}

//Set leader as true or false
bool List::ListNode::getLeader()
{
    return leader;
}


//Insert Back 
void List::insertBack(std::string a_name)
{
    ListNode * temp = new ListNode(a_name);
    if(head == NULL)
    {
        head = temp;
        tail = temp;
    }
    
    else
    {
        tail->next = temp;
        tail = tail->next;
    }
    
    length ++;
}

//Reorganize the list
//Example : a -> b -> c -> d -> e -> f -> NULL becomes
// a -> e -> b -> c -> d -> f -> NULL since a and e are leaders
void List::reorganizeList()
{
    //TODO Your code here
	ListNode * curr = head->next;
	ListNode * prev = head;
	ListNode * tempT = tail;
	while (curr!=tail) {
		// unmove leader, and skip
		if (curr->leader) {
			prev = curr;
			curr = curr->next;
		}
		else {
			prev->next = curr->next;
			tempT->next = curr;
			tempT = tempT->next;
			curr = prev->next;
		}
	}
	// curr==tail
	if (curr->leader) ;
	else {
		prev->next = curr->next;
		tempT->next = curr;
		tempT = tempT->next;
		curr = prev->next;
	}
	tail = tempT;
	tail->next = NULL;
	curr = NULL;
	prev = NULL;
	tempT = NULL;
}

//Use this function to display the list
void List::print()
{
    cout<<"----------------Printing List----------"<<endl;
    ListNode * curr = head;
    
    while(curr != tail)
    {
        cout<<curr->m_sName<<" -> ";
        curr = curr->next;
    }
    
    cout<<curr->m_sName<<endl;
    cout<<"--------------------------------------"<<endl;
}

int main()
{
    List studentNames;
    studentNames.insertBack("a");
    studentNames.insertBack("b");
    studentNames.insertBack("c");
    studentNames.insertBack("d");
    studentNames.insertBack("e");
    
    studentNames.print();
    
    studentNames.reorganizeList();
    
    //Expected output
    //a -> e -> b -> c -> d
    
    
    studentNames.print();
}

