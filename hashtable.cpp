// File:        hashtable.h
// Author:      Travis- Caitlin
// Date:        March 29, 2016
// Description: Definition of a hash table class for CMPT 225 assignment 5
//              must include hashtableprivate.h file for additional private member functions added by student

#include "useraccount.h"
#include "hashtable.h"

// hash function, uses Horner's method
// Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const
{
	int index = 0;

	for(int i=0; i< input.length(); i++ )
	{
		int alpha = input[i];
		//Uses horner's method to calculate the index of the string to be inserted in the array
		//each character's ASCII value is subtracted by 96 to convert to integer: 1 to 26
		index = (index*32 + ((int)alpha-96))%maxsize; 
	}
	return index;
}


// helper function to find smallest prime number greater than supplied parameter		--------------------------------		--------------------------------
int HashTable::SmallestPrime(int n) const 
{
	while(true)
	{
		if(IsPrime(n))
		{
			return n;
		}	
			n++; //increment until a prime number "n" is found
	}	
}

// helper function to determine whether a number is prime		--------------------------------		--------------------------------
bool HashTable::IsPrime(int n) const
{	
	if(n<2) //1 & 0 are not prime numbers
	{
		return false;
	}
		else if(n==2) // 2 is a prime number 
	{
		return true;
	}
	else if (n%2==0) //if n is a multiple of 2 then it's not a prime number.
	{
		return false;
	}

	for(int i=3; i<(n/2); i+=2)  //i is incremented by 2, to skip even numbers
	{
		if(n%i==0)	//if modulus is zero, then it is NOT a prime number
			return false;
	}
	return true;
}

// Resizes the hashtable into a larger array.
// Return false if n is smaller than current array size or if n is negative.
// Else, set array size to the smallest prime number larger than n
//   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable::Resize(int n)
{	
	int array_size = 0;
	if(n <= maxsize) 
		return false;
	SLinkedList<UserAccount> * temp = table; //creates a temporary pointer to the old table
	table = new SLinkedList<UserAccount>[SmallestPrime(n)]; //make table point to a new larger table
	
	vector<UserAccount> v; //create vector for dumping 
	for( int i = 0; i < maxsize; i ++ ) 
	{
		v = temp[i].Dump(); //dumps each list into the vector
		for( int i = 0; i < v.size(); i++ )
			table[Hash(v[i].GetUsername())].InsertBack(v[i]); //Uses hash function to find index and inserts each element of the vector
	}
	delete [] temp;
	return true;
	
}


// default constructor
// creates an array of size 101		--------------------------------		--------------------------------
HashTable::HashTable()
{
	maxsize=101;
	size=0;
	table = new SLinkedList<UserAccount>[maxsize];
}

// parameterized constructor
// creates an array of size = smallest prime number > 2n		--------------------------------		--------------------------------
HashTable::HashTable(int n)
{
	
	maxsize=SmallestPrime(2*n+1);
	
	size=0;
	table = new SLinkedList<UserAccount>[maxsize];
	
}

// copy constructor
// Creates deep copy of sourceht		--------------------------------		--------------------------------
HashTable::HashTable(const HashTable& sourceht)
{
	CopyArray(sourceht);
}

// destructor		--------------------------------		--------------------------------
HashTable::~HashTable()
{	
	DeleteArray();
}

// overloaded assignment operator		--------------------------------		--------------------------------
HashTable& HashTable::operator=(const HashTable& sourceht)
{
	delete [] table;

	size= sourceht.size;
	maxsize= sourceht.maxsize;
	table= new SLinkedList<UserAccount>[maxsize];

	for(int i=0; i<maxsize; i++) 
	{
		table[i]=sourceht.table[i]; //copy older array into new array
	}
	return * this;	
}


// Insertion
// If item does not already exist, inserts at back of hashed list and returns true
//   otherwise returns false
// If load factor (before insertion) is above 2/3, expand into a new
//   table of smallest prime number size at least double the present table size
//   and then insert the item.
bool HashTable::Insert(UserAccount acct)
{
	int index= Hash(acct.GetUsername());	// Calculate hash index
	double two = 2;
	double three = 3;
	double number = 2/3;

	if(Search(acct))	// If item is found in the hash table already, don't add another copy
		return false;

	if(LoadFactor()<= number)	// If load factor is more than 2/3, Resize the hash table
		Resize(2*size);
	table[index].InsertBack(acct);	// Insert item in the back of the chain at the index of the hash table
	size++;
	return true;
}

// Removal
// If item exists, removes and returns true		--------------------------------		--------------------------------
//   otherwise returns false
bool HashTable::Remove(UserAccount acct)
{
	int index= Hash(acct.GetUsername());

	if((table[index].Remove(acct)))	// If item exists, it is removed
	{
		size--;
		return true;
	}

	return false;
}

// Search
// Returns true if item exists, false otherwise 	--------------------------------		--------------------------------
bool HashTable::Search(UserAccount acct) const
{
	int index= Hash(acct.GetUsername());
	return table[index].Contains(acct);
}

// Retrieval
// Returns a pointer to a UserAccount object inside the hash table (linked list)	--------------------------------		--------------------------------
//   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct)
{
	int index= Hash(acct.GetUsername());
	UserAccount * account= table[index].Retrieve(acct);
	return account;
}

// Returns the number of items stored in the hash table	--------------------------------		--------------------------------
int HashTable::Size() const
{
	return size;
}


// Returns the size of the underlying array	--------------------------------		--------------------------------
int HashTable::MaxSize() const
{
	return maxsize;
}


// Returns the load factor as size / maxsize.
// Note that due to separate chaining, load factor can be > 1.	--------------------------------		--------------------------------
double HashTable::LoadFactor() const
{
	if(maxsize==0)
		return 0;
	return ((double)size/(double)maxsize); // Convert size and max size to doubles
}
