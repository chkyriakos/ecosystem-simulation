#include "plants.h"



//---------------------------------------class Plant---------------------------------------

Plant::Plant(char t,string n,int l,float bp,float ip,int lf,int s)
{
    token=t;
    name=n;
    life=l;
    breedingProb=bp;
    illnessProb=ip;
    lifeFactor=lf;
    isAlive=true;
}

Plant::~Plant()
{

}

int Plant::LoseLife(int i)
{
    int j=i;
    if(!isAlive)
        return 0;
    if(token=='O'||token=='P'||token=='M')
    {
        if(getSeeds())
        {
            if(getSeeds()>=i)
            {
                setSeeds(getSeeds()-i);
                return(i);
            }
            else
            {
                i-=getSeeds();
                setSeeds(0);
                if(getFoliage()>=i)
                {
                    setFoliage(getFoliage()-i);
                    return j;
                }
                else
                {
                    j=i;
                    i-=getFoliage();
                    setFoliage(0);
                    isAlive=false;
                    return (j-i);
                }
            }
        }  
    }
    else
    {
        if(life<=i)
        {
            life-=i;
            return i;
        }
        else
        {
            i-=life;
            life=0;
            isAlive=false;
            return (j-i);
        }    
    }
    
    life-=i;
    if(!life)
    {
        isAlive=false;
    }
}

string Plant::getName()
{
    return name;
}

coordinates Plant::getPosition()
{
    return position;
}

char Plant::getToken()
{
    return token;
}

float Plant::getBreedingProb()
{
    return breedingProb;
}

float Plant::getIllnessProb()
{
    return illnessProb;
}

int Plant::getLife()
{
    return life;
}

int Plant::getLifeFactor()
{
    return lifeFactor;
}

int Plant::getSize()
{
    return size;
}

bool Plant::getIfAlive()
{
    return isAlive;
}

void Plant::setPosition(int x,int y)
{
    position.x=x;
    position.y=y;
}

void Plant::setLife(int i)
{
    life=i;
}

void Plant::setSize(int i)
{
    size=i;
}

void Plant::setIfAlive(bool i)
{
    isAlive=i;
}



//---------------------------------------class seedless--------------------------------------

seedless::seedless(char t,string n,int l,float bp,float ip,int lf) : Plant(t,n,l,bp,ip,lf,0)
{

}



//---------------------------class grass---------------------------

grass::grass() : seedless('G',"Grass",5,0.15,0.15,4)
{

}

//---------------------------class algae---------------------------

algae::algae() : seedless('A',"Algae",5,0.25,0.25,2)
{
    
}

//---------------------------------------class seeded----------------------------------------

seeded::seeded(char t,string n,int l,float bp,float ip,int lf,int f,int s,int si) : Plant(t,n,l,bp,ip,lf,si)
{
    foliage=f;
    seeds=s;
}

void seeded::setSeeds(int i)
{
    seeds=i;
}

int seeded::getSeeds()
{
    return seeds;
}

void seeded::setFoliage(int i)
{
    foliage=i;
}

int seeded::getFoliage()
{
    return foliage;
}

//---------------------------class oak----------------------------

oak::oak() : seeded('O',"Oak",45,0.2,0.2,15,30,15,5)
{

}

void oak::transition()
{
    srand(time(NULL));    
    if(((rand()%101)/100.0)>getIllnessProb())
    {
        setFoliage(getFoliage()+getLifeFactor());
        setSize(getSize()+1);
        setSeeds(getSeeds()+(getLifeFactor()*2));
        setLife(getLife()+(getLifeFactor()*3));
    }
    else
    {
        int i,j;
        i=j=getLifeFactor();
        if((getFoliage()-getLifeFactor())>=0)
        {
            setFoliage(getFoliage()+getLifeFactor());
            setSize(getSize()-1);
        }
        else
        {
            i=i-(i-getFoliage());
            setFoliage(0);
        }
        if((getSeeds()-(getLifeFactor()*2))>=0)
            setSeeds(getSeeds()+(getLifeFactor()*2));
        else
        {
            j=j-(j-getSeeds());
        }
        
        setLife(getLife()-(i+j));

        if (!getLife())
        {
            setIfAlive(false);
        }
    }
}

//---------------------------class pine---------------------------

pine::pine() : seeded('P',"Pine",60,0.15,0.15,20,40,20,5)
{

}

void pine::transition()
{
    srand(time(NULL));    
    if(((rand()%101)/100.0)>getIllnessProb())
    {
        setFoliage(getFoliage()+getLifeFactor());
        setSize(getSize()+1);
        setSeeds(getSeeds()+(getLifeFactor()*2));
        setLife(getLife()+(getLifeFactor()*3));
    }
    else
    {
        int i,j;
        i=j=getLifeFactor();
        if((getFoliage()-getLifeFactor())>=0)
        {
            setFoliage(getFoliage()+getLifeFactor());
            setSize(getSize()-1);
        }
        else
        {
            i=i-(i-getFoliage());
            setFoliage(0);
        }
        if((getSeeds()-(getLifeFactor()*2))>=0)
            setSeeds(getSeeds()+(getLifeFactor()*2));
        else
        {
            j=j-(j-getSeeds());
        }
        
        setLife(getLife()-(i+j));

        if (!getLife())
        {
            setIfAlive(false);
        }
    }
}

//---------------------------class maple---------------------------

maple::maple() : seeded('M',"Maple",30,0.05,0.05,10,20,10,2)
{

}

void maple::transition()
{
    srand(time(NULL));    
    if(((rand()%101)/100.0)>getIllnessProb())
    {
        setFoliage(getFoliage()+getLifeFactor());
        setSize(getSize()+1);
        setSeeds(getSeeds()+(getLifeFactor()*2));
        setLife(getLife()+(getLifeFactor()*3));
    }
    else
    {
        int i,j;
        i=j=getLifeFactor();
        if((getFoliage()-getLifeFactor())>=0)
        {
            setFoliage(getFoliage()+getLifeFactor());
            setSize(getSize()-1);
        }
        else
        {
            i=i-(i-getFoliage());
            setFoliage(0);
        }
        if((getSeeds()-(getLifeFactor()*2))>=0)
            setSeeds(getSeeds()+(getLifeFactor()*2));
        else
        {
            j=j-(j-getSeeds());
        }
        
        setLife(getLife()-(i+j));

        if (!getLife())
        {
            setIfAlive(false);
        }
    }
}