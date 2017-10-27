#pragma once

#include <cmath>
#include <cfloat>
#include <ctime>

class PID {
public:
	enum PIDType {distance, rate};
	PID(PIDType _pidType, double _kp, double _ki, double _kd);

	void setTarget(double _target) { target = _target; }
	void setIntegratorLimit(double limit) { iLimit = limit; }
	void setIntegratorErrorBand(double errBand) { iErrBand = errBand; }
	void setTargetErrorBand(double errBand) { targetErrBand = errBand; }
	void setDoneSpeed(double speed) { doneSpeed = speed; }

	double getAccumulatedIntegralError() { return accI; }
	double getLastError() const { return lastError; }
	bool getIfDone() { return done; }

	double compute(double curValue);
	void reset();
	void resetIntegrator();

private:
	PIDType pidType;
	double kp, ki, kd;

	double target;
	double iLimit;
	double iErrBand;
	double targetErrBand;
	double doneSpeed;

	clock_t lastTime;
	double lastError;
	double accI;
	double output;
	bool done;
};

