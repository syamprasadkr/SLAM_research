#ifndef ROBOT_H
#define ROBOT_H


class Robot{

    public:
        Robot(float, float, float);
        array <float, 3> get_velocities();
        array <float, 3> get_pose();
        void motion_model(float, WorldState&);
        void jacobian_motion(float);

    protected:

    private:
        float x;
        float y;
        float theta;
        float v_tx = 0.0;
        float v_ty = 0.0;
        float omega_t = 0.0;
        array <array <float, 3>, 3> jacobian_matrix;
        // Consider making global
        array <float, 3> ret_matrix;

};

#endif // ROBOT_H
