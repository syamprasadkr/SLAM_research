#ifndef WORLDSTATE_H
#define WORLDSTATE_H
#include "global.h"


class WorldState{

    public:
        WorldState(array <float, dim>& a, array <array <float, dim>, dim>& b);
        void print_wstate();
        void print_cmatrix();
        void predict_wstate(float, float, float);
        void predict_cmatrix();

    protected:

    private:
        array <float, dim> w_state;
        array <array <float, dim>, dim> covar_matrix;

};

#endif // WORLDSTATE_H
