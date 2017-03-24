#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include "global.h"
#include "WorldState.h"
#include "Robot.h"
#include "Sensor.h"
#include "Marker.h"



int main(){


    cout << "Hello, Welcome to SLAM!!" << endl;
    bool run(true);
    array <float, 3> rob_vel;
    array <float, 3> rob_pose;
    float dt = 1.0;
    std::clock_t t1;
    std::clock_t t2;
    //f = {{0}};
    //f_transpose = {{0}};
    /*f[0][0] = 1;
    f[1][1] = 1;
    f[2][2] = 1;
    f_transpose[0][0] = 1;
    f_transpose[1][1] = 1;
    f_transpose[2][2] = 1;*/
    print_ffamily();
    // Initialize Robot
    Robot segway_rmp(0.0, 0.0, 0.0);
    // Initialize World
    array <float, dim> w_state = {0};
    array <array <float, dim>, dim> covar_matrix = {{0}};
    for (int i = 3; i < dim; i++){
        for (int j =3; j < dim; j++){
            if (i == j){
                covar_matrix[i][j] = 10000000;
            }
        }
    }
    WorldState segway_world(w_state, covar_matrix);
    //cout << dim << endl;
    //segway_world.print_wstate();
    //segway_world.print_cmatrix();


    while (run){

        t1 = std::clock();
        rob_vel = segway_rmp.get_velocities();
        //cout << rob_vel[2];
        rob_pose = segway_rmp.get_pose();
        //cout << rob_pose[2];
        segway_rmp.motion_model(dt, segway_world);
        //segway_world.print_wstate();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        t2 = std::clock();
        dt = float((t2 - t1) / (double(CLOCKS_PER_SEC)));

        //cout << t1 << endl << t2 << endl << dt << endl;
        run = false;
    }

    return 0;
}
