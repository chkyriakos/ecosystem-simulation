#include "global.h"

//---------------------------------------class Plant---------------------------------------

class Plant
{
        string name;
        coordinates position;
        char token;
        float breedingProb;
        float illnessProb;
        int life;
        int lifeFactor;
        int size;
        bool isAlive;
    public:
        Plant(char t,string n,int l,float bp,float ip,int lf,int s);
        ~Plant();
        int LoseLife(int i);
        string getName();
        coordinates getPosition();
        virtual int getSeeds(){};
        virtual int getFoliage(){};
        virtual void setSeeds(int i){};
        virtual void setFoliage(int i){};
        virtual void transition(){};

        char getToken();
        float getBreedingProb();
        float getIllnessProb();
        int getLife();
        int getLifeFactor();
        int getSize();
        bool getIfAlive();

        void setPosition(int x,int y);
        void setLife(int i);
        void setSize(int i);
        void setIfAlive(bool i);

};

//---------------------------------------class seedless--------------------------------------

class seedless : public Plant
{
    public:
        seedless(char t,string n,int l,float bp,float ip,int lf);
        ~seedless();
};

//---------------------------class grass---------------------------

class grass : public seedless
{
    public:
        grass();
        ~grass();
};

//---------------------------class algae---------------------------

class algae : public seedless
{
    public:
        algae();
        ~algae();
};

//---------------------------------------class seeded----------------------------------------

class seeded : public Plant
{
        int seeds;
        int foliage;
    public:
        seeded(char t,string n,int l,float bp,float ip,int lf,int f,int s,int si);
        ~seeded();
        virtual void transition()=0;
        
        void setSeeds(int i);
        int getSeeds();
        void setFoliage(int i);
        int getFoliage();
        
};

//---------------------------class oak----------------------------

class oak : public seeded
{
    public:
        oak();
        ~oak();
        void transition();
};

//---------------------------class pine----------------------------

class pine : public seeded
{
    public:
        pine();
        ~pine();
        void transition();
};

//---------------------------class maple---------------------------

class maple : public seeded
{
    public:
        maple();
        ~maple();
        void transition();
};