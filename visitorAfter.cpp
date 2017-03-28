#include <iostream>

using namespace std;

template <class T>
class Visitor;

template <class T>
class Number{
protected:
    string quienSoy;
public:
    string getQuienSoy(){return quienSoy;}
    virtual void accept(Visitor<T>*)=0;
};


class Integer: public Number<class T>
{
public:
    Integer(){
        quienSoy = "Integer";
    }
    static int countInts;
    void accept(Visitor<T>*);
};
int Integer::countInts=0;


class Double : public Number<class T>
{
public:
    Double(){
        quienSoy = "Double";
    }
    static int countDouble;
    void accept(Visitor<T>*);
};
int Double::countDouble=0;

/******************************************* VISITOR **************************************************/

template <class T>
class Visitor{
    
    /*Visitor(){
        instance = this;
    }
    static Visitor* instance;*/
public:
    /*static Visitor* getInstance(){
        if (instance==0) {
            return new Visitor*;
        }
        else
            return instance;
    }*/
    
    virtual void visit(Integer*)=0;
    virtual void visit(Double*)=0;
};
//template<> Visitor<T>* Visitor<T>::instance=0;

/******************************************** COUNT VISITOR **************************************/

class CountVisitor : public Visitor<class T>
{
    CountVisitor(){
        instance = this;
    }
    static CountVisitor* instance;
public:
    static CountVisitor* getInstance(){
        if (instance==0) {
            return new CountVisitor;
        }
        else
            return instance;
    }
    
    void visit(Integer* i)
    {
        cout << Integer::countInts << endl;
    }
    void visit(Double* d)
    {
        cout << Double::countDouble << endl;
    }
};
CountVisitor* CountVisitor::instance=0;


/******************************************** ADD VISITOR **************************************/
class AddVisitor : public Visitor<class T>
{
    AddVisitor(){
        instance = this;
    }
    static AddVisitor* instance;
public:
    static AddVisitor* getInstance(){
        if (instance==0) {
            return new AddVisitor;
        }
        else
            return instance;
    }
    
    void visit(Integer* i)
    {
        Integer::countInts++;
    }
    void visit(Double* d)
    {
        Double::countDouble++;
    }
};
AddVisitor* AddVisitor::instance=0;


/***************************** PRESENT VISITOR *************************************************/
class PresentVisitor : public Visitor<class T>
{
    PresentVisitor(){
        instance = this;
    }
    static PresentVisitor* instance;
public:
    
    static PresentVisitor* getInstance(){
        if (instance==0) {
            return new PresentVisitor;
        }
        else
            return instance;
    }
    
    void visit(Integer *i)
    {
        cout << i->getQuienSoy() << " ";
    }
    void visit(Double *d)
    {
        cout << d->getQuienSoy() << " ";
    }
};
PresentVisitor* PresentVisitor::instance=0;

/*********************************** ACCEPT DOUBLE AND INTEGER ********************************/
void Double::accept(Visitor<T>* v)
{
    v->visit(this);
}

void Integer::accept(Visitor<T>* v)
{
    v->visit(this);
}


/*********************************************  MAIN *******************************************/

int main (){
    
    AddVisitor* a = AddVisitor::getInstance();
    CountVisitor* c = CountVisitor::getInstance();
    PresentVisitor* p = PresentVisitor::getInstance();
    
    Number<T>::Number* n[] = {new Integer, new Double};
    
    for (int i=0; i < 5; i++){
        for (int j=0; j<2; j++) {
            //n[j]->accept(&a);
            n[j]->accept(a);
        }
    }
    
    n[0]->accept(p);
    //n[0]->accept(&c);
    n[0]->accept(c);
    
    cout << endl;
    
    n[1]->accept(p);
    //n[1]->accept(&c);
    n[1]->accept(c);
    
    return 0;
}
