#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

class Visitor;

class ModeloVideojuego
{
public:
    
    string tipo;
    int posX,posY;
    //Planet planet;
    
    virtual ModeloVideojuego* clonar() = 0;
    virtual void concepcionModelo()
    {
        cout<< "Construyendo modelo" << endl;
    }
    
     virtual void accept(Visitor*,ModeloVideojuego*) = 0;
    
    //virtual void construccion()=0;
    
};//Clase principal de videojuego

template <class SubClase>
class ClonModelo : public ModeloVideojuego
{
public:
    virtual ModeloVideojuego* clonar()
    {
        return new SubClase(dynamic_cast<SubClase&>(*this));
    }
};//Template Subclases


class Spacecraft : public ClonModelo<Spacecraft>
{
public:
    void constr(){
        cout << "Construyendo nave del tipo " << tipo << endl;
    }
    
    void accept(Visitor*,ModeloVideojuego*);
    

};

class Asteroids : public ClonModelo<Asteroids>
{
public:
    void constr(){
        cout << "Construyendo asteroide del tipo " << tipo << endl;
    }

  void accept(Visitor*,ModeloVideojuego*);
};



class Planets : public ClonModelo<Planets>
{
public:
    void constr(){
        cout << "Construyendo planeta del tipo " << tipo << endl;
    }
    
 void accept(Visitor*,ModeloVideojuego*);

};


class ModelFactory
{
    ModelFactory(){
        instance = this;
    }
    static ModelFactory* instance;
public:
    template<class T>
    static T* construirModelo(string n)
    {
        T* vg = new T;
        vg->tipo = n;
        vg->concepcionModelo();
        vg->constr();
        return vg;
    }
    
    static ModelFactory* getInstance(){
        if (instance==0) {
            return new ModelFactory;
        }
        else
            return instance;
    }
};
ModelFactory* ModelFactory::instance=0;

/*******************************************************************************************************/
/*******************************************************************************************************/
/************************************************Visitor************************************************/
/*******************************************************************************************************/


class Visitor
{
public:
    virtual void visit(Spacecraft*,ModeloVideojuego*) = 0;
    virtual void visit(Asteroids*,ModeloVideojuego*) = 0;
    virtual void visit(Planets*,ModeloVideojuego*) = 0;
};

class ColisionVisitor : public Visitor
{
    ColisionVisitor()
    {
        instance = this;
    }
    static ColisionVisitor* instance;
public:
    
    static ColisionVisitor* getInstance()
    {
        if(instance == 0)
        {
            return new ColisionVisitor;
        }
        else
            return instance;
    }
    
    void visit(Spacecraft* s,ModeloVideojuego* m)
    {
        cout <<  s->tipo << "  collides with " <<  m->tipo << endl;
    }
    void visit(Asteroids* a,ModeloVideojuego* m)
    {
        cout <<  a->tipo << "  collides with " <<  m->tipo << endl;
    }
    void visit(Planets* p,ModeloVideojuego* m)
    {
        cout <<  p->tipo << "  collides with " <<  m->tipo << endl;
    }
};
ColisionVisitor* ColisionVisitor::instance = 0;



void Spacecraft::accept(Visitor* v,ModeloVideojuego* m)
{
    v->visit(this,m);
}

void Asteroids::accept(Visitor* v,ModeloVideojuego* m)
{
    v->visit(this,m);
}

void Planets::accept(Visitor* v,ModeloVideojuego* m)
{
    v->visit(this,m);
}

/*******************************************************************************************************/
/*******************************************************************************************************/

int main() {
    
    ColisionVisitor* c = ColisionVisitor::getInstance();
    
    
    //Naves
    ModeloVideojuego* s1 = ModelFactory::getInstance()->construirModelo<Spacecraft>("Planet exploration ship");
    ModeloVideojuego* c1 = ModelFactory::getInstance()->construirModelo<Spacecraft>("Colonization ship");
    ModeloVideojuego* o1 = ModelFactory::getInstance()->construirModelo<Spacecraft>("Planet observtion ship");
    
    //Asteroides
    ModeloVideojuego* a1 = ModelFactory::getInstance()->construirModelo<Asteroids>("Stony meteorites");
    ModeloVideojuego* i1 = ModelFactory::getInstance()->construirModelo<Asteroids>("Iron meteorites");
    
    //Planetas
    ModeloVideojuego* p1 = ModelFactory::getInstance()->construirModelo<Planets>("Desert Planet");
    ModeloVideojuego* e1 = ModelFactory::getInstance()->construirModelo<Planets>("Earth Analog");
    
    //Clones
    ModeloVideojuego* s2 = s1->clonar();
    ModeloVideojuego* a2 = a1->clonar();
    ModeloVideojuego* p2 = p1->clonar();
    
    cout << endl << endl;
    cout << "Combinaciones de choques de naves" << endl;
    s1->accept(c,s2); //con una nave igual
    s1->accept(c, c1); //con otra nave
    s1->accept(c, a1); //con un asteroide
    s1->accept(c, p1); //con un planeta
    
    cout << endl << endl;
    cout << "Combinaciones de choques de asteroides" << endl;
    p1->accept(c,p2); //con una planeta clon
    p1->accept(c, o1); //con una nave
    p1->accept(c, e1); //con un planeta diferente
    p1->accept(c, i1); //con un asteroide
    
    cout << endl << endl;
    cout << "Combinaciones de choques de asteroides" << endl;
    a1->accept(c,a2); //con una asteroide igual
    a1->accept(c, c1); //con una nave
    a1->accept(c, i1); //con un asteroide diferente
    a1->accept(c, e1); //con un planeta
    
    
    //cout << s1->tipo << endl;
    //cout << s2->tipo << endl;
    //cout << v1->tipo << endl;
    
    
    return 0;
}
