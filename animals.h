#include "plants.h"

//-------------------------------------------------------class animal--------------------------------

class Ecosystem;

class Animal
{
        char token;
        string name;
        int size;
        int hungerCount;    //how many days it was unfed
        int eatenFood;
        int eatCount;       //unit of food per hour
        coordinates position;
        bool isAlive;
        bool isHungry;
        bool inHeat;        //breeding season?//Περιοδος αναπαραγωγης?
        bool hibernates;    //is animal that fall in hibernation?//Χειμερια ναρκη
        bool inHibernation; //is in hiberntion?//Χειμερια ναρκη
        int speed;
        bool isAdult;
    public:
        bool moved;
        static Ecosystem* Ecosys;               
        Animal(char t,string n,int si,int sp);
        ~Animal();
        virtual coordinates* Move()=0;          //implementation in Ecosystem.cpp
        virtual void Eat(Animal* animal);
        virtual void Eat(Plant* plant);
        virtual void Raise();
        virtual int getAttack();
        virtual int getDefence();
        void initializenextday();
        void setIfHungry(bool h);
        bool getIfHungry();
        void setToken(char t);
        char getToken();
        void setName(string n);
        string getName();
        void setSize(int s);
        int getSize();
        void initialHungerCount();
        void increaseHungerCount(int i);
        int getHungerCount();
        void initialEatenFood();
        void increaseEatenFood(int i);
        int getEatenFood();
        void initialEatCount();
        void increaseEatCount(int i);
        int getEatCount();
        void setposition(int x,int y);
        coordinates getposition();
        void setIfAlive(bool a);
        bool getIfAlive();
        void setIfinHeat(bool h);
        bool getIfinHeat();
        void setIfHibernates(bool hi);
        bool getIfHibernates();
        void setIfinHibernation(bool hi);
        bool getIfinHibernation();
        void setSpeed(int sp);
        int getSpeed();
        void setAdult();
        bool getIfAdult();
        void setTerrainSize();
        coordinates* PositionPointer();    
};

//------------------------------------------------------class Herbivores------------------------------

class Herbivores : public Animal
{
        bool canClimb;
        int neededFood;
    public:
        Herbivores(string n,int si,int sp,int nf,bool c);
        ~Herbivores();
        virtual void Eat(Plant* plant)=0;
        virtual void Raise()=0;
        virtual coordinates* Move()=0;
        void setCanClimb(bool i);
        bool getCanClimb();
        void setNeededFood(int i);
        int getNeededFood();
};

//--------------------class Deer-----------------------

class Deer : public Herbivores
{
    public:
        Deer(bool adult);
        ~Deer();
        void Eat(Plant* plant);
        void Raise();
        coordinates* Move();
};

//--------------------class Rabbit---------------------

class Rabbit : public Herbivores
{
    public:
        Rabbit(bool aduld);
        ~Rabbit();
        void Eat(Plant* plant);
        void Raise();
        coordinates* Move();
};

//--------------------class GroundHog------------------

class GroundHog : public Herbivores
{
    public:
        GroundHog(bool adult);
        ~GroundHog();
        void Eat(Plant* plant);
        void Raise();
        coordinates* Move();
};

//--------------------class Salmon---------------------

class Salmon : public Herbivores
{
    public:
        Salmon(bool adult);
        ~Salmon();
        void Eat(Plant* plant);
        void Raise(){};
        coordinates* Move();
};

//------------------------------------------------------class Carnivores------------------------------

class Carnivores : public Animal
{
        int attack;
        int defence;
    public:
        Carnivores(string n,int si,int sp,int a,int d);
        ~Carnivores();
        virtual void Eat(Animal* animal)=0;
        virtual void Raise()=0;
        virtual coordinates* Move()=0;
        void setAttack(int i);
        void setDefence(int i);
        int getAttack();
        int getDefence();

};

//--------------------class Fox-------------------------

class Fox : public Carnivores
{
    public:
        Fox(bool adult);
        ~Fox();
        void Eat(Animal* animal);
        void Raise();
        coordinates* Move();
};

//--------------------class Wolf------------------------

class Wolf : public Carnivores
{
    public:
        Wolf(bool adult);
        ~Wolf();
        void Eat(Animal* animal);
        void Raise();
        coordinates* Move();
};

//--------------------class Bear------------------------

class Bear : public Carnivores
{
    public:
        Bear(bool adult);
        ~Bear();
        void Eat(Animal* animal);
        void Raise();
        coordinates* Move();
};