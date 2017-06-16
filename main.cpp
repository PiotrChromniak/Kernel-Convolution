#include "Filter.h"

int main() {
    bitmap_image bmp0("image.bmp");
    Filter::gaussian(bmp0);
    bmp0.save_image("gauss.bmp");

    bitmap_image bmp1("image.bmp");
    Filter::average_blur(bmp1);
    bmp1.save_image("blur.bmp");

    bitmap_image bmp2("image.bmp");
    Filter::edge_detection(bmp2);
    bmp2.save_image("edge_detect.bmp");

    bitmap_image bmp3("image.bmp");
    Filter::sharpen(bmp3);
    bmp3.save_image("sharpen.bmp");
    return 0;
}