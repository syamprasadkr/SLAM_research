#ifndef MARKER_H
#define MARKER_H


class Marker{

    public:
        Marker(int, float, float);
        int marker_id();
        float marker_x();
        float marker_y();


    protected:

    private:
        int id;
        float mx;
        float my;
};

#endif // MARKER_H
