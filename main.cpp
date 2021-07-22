#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

struct PairCoordinates {
    double x;
    double y;
};

class Curve
{
public:
    virtual PairCoordinates getCoordinates (double) = 0;
    virtual double getDerivative (double) = 0;
};

class Line : public Curve
{
public:
    double x0;
    double y0;
    double l;
    double m;

    Line(double x0, double y0, double l, double m) {
        this->x0 = x0;
        this->y0 = y0;
        this->l = l;
        this->m = m;
    }

    PairCoordinates getCoordinates (double t) override {
        PairCoordinates coord;
        coord.x = l*t + x0;
        coord.y = m*t + y0;

        return coord;
    }

    double getDerivative(double t) override {
        return m/l;
    }
};

class Ellipse : public Curve
{
public:
    double rx;
    double ry;

    Ellipse(double rx, double ry) {
        this->rx = rx;
        this->ry = ry;
    }

    PairCoordinates getCoordinates(double t) override {
        PairCoordinates coord;
        coord.x = rx*cos(t);
        coord.y = ry*sin(t);

        return coord;
    }

    double getDerivative(double t) override {
        return (-1)*((ry*cos(t))/(rx*sin(t)));
    }
};

int main()
{
    std::vector<std::unique_ptr<Curve>> curves;

    curves.emplace_back(new Line(0, 0, 2, 2));
    curves.emplace_back(new Line(1, 2, 1, 3));
    curves.emplace_back(new Ellipse(4.5, 3));
    curves.emplace_back(new Ellipse(2.75, 1));
    curves.emplace_back(new Line(2, -2, 1, 1));
    curves.emplace_back(new Ellipse(5, 2));
    curves.emplace_back(new Line(-2, -3, -1, -6));
    curves.emplace_back(new Ellipse(3, 2));

    int i = 1;
    for(auto& curve : curves) {
        PairCoordinates coordinate;
        coordinate = curve->getCoordinates(M_PI/4);
        std::cout << "Координаты " << i << "-й кривой: (" << coordinate.x <<", " << coordinate.y << ")" << std::endl;
        std::cout << "Производная в этой точке равна " << curve->getDerivative(M_PI/4)<< std::endl;
        i++;
    }

    return 0;
}
