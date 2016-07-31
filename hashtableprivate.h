// File:        hashtableprivate.h
// Author:      Travis- Caitlin
// Date:        March 25, 2016
// Description: Add your own private member functions for the HashTable class
//              Private member functions only!
//              No changes to private member attributes!

// helper function for deep delete
// Used by destructor
void DeleteArray()
{
	maxsize=0;
	size=0;
	delete [] table;
}

 // helper function for deep copy
// Used by copy constructor
void CopyArray(const HashTable &sourceht)
{
	size= sourceht.size;
	maxsize= sourceht.maxsize;
	table= new SLinkedList<UserAccount>[maxsize];

	for(int i=0; i<maxsize; i++) //copys the elements from the old array to new array
	{
		table[i]=sourceht.table[i];
	}
}

