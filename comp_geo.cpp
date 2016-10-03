#include<bits/stdc++.h>
#include "comp_geo.h"
#include "point.h"
# define pl fprintf(fp,"\n")
using namespace std;
Point origin;

/**************************************************************************************************
  FUNCTION TO SET VALUE OF A POINT OBJECT TAKING ANOTHER POINT OBJECT AS PARAMETER
**************************************************************************************************/
/*void Point::Set_value(Point p)
{
 x=p.x;                                    //COPIES VALUES OF X AND Y OF A POINT TO ANOTHER
 y=p.y;	
}*/
/*************************************************************************************************
 FUNCTION TO SET BALUE OF A POINT OBJECT BY TAKING X AND Y COORDS AS PARAMETERS
***************************************************************************************************/
/*void Point::Set_value(double nx,double ny)
{
 x=nx;
 y=ny;	
}*/
/****************************************************************************************************
 FUNCTION TO CHECK THE DIRECTION OF ROTAITION OF THREE POINTS
*****************************************************************************************************/
int comp_geo::Check_left(Point a,Point b,Point c)
{
 double val;
 val=(b.y-a.y)*(c.x-b.x)-(c.y-b.y)*(b.x-a.x);
 if (val==0)
 return 0;                    // RETURNS 0 WHEN POINTS ARE COLLINEAR
 return val<0?1:2;           // RETURNS 1 WHEN A LEFT TURN IS  MADE AND 2 IF A RIGHT TURN IS MADE
}

/***************************************************************************************************
 FUNCTION TO CALCULATE THE COSINE OF ANGLE MADE BY A POINT AND THE ORIGIN 
*****************************************************************************************************/
double comp_geo::Get_angle(Point p1)
{
 double l=p1.x-origin.x;
 double a=p1.y-origin.y;                       
 double k=sqrt((l*l) +(a*a));
 if((origin.y-p1.y)<=0)
 return l/k;                 //RETURNS COS X WHERE X IS ANGLE BETWEEN POINT AND ORIGIN
 return -2-l/k;
}
/****************************************************************************************************
 FUNCTION TO CALCULATE THE ANGLE BETWEEN TWO VECTOS P2P1 AND P3P2
****************************************************************************************************/
double comp_geo::Get_angle(Point p1,Point p2,Point p3)
{
 double f,a,t;
 f=(p2.x-p1.x)*(p3.x-p2.x)+(p2.y-p1.y)*(p3.y-p2.y);      //CALCULATES DOT PRODUCT OF VECTORS
 t=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));//CALCULATES THE
 a=sqrt((p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y));//LENGTH OF EACH VECTOR
 t=f/(t*a);                                             //RETURNS THE COSINE OF ANGLE B/W THE VECTORS
 return t; 
}
/****************************************************************************************************
 FUNCTIONS USED BY QSORT(STL) TO SORT POINTS W.R.T THE ANGLE MADE WITH ORIGIN
****************************************************************************************************/

int comp_geo::Compare(const void* p1,const void* p2)
{
 Point *f1=(Point *)p1, *f2=(Point *)p2;
 if(f1->angch ==f2->angch)
 {                      
   return complen(f1,f2);
 }
 else if(f1->angch<f2->angch)
 {
    return 1;
 }
 else
 return -1;
}
/****************************************************************************************************
 FUNCTION USED BY QSORT(STL) TO SORT POINTS LEXICOGRAPHICALLY--USED FOR ANDREW'S HULL ALGO
****************************************************************************************************/
int comp_geo::Comapare_andrew(const void  *x,const void *y)
{
    Point *p1=(Point *)x;
    Point *p2=(Point *)y;
    if(p1->x < p2->x)   
	return -1;
    else if(p1->x > p2->x)  
	return 1;
    else
	{
        if(p1->y < p2->y)   
		return -1;
        else return 1;
    }
}
/****************************************************************************************************
 FUNCTION TO COMPARE DISTANCE OF W.R.T ORIGIN IN CASE OF SAME ANGLE--USED FOR GRAHAM SCAN 
****************************************************************************************************/
int comp_geo::complen(Point *f1,Point * f2)
{
    double l1,l2;
    l1=(origin.x-f1->x)*(origin.x-f1->x)+(origin.y-f1->y)*(origin.y-f1->y);
    l2=(origin.x-f2->x)*(origin.x-f2->x)+(origin.y-f2->y)*(origin.y-f2->y);
    if(l1>l2)   
	return -1;     //RETURNS -1 IF POINT F1 IS FARTHER FROM ORGIGIN
    else 
	return 1;      //RETURNS 1 IF POINT F1 IS CLOSER TO THE ORIGIN      
}
/****************************************************************************************************
 FUNCTION TO REMOVE MIDDLE POINT FROM RESULT IN CASE OF ILLEGAL ROTATION
****************************************************************************************************/

