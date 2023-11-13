#include "PidController.h"

PidController::PidController(double pWeight, double iWeight, double dWeight)
    : pWeight(pWeight),
      iWeight(iWeight),
      dWeight(dWeight),
      integralValue(0),
      lastError(0)
{
}

double PidController::Calculate(double error, double deltaTime)
{
    integralValue += error * deltaTime;
    double compP = error * pWeight;
    double compI = integralValue * iWeight;
    double compD = ((error - lastError) / deltaTime) * dWeight;
    lastError = error;
    return compP + compI + compD;
}

void PidController::Reset()
{
    integralValue = 0;
    lastError = 0;
}

void PidController::SetPWeight(double value)
{
    pWeight = value;
}

void PidController::SetIWeight(double value)
{
    iWeight = value;
}

void PidController::SetDWeight(double value)
{
    dWeight = value;
}