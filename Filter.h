#ifndef KERNELCONVOLUTION_FILTER_H
#define KERNELCONVOLUTION_FILTER_H

#include <limits>
#include <array>
#include <type_traits>
#include "bitmap_image.hpp"

using Matrix3X3 = std::array<std::array<float, 3>, 3>;

class Filter {
    template<typename T>
    struct Rgb{
        static_assert(std::is_arithmetic<T>::value, "T is not arithmetic type");
        T red;
        T green;
        T blue;
    };
    struct Point {
        unsigned int x;
        unsigned int y;
    };

    static void convolution(bitmap_image &image, const Matrix3X3 &kernel);
    static rgb_t pixel_neighbourhood_convolution(bitmap_image &image, const Matrix3X3 &kernel, const Point &point);
public:
    static void gaussian(bitmap_image &image);
    static void average_blur(bitmap_image &image);
    static void sharpen(bitmap_image &image);
    static void edge_detection(bitmap_image &image);
};


#endif //KERNELCONVOLUTION_FILTER_H
