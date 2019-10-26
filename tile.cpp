#include "tile.h"

Tile::Tile()
{
    token='-';
    plant=NULL;
}

Tile::~Tile()
{

}

void Tile::setToken(char t)
{
    token=t;
}

void Tile::setCoordinates(int x,int y)
{
    position.x=x;
    position.y=y;
}

char Tile::getToken()
{
    return token;
}

void Tile::printToken()
{
    cout<<token;
}

void Tile::printPlantToken()
{
    if(plant!=NULL)
        cout<<plant->getToken();
    else
        printToken();   
}

void Tile::setPlant(Plant* p)
{
    plant=p;
}

Plant* Tile::getPlant()
{
    return plant;
}

void Tile::setAnimal(Animal* a)
{
    a->setposition(position.x,position.y);
    animals.push_back(a);
}

int Tile::getNumberofAnimals()
{
    return animals.size();
}



void Tile::AnimalsGrowth()
{
    for(int i=0;i<getNumberofAnimals();i++)
        animals[i]->Raise();
}

void Tile::PlantGrowth()
{
    if(plant!=NULL)
        plant->transition();
}

void Tile::Eat()
{
    for (int i=0;i<animals.size();i++)
    {
        if(animals[i]->getIfinHibernation()==false)
        {
            if(animals[i]->getIfHungry())
            {
                if(animals[i]->getToken()=='H')
                {
                    if(animals[i]->getHungerCount()>7)
                        if(getPlant()!=NULL)
                        {
                            animals[i]->Eat(plant);
                        }
                }
                else
                {
                    for (int j=0;j<animals.size();j++)  //search for herbivore
                    {
                        if(animals[j]->getToken()=='H')
                        {
                            if(animals[j]->getIfinHibernation()==false)
                            {
                                animals[i]->Eat(animals[j]);
                            }
                        }                    
                    }
                    if(animals[i]->getIfHungry())
                    {
                        if(animals[i]->getHungerCount()>8)
                        {
                            for(int j=0;j<animals.size();j++)
                            {
                                if(animals[j]->getIfinHibernation()==false)
                                {
                                    if(i!=j)
                                    {
                                        animals[i]->Eat(animals[j]);
                                    }
                                }
                            }
                        }
                    }    
                }
            }
        }
    }
}



Animal* Tile::getHerbivore()
{
    for(int i=0;i<getNumberofAnimals();i++)
    {  
        if(animals[i]->getToken()=='H')
            return animals[i];
    }
    return NULL;
}

Animal* Tile::getCarnivore(int n)
{
    for(int i=0;i<getNumberofAnimals();i++)
    {  
        if(animals[i]->getToken()=='C')
            if(i!=n)
                return animals[i];
    }
    return NULL;
}

vector <Animal*> Tile::Move()
{
    vector <Animal*> A;
    vector <int> n;
    coordinates* newPosition;
    for(int i=0;i<animals.size();i++)
    {
        if(animals[i]->moved==false)
        {
            if(animals[i]->getIfinHibernation()==false)
            {
                newPosition=animals[i]->Move();
                if((newPosition->x!=position.x) || newPosition->y!=position.y)
                {
                    A.push_back(animals[i]);
                    n.push_back(i);
                }
            }
        }    
    }
    for(int i=n.size()-1;i>=0;i--)
    {
        animals[n[i]]->moved=true;
        animals.erase(animals.begin()+n[i]);
    }
    return A;
}

void Tile::setHiberation(bool h)
{
    if(h)
    {
        for(int i=0;i<getNumberofAnimals();i++)
        {
            if(animals[i]->getIfHibernates()==true)
            {
                animals[i]->setIfinHibernation(true);
            }
        }
    }
    else
    {
        for(int i=0;i<getNumberofAnimals();i++)
        {
            if(animals[i]->getName()=="Bear")
            {
                animals[i]->setIfinHibernation(false);
            }
            if(animals[i]->getName()=="GroundHog")
            {
                animals[i]->setIfinHibernation(false);
            }
        }
    }
}

void Tile::DailyReset()
{
    for(int i=0;i<getNumberofAnimals();i++)
    {
        animals[i]->initializenextday();
    }
}