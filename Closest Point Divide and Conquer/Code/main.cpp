/* @Author
* Student Name: Harun Çatal
* Student ID : 15013034
* Date: 21.04.2018
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <chrono>


using namespace std;

int total = 0;

class Point {
public:
	int x, y, z;
	Point() {}
	~Point() {}
};

bool compX(const Point & p1, const Point & p2)
{
	return p1.x < p2.x;
}
bool compY(const Point & p1, const Point & p2)
{
	return p1.y < p2.y;
}
bool compZ(const Point & p1, const Point & p2)
{
	return p1.z < p2.z;
}

float euclidean(Point &p1, Point &p2)
{	
	total++;
	return (float)sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}

float min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}

float do_brute_force(vector<Point> &P, int n)
{
	float min = 9999999;		// FLT_MAX gives error on ssh, so i just give enough big number.
	float temp = 0;
	for (int i = 0; i < n; ++i) 
	{
		for (int j = i + 1; j < n; ++j)
		{
			temp = euclidean(P[i], P[j]);
			if (temp < min)
				min = temp;
		}
		return min;
	}
}

float closest_pair_rec(vector<Point> &Px, int n)
{
	// Termination Case
	if (n <= 3)	
	{
		return do_brute_force(Px, n);
	}
	int	m = (int)ceil((float)n / 2);		// middle of the vector

	vector<Point> Qx(m);
	vector<Point> Rx(n - m); 

	// Forming Qx, Rx
	int left_index = 0, right_index = 0;
	for (int i = 0; i < n; i++)
	{
		if (left_index < m)	
			Qx[left_index++] = Px[i];
		else
			Rx[right_index++] = Px[i];
	}
	int Q_n = Qx.size();
	int R_n = Rx.size();

	// Rescursive Calls
	float left_d = closest_pair_rec(Qx, Q_n);
	float right_d = closest_pair_rec(Rx, R_n);

	float d = min(left_d, right_d);

	// Strip Part
	vector<Point> Sy;
	for (int i = 0; i < n; i++)
	{
		if (abs(Px[i].x - Px[m - 1].x) < d)
		{
			Sy.push_back(Px[i]);
		}
	}

	sort(Sy.begin(), Sy.end(), compY);		// Sorting Strip by y

	// Comparison
	float strip_d;
	int num = Sy.size();
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i + j + 1 >= num) {
				break;
			}
			strip_d = euclidean(Sy[i], Sy[i + j + 1]);
			d = min(strip_d, d);
		}
	}
	return d;
}

float closest_pair(vector<Point> &pointVector) {

	// PX, PY, PZ
	vector<Point> pointVecX(pointVector);

	// SORT
	sort(pointVecX.begin(), pointVecX.end(), compX);

	return closest_pair_rec(pointVecX, pointVector.size());
}


int main(int argc, char* argv[]) {

	string arg;
	int N;

	if (argc == 2) {
		arg = argv[1];
	}
	else {
		cout << "Please enter only 1 argument after ./program !" << endl;
	}

	ifstream inFile;
	inFile.open(arg.c_str());

	inFile >> N;

	vector<Point> pointVector;
	for (int i = 0; i < N; i++)
	{
		Point pointObject;
		inFile >> pointObject.x;
		inFile >> pointObject.y;
		inFile >> pointObject.z;
		pointVector.push_back(pointObject);
	}
	inFile.close();			 //closing file

	auto start = std::chrono::high_resolution_clock::now();
	float distance = closest_pair(pointVector);
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> elapsed = finish - start;

	cout << "The distance is " << distance << endl;
	cout << "Number of total distance calculations is " << total << endl;

	cout << "Elapsed Time(s): " << elapsed.count() << endl;

	getchar();
	return 0;
}
