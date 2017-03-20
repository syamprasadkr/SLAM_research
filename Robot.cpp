#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"

Robot::Robot(float a, float b, float c){

    //ctor
    x = a;
    y = b;
    theta = c;
}

array <float, 3> Robot::get_velocities(){

    // Comment out the next three lines when velocities from actual hardware is available.
    v_tx = 1.0;
    v_ty = 0.0;
    omega_t = 0.0;

    ret_matrix = {v_tx, v_ty, omega_t};
    return ret_matrix;

}

array <float, 3> Robot::get_pose(){

    ret_matrix = {x, y, theta};
    return ret_matrix;

}

void Robot::motion_model(float dt, WorldState& segway_world){

        // Change the angular velocity equation depending on units
        x = x + (((cos(theta * PI / 180) * v_tx) - (sin(theta * PI / 180) * v_ty)) * dt);
        y = y + (((sin(theta * PI / 180) * v_tx) + (cos(theta * PI / 180) * v_ty)) * dt);
        theta = theta + (omega_t * 180 / PI) * dt;

        segway_world.predict_wstate(x, y, theta);
        jacobian_motion(dt);
}

void Robot::jacobian_motion(float dt){

    jacobian_matrix[0] = {1.0, 0.0, (((-sin(theta * PI / 180) * v_tx) - (cos(theta * PI / 180) * v_ty)) * dt)};
    jacobian_matrix[1] = {0.0, 1.0, (((cos(theta * PI / 180) * v_tx) - (sin(theta * PI / 180) * v_ty)) * dt)};
    jacobian_matrix[2] = {0.0, 0.0, 1.0};
    // Reached till Eq. 5.

}
