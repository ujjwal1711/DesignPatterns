//
// Created by Ujjwal Shukla on 04/10/23.
//

#include <iostream>
#include <string>

using namespace std;

enum ShapeType {
    SphericalShape,
    SquareShape,
};

class Shape {
public:
    virtual void shapeInfo() = 0;
};


class Sphere: public Shape {
public:
    void shapeInfo() {
        cout<<"shape is sphere" <<"\n";
    }
};

class Square: public Shape {
public:
    void shapeInfo() {
        cout<<"shape is square"<<"\n";
    }
};


class ShapeFactory {
public:
    Shape* getShape(ShapeType shapeName) {
        if (shapeName == SquareShape) {
               return new Square();
        } else if (shapeName == SphericalShape) {
            return new Sphere();
        }
        return nullptr;
    }
};


int main() {
    ShapeFactory* shapeFactory = new ShapeFactory();
    Shape* sphere = shapeFactory->getShape(SphericalShape);
    Shape* square = shapeFactory->getShape(SquareShape);
    sphere->shapeInfo();
    square->shapeInfo();
}
