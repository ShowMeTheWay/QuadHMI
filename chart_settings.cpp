#include "chart_settings.h"

chart_settings::chart_settings()
{
    this->num_ticks_X = 5;
    this->num_ticks_Y = 5;

    this->maxX = 10.0;
    this->maxY = 2.0;
    this->minX = 0.0;
    this->minY = -2.0;
}

void chart_settings::adjust_axis_X(double minX, double maxX, int num_ticks_X)
{
    this->maxX = (maxX);
    this->minX = minX;
    this->num_ticks_X = num_ticks_X;
}

double chart_settings::spanX()
{
    return (this->maxX-this->minX);
}

double chart_settings::spanY()
{
    return (this->maxY-this->minY);
}
