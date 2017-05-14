#include <iostream>
#include <cstdio>
#include <cmath>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"

Robot::Robot(float a, float b, float c)
{
    //ctor
    x = a;
    y = b;
    theta = c;
    generate_noise_matrix(r_matrix_low);
    generate_r_matrix();
}

void Robot::generate_r_matrix()
{
    array <array <float, dim>, 3> temp2{{}};
    // Create higher order R noise matrix
    mat_mult(r_matrix_low, f, temp2);
    mat_mult(f_transpose, temp2, r_matrix);
}

array <float, 3> Robot::get_velocities()
{
    // Comment out the next three lines when velocities from actual hardware is available.
    v_tx = 1.0;
    v_ty = 0.0;
    omega_t = 0.0;

    ret_matrix = {v_tx, v_ty, omega_t};
    return ret_matrix;
}

array <float, 3> Robot::get_pose()
{
    ret_matrix = {x, y, theta};
    return ret_matrix;
}

void Robot::motion_model(float dt, WorldState& segway_world)
{
        // Change the angular velocity equation depending on units
        x = x + (((cos(theta * PI / 180) * v_tx) - (sin(theta * PI / 180) * v_ty)) * dt);
        y = y + (((sin(theta * PI / 180) * v_tx) + (cos(theta * PI / 180) * v_ty)) * dt);
        theta = theta + (omega_t * 180 / PI) * dt;

        segway_world.predict_wstate(x, y, theta);
        jacobian_motion(dt, segway_world);
}

void Robot::jacobian_motion(float dt, WorldState& segway_world)
{
    jacobian_matrix_low[0] = {1.0, 0.0, (((-sin(theta * PI / 180) * v_tx) - (cos(theta * PI / 180) * v_ty)) * dt)};
    jacobian_matrix_low[1] = {0.0, 1.0, (((cos(theta * PI / 180) * v_tx) - (sin(theta * PI / 180) * v_ty)) * dt)};
    jacobian_matrix_low[2] = {0.0, 0.0, 1.0};
    // Reached till Eq. 5.

    // The construction of jacobian high. Make necessary changes if jacobian_matrix_low is eliminated.

    jacobian[0][2] = jacobian_matrix_low[0][2];
    jacobian[1][2] = jacobian_matrix_low[1][2];

    for (int i = 0; i < dim; i++)
    {
        jacobian[i][i] = 1;
    }

    transpose<dim, dim>(jacobian, jacobian_transposed);
    //cout << "Jacobian" << endl;
    //print_matrix<dim, dim>(jacobian);

    //cout << "Transposed Jacobian" << endl;
    //print_matrix<dim, dim>(jacobian_transposed);

    //cout << "R matrix" << endl;
    //print_matrix<dim, dim>(r_matrix);


    segway_world.predict_cmatrix(jacobian, jacobian_transposed, r_matrix);
}

void Robot::update_pose(float a, float b, float c)
{
    x = a;
    y = b;
    theta = c;
}
