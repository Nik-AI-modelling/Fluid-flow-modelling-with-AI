#include "AdvectionVelocityCalc.h"
#include "TaylorGreenAnalytical.h"
#include <iostream>
#include <vector>
#include <cmath>


//Calculate intial condition e.g. initial distribution of velocities. It can be either a constant value everywhere or
//or distribution calculated with Taylor And Green 
//In the even case, it is assumed that velocity and pressure are equal to zero.
std::vector <float> AdvectionVelocityCalc::InitialCondition(float x, float y, const std::string& Method, TaylorGreenAnalytical* Obj) {
	std::vector<float> InitialVel;
	if (Method == "even") {
		InitialVel.push_back(0.0); //ux
		InitialVel.push_back(0.0); //vy
		InitialVel.push_back(0.0); //pressure
	}
	else if (Method == "TaG") {
		Obj->setValue_y(y);
		Obj->setValue_x(x);
		Obj->setValue_T(0.0);

		InitialVel.push_back(Obj->getValueUx_TaylorGreenAna());
		InitialVel.push_back(Obj->getValueVy_TaylorGreenAna());
		InitialVel.push_back(Obj->getValueP_TaylorGreenAna());
	}

	else {
		//This is returned when a wrong method is specified by the user
		throw std::invalid_argument ("Wrong Initial condition Method is specified!");
	}

	return InitialVel;
}

//This calculates intial velocity @ user provided x, y using the InitialCondition function.
//Then it calculates the evolution velocity. 
AdvectionVelocityCalc::AdvectionVelocityCalc(const std::string& Method, TaylorGreenAnalytical* Obj, float dt, float t_end, float RangeMax, float StepInRange, int NumberRowsVector) {
	//this->x = Obj->x;
	//this->y = Obj->y;
	//ScaleVectors
	this->u_adv_plus_1_y.resize(NumberRowsVector);
	this->u_adv_plus_1_x.resize(NumberRowsVector);

	//To count the number of rows
	int count = 0;
	this->dt = dt;
	this->t_end = t_end;
	//0.3 is used in the loop becuase later on we substarct from the coordinate i a product of dt and ux_unit
	for (float t = 0.0;t <= t_end;t += dt) {
		for (int i = 0.3;i < RangeMax; i += StepInRange) {
			for (int j = 0.3;j < RangeMax; j += StepInRange) {

				std::vector <float> InitCondVect = InitialCondition(i, j, Method, Obj);


				//This takes the X component of the velocity vector along the X coordinate 
				float ux_init = InitCondVect[1];

				//This calculates the advected velocity based on the X component of the velocity vector
				float ux_adv = ux_init * (i - dt * ux_init);//this is wrong 

				this->u_adv_plus_1_x[count].push_back(ux_adv);


				//This takes the Y component of the velocity vector along the Y coordinate 
				float vy_init = InitCondVect[0];

				//This calculates the advected velocity based on the X component of the velocity vector
				float vy_adv = vy_init * (j - dt * vy_init);

				this->u_adv_plus_1_y[count].push_back(vy_adv);

				//pres = InitCondVect[2];
			}
			//Count is the row counter
			count = count + 1;
		}
		//Print obtained vectors 
	}
}
	 float  AdvectionVelocityCalc::getValueUx() {
		 return ux_init;
	 }


	 float  AdvectionVelocityCalc::getValueVy() {
		 return vy_init;
	 }

	 float  AdvectionVelocityCalc::getValueP() {
		 return pres;
	 }

	 std::vector<std::vector<float>> AdvectionVelocityCalc::getVector_u_adv_y() {
		 return u_adv_plus_1_y;
	 }

	 std::vector<std::vector<float>> AdvectionVelocityCalc::getVector_u_adv_x() {
		 return u_adv_plus_1_x;
	 }