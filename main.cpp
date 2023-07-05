#include <iostream>
#include "mazesolver/MazeBuilder.h"

int main() {
    const int scale = 20;
    MazeBuilder mb(1920/scale,1080/scale,scale);
    mb.Run();
    return 0;
}
