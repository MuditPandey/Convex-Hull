#ifndef COMP_GEO_H
#define COMP_GEO_H
#include<bits/stdc++.h>
#include "point.h"
using namespace std;
class comp_geo
{
	public:
	static int Check_left(Point,Point,Point);
	static double Get_angle(Point);
	static double Get_angle(Point,Point,Point);
	static int Compare(const void*,const void*);
	static int Comapare_andrew(const void *,const void*);
	static int complen(Point *,Point *);
	static void Middle_out_graham(list <Point> *);
	static void Middle_out_andrew(list <Point> *);
	static void Graham_scan();
	static void Jarvis_march();
	static void Andrew_hull();
	static void Matlab_Script(Point[],int,list <Point>,char*);
	static void Input_Points(int,Point *);
	
};

#endif
