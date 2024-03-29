#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

class Shape
{
public:
    virtual void Show() const = 0;
    virtual void Save(ofstream& outfile) const = 0;
    virtual void Load(ifstream& infile) = 0;
    virtual ~Shape() {}
};

class Square : public Shape {
private:
    int x, y;
    int side;
public:
    Square(int x_val, int y_val, int side_val) : x(x_val), y(y_val), side(side_val) {}

    void Show() const override {
        cout << "Square with top-left corner at (" << x << ", " << y << ") and side length " << side << endl;
    }

    void Save(ofstream& outfile) const override {
        outfile << "Square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& infile) override {
        infile >> x >> y >> side;
    }
};

class Rectangle : public Shape {
private:
    int x, y;
    int width, height;
public:
    Rectangle(int x_val, int y_val, int width_val, int height_val) : x(x_val), y(y_val), width(width_val), height(height_val) {}

    void Show() const override {
        cout << "Rectangle with top-left corner at (" << x << ", " << y << ") and dimensions " << width << "x" << height << endl;
    }

    void Save(ofstream& outfile) const override {
        outfile << "Rectangle " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& infile) override {
        infile >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
private:
    int x, y;
    int radius;
public:
    Circle(int x_val, int y_val, int radius_val) : x(x_val), y(y_val), radius(radius_val) {}

    void Show() const override {
        cout << "Circle with center at (" << x << ", " << y << ") and radius " << radius << endl;
    }

    void Save(ofstream& outfile) const override {
        outfile << "Circle " << x << " " << y << " " << radius << endl;
    }

    void Load(ifstream& infile) override {
        infile >> x >> y >> radius;
    }
};

class Ellipse : public Shape {
private:
    int x, y;
    int width, height;
public:
    Ellipse(int x_val, int y_val, int width_val, int height_val) : x(x_val), y(y_val), width(width_val), height(height_val) {}

    void Show() const override {
        cout << "Ellipse with top-left corner at (" << x << ", " << y << ") and dimensions " << width << "x" << height << endl;
    }

    void Save(ofstream& outfile) const override {
        outfile << "Ellipse " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& infile) override {
        infile >> x >> y >> width >> height;
    }
};

int main() {
    vector<shared_ptr<Shape>> shapes;

    shapes.push_back(make_shared<Square>(0, 0, 5));
    shapes.push_back(make_shared<Rectangle>(0, 0, 4, 6));
    shapes.push_back(make_shared<Circle>(0, 0, 3));
    shapes.push_back(make_shared<Ellipse>(0, 0, 4, 2));

    ofstream outfile("shapes.txt");
    if (outfile.is_open()) {
        for (const auto& shape : shapes) {
            shape->Save(outfile);
        }
        outfile.close();
    }
    else {
        cerr << "Unable to open file for writing!" << endl;
        return 1;
    }

    vector<shared_ptr<Shape>> loaded_shapes;
    ifstream infile("shapes.txt");
    if (infile.is_open()) {
        string shape_type;
        while (infile >> shape_type) {
            if (shape_type == "Square") {
                int x, y, side;
                infile >> x >> y >> side;
                loaded_shapes.push_back(make_shared<Square>(x, y, side));
            }
            else if (shape_type == "Rectangle") {
                int x, y, width, height;
                infile >> x >> y >> width >> height;
                loaded_shapes.push_back(make_shared<Rectangle>(x, y, width, height));
            }
            else if (shape_type == "Circle") {
                int x, y, radius;
                infile >> x >> y >> radius;
                loaded_shapes.push_back(make_shared<Circle>(x, y, radius));
            }
            else if (shape_type == "Ellipse") {
                int x, y, width, height;
                infile >> x >> y >> width >> height;
                loaded_shapes.push_back(make_shared<Ellipse>(x, y, width, height));
            }
            else {
                cerr << "Unknown shape type encountered while loading from file!" << endl;
            }
        }
        infile.close();
    }
    else {
        cerr << "Unable to open file for reading!" << endl;
        return 1;
    }

    for (const auto& shape : loaded_shapes) {
        shape->Show();
    }
}