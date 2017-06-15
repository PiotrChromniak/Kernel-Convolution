#include "Filter.h"
#include "value_range.h"

void Filter::gaussian(bitmap_image &image) {
    const Matrix3X3 kernel{{{1 / 9.0f, 1 / 9.0f, 1 / 9.0f},
                                   {1 / 9.0f, 1 / 9.0f, 1 / 9.0f},
                                   {1 / 9.0f, 1 / 9.0f, 1 / 9.0f}}};
    convolution(image, kernel);
}

void Filter::average_blur(bitmap_image &image) {
    const Matrix3X3 kernel{{{1 / 16.0f, 2 / 16.0f, 1 / 16.0f},
                                   {2 / 16.0f, 4 / 16.0f, 2 / 16.0f},
                                   {1 / 16.0f, 2 / 16.0f, 1 / 16.0f}}};
    convolution(image, kernel);
}

void Filter::edge_detection(bitmap_image &image) {
    const Matrix3X3 kernel{{{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}};
    convolution(image, kernel);
}

void Filter::sharpen(bitmap_image &image) {
    const Matrix3X3 kernel{{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}};
    convolution(image, kernel);
}

void Filter::convolution(bitmap_image &image, const Matrix3X3 &kernel) {
    const auto width = image.width();
    const auto height = image.height();
    bitmap_image buffer_image(image);

    for (auto y = 1; y < height - 1; ++y)
        for (auto x = 1; x < width - 1; ++x)
            image.set_pixel(x, y, pixel_neighbourhood_convolution(buffer_image, kernel, Point{x, y}));
}

rgb_t Filter::pixel_neighbourhood_convolution(bitmap_image &image, const Matrix3X3 &kernel,
                                              const Filter::Point &point) {
    using uchar = unsigned char;
    auto accum_result = Rgb<int>{0, 0, 0};

    for (auto i = -1; i <= 1; ++i)
        for (auto j = -1; j <= 1; ++j) {
            auto temp_colour = rgb_t{};
            image.get_pixel(point.x + j, point.y + i, temp_colour);

            const auto kernel_coeff = kernel[j + 1][i + 1];
            accum_result.red += temp_colour.red * kernel_coeff;
            accum_result.green += temp_colour.green * kernel_coeff;
            accum_result.blue += temp_colour.blue * kernel_coeff;
        }

    return rgb_t{value_within_range<uchar>(accum_result.red), value_within_range<uchar>(accum_result.green),
                 value_within_range<uchar>(accum_result.blue)};
}
