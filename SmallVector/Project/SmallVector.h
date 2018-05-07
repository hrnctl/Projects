/*
Object Oriented Programming
Homework-1
Harun Çatal
150130034
*/

#ifndef SMALLVECTOR_H
#define SMALLVECTOR_H
class SmallVector
{
private:
	int s_array[32];//statik buffer
	int *d_array;//dinamic buffer
	int a_size;//array size
public:
	SmallVector();
	SmallVector(int[], int);
	SmallVector(const SmallVector&);
	void printSmallVector(const char* const message,  SmallVector& vector);
	int& operator[](int);
	int& pop_back();
	void push_back(int);
	void push_back(int[],int);
	SmallVector& reverse();
	SmallVector& operator=(SmallVector&);
	SmallVector& operator*(int);
	SmallVector& operator+(SmallVector&);
	int& getSize();
	~SmallVector();
};
#endif
