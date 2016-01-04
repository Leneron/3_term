#pragma once

//Just a tree realization

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Tree
{
public:
	Tree()
	{
		data = 0;
		//children.clear();
	}

	Tree(const T& dataValue)
	{
		data = dataValue;
		//children.clear();
	}

	void setValue(const T& dataValue)
	{
		data = dataValue;
	}

	T& getValue()
	{
		return data;
	}

	void addChildByValue(const T& dataValue)
	{
		Tree* child = new Tree(dataValue);
		addChild(child);
	}

	void addChild(Tree* child)
	{
		children.push_back(child);
	}

	void deleteChild(const int& n)
	{
		if (n < children.size())
		{
			Tree* p = children[n];
			for (int i = 0; i < p->children.size(); i++)
			{
				addChild(p->children[i]);
			}
			children.erase(children.begin() + n);
			delete p;
		}
	}

	Tree* getChild(const int& i)
	{
		return children[i];
	}

private:
	T data;
	vector <Tree*> children;
};
