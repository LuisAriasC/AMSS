#include <iostream>
#include <vector>
using namespace std;

class Observer;



class Subject {
    vector < class Observer * > views;
    string dijo,name;
    
public:
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    
    void setName(string na){
        name = na;
    }
    
    string getName() {
        return name;
    }
    
    void setDijo(string di) {
        dijo = di;
        notify();
    }
    
    string getDijo() {
        return dijo;
    }
    
    void notify();
};

class Observer {
    Subject *model;
    string name;
public:
    
    void setName(string na){
        name = na;
    }
    
    string getName(){
        return name;
    }
    
    Observer(Subject *mod) {
        model = mod;
        model->attach(this);
    }
    
    void update() {
        string n = getSubject()->getName();
        string v = getSubject()->getDijo();
        cout << name << " Informa: " << n << " dijo: " << "'" << v << "'"<< "\n";
    }
protected:
    Subject *getSubject() {
        return model;
    }
};

void Subject::notify() {
    for (int i = 0; i < views.size(); i++)
        views[i]->update();
}

class StringCheck : public Observer{

};


int main() {
    Subject sub1,sub2;
    sub1.setName("Donald Trump");
    sub2.setName("Peña Nieto");
    
    Observer Televisa(&sub1);
    Televisa.setName("Televisa");
    Observer Reforma(&sub2);
    Reforma.setName("Reforma");
    
    sub1.setDijo("Wall");
    sub2.setDijo("Ayotzinapa");
    
}
