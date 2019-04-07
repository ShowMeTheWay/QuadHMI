#ifndef CHART_SETTINGS_H
#define CHART_SETTINGS_H

class chart_settings
{
public:
    chart_settings();
    double minX;
    double maxX;
    double spanX();
    double minY;
    double maxY;
    double spanY();

    int num_ticks_X;
    int num_ticks_Y;

protected:
    void adjust_axis_X(double minX, double maxX, int num_ticks_X);
};

#endif // CHART_SETTINGS_H
