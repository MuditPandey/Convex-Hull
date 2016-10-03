#include "point.h"
/**************************************************************************************************
  FUNCTION TO SET VALUE OF A POINT OBJECT TAKING ANOTHER POINT OBJECT AS PARAMETER
**************************************************************************************************/
void Point::Set_value(Point p)
{
 x=p.x;                                    //COPIES VALUES OF X AND Y OF A POINT TO ANOTHER
 y=p.y;	
}
/*************************************************************************************************
 FUNCTION TO SET BALUE OF A POINT OBJECT BY TAKING X AND Y COORDS AS PARAMETERS
***************************************************************************************************/
void Point::Set_value(double nx,double ny)
{
 x=nx;
 y=ny;	
}
