#include <iostream>
#include <string>

using namespace std;

class Product{
public:
    virtual void SetUp()=0;
};


class Prod1 : public Product
{
public:
    void SetUp()
    {
    cout<<"Construcción del objeto complejo"<<endl;
        };
};

class FactoryMethod{
public:
    virtual Product* factoryMethod() = 0;
public:
    
};

class ConcreteFactoryOO : public FactoryMethod
{
public:
    Product* factoryMethod(){
        return new Prod1();
    }
    
};



int main() {
    Product* p = ConcreteFactoryOO::factoryMethod();
    return 0;
}
