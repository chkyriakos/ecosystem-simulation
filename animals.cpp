#include "animals.h"


//--------------------------class animal--------------------------------

Animal::Animal(char t,string n,int si,int sp)
{
    token=t;
    hungerCount=0;
    eatenFood=0;
    eatCount=0;
    name=n;
    position.x=0;
    position.y=0;
    isAlive=true;
    isHungry=true;
    inHeat=false;
    hibernates=false;
    inHibernation=false;
    isAdult=false;
    moved=false;
}

Animal::~Animal()
{

}

coordinates* Animal::Move()
{

}

void Animal::Eat(Animal* animal)
{

}

void Animal::Eat(Plant* plant)
{

}

void Animal::Raise()
{

}

int Animal::getAttack()
{

}

int Animal::getDefence()
{
    
}

void Animal::initializenextday()
{
    if(!inHibernation)
    {
        if(isHungry)
        {
            hungerCount++;
            if(hungerCount>10)
            {
                setIfAlive(false);
            }
        }
        else
        {
            hungerCount=0;
        }
        isHungry=true;
        eatenFood=0;
        moved=false;
    }
    else
    {
        isHungry=false;
        hungerCount=0;
    }   
}

void Animal::setIfHungry(bool h)
{
    isHungry=h;
}

bool Animal::getIfHungry()
{
    return isHungry;
}

void Animal::setToken(char t)
{
    token=t;
}

char Animal::getToken()
{
    return token;
}

void Animal::setName(string n)
{
    name=n;
}

string Animal::getName()
{
    return name;
}

void Animal::setSize(int s)
{
    size=s;
}

int Animal::getSize()
{
    return size;
}

void Animal::initialHungerCount()
{
    hungerCount=0;
}

void Animal::increaseHungerCount(int i)
{
    hungerCount+=i;
}

int Animal::getHungerCount()
{
    return hungerCount;
}

void Animal::initialEatenFood()
{
    eatenFood=0;
}

void Animal::increaseEatenFood(int i)
{
    eatenFood+=i;
}

int Animal::getEatenFood()
{
    return eatenFood;
}

void Animal::initialEatCount()
{
    eatCount=0;
}

void Animal::increaseEatCount(int i)
{
    eatCount+=i;
}

void Animal::setposition(int x,int y)
{
    position.x=x;
    position.y=y;
}

coordinates Animal::getposition()
{
    return position;
}

void Animal::setIfAlive(bool a)
{
    isAlive=a;
}

bool Animal::getIfAlive()
{
    return isAlive;
}

void Animal::setIfinHeat(bool h)
{
    inHeat=h;
}

bool Animal::getIfinHeat()
{
    return inHeat;
}

void Animal::setIfHibernates(bool hi)
{
    hibernates=hi;
}

bool Animal::getIfHibernates()
{
    return hibernates;
}

void Animal::setIfinHibernation(bool hi)
{
    inHibernation=hi;
}

bool Animal::getIfinHibernation()
{
    return inHibernation;
}

void Animal::setSpeed(int sp)
{
    speed=sp;
}

int Animal::getSpeed()
{
    return speed;
}

void Animal::setAdult()
{
    isAdult=true;
}

bool Animal::getIfAdult()
{
    return isAdult;
}

coordinates* Animal::PositionPointer()
{
    return &position;
}

//------------------------class Herbivores------------------------------

Herbivores::Herbivores(string n,int si,int sp,int nf,bool c) : Animal('H',n,si,sp)
{
    neededFood=nf;
    canClimb=c;
}

Herbivores::~Herbivores()
{
    
}

void Herbivores::Raise()
{

}

void Herbivores::setCanClimb(bool i)
{
    canClimb=i;
}

bool Herbivores::getCanClimb()
{
    return canClimb;
}

void Herbivores::setNeededFood(int i)
{
    neededFood=i;
}

int Herbivores::getNeededFood()
{
    return neededFood;
}

//--------------------class Deer-----------------------

Deer::Deer(bool adult) : Herbivores("Deer",BABY_DEER_SIZE,BABY_DEER_SPEED,BABY_DEER_NEEDED_FOOD,DEER_CAN_CLIMB)
{
    if (adult)
    {
        setSize(DEER_SIZE);
        setSpeed(DEER_SPEED);
        setNeededFood(DEER_NEEDED_FOOD);
        setAdult();
    }
    
}

Deer::~Deer()
{

}

void Deer::Eat(Plant* plant)
{
    if(plant->getSize()<=(getSize()+4))
        if(getIfHungry())
            increaseEatenFood(plant->LoseLife(DEER_EAT_COUNT));
    if(getEatenFood()>=getNeededFood())
    {
        setIfHungry(false);
    }
}

