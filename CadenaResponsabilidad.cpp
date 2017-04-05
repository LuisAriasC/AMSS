#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Dominio{
    
public:
    string ip;
    vector<string> url;
    void setIP(string i){ip = i;}
    string getIP(){return ip;}
    void pushURL(string ur){url.push_back(ur);}
};

class ServidorDNS
{
    ServidorDNS *next; // 1. "next" pointer in the base class
    
public:
    ServidorDNS()
    {
        next = 0;
    }
    
    void setNext(ServidorDNS *n)
    {
        next = n;
    }
    
    void add(ServidorDNS *n)
    {
        if (next)
            next->add(n);
        else
            next = n;
    }
    
    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(string m)
    {
        next->handle(m);
    }
};


class ServidorA: public ServidorDNS
{
    public:
    Dominio a;
    ServidorA(){
        a.setIP("192.16.4.5");
        a.pushURL("www.google.com");
        a.pushURL("www.amazon.com");
    }
    /*virtual*/ void handle(string m)
    {
        if (m=="www.google.com" || m=="www.amazon.com") {
            cout << "Server A handled " << m << "  ";
        }
        else
            cout << "Server A passed " << m << "  ";
        ServidorDNS::handle(m); // 3. Delegate to the base class
        
        /*if (rand() % 5)
        {
            // 3. Don't handle requests 3 times out of 4
            cout << "Server A passed " << m << "  ";
            ServidorDNS::handle(m); // 3. Delegate to the base class
        }
        else
            cout << "Server A handled " << m << "  ";*/
    }
};

class ServidorB: public ServidorDNS
{
public:
    Dominio b;
    ServidorB(){
        b.setIP("198.144.8.7");
        b.pushURL("www.yahoo.com");
        b.pushURL("www.forbes.com");
    }
    /*virtual*/void handle(string m)
    {
        if (m=="www.yahoo.com" || m=="www.forbes.com") {
            cout << "Server B handled " << m << "  ";
        }
        else
            cout << "Server B passed " << m << "  ";
        ServidorDNS::handle(m); // 3. Delegate to the base class
     /*   if (rand() % 5)
        {
            cout << "Server B passed " << m << "  ";
            ServidorDNS::handle(m);
        }
        else
            cout << "Server B handled " << m << "  ";*/
    }
};

class ServidorC: public ServidorDNS
{
public:
    Dominio c;
    ServidorC(){
        c.setIP("157.35.34.7");
        c.pushURL("www.facebook.com");
        c.pushURL("www.mitec.itesm.com");
    }
    /*virtual*/void handle(string m)
    {
        if (m=="www.facebook.com" || m=="www.mitec.itesm.com") {
            cout << "Server C handled " << m << "  ";
        }
        else
            cout << "Server C passed " << m << "  ";
        ServidorDNS::handle(m); // 3. Delegate to the base class
        /*if (rand() % 5)
        {
            cout << "Server C passed " << m << "  ";
            ServidorDNS::handle(m);
        }
        else
            cout << "Server C handled " << m << "  ";*/
    }
};

class ServidorD: public ServidorDNS
{
public:
    Dominio d;
    ServidorD(){
        d.setIP("146.12.20.3");
        d.pushURL("www.miscursos.tec.com");
        d.pushURL("www.fifa.com");
    }
    /*virtual*/void handle(string m)
    {
        if (m=="www.miscursos.tec.com" || m=="www.fifa.com") {
            cout << "Server D handled " << m << "  ";
        }
        else
            cout << "Server D passed " << m << "  ";
        ServidorDNS::handle(m); // 3. Delegate to the base class
        /*if (rand() % 5)
        {
            cout << "Server D passed " << m << "  ";
            ServidorDNS::handle(m);
        }
        else
            cout << "Server D handled " << m << "  ";*/
    }
};

class ServidorE: public ServidorDNS
{
public:
    Dominio e;
    ServidorE(){
        e.setIP("124.70.20.100");
        e.pushURL("www.nfl.com");
        e.pushURL("www.espn.com");
    }
    /*virtual*/void handle(string m)
    {
        if (m=="www.nfl.com" || m=="www.espn.com") {
            cout << "Server E handled " << m << "  ";
        }
        else
            cout << "Server E passed " << m << "  ";
        ServidorDNS::handle(m); // 3. Delegate to the base class
        /*if (rand() % 5)
        {
            cout << "Server E passed " << m << "  ";
            ServidorDNS::handle(m);
        }
        else
            cout << "Server E handled " << m << "  ";*/
    }
};

int main()
{
   // srand(time(0));
    ServidorA one;
    ServidorB two;
    ServidorC thr;
    ServidorD four;
    ServidorE five;
    one.add(&two);
    one.add(&thr);
    one.add(&four);
    one.add(&five);
    
    //one.a.setIP("192.16.4.5");
    //one.a.pushURL("www.google.com");
    //one.a.pushURL("www.amazon.com");
    
    
    five.setNext(&one);
    
    string pag[5];
    pag[0]="www.google.com";
    pag[1]="www.forbes.com";
    pag[2]="www.facebook.com";
    pag[3]="www.fifa.com";
    pag[4]="www.nfl.com";
    
    for (int i = 0; i < 6; i++)
    {
        one.handle(pag[i]);
        cout << '\n';
    }
}
