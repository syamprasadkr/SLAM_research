#ifndef WORLDSTATE_H
#define WORLDSTATE_H
#include "global.h"
#include "Marker.h"


class WorldState{

    public:
        WorldState(array <float, dim>& a, array <array <float, dim>, dim>& b);
        void print_wstate();
        void print_cmatrix();
        void predict_wstate(float, float, float);
        void predict_cmatrix(array <array <float, dim>, dim>&, array <array <float, dim>, dim>&,
                             array <array <float, dim>, dim>&);
        void update_wstate(vector <Marker>&);

    protected:

    private:
        array <float, dim> w_state;
        array <array <float, dim>, dim> covar_matrix;
        array <array <float, dim>, dim> temp{{}};
        //array <array <float, dim>, dim> temp2{{}};

};

#endif // WORLDSTATE_H
