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
    virtual PairCoordinates get2DCoordinatesDerivative(double) = 0;
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
        PairCoordinates coordinates;
        coordinates.x = l*t + x0;
        coordinates.y = m*t + y0;

        return coordinates;
    }

    double getDerivative(double t) override {

        return m/l;
    }

    PairCoordinates get2DCoordinatesDerivative(double t) override {
        PairCoordinates coordinates;
        coordinates.x = 1;
        coordinates.y = getDerivative(t);

        return coordinates;
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
        PairCoordinates coordinates;
        coordinates.x = rx*cos(t);
        coordinates.y = ry*sin(t);

        return coordinates;
    }

    double getDerivative(double t) override {

        return (-1)*((ry*cos(t))/(rx*sin(t)));
    }

    PairCoordinates get2DCoordinatesDerivative(double t) override {
        PairCoordinates coordinates;
        coordinates.x = 1;
        coordinates.y = getDerivative(t);

        return coordinates;
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
        coordinate = curve->get2DCoordinatesDerivative(M_PI/4);
        std::cout << "2D-вектор производной в этой точке: {" << coordinate.x <<", " << coordinate.y << "}" << std::endl;
        i++;
    }

    return 0;
}
