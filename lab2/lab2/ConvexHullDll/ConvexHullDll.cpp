// ConvexHullDll.cpp : Defines the exported functions for the DLL application.

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "ConvexHullDll.h"

using namespace std;

namespace ConvexHull
{
	static const float EPS = 0.1e-8;

	//Return true if the point C is on the right side from the line segment AB
	bool isRight(Point c, Point a, Point b)
	{
		float result = (float)((b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x));
		if (result < 0) return true;
		return false;
	}

	void rebuild(int last, vector<Point>& a, vector<int>& p)
	{
		for (int i = 1; i < (last / 2); i++)
		{
			if (isRight(a[p[1]], a[p[i]], a[p[2 * i]]))
			{
				swap(p[i], p[2 * i]);
			}
			if (isRight(a[p[1]], a[p[i]], a[p[2 * i + 1]]))
			{
				swap(p[i], p[2 * i + 1]);
			}
		}
	}

	vector<int> grahamScan(vector<Point>& a)
	{
		vector<int> s;
		if (a.size() >= 3)
		{
			//Init p
			vector<int> p;
			p.resize(a.size(), 0);
			for (int i = 0; i < p.size(); i++)
			{
				p[i] = i;
			}

			//Find first point in MBO (e.g. the leftmost lowest point of the array) and put it in p[0]
			int minIndex = 0;
			for (size_t i = 1; i < p.size(); i++)
			{
				if ((a[p[i]].x < a[p[minIndex]].x) ||
					((abs(a[p[i]].x - a[p[minIndex]].x) < EPS) && (a[p[i]].y <= a[p[minIndex]].y)))
				{
					minIndex = i;
				}
			}
			swap(p[minIndex], p[0]);

			//Sorting by the "left side" relatively the first point
			for (size_t i = 2; i < p.size(); i++)
			{
				int j = i;
				while ((j > 1) && isRight(a[p[0]], a[p[j - 1]], a[p[j]]))
				{
					swap(p[j], p[j - 1]);
					j--;
				}
			}


			//Creating the minimal convex hull
			s.push_back(p[0]);
			s.push_back(p[1]);

			//Now s is a stack
			for (int i = 2; i < p.size(); i++)
			{
				//Check the last 2 elements of the stack
				while ((s.size() > 1) && (isRight(a[s[s.size() - 2]], a[s[s.size() - 1]], a[p[i]])))
				{
					s.pop_back();
				}
				s.push_back(p[i]);
			}
		}
		return s;
	}

	vector<int> giftWrappingAlgorithm(vector<Point>& a)
	{
		vector <int> s;
		if (a.size() >= 3)
		{
			//Init p
			vector <int> p;
			p.resize(a.size(), 0);
			for (int i = 0; i < p.size(); i++)
			{
				p[i] = i;
			}

			//Find first point in MBO (e.g. the leftmost lowest point of the array) and put it in p[0]
			int minIndex = 0;
			for (size_t i = 1; i < p.size(); i++)
			{
				if ((a[p[i]].x < a[p[minIndex]].x) ||
					((abs(a[p[i]].x - a[p[minIndex]].x) < EPS) && (a[p[i]].y <= a[p[minIndex]].y)))
				{
					minIndex = i;
				}
			}
			swap(p[minIndex], p[0]);

			//Creating the minimal convex hull
			//Add p[0] to the end of the array p
			s.push_back(p[0]);
			p.erase(p.begin());
			p.push_back(s[0]);

			bool flag = true;
			while (flag)
			{
				int right = 0;
				for (size_t i = 1; i < p.size(); i++)
				{
					if (isRight(a[s[s.size() - 1]], a[p[right]], a[p[i]]))
					{
						right = (int)i;
					}
				}

				if (p[right] == s[0])
				{
					flag = false;
				}
				else
				{
					s.push_back(p[right]);
					p.erase(p.begin() + right);
				}
			}
		}
		return s;
	}

	vector<int> hull(vector<Point>& a, int m)
	{
		vector<int> smallerHulls;
		for (int i = 0; i < (a.size() / m); i++)
		{
			vector<Point> group;
			for (int j = 0; j < m; j++)
			{
				group.push_back(a[i * m + j]);
			}
			vector<int> indexesSmallerHulls = grahamScan(group);
			smallerHulls.insert(smallerHulls.end(), indexesSmallerHulls.begin(), indexesSmallerHulls.end());
		}

		vector<Point> newA;
		for (int i = 0; i < smallerHulls.size(); i++)
		{
			newA.push_back(a[smallerHulls[i]]);
		}

		vector<int> commonHull;
		commonHull = giftWrappingAlgorithm(a);

		vector<int> empty;
		if (commonHull.size() > m) return empty;

		return commonHull;
	}

	vector<int> algorithm(vector<Point>& a)
	{
		//the alorithm is not effective for small number of points
		vector<int> indexes;
		for (int t = 1; t < a.size(); t++)
		{
			int m;
			if (t > 3)
				m = a.size();
			else
				m = std::min(pow(2, pow(2, t)), (double)a.size());
			indexes = hull(a, m);
			if (indexes.size() != 0)
			{
				return indexes;
			}
		}
		return indexes;
	}
}
