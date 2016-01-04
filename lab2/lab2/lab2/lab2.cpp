// lab2.cpp : Defines the entry point for the console application.

#define  GLFW_DLL

#include <iostream>
#include <Windows.h>
#include <vector>
#include <GLFW\glfw3.h>

using namespace std;

struct Point
{
	Point() { x = 0; y = 0; }
	Point(double xValue, double yValue) { x = (float)(xValue); y = (float)(yValue); }
	float x;
	float y;
};
typedef std::vector<int>(*AlgorithmFunc) (std::vector<Point>&);
typedef vector<int>(CALLBACK* algorithmType)(vector<Point>);

void paint(vector <Point>& a, vector <int>& indexes);

int main(void)
{
	//Loading the library
	auto lib = LoadLibrary("ConvexHullDll.dll");
	if (lib == nullptr)
	{
		auto a = GetLastError();
		cout << a << endl;
	}

	//The name was generated with the program www.dependencywalker.com
	//There's no way to simplify it, because the dll was written on C++
	AlgorithmFunc algorithm = (AlgorithmFunc) GetProcAddress(lib, "?algorithm@ConvexHull@@YA?AV?$vector@HV?$allocator@H@std@@@std@@AEAV?$vector@UPoint@ConvexHull@@V?$allocator@UPoint@ConvexHull@@@std@@@3@@Z");
	if (algorithm == nullptr) 
	{
		auto a = GetLastError();
		cout << a << endl;
	}

	GLFWwindow* window;

	//Initializing GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Creating the window
	window = glfwCreateWindow(800, 600, "Chan's algorithm", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	//Tracking pressing keys mode on
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	vector <Point> a;
	vector <int> indexes;

	//Drawing
	do
	{
		// glfwSetInputMode(window, GLFW_PRESS, GL_TRUE);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{

			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
			double x;
			double y;
			glfwGetCursorPos(window, &x, &y);
			int width;
			int height;
			glfwGetWindowSize(window, &width, &height);
			x = (x / width - 0.5) * 2;
			y = (0.5 - y / height) * 2;
			//Debugging the position of points
			cout << x << " " << y << endl;

			Point point = Point(x, y);
			a.push_back(point);
			Sleep(200);
			indexes = algorithm(a);
		}
		paint(a, indexes);
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (!glfwWindowShouldClose(window)));

	//Exit app
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

//Paint the convex hull by the order of points
void paint(vector <Point>& a, vector <int>& indexes)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(4.0f);
	glBegin(GL_LINES);
	if ((indexes.size() > 0) && (a.size() >= 3))
	{
		for (size_t i = 0; i < indexes.size() - 1; i++)
		{
			if (indexes[i] < a.size() && (indexes[i + 1] < a.size()))
			{
				glVertex2f(a[indexes[i]].x, a[indexes[i]].y);
				glVertex2f(a[indexes[i + 1]].x, a[indexes[i + 1]].y);
			}
		}
		glVertex2f(a[indexes[indexes.size() - 1]].x, a[indexes[indexes.size() - 1]].y);
		glVertex2f(a[indexes[0]].x, a[indexes[0]].y);
	}
	glEnd();

	glBegin(GL_POINTS);
	for (size_t i = 0; i < a.size(); i++)
	{
		glPointSize(4.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(a[i].x, a[i].y);
	}
	glEnd();
}