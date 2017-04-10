#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <array>
#include <cmath>
#include <vector>
#define PI 3.14159

using std::cout;
using std::cin;
using std::endl;
using std::array;
using std::vector;
using std::abs;

static constexpr const int marker_num = 10;
static constexpr const int dim = (2 * marker_num) + 3;
static constexpr const float sigma = 1;
static array <array <float, 3>, 3> h1 = {{{{-1, 0, 1}}, {{-1, 0, 1}}, {{-1, 0, 1}}}};
static array <array <float, 3>, 3> h2 = {{{{-1, -1, -1}}, {{0, 0, 0}}, {{1, 1, 1}}}};
static array <array <float, 3>, dim> f_transpose = {{{1}, {0, 1}, {0, 0, 1}}};
static array <array <float, dim>, 3> f = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
extern void transpose(array <array <float, dim>, dim>&, array <array <float, dim>, dim>&);
extern void transpose2(array <array <float, dim>, 2>& a, array <array <float, 2>, dim>& b);
extern void mat_mult(array <array <float, dim>, dim>&, array <array <float, dim>, dim>&, array <array <float, dim>, dim>&);
extern void generate_noise_matrix(array <array <float, 3>, 3>&);
extern void generate_noise_matrix2(array <array <float, 2>, 2>& a);
extern void print_matrix1(array <array <float, dim>, dim>&);
extern void print_matrix2(array <array <float, 3>, 3>&);
extern void print_ffamily();


#endif // GLOBAL_H_INCLUDED
