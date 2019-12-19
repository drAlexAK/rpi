#pragma once

class piConfigCamera{
private:
public:
    // value of color that less or equal this value will be recognize as the black color, the range of the value from 0 to 255
    const int color_black;
    // do morphological transformation for images, very poor performance
    const bool do_morphological ;
    piConfigCamera(int _color_black, bool _do_morphological ): color_black(_color_black), do_morphological(_do_morphological) {}
};
