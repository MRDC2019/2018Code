#include "PID.h"

PID::PID(PIDType _pidType, double _kp, double _ki, double _kd) :
pidType(_pidType),
kp(_kp), ki(_ki), kd(_kd),
target(0.0),
iLimit(DBL_MAX),
iErrBand(0.0),
targetErrBand(1.0),
doneSpeed(0.1),
lastTime(clock()),
lastError(0.0),
accI(0.0),
output(0.0),
done(false)
{}

double PID::compute(double curValue){
	clock_t time = clock();
	double dt = double(time - lastTime) / CLOCKS_PER_SEC;
	double error = target - curValue;

	double pOut = error * kp;
	double iOut = ((error + lastError) / 2.0) * dt * ki;
	double dOut = (error - lastError) / dt * kd;
	if (dt == 0.0)
		dOut = 0.0;

	// don't accumulate integrator error in steady state
	if(fabs(error) > iErrBand)
		accI += iOut;
	// integrator clamping to prevent runaway on integrator build up
	if(accI > iLimit)
		accI = iLimit;
	else if(accI < -iLimit)
		accI = -iLimit;

	if(pidType == rate)
		output += pOut + accI + dOut;
	else if(pidType == distance)
		output = pOut + accI + dOut;

	// clamp output
	if(output > 1.0)
		output = 1.0;
	else if(output < -1.0)
		output = -1.0;

	done = (fabs(error) <= targetErrBand && fabs(output) < doneSpeed);
	lastTime = time;
	lastError = error;

	return output;
}

void PID::reset(){
	lastTime = clock();
	lastError = 0.0;
	accI = 0.0;
	output = 0.0;
	done = false;
}

void PID::resetIntegrator(){
	accI = 0.0;
}
