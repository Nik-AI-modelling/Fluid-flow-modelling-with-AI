#pragma once


#include <iostream>
#include <vector>
class TaylorGreenAnalytical;

class AdvectionVelocityCalc {
private:
	//Backtracked location
	float x_bc;

public:
	float x;
	float y;
	float pres;
	float ux_init;
	float vy_init;
	float dt; // time increment 
	char Method; //Method for initial condition calculations: Case="even" even distirbution ; Case ="TG" calculated with 
	//Taylor and Green function @t=0
	float t_end; 
	std::vector<std::vector<float>> u_adv_plus_1_y; //this matrix containes a vector of advected velocity along y
	std::vector<std::vector<float>> u_adv_plus_1_x;// this matrix containes a vector of advected velocity along x

	//Multiple matrixes 

	//Calculate intial condition
	std::vector <float> InitialCondition(float x, float y, const std::string& Method, TaylorGreenAnalytical* Obj);

	//Calculate backtracked location
	//float (*func)(int, int)//This is a funciton which supplies the initial distribution of velocities in 2D
	//Depending on the choise, it could be either Teylor-Green vortex or even (equal to zero) evetywhere
	//argument Method is responsible for that

	AdvectionVelocityCalc (const std::string& Method, TaylorGreenAnalytical* Obj,  float dt, float t_end, float RangeMax, float StepInRange, int NumberRowsVector);
	//GetValueAtSpecificCoordinate
	float getValueUx();
	float getValueVy();
	float getValueP();

	std::vector<std::vector<float>> getVector_u_adv_y();
	std::vector<std::vector<float>> getVector_u_adv_x();
};