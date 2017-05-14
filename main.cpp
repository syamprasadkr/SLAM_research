#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"



int main()
{
    cout << "Hello, Welcome to SLAM!!" << endl;
    bool run(true);
    array <float, 3> rob_vel;
    array <float, 3> rob_pose;
    array <array <float, 1>, 2> z_obs;
    array <array <float, 1>, 2> z_predicted;
    array <array <float, 2>, dim> kalman_gain;
    array <array <float, dim>, dim> kt_ht;
    float dt = 1.0;
    std::clock_t t1;
    std::clock_t t2;
    //print_matrix(f);
    //print_matrix(f_transpose);

    // Initialize Robot
    Robot segway_rmp(0.0, 0.0, 0.0);
    // Initialize World
    array <float, dim> w_state = {0};
    array <array <float, dim>, dim> covar_matrix = {{0}};
    for (int i = 3; i < dim; i++)
    {
        for (int j =3; j < dim; j++)
        {
            if (i == j)
            {
                covar_matrix[i][j] = 10000000;
            }
        }
    }
    WorldState segway_world(w_state, covar_matrix);
    //cout << dim << endl;
    //segway_world.print_wstate();
    //segway_world.print_cmatrix();
    Sensor rgbd_camera;

    while (run)
    {

        t1 = std::clock();
        rob_vel = segway_rmp.get_velocities();
        //cout << rob_vel[2];
        //rob_pose = segway_rmp.get_pose();
        //cout << rob_pose[2];
        segway_rmp.motion_model(dt, segway_world);
        //segway_world.print_wstate();

        z_obs = rgbd_camera.get_measurement();
        rob_pose = segway_rmp.get_pose();
        z_predicted = rgbd_camera.marker_pos(rob_pose[0], rob_pose[1], rob_pose[2], segway_world);
        //cout << z_obs[0][0];
        kalman_gain = rgbd_camera.kalman_gain(segway_world);
        segway_world.correct_wstate(kalman_gain, z_obs, z_predicted);
        kt_ht = rgbd_camera.calc_ktht(kalman_gain);
        segway_world.correct_cmatrix(kt_ht);
        w_state = segway_world.get_wstate();
        segway_rmp.update_pose(w_state[0], w_state[1], w_state[2]);
        // Basic architecture finished
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        t2 = std::clock();
        dt = float((t2 - t1) / (double(CLOCKS_PER_SEC)));

        //cout << t1 << endl << t2 << endl << dt << endl;
        run = false;
    }

    return 0;
}
