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
    virtual ~Curve(){ }
    virtual PairCoordinates getCoordinates (double) = 0;
    virtual PairCoordinates get2DCoordinatesDerivative(double) = 0;
};

class Line : public Curve
{
    double x0;
    double y0;
    double l;
    double m;

public:
    Line(double x0, double y0, double l, double m) {
        this->x0 = x0;
        this->y0 = y0;
        this->l = l;
        this->m = m;
    }
    virtual ~Line(){ }
    PairCoordinates getCoordinates (double t) override {
        PairCoordinates coordinates;
        coordinates.x = l*t + x0;
        coordinates.y = m*t + y0;

        return coordinates;
    }

    PairCoordinates get2DCoordinatesDerivative(double t) override {
        PairCoordinates coordinates;
        coordinates.x = l;
        coordinates.y = m;

        return coordinates;
    }
};

class Ellipse : public Curve
{
    double rx;
    double ry;

public:
    Ellipse(double rx, double ry) {
        this->rx = rx;
        this->ry = ry;
    }
    virtual ~Ellipse(){ }
    PairCoordinates getCoordinates(double t) override {
        PairCoordinates coordinates;
        coordinates.x = rx*cos(t);
        coordinates.y = ry*sin(t);

        return coordinates;
    }

    PairCoordinates get2DCoordinatesDerivative(double t) override {
        PairCoordinates coordinates;
        coordinates.x = rx*(-sin(t));
        coordinates.y = ry*(cos(t));

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