void Deer::Raise()
{
    if(getSize()<DEER_SIZE)
    {
        if((getSize()+1)<=DEER_SIZE)
        {
            setSize(getSize()+1);
        }
        else
        {
            setSize(DEER_SIZE);
        }   
    }
    if(getSpeed()<DEER_SPEED)
    {
        if((getSpeed()+2)<=DEER_SPEED)
        {
            setSpeed(getSpeed()+2);
        }
        else
        {
            setSpeed(DEER_SPEED);
        }   
    }
    if(getNeededFood()<DEER_NEEDED_FOOD)
    {
        if((getNeededFood()+2)<=DEER_NEEDED_FOOD)
        {
            setNeededFood(getNeededFood()+2);
        }
        else
        {
            setNeededFood(DEER_NEEDED_FOOD);
        }
    }
    if(getSize()==DEER_SIZE && getSpeed()==DEER_SPEED && getNeededFood()==DEER_NEEDED_FOOD)
    {
        setAdult();
    }
}

//--------------------class Rabbit---------------------

Rabbit::Rabbit(bool adult) : Herbivores("Rabbit",BABY_RABBIT_SIZE,BABY_RABBIT_SPEED,BABY_RABBIT_NEEDED_FOOD,RABBIT_CAN_CLIMB)
{
    if (adult)
    {
        setSize(RABBIT_SIZE);
        setSpeed(RABBIT_SPEED);
        setNeededFood(RABBIT_NEEDED_FOOD);
        setAdult();
    }
}

Rabbit::~Rabbit()
{

}

void Rabbit::Eat(Plant* plant)
{
    if(plant->getToken()=='A')
        return;
    if(plant->getToken()=='O'||plant->getToken()=='P'||plant->getToken()=='M')
        if(plant->getSize()>getSize())
            return;
    if(getIfHungry())
        increaseEatenFood(plant->LoseLife(RABBIT_EAT_COUNT));

    if(getEatenFood()>=getNeededFood())
    {
        setIfHungry(false);
    }

}

void Rabbit::Raise()
{
    if(getSize()<RABBIT_SIZE)
    {
        if((getSize()+1)<=RABBIT_SIZE)
        {
            setSize(getSize()+1);
        }
        else
        {
            setSize(RABBIT_SIZE);
        }   
    }
    if(getSpeed()<RABBIT_SPEED)
    {
        if((getSpeed()+2)<=RABBIT_SPEED)
        {
            setSpeed(getSpeed()+2);
        }
        else
        {
            setSpeed(RABBIT_SPEED);
        }   
    }
    if(getNeededFood()<RABBIT_NEEDED_FOOD)
    {
        if((getNeededFood()+1)<=RABBIT_NEEDED_FOOD)
        {
            setNeededFood(getNeededFood()+1);
        }
        else
        {
            setNeededFood(RABBIT_NEEDED_FOOD);
        }
    }
    if(getSize()==RABBIT_SIZE && getSpeed()==RABBIT_SPEED && getNeededFood()==RABBIT_NEEDED_FOOD)
    {
        setAdult();
    }
}


//--------------------class GroundHog------------------

GroundHog::GroundHog(bool adult) : Herbivores("GroundHog",BABY_GROUNDHOG_SIZE,BABY_GROUNDHOG_SPEED,BABY_GROUNDHOG_NEEDED_FOOD,false)
{
    setIfHibernates(GROUNDHOG_HIBERNATATION);
    if (adult)
    {
        setSize(GROUNDHOG_SIZE);
        setSpeed(GROUNDHOG_SPEED);
        setNeededFood(GROUNDHOG_NEEDED_FOOD);
        setCanClimb(GROUNDHOG_CAN_CLIMB);
        setAdult();
    }
}

GroundHog::~GroundHog()
{

}

void GroundHog::Eat(Plant* plant)
{

    if(plant->getToken()=='A')
        return;
    if(plant->getToken()=='O'||plant->getToken()=='P'||plant->getToken()=='M')
    {
        if(getCanClimb())
        {
            if(plant->getSize()>(getSize()*3))
            {
                return;
            }                                
        }
        else
        {
            if(plant->getSize()>(getSize()))
            {
                return;
            }
        }
    }
    if(getIfHungry())
        increaseEatenFood(plant->LoseLife(GROUNDHOG_EAT_COUNT));

    if(getEatenFood()>=getNeededFood())
    {
        setIfHungry(false);
    }
}

