#pragma once

#include <iostream>
//Create class for the analytical solution of Taylor and Green equation 
class AdvectionVelocityCalc;
class TaylorGreenAnalytical
{
private:                                                                                                       
	float ux;// 2D array of velocities in the x direction. Calculated analytically. Pointer to pointer-2D array
	float vy;//2D array of velocities in the x direction. Calculated analytically.Pointer to pointer-2D array
	float p;//2D array of pressure.Calculated analytically. Pointer to pointer-2D array
	float x;
	float y;
	float T;

	void recalculate();
public:


	//Constructor
	TaylorGreenAnalytical();

	//This is because 
	friend class AdvectionVelocityCalc;
	//Destructor
	//~TaylorGreenAnalytical(float x, float y, float T);

	//Constructor of ux, vy and p
	//Dynamic2Dux_TaylorGreenAna(float x, float y, float T);
	//Dynamic2Dvy_TaylorGreenAna(float x, float y, float T);
	//Dynamic2Dp_TaylorGreenAna(float x, float y, float T);

	//Destructor for ux
	//~Dynamic2Dux_TaylorGreenAna();
	//~Dynamic2Dvy_TaylorGreenAna();
	//~Dynamic2Dp_TaylorGreenAna();
	// 
	//Set value of x
	void setValue_x(float x);
	//Set value of y
	void setValue_y(float y);
	//Set value of T
	void setValue_T(float T);

	//GetValueAtSpecificCoordinate
	float getValueUx_TaylorGreenAna() ;
	float getValueVy_TaylorGreenAna() ;
	float getValueP_TaylorGreenAna() ;

	//destructot

};