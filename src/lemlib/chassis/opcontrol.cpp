#include "lemlib/chassis/chassis.hpp"
#include <algorithm>
#include <math.h>

namespace lemlib {

double calcDriveCurve(double input, double scale) {
    if (scale != 0) {
        return (powf(2.718, -(scale / 10)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(scale / 10)))) *
               input;
    }
    return input;
}

void Chassis::tank(int left, int right, float gain) {
    drivetrain.leftMotors->move(calcDriveCurve(left, gain));
    drivetrain.rightMotors->move(calcDriveCurve(right, gain));
};

void Chassis::arcade(int forward, int turn, float gain) {
    int leftPower = calcDriveCurve(forward + turn, gain);
    int rightPower = calcDriveCurve(forward - turn, gain);
    drivetrain.leftMotors->move(leftPower);
    drivetrain.rightMotors->move(rightPower);
};

void Chassis::curvature(int forward, int curvature, float gain) {
    // If we're not moving forwards change to arcade drive
    if (forward == 0) {
        arcade(forward, curvature, gain);
        return;
    }

    double leftPower = forward + std::abs(forward) * curvature;
    double rightPower = forward - std::abs(forward) * curvature;

    drivetrain.leftMotors->move(leftPower);
    drivetrain.rightMotors->move(rightPower);
};
} // namespace lemlib