void GroundHog::Raise()
{
    if(getSize()<GROUNDHOG_SIZE)
    {
        if((getSize()+1)<=GROUNDHOG_SIZE)
        {
            setSize(getSize()+1);
        }
        else
        {
            setSize(GROUNDHOG_SIZE);
        }   
    }
    if(getSpeed()<GROUNDHOG_SPEED)
    {
        if((getSpeed()+1)<=GROUNDHOG_SPEED)
        {
            setSpeed(getSpeed()+1);
        }
        else
        {
            setSpeed(GROUNDHOG_SPEED);
        }   
    }
    if(getNeededFood()<GROUNDHOG_NEEDED_FOOD)
    {
        if((getNeededFood()+1)<=GROUNDHOG_NEEDED_FOOD)
        {
            setNeededFood(getNeededFood()+1);
        }
        else
        {
            setNeededFood(GROUNDHOG_NEEDED_FOOD);
        }   
    }
    if(getSize()==GROUNDHOG_SIZE && getSpeed()==GROUNDHOG_SPEED && getNeededFood()==GROUNDHOG_NEEDED_FOOD)
    {
        setCanClimb(true);
        setAdult();
    }
}


//---------------------class Salmon--------------------

Salmon::Salmon(bool adult) : Herbivores("Salmon",SALMON_SIZE,SALMON_SPEED,SALMON_NEEDED_FOOD,SALMON_CAN_CLIMB)
{
    setAdult();
}

Salmon::~Salmon()
{

}

void Salmon::Eat(Plant* plant)
{
    if(getIfHungry())
        increaseEatenFood(plant->LoseLife(SALMON_EAT_COUNT));

    if(getEatenFood()>=getNeededFood())
    {
        setIfHungry(false);
    }
}

//------------------------class Carnivores------------------------------

Carnivores::Carnivores(string n,int si,int sp,int a,int d) : Animal('C',n,si,sp)
{
    attack=a;
    defence=d;
}

Carnivores::~Carnivores()
{

}

void Carnivores::setAttack(int i)
{
    attack=i;
}

int Carnivores::getAttack()
{
    return attack;
}

void Carnivores::setDefence(int i)
{
    defence=i;
}

int Carnivores::getDefence()
{
    return defence;
}

//--------------------class Fox-------------------------

Fox::Fox(bool adult) : Carnivores("Fox",BABY_FOX_SIZE,BABY_FOX_SPEED,BABY_FOX_ATTACK,BABY_FOX_DEFENCE)
{
    if (adult)
    {
        setSize(FOX_SIZE);
        setSpeed(FOX_SPEED);
        setAttack(FOX_ATTACK);
        setDefence(FOX_DEFENCE);
        setAdult();
    }

}

Fox::~Fox()
{

}