//FOR GRAHAM SCAN ALGORITHM

void comp_geo::Middle_out_graham(list <Point> *st)
 {
  while(st->size()>2)
  {
 	 Point temp[3];
	 for(int i=0;i<3;i++)
	 {
      temp[i]=st->front();
      st->pop_front();
	 }
	 if(Check_left(temp[2],temp[1],temp[0])==1) //VALID IF POINTS FORM A LEFT TURN
	 {
	  st->push_front(temp[2]);                 
	  st->push_front(temp[1]);
	  st->push_front(temp[0]);
	  break;
	 }
	 else
	 {              
	  st->push_front(temp[2]);                  //DELETING MIDDLE ELEMENT FROM LIST
	  st->push_front(temp[0]);	
     }
   }
 }
 
 //FOR ANDREW HULL ALGORITHM
 
 void comp_geo::Middle_out_andrew(list <Point> *l)
 {
    while(l->size()>2)
	{
        Point p[3];
        for(int i=0;i<3;i++)
        {
            p[i]=l->back();
            l->pop_back();
        }
       if(Check_left(p[2],p[1],p[0])==2)     //VALID IF POINTS FORM A RIGHT TURN
	   {
            l->push_back(p[2]);
            l->push_back(p[1]);
            l->push_back(p[0]);
            break;
       }
        else
		{
         l->push_back(p[2]);                  //DELETING MIDDLE ELEMENT FROM LIST
         l->push_back(p[0]);
        }
    }
}
/***************************************************************************************************
 MAIN DRIVER FUNCTION FOR GRAHAM SCAN ALGORITHM
****************************************************************************************************/ 

void comp_geo::Graham_scan()
{
 int n;
 scanf("%d",&n);
 Point p[n];
 Input_Points(n,p);             //INPUTING ALL POINTS WHOSE CONVEX HULL IS TO BE FOUND
 origin.x=p[0].x;
 origin.y=p[0].y;
 for(int i=1;i<n;i++)          //FINDS THE ORIGIN FROM ALL THE POINTS
 {
  	if(p[i].y<origin.y)
  	{
   		origin.x=p[i].x;
   		origin.y=p[i].y;
  	}
  	if(p[i].y==origin.y && p[i].x<origin.x)
  	{
   		origin.x=p[i].x;
  	}
 }
 Point nw[n-1];
 int c=0;
 for(int i=0;i<n;i++)         //STORES ALL POINTS EXCEPT THE ORIGIN
 {
 	if(p[i].x!=origin.x || p[i].y!=origin.y)
	{	
	 nw[c].x=p[i].x;
	 nw[c].y=p[i].y;
	 c++;
	}
 }
 
 for(int i=0;i<c;i++)        //CALCULATES ANGLE THAT EACH POINTS MAKE WITH THE ORIGIN
 {
  	nw[i].angch=Get_angle(nw[i]);
 }
 qsort(nw,c,sizeof(Point),Compare); //SORTING THE POINTS IN ASCENDING ORDER OF ANGLE WITH ORIGIN
 list <Point> s;
 s.push_front(origin);
 int i=1;
 Point x,y;
 for(int i=0;i<c;i++)              //IMPLEMENTING THE MIDDLE-ELEMENT DELETING ALGORITHM IN CASE OF 
 {                                 //ILLEGAL ROTATION
  	s.push_front(nw[i]);	
  	Middle_out_graham(&s);	
 }
 s.push_front(origin);
 Middle_out_graham(&s);            //FINAL LIST CONTAINING POINTS ON CONVEX HULL
 Matlab_Script(p,n,s,"GS_OUPUT.m"); //GENERATES MATLAB SCRIPT NAMED GS_OUTPUT THAT CONTAINS POINTS ON CONVEX HULL
 
}	

