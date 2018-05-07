/*
Object Oriented Programming
Homework-1
Harun Çatal
150130034
*/
/*
DIKKAT:
Pdf te verilen print fonksiyonu ile uyumlu çalýþabilmesi için lütfen 
void printSmallVector(const char* const message, const SmallVector& in_vector)
ibaresindeki const u silerek
void printSmallVector(const char* const message,SmallVector& in_vector)
þeklinde çalýþtýrýnýz.Bu durumda sorun vermeyecektir.
*/
#include<iostream>
#include<stdio.h>
#include"SmallVector.h"
using namespace std;

SmallVector::SmallVector()//default constructor
{
	a_size = 0;

};
SmallVector::SmallVector(int arr[], int size)//normal constructor
{
	a_size = size;
	if (a_size <= 32)
	{
		for (int i = 0; i<size; i++)
			s_array[i] = arr[i];
	}
	else if (a_size>32)
	{
		d_array = new int[a_size - 32];
		for (int i = 0; i<32; i++)
			s_array[i] = arr[i];

		for (int j = 0; j<size - 32; j++)
		{
			d_array[j] = arr[32 + j];
		}
	}
};
SmallVector::SmallVector(const SmallVector& element)//copy constructor
{
	a_size = element.a_size;
	if (a_size <= 32)//if we only use static buffer
	{
		for (int i = 0; i<a_size; i++)
			s_array[i] = element.s_array[i];
	}
	else//we need to use dinamic buffer
	{
		for (int i = 0; i<32; i++)
			s_array[i] = element.s_array[i];
		d_array = new int[a_size - 32];
		for (int j = 0; j<a_size - 32; j++)
			d_array[j] = element.d_array[j];
	}
};
int& SmallVector::operator[](int i)//operator [] definition
{

	if (i >= 0)
	{
		if (i<32)
			return s_array[i];
		else
			return d_array[i - 32];
	}
	else if (i<0)
	{
		if (a_size <= 32)
			return s_array[a_size + i];
		else
		{
			int d_size = a_size - 32;
			if ((-1 * i)>d_size)
			{
				return s_array[a_size + i];
			}
			else
				return d_array[d_size + i];
		}
	}

};



SmallVector& SmallVector::reverse()//create a SmartVector,assigned reverse of rector and return it
{
	SmallVector *reversed = new SmallVector();
	reversed->a_size = a_size;
	if (a_size>32)
		reversed->d_array = new int[a_size - 32];
	int d_size = a_size - 32;

	for (int i = 0; i < a_size; i++)
	{
		reversed->operator[](i) = this->operator[](-1 - i);
	}
	return *reversed;
};
SmallVector& SmallVector::operator+(SmallVector& newvector) //+operator
{
	SmallVector *sum = new SmallVector;
	sum->a_size = this->a_size + newvector.a_size;
	if (sum->a_size> 32)//if we use dinamic array
	{
		sum->d_array = new int[sum->a_size - 32];
	}
	for (int i = 0; i < this->a_size; i++)//add element after first parameter
	{
		sum->operator[](i) = this->operator[](i);
	}
	for (int j = 0; j < newvector.a_size; j++)
	{
		sum->operator[](j + a_size) = newvector.operator[](j);
	}
	return *sum;
};
SmallVector& SmallVector::operator=(SmallVector& source) //= operator
{
	if (a_size != source.a_size)//size must be equal or fixed
	{
		a_size = source.a_size;
		d_array = NULL;
	}

	if (a_size < 32)//data transfer
	{
		for (int i = 0; i < a_size; i++)
		{
			s_array[i] = source.s_array[i];
		}
	}
	else
	{
		for (int i = 0; i<32; i++)
			s_array[i] = source.s_array[i];
		d_array = new int[a_size - 32];
		for (int j = 0; j<a_size - 32; j++)
			d_array[j] = source.d_array[j];
	}
	return *this;
};
SmallVector& SmallVector::operator*(int number) // * operator
{
	if (a_size*number <= 32)//if we use only static buffer
	{

		int m = 0;
		int n = 0;
		for (int i = 0; i < number*a_size; i++)
		{
			this->operator[](m) = this->operator[](n);
			m++;
			n++;
			if (n == a_size)
				n = 0;
		}

		a_size = a_size*number;

	}
	else//if we need dynamic buffer
	{
		int *temp = new int[a_size];
		for (int i = 0; i < a_size; i++)
		{
			temp[i] = this->operator[](i);
		}
		d_array = new int[a_size*number - 32];//memory operation
		int m = 0;
		int n = 0;
		for (int i = 0; i < number*a_size; i++)
		{
			this->operator[](m) = temp[n];
			m++;
			n++;
			if (n == a_size)
				n = 0;
		}
		a_size = a_size*number;
		delete[] temp;
	}
	return *this;
};
int& SmallVector::pop_back()//pop last element
{
	int *temp;
	temp = new int[0];
	temp[0] = this->operator[](a_size);
	a_size--;
	return *temp;

};
void SmallVector::push_back(int newnumber)//push back from vector
{
	if (a_size < 32)//if use only static buffer
	{
		this->operator[](a_size) = newnumber;//next element is newnumber
	}
	else if (a_size >= 32)//if we need dynamic buffer assign right place new number via [] operator
	{
		SmallVector temp;
		temp.d_array = new int[a_size];
		for (int i = 0; i < a_size; i++)
		{
			temp.operator[](i) = this->operator[](i);
		}
		d_array = new int[a_size + 1 - 32];
		for (int i = 0; i < a_size; i++)
		{
			this->operator[](i) = temp.operator[](i);
		}
		this->operator[](a_size) = newnumber;

	}
	a_size++;
}
void SmallVector::push_back(int arr[], int size)//push array to back of the vector
{
	if (a_size + size < 32)//if total number dont use dynamic buffer
	{
		for (int i = 0; i < size; i++)
		{
			this->operator[](a_size + i) = arr[i];
		}
	}
	else
	{
		SmallVector temp;
		temp.d_array = new int[a_size];
		for (int i = 0; i < a_size; i++)
		{
			temp.operator[](i) = this->operator[](i);
		}
		d_array = new int[a_size + size - 32];
		for (int i = 0; i < a_size; i++)
		{
			this->operator[](i) = temp.operator[](i);
		}
		for (int i = 0; i < size; i++)
		{
			this->operator[](a_size + i) = arr[i];
		}

	}
	a_size += size;
}
int& SmallVector::getSize()
{
	return a_size;
}
SmallVector::~SmallVector()
{
	if(a_size>32)//when smaller than 32 we just use static array
	delete[] d_array;
}