void Fox::Eat(Animal* animal)
{
    if(getIfHungry())
    {
        if(animal->getToken()=='H')
        {
            if(animal->getName()=="Salmon")
            {
                return;
            }
            if(animal->getSize()<=getSize() && animal->getSpeed()<getSpeed())
            {
                animal->setIfAlive(false);
                setIfHungry(false);
                return;
            }
        }
        else
        {
            if(getHungerCount()>8)
            {
                if((animal->getSize()<getSize())||(animal->getSize()==getSize() && animal->getDefence()<getAttack()))
                {
                    animal->setIfAlive(false);
                    setIfHungry(false);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        
    }
}

void Fox::Raise()
{
    if(getSize()<FOX_SIZE)
    {
        if((getSize()+1)<=FOX_SIZE)
        {
            setSize(getSize()+1);
        }
        else
        {
            setSize(FOX_SIZE);
        }   
    }
    if(getSpeed()<FOX_SPEED)
    {
        if((getSpeed()+1)<=FOX_SPEED)
        {
            setSpeed(getSpeed()+1);
        }
        else
        {
            setSpeed(FOX_SPEED);
        }   
    }
    if(getAttack()<FOX_ATTACK)
    {
        if((getAttack()+1)<=FOX_ATTACK)
        {
            setAttack(getAttack()+1);
        }
        else
        {
            setAttack(FOX_ATTACK);
        }   
    }
    if(getDefence()<FOX_DEFENCE)
    {
        if((getDefence()+1)<=FOX_DEFENCE)
        {
            setDefence(getDefence()+1);
        }
        else
        {
            setDefence(FOX_DEFENCE);
        }   
    }
    if(getSize()==FOX_SIZE && getSpeed()==FOX_SPEED && getAttack()==FOX_ATTACK && getDefence()==FOX_DEFENCE)
    {
        setAdult();
    }
}

//--------------------class Wolf------------------------

Wolf::Wolf(bool adult) : Carnivores("Wolf",BABY_WOLF_SIZE,BABY_WOLF_SPEED,BABY_WOLF_ATTACK,BABY_WOLF_DEFENCE)
{
    if(adult)
    {
        setSize(WOLF_SIZE);
        setSpeed(WOLF_SPEED);
        setAttack(WOLF_ATTACK);
        setDefence(WOLF_DEFENCE);
        setAdult();
    }
}

Wolf::~Wolf()
{

}

void Wolf::Eat(Animal* animal)
{
    if(getIfHungry())
    {
        if(animal->getToken()=='H')
        {
            if(animal->getName()=="Salmon")
            {
                return;
            }
            if(animal->getSize()<=getSize() && animal->getSpeed()<getSpeed())
            {
                animal->setIfAlive(false);
                setIfHungry(false);
                return;
            }
        }
        else
        {
            if(getHungerCount()>8)
            {
                if((animal->getSize()<getSize())||(animal->getSize()==getSize() && animal->getDefence()<getAttack()))
                {
                    animal->setIfAlive(false);
                    setIfHungry(false);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        
    } 
} 

void Wolf::Raise()
{
    if(getSize()<WOLF_SIZE)
    {
        if((getSize()+1)<=WOLF_SIZE)
        {
            setSize(getSize()+1);
        }
        else
        {
            setSize(WOLF_SIZE);
        }   
    }
    if(getSpeed()<WOLF_SPEED)
    {
        if((getSpeed()+2)<=WOLF_SPEED)
        {
            setSpeed(getSpeed()+2);
        }
        else
        {
            setSpeed(WOLF_SPEED);
        }   
    }
    if(getAttack()<WOLF_ATTACK)
    {
        if((getAttack()+2)<=WOLF_ATTACK)
        {
            setAttack(getAttack()+2);
        }
        else
        {
            setAttack(WOLF_ATTACK);
        }   
    }
    if(getDefence()<WOLF_DEFENCE)
    {
        if((getDefence()+2)<=WOLF_DEFENCE)
        {
            setDefence(getDefence()+2);
        }
        else
        {
            setDefence(WOLF_DEFENCE);
        }   
    }
    if(getSize()==WOLF_SIZE && getSpeed()==WOLF_SPEED && getAttack()==WOLF_ATTACK && getDefence()==WOLF_DEFENCE)
    {
        setAdult();
    }
}

//--------------------class Bear------------------------

Bear::Bear(bool adult) : Carnivores("Bear",BABY_BEAR_SIZE,BABY_BEAR_SPEED,BABY_BEAR_ATTACK,BABY_BEAR_DEFENCE)
{
    setIfHibernates(BEAR_HIBERNATION);
    if(adult)
    {
        setSize(BEAR_SIZE);
        setSpeed(BEAR_SPEED);
        setAttack(BEAR_ATTACK);
        setDefence(BEAR_DEFENCE);
        setAdult();
    }
}

Bear::~Bear()
{

}

void Bear::Eat(Animal* animal)
{
    bool adult=false;
    if(getSize()==BEAR_SIZE && getAttack()==BEAR_ATTACK && getDefence()==BEAR_DEFENCE)
    {
        adult=true;
    }
    if(getIfHungry())
    {
        if(animal->getToken()=='H')
        {
            if(adult)
            {
                animal->setIfAlive(false);
                setIfHungry(false);
                return;
            }
            else if(animal->getSize()<=getSize() && animal->getSpeed()<getSpeed())
            {
                animal->setIfAlive(false);
                setIfHungry(false);
                return;
            }
        }
        else
        {   
            if(getName()=="Bear")
            {
                return;
            }
            if(getHungerCount()>8)
            {
                if(adult)
                {
                    animal->setIfAlive(false);
                    setIfHungry(false);
                    return;
                }                
                else if((animal->getSize()<getSize())||(animal->getSize()==getSize() && animal->getDefence()<getAttack()))
                {
                    animal->setIfAlive(false);
                    setIfHungry(false);
                    return;
                }
                else
                {
                    return;
                }
            }
        }
        
    } 
} 

void Bear::Raise()
{
    if(getSize()<BEAR_SIZE)
    {
        if((getSize()+2)<=BEAR_SIZE)
        {
            setSize(getSize()+2);
        }
        else
        {
            setSize(BEAR_SIZE);
        }   
    }
    if(getSpeed()<BEAR_SPEED)
    {
        if((getSpeed()+2)<=BEAR_SPEED)
        {
            setSpeed(getSpeed()+2);
        }
        else
        {
            setSpeed(BEAR_SPEED);
        }   
    }
    if(getAttack()<BEAR_ATTACK)
    {
        if((getAttack()+2)<=BEAR_ATTACK)
        {
            setAttack(getAttack()+2);
        }
        else
        {
            setAttack(BEAR_ATTACK);
        }   
    }
    if(getDefence()<BEAR_DEFENCE)
    {
        if((getDefence()+2)<=BEAR_DEFENCE)
        {
            setDefence(getDefence()+2);
        }
        else
        {
            setDefence(BEAR_DEFENCE);
        }   
    }
    if(getSize()==BEAR_SIZE && getSpeed()==BEAR_SPEED && getAttack()==BEAR_ATTACK && getDefence()==BEAR_DEFENCE)
    {
        setAdult();
    }
}

