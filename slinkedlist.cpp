// File:        slinkedlist.h
// Author:      Travis- Caitlin
// Date:        March 26, 2016
// Description: Definition of a template singly-linked-list class for CMPT 225 assignment 5

#ifdef _SLINKEDLIST_H_

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

template <class T>
 // helper function for deep copy
    // Used by copy constructor and operator=
void SLinkedList<T>::CopyList(const SLinkedList& ll)
{
	size=0;
		Node<T> * temp = ll.front;
		while(temp)						//Loop until temp is NULL
		{
			Node<T> * newNode = new Node<T>(temp->data);		//creates a new node
			if(size == 0) //list is empty
			{
				front = newNode;
				back = newNode;
			}
			else //list is not empty
			{
				back->next = newNode;
				back = newNode;
			}
			size++;
			temp = temp->next;				//temp moves to the node after
		}
}
    // helper function for deep delete
    // Used by destructor and copy/assignment
	template <class T>
    void SLinkedList<T>::DeleteList()
	{
		Node<T>* searchptr = front;
        while (searchptr != NULL)
        {
                searchptr = front->next;//to traverse the list to find the last pinter
                delete front;//increment the pointer
                front = searchptr;
        }
        front = NULL;
		back= NULL;
		size=0;
	}

    // default constructor
	template <class T>
    SLinkedList<T>::SLinkedList()
	{
		size = 0;//set the initial size to 0
        front = NULL;//set the pointer "front" to null
        back = NULL;//set the pointer "back"
	}

    // copy constructor, performs deep copy of list elements
	template <class T>
    SLinkedList<T>::SLinkedList(const SLinkedList& ll)
	{
		CopyList(ll);//use the helper method to copy the list
	}

    // destructor
	template <class T>
    SLinkedList<T>::~SLinkedList()
	{
		DeleteList(); //calls delete list helper function
	}

    // MUTATORS

    // Inserts an item at the front of the list
    // POST:  List contains item at front
    // PARAM: item = item to be inserted
	template <class T>
    void SLinkedList<T>::InsertFront(T item)
	{
		Node<T>* newNode = new Node<T>(item);
		if(size == 0)
		{
			front = newNode;
			back = newNode;
		}
		else
		{
			newNode->next = front;
			front = newNode;
		}
        size++;//increment the size
	}

    // Inserts an item at the back of the list
    // POST:  List contains item at back
    // PARAM: item = item to be inserted
	template <class T>
    void SLinkedList<T>::InsertBack(T item)
	{
		Node<T>* newNode = new Node<T>(item);
		if(size == 0) //list is empty
		{
			front = newNode;
			back = newNode;
		}
		else //list is not empty
		{
			back->next = newNode;
			back = newNode;
		}
		size++;//increment the size
	}

    // Removes the first occurrence of the supplied parameter
    // Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
	template <class T>
    bool SLinkedList<T>::Remove(T item)
	{
		Node<T>* temp1 = front;
		Node<T>* temp2 = front;

		if(front != NULL && front != back && item ==front->data) //Case1: Item is at front
			{
				temp2=front->next;
				front->next=NULL;
				front=temp2;
				size--;
				return true;

			}
		else if(front != NULL && front ==back && item == front->data)// Case2: There is only 1 item
		{
			//delete front;
			front=NULL;
			back=NULL;
			size--;
			return true;
		}

		while (temp1 != NULL) // multiple items
        {
			if(temp1 != back && temp1->next != back && item == temp1->next->data) //Case3: Many items but Item is NOT at the back
			{
				temp1->next=temp1->next->next;
				size --;
				return true;
			}
			else if(temp1->next == back && item==temp1->next->data)// Many items and Item is at the Back
			{
				temp1->next=NULL;
				back=temp1;
			size--;
			return true;
			}
			temp1=temp1->next;
        }
		return false;
	}

    // Removes all items in the list
	template <class T>
    void SLinkedList<T>::RemoveAll()
	{
		DeleteList();
	}

    // ACCESSORS

    // Returns size of list
	template <class T>
    int SLinkedList<T>::Size() const
	{
		return size;
	}

    // Returns whether the list is empty
	template <class T>
    bool SLinkedList<T>::IsEmpty() const
	{
		if(size == 0)
        {
                return true;//check if the list is empty
        }
        else
        {
                return false;//only if the list is not empty
        }
	}

    // Returns existence of item
	template <class T>
    bool SLinkedList<T>::Contains(T item) const
	{
		if(size == 0)
        {
                return false;
        }
        else
        {
                Node<T>* searchptr = front;
                for(int i = 0; i < size; i++)
                {
                        if(searchptr->data == item)//check if its our wanted item or not
                        {
                                return true;
                        }
                        searchptr = searchptr->next; //set the pointer to the next nodes pointer
                }
        }
        return false;
	}

    // Returns a pointer to the in-place list item or NULL if item not found
   template <class T>
	T* SLinkedList<T>::Retrieve(T item)
	{
		Node<T>* temp = front;

		if(temp!= NULL && temp->data == item)//if item is at the front
		{
			return &(temp->data);
		}
		while(temp != NULL && temp->next!= NULL)//if item is after the front
		{
			if(temp!=NULL && temp->data==item) //when the item is found, return the pointer to the item
			{
				return &(temp->data);
			}
			temp=temp->next;
		}
		return NULL;
	}


    // Returns a vector containing the list contents using push_back
    template <class T>
	vector<T> SLinkedList<T>::Dump() const
	{
		Node<T>* temp = front;
		vector<T> v;

		while(temp!=NULL)
		{
			v.push_back(temp->data); //inserts each item into the back of the vector
			temp=temp-> next;
		}
		return v;
	}

    // OVERLOADED OPERATORS

    // must work in the following cases:
    // list2 = list1 -> general case
    // list2 = list2 -> should do nothing
	template <class T>
    SLinkedList<T>& SLinkedList<T>::operator=(const SLinkedList& ll)
	{
		if (this != &ll)
        {
                DeleteList();//this is to delete it all using our helper function
				CopyList(ll);//and this is to copy it all using our helper function
        }
		return *this;

	}

#endif
