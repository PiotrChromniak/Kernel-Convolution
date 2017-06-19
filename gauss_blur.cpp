#include "gauss_blur.hpp"

#include <algorithm>

using std::array;
using std::vector;
using std::cbegin;
using std::cend;

std::vector<double> chrom::get_gauss_kernel(int kernel_width)
{
    Expects(kernel_width > 0 && kernel_width % 2 == 1);

    vector<double> kernel(kernel_width*kernel_width);
    const auto half = kernel_width / 2 ;

    for (auto r = 0; r <= half; ++r) {
        const array<const Index2D, 4> positions{
            Index2D{ half + r,half },
            Index2D{ half - r,half },
            Index2D{ half, half + r },
            Index2D{ half, half - r }
        };

        const Point upper_left{ -0.5 + r, -0.5 },
            lower_right{ 0.5 + r,0.5 };
        const auto fn_value = integrate_normal_bi_distrib(upper_left, lower_right);

        std::for_each(cbegin(positions), cend(positions), [&](const Index2D idx_2d) {
            const auto idx_1d = translate(idx_2d, kernel_width);
            kernel[idx_1d] = fn_value;
        });

    }

    for (auto x = 1; x <= half; ++x)
        for (auto y = 1; y <= half; ++y) {
            const auto points = array<const Index2D, 4>{
                    Index2D{ half + x,half + y },
                    Index2D{ half - x,half + y },
                    Index2D{ half + x,half - y },
                    Index2D{ half - x,half - y }
            };

            const Point upper_left{ -0.5 + x, -0.5 + y }, lower_right{ 0.5 + x,0.5 + y };
            const auto fn_value = integrate_normal_bi_distrib(upper_left, lower_right);

            std::for_each(cbegin(points), cend(points), [&](const Index2D idx_2d) {
                const auto idx_1d = translate(idx_2d, kernel_width);
                kernel[idx_1d] = fn_value;
            });
        }

    return kernel;
}
