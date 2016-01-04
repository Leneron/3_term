#pragma once

//Builts a tree
//The root has m children and each of them has n children
//m - amount of rows, n - amount of columns

#include <initializer_list>
#include "Tree.h"

template <typename T>
class Array
{
public:
	//Inner class for overloading operator [][]
	class Row
	{
	public:
		Row(Array* arrayValue, int iValue){ array = arrayValue; i = iValue; }
		T& operator[](const int& j)
		{
			return array->getElement(i, j);
		}
	private:
		Array* array;
		int i;
	};

	Array(){}
	Array(const initializer_list<initializer_list<T> >& values);
	~Array();

	Row& operator[](const int& i)
	{
		Row* row = new Row(this, i);
		return *row;
	}

	T& getElement(int i, int j);

private:
	Tree<T>* tree;
	T emptyValue;
};

template <typename T>
Array<T>::Array(const initializer_list<initializer_list<T> >& values)
{
	emptyValue = T();
	tree = new Tree<T>();
	int n = values.size();
	if (n > 0)
	{
		int m = values.begin()->size();
		for (int i = 0; i < values.size(); i++)
		{
			if ((values.begin() + i)->size() > m)
				m = (values.begin() + i)->size();
		}

		for (int i = 0; i < n; i++)
		{
			tree->addChildByValue(emptyValue);
			Tree<T>* leave = tree->getChild(i); 
			const initializer_list<T>* rowList = ((values.begin() + i));
			for (int j = 0; j < m; j++)
			{
				if (j >= rowList->size())
					leave->addChildByValue(emptyValue);
				else
				{
					auto iterJ = rowList->begin();
					iterJ = iterJ + j;
					leave->addChildByValue(*iterJ);
				}
					
			}
		}
	}
}

template <typename T>
Array<T>::~Array()
{

}

template <typename T>
T& Array<T>::getElement(int i, int j)
{
	return tree->getChild(i)->getChild(j)->getValue();
}