/***************************************************************************************************
 MAIN DRIVER FUNCTION FOR JARVIS MARCH ALGORITHM
***************************************************************************************************/
void comp_geo::Jarvis_march()
{
 list<Point> l;
 int n;
 scanf("%d",&n);      
 int done[n];
 Point p[n];
 memset(done,0,sizeof(done));
 Input_Points(n,p);         //INPUTING ALL POINTS WHOSE CONVEX HULL IS TO BE FOUND.
 Point org;
 org.Set_value(p[0]);
 double temp1,temp2;
 for(int i=0;i<n;i++)
 {
 	if(p[i].x<org.x) 
		org.x=p[i].x;
	if(p[i].y<org.y) 
		org.y=p[i].y;
 }
 org.x--;                 //FINDING AN ORIGIN WHICH IS BELOW THE BOTTOM-MOST AND TO THE LEFT OF 
 org.y--;                 //THE LEFTMOST POINT.
 Point norg;              //INITIALING A POINT TO CALCUALATE VECTOR WITH FIRST ORIGIN.
 norg.Set_value(org.x-1,org.y);
 double f1,f2;
 int count=0;
 while(1)
 {
 	count++;
 	f1=-3;
    int i1=-1;
    for(int i=0;i<n;i++)
    {
    	if(done[i]==1 &&!(p[i].x==l.front().x && p[i].y==l.front().y)) 
        continue;
        f2=Get_angle(norg,org,p[i]);
        if(f1<f2)
        {
        	f1=f2;
            i1=i;
            temp1=p[i].x;
            temp2=p[i].y;
        }
    }
    norg.Set_value(org);
    org.Set_value(temp1,temp2);
    Point p1,p;
    p1.x=l.front().x;
    p1.y=l.front().y;
    p.Set_value(org);
    done[i1]=1;
    l.push_back(p);
    if(p1.x==org.x && p1.y==org.y) 
    	 break;
    }
    Matlab_Script(p,n,l,"JM_OUTPUT.m");//GENERATES A MATLAB SCRIPT WITH POINTS ON HULL NAMED JM_OUTPUT

}
/****************************************************************************************************
  MAIN DRIVER FUNCTION FOR ANDREW HULL ALGORITHM
****************************************************************************************************/
 void comp_geo::Andrew_hull()
 {
    list<Point> lup,llw;
	Point temp;
    int n;
    scanf("%d",&n);
    Point p[n];
    Input_Points(n,p);               //INPUTING ALL POINTS WHOSE CONVEX HULL IS TO BE FOUND
    qsort(p,n,sizeof(Point),Comapare_andrew);
	lup.push_back(p[0]);             //PUSHING FIRST TWO ELEMENTS
    lup.push_back(p[1]);             //INTO THE UPPER HULL.
    llw.push_back(p[n-1]);           //PUSHING LAST TWO ELEMENTS 
    llw.push_back(p[n-2]);           //INTO THE LOWER HULL.
    for(int i=2;i<n;i++)
	{
    	lup.push_back(p[i]);        //FINDING OUT THE LOWER CONVEX HULL
    	Middle_out_andrew(&lup);
    }
    for(int i=n-3;i>=0;i--)
	{
        llw.push_back(p[i]);
        Middle_out_andrew(&llw);    //FINDING OUT THE UPPER CONVEX HULL
    }
    list<Point> ans;
    while(!lup.empty())             //CONCATENATING THE  
	{
        temp=lup.front();           //TWO LISTS TO GET
        lup.pop_front();
        ans.push_back(temp);        //LIST OF POINTS IN CONVEX HULL
    }
    llw.pop_front();
    while(!llw.empty())
    { 
      temp=llw.front();
      llw.pop_front();
      ans.push_back(temp);
    }
    Matlab_Script(p,n,ans,"ACH_OUTPUT.m"); //GENERATES MATLAB SCRIPT WITH POINTS ON HULL NAMED ACH_OUPUT
}

/************************************************************************************************
 MATLAB SCRIPT FUNCTION--CREATES A MATLAB SCRIPT WHICH PLOTS THE CONVEX HULL
************************************************************************************************/
void comp_geo::Matlab_Script(Point p[],int n,list <Point> s,char* str)
{
 list<Point> t;
 FILE *fp =fopen(str,"w");
 if(fp==NULL)
 {
 	printf("Error while creating Script\n");
 	return ;
 }
 char stringx[]="x = [ ";
 char stringy[]="y = [ ";
 fprintf(fp,"%s",stringx);
 for(int i=0;i<n;i++)    
 	fprintf(fp,"%lf ",p[i].x);
 fprintf(fp,"];");
 pl;
 fprintf(fp,"%s",stringy);
 for(int i=0;i<n;i++)    
 	fprintf(fp,"%lf ",p[i].y);
 fprintf(fp,"];");
 pl;
 fprintf(fp,"X = [ ");
 while(!s.empty())
 {
	fprintf(fp,"%lf ",s.front().x);   // X COORDINATES OF CONVEX HULL
 	t.push_back(s.front());
 	s.pop_front();
 }
 fprintf(fp,"];");
 pl; 
 fprintf(fp,"Y = [ ");
 while(!t.empty())
 {
 	fprintf(fp,"%lf ",t.front().y);  //CORRESPONDING Y COORDINATES OF CONVEX HULL
 	t.pop_front();
 }
 fprintf(fp,"];");
 pl;
 fprintf(fp,"plot(x,y,'b*',X,Y,'b');");
}
/****************************************************************************************************
 FUNCTION TO INPUT ALL POINTS WHOSE CONVEX HULL IS TO BE FOUND
****************************************************************************************************/
void comp_geo::Input_Points(int n,Point *p)
{
	for(int i=0;i<n;i++)
	{
		scanf("%lf%lf",&p[i].x,&p[i].y);
	}
}

//*************************************************************************************************
//******************************* END OF FILE *****************************************************
//*************************************************************************************************
