#include "TaylorGreenAnalytical.h"
#include <iostream>
#include <cmath>

TaylorGreenAnalytical::TaylorGreenAnalytical()
{
	float ux = 0.0;// 2D array of velocities in the x direction. Calculated analytically. Pointer to pointer-2D array
	float vy = 0.0;//2D array of velocities in the x direction. Calculated analytically.Pointer to pointer-2D array
	float p = 0.0;//2D array of pressure.Calculated analytically. Pointer to pointer-2D array
	float x = 0.0;
	float y = 0.0;
	float T = 0.0;
}
void TaylorGreenAnalytical::recalculate() {
	this->vy = -exp(-2.0 * this->T) * cos(this->x) * sin(this->y);
	this->ux = exp(-2.0 * this->T) * sin(this->x) * cos(this->y);
	this->p = -0.25 * exp(-4 * this->T) * (cos(2.0 * this->x) + sin(2 * this->y));
}

void TaylorGreenAnalytical::setValue_x(float x) 
{
	this->x = x;//this->x-references x as the field
	recalculate();
}
	////this->x = x;//this->x-references x as the field
//}

void TaylorGreenAnalytical::setValue_y(float y) {
	this->y = y;
	recalculate();
}

void TaylorGreenAnalytical::setValue_T(float T) {
	this->T = T;
	recalculate();
}

//GetValueAtSpecificCoordinate
float TaylorGreenAnalytical:: getValueUx_TaylorGreenAna() 
{
	return ux;
}
float TaylorGreenAnalytical::getValueVy_TaylorGreenAna() 
{
	return vy;
}
float TaylorGreenAnalytical::getValueP_TaylorGreenAna() 
{
	return p;
}  