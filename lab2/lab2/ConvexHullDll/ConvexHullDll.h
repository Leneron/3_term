#pragma once
#include <vector>

#ifdef CONVEXHULLDLL_EXPORTS
#define CONVEXHULLDLL_API __declspec(dllexport) 
#else
#define CONVEXHULLDLL_API __declspec(dllimport) 
#endif

namespace ConvexHull
{	

	using namespace std;

		struct Point
		{
			Point() { x = 0; y = 0; }
			Point(double xValue, double yValue) { x = (float)(xValue); y = (float)(yValue); }
			float x;
			float y;
		};

		CONVEXHULLDLL_API vector<int> grahamScan(vector<Point>& a);
		CONVEXHULLDLL_API vector<int> giftWrappingAlgorithm(vector<Point>& a);
		CONVEXHULLDLL_API vector<int> hull(vector<Point>& a, int m);
		CONVEXHULLDLL_API vector<int> algorithm(vector<Point>& a);

		CONVEXHULLDLL_API bool isRight(Point c, Point a, Point b);
		CONVEXHULLDLL_API void rebuild(int last, vector<Point>& a, vector<int>& p);
}

