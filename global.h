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
template <size_t M, size_t N>
extern void transpose(array <array <float, N>, M>&, array <array <float, M>, N>&);
template <size_t M, size_t N, size_t P>
extern void mat_mult(array <array <float, N>, M>&, array <array <float, P>, N>&, array <array <float, P>, M>&);
extern void mat_invert(array <array <float, 2>, 2>&, array <array <float, 2>, 2>&);
extern void generate_noise_matrix(array <array <float, 3>, 3>&);
extern void generate_noise_matrix2(array <array <float, 2>, 2>& a);
template <size_t M, size_t N>
extern void print_matrix(array <array <float, N>, M>&);

#endif // GLOBAL_H_INCLUDED
