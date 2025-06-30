#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Point {

    double x;
    double y;

public:

    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }

    void setX(double x) {
        this->x = x;
    }
    void setY(double y) {
        this-> y = y;
    }

    /* !!!!!!!!!!!!! */
    Point operator-(const Point & thing) const {
        return Point (std::abs(x - thing.getX() ), std::abs (y - thing.getY() ) );
    }

};


class Shape {

protected:

    Point mFirst;
    Point mSecond;
    std::string mName;

public:

    Shape() : mFirst(Point(0, 0)), mSecond(Point(0, 0)), mName("") {} //WoW
    Shape(Point First, Point Second): mFirst(First), mSecond(Second), mName("") {}

    Point getFirst() const {
        return mFirst;
    }
    Point getSecond() const {
        return mSecond;
    }
    std::string getName() {
        return mName;
    }


    void setFirst(Point First) {
        mFirst = First;
    }
    void setSecond(Point Second) {
        mSecond = Second;
    }
    void setName(std::string Name) {
        mName = Name;
        // strcpy (mName, Name)
    }

    virtual double getPerimeter() const = 0 ;
    virtual double getArea() const = 0;

};

class Quadrilateral : public Shape {

public:

    Quadrilateral() : Shape() { mName = "Unknown"; }
    Quadrilateral(Point  First, Point Second, std::string Name) : Shape(First,Second) { mName = Name; }

    double getLength() const {
        Point diff = mFirst - mSecond;
        return diff.getX();
    }
    double getWidth() const {
        Point diff = mFirst - mSecond;
        return diff.getY();
    }

    double getPerimeter() const override {
        return 2 * ( getLength() + getWidth()) ;
    }

    double getArea() const override {
        return getLength() * getWidth() ;
    }
};

class Circle : public Shape {

    double mRadius;

public:

    Circle() : Shape(), mRadius(0) { mName = "Unknown"; }
    Circle(Point center, double radius) : Shape(center,Point()), mRadius(radius) { mName = "cerc"; }

// M_PI
    double getPerimeter() const override {
        return 2 * M_PI* mRadius;
    }

    double getArea() const override {
        return M_PI * mRadius * mRadius ;
    }

    double getRadius() const { return mRadius; }
    void setRadius(double radius) { mRadius = radius; }



};

bool comparator(const Shape * s1, const Shape * s2) {
    return s1->getArea() < s2->getArea();
}


int main() {

    int n;
    scanf("%d", &n);

    double min, max;
    scanf("%lf %lf", &min, &max);

    double x,y,radius, x1, x2, y1, y2;
    std::string Name;

    if ( n >= 1 && n <= 500 && min <= max ) {
        std::vector<Shape *> shapes;
        //   std::sort(shapes.begin(), shapes.end(), comparator);

        for (int i = 0; i < n; i++) {

            cin >> Name;

            if (Name == "cerc") {
                scanf("%lf %lf %lf", &x, &y, &radius);
                if(radius >= 0 && radius <= 1000 ) {
                    Point p(x, y);
                    // Circle* temp (p,radius);
                    shapes.push_back(new Circle(p, radius));
                } else {
                    printf("Valoare de intrare invalida\n");
                    //break;
                    exit(0);
                }
            } else if (Name == "patrat") {
                scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
                if (x1 >= -1000 && x2 >= -1000 && y1 >= -1000 && y2 >= -1000 && x1 <= 1000 && x2 <= 1000 && y1 <= 1000 && y2 <= 1000 ) {
                    Point p1(x1, y1);
                    Point p2(x2, y2);
                    shapes.push_back(new Quadrilateral(p1, p2, "patrat"));
                } else {
                    printf("Valoare de intrare invalida\n");
                    //break;
                    exit(0);
                }
            } else if (Name == "dreptunghi") {
                scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
                if (x1 >= -1000 && x2 >= -1000 && y1 >= -1000 && y2 >= -1000 && x1 <= 1000 && x2 <= 1000 && y1 <= 1000 && y2 <= 1000 ) {
                    Point p1(x1, y1);
                    Point p2(x2, y2);
                    shapes.push_back(new Quadrilateral(p1, p2, "dreptunghi"));
                } else {
                    printf("Valoare de intrare invalida\n");
                  //  break;
                  exit(0);
                }
            }


        }


        for (int i = 0; i < n; i++) {
            std::sort(shapes.begin(), shapes.end(), comparator);
        }

        for (int i = 0; i < n; i++) {
            printf("%s %.6lf %.6lf\n", shapes[i]->getName().c_str(), shapes[i]->getArea(), shapes[i]->getPerimeter());
        }

    } else {
        printf("Valoare de intrare invalida\n");
    }
    return 0;
}
