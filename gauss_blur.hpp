#ifndef GAUSS_BLUR_HPP
#define GAUSS_BLUR_HPP

#include <vector>
#include <array>
#include <gsl/gsl_assert>
#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

namespace chrom {
    std::vector<double> get_gauss_kernel(int kernel_width);
    namespace {
        struct Index2D {
            int x, y;
        };

        struct Point{
            double x, y;
        };

        int translate(const Index2D point, const int dimension) {
            const auto index = point.y*dimension + point.x;
            Expects(index >= 0);
            return index;
        }

        double integrate_normal_bi_distrib(const Point& upper_left, const Point& lower_right){
            const auto sqrt2 = std::sqrt(2);
            const auto erf_x0 = std::erf(upper_left.x / sqrt2);
            const auto erf_x1 = std::erf(lower_right.x / sqrt2);
            const auto erf_y0 = std::erf(upper_left.y / sqrt2);
            const auto erf_y1 = std::erf(lower_right.y / sqrt2);
            return ((erf_x1*erf_y1 - erf_x0*erf_y1) - (erf_x1*erf_y0 - erf_x0*erf_y0)) / 4;
        }
    }
}

#endif
