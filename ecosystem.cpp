#include "ecosystem.h"

Ecosystem::Ecosystem(int s)
{
    terrainSize=s;
    water=0;
    hills=0;
    meadow=0;
    

//num of plants in ecosystem
    sumOfPlants=0;
    sumOfGrass=0;
    sumOfAlgae=0;
    sumOfMaple=0;
    sumOfPine=0;
    sumOfOak=0;

//num o animals in ecosystem
    sumOfAnimals=0;
    sumOfHerbivores=0;
    sumOfCarnivores=0;
    sumOfDeer=0;
    sumOfRabbit=0;
    sumOfSalmon=0;
    sumOfGroundHog=0;
    sumOfFox=0;
    sumOfWolf=0;
    sumOfBear=0;

    MapGenerator();
    PlaceEntities();
}

Ecosystem::~Ecosystem()
{
    for(int i=terrainSize-1;i>=0;i--)
    {
        delete[] terrain[i];
    }
    delete[] terrain;
}

void Ecosystem::GenerateRiver()
{
    srand(time(NULL));
    int x,y;
    int deflectionProbability;
    int deflectionRoute;                 //right:1    left:0
    int deflectionSize;
    x=rand()%(terrainSize-9)+5;
    y=0;
    terrain[x][y].setToken('#'); 
    water++; 
    y++;
    terrain[x][y].setToken('#');
    water++;  
    do
    {
        deflectionProbability=(rand()%101)/100.0;
        if(deflectionProbability<=0.3)
        {
            deflectionRoute=rand()%2;
            if(!deflectionRoute)
            {
                deflectionRoute--;
            }
            deflectionSize=rand()%2+1;
            for(int i=1;i<=deflectionSize;i++)
            {
                if((x+deflectionRoute)>=0 && (x+deflectionRoute)<terrainSize)
                {
                    x=x+deflectionRoute;
                    terrain[x][y].setToken('#'); 
                    water++;
                }
            }
            y++;
            terrain[x][y].setToken('#'); 
            water++;
        }
        if(!(y < terrainSize-1 && x>0 && x<terrainSize-1))
            break;
        y++;
        terrain[x][y].setToken('#');
        water++;
    }while((y < terrainSize-1) && (x>0) && (x<terrainSize-1));


}


void Ecosystem::GenerateLake()
{
    int x,y,i,j;
    srand(time(NULL));
    lakeSize=rand()%rand()%(terrainSize-7)+2;
    x=rand()%(terrainSize-lakeSize);
    y=rand()%(terrainSize-lakeSize);

        for(i=x;i<(lakeSize+x);i++)
        {
            for(j=y;j<(lakeSize+y);j++)
            {
                if(terrain[i][j].getToken()!='#')
                {
                    terrain[i][j].setToken('#');
                    water++;
                }            
            }
        }    
}

void Ecosystem::GenerateHills()
{
    int x,y,i=0,j=0,c;
    bool canPlace;
    int Hillsize;
    srand(time(NULL));
    int NumOfHills=rand()%(terrainSize/5)+1;
    for(c=1;c<=NumOfHills;c++)
    {
        do
        {
            canPlace=true;
            Hillsize=rand()%3 +2;
            x=rand()%(terrainSize-Hillsize);
            y=rand()%(terrainSize-Hillsize);
    
            for(i=x;i<Hillsize+x;i++)
            {
                for(j=y;j<Hillsize+y;j++)
                {
                    if(terrain[i][j].getToken()=='#')
                    {
                        canPlace=false;
                        break;
                    }
                }
                if (canPlace==false)
                {
                    break;
                }
            }    
        }while(canPlace==false);
        for(i=x;i<Hillsize+x;i++)
        {
            for(j=y;j<Hillsize+y;j++)
            {   
                if(terrain[i][j].getToken()!='^')
                {                    
                    terrain[i][j].setToken('^');
                    hills++;
                }
            }
        }    
    }

}

void Ecosystem::GenerateMeadow()
{
    int i,j;
    for(i=0;i<terrainSize;i++)
        for(j=0;j<terrainSize;j++)
        {
            if(terrain[i][j].getToken()=='-')
            {
                terrain[i][j].setToken('"');
                meadow++;
            }
        }
}

void Ecosystem::PlacePlants()
{
    int i,j,a,b,c,x,y;
    bool canPlace;
    srand(time(NULL));
    vector <Plant*> plants;
    
    //--------------------//plants in water
    
    for(x=0;x<terrainSize;x++)
    {
        for(y=0;y<terrainSize;y++)
        {
            if(terrain[x][y].getToken()=='#')
            {
                terrain[x][y].setPlant(new algae);
                sumOfAlgae++;
            }
        }
    }
    sumOfPlants+=sumOfAlgae;
    //Print();

    //-------------------------//plants on hills

    b=hills/2; //num of pines on hills
    sumOfPine+=b;
    sumOfPlants+=b;
    for(i=1;i<=b;i++)
    {
        plants.push_back(new pine);
    }


    a=hills/4; //num of maples on hills
    sumOfMaple+=a;
    sumOfPlants+=a;
    for(i=1;i<=a;i++)
    {
        plants.push_back(new maple);
    }

    for(i=0;i<plants.size();i++)       //placing on hills
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getPlant()==NULL)
            {
                if(terrain[x][y].getToken()=='^')
                {
                    canPlace=true;
                }
            }    
        }while(canPlace==false);
        terrain[x][y].setPlant(plants[i]);
    }
    plants.clear();
    //Print();

    //-------------------------//plants on meadow


    b=meadow/3;    //num of maple on meadow
    sumOfMaple+=b;
    sumOfPlants+=b;
    for(i=1;i<=b;i++)
    {
        plants.push_back(new maple);
    }
    c=meadow/2;    //num of oak   on meadow
    sumOfOak+=c;
    sumOfPlants+=c;
    for(i=1;i<=c;i++)
    {
        plants.push_back(new oak);
    }
    for(i=0;i<plants.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getPlant()==NULL)
            {
                if(terrain[x][y].getToken()=='"')
                {
                    canPlace=true;
                }    
            }
        }while(canPlace==false);
        terrain[x][y].setPlant(plants[i]);
    }
    plants.clear();

    for(x=0;x<terrainSize;x++)
    {
        for(y=0;y<terrainSize;y++)
        {
            if(terrain[x][y].getToken()=='"')
            {
                if(terrain[x][y].getPlant()==NULL)
                {
                    terrain[x][y].setPlant(new grass);
                    sumOfGrass++;
                    sumOfPlants++;
                }
            }
        }
    }
}

void Ecosystem::PlaceAnimals()
{
    int i,j,a,b,c,x,y;
    bool canPlace;
    srand(time(NULL));
    vector <Animal*> Animals;

    //--------------------//animals in water 

    a=rand()%3+10;        //num of salmons
    sumOfSalmon+=a;
    sumOfAnimals+=a;
    sumOfHerbivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Salmon(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on water
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='#')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    //-------------------------//animals on hills

    a=rand()%2+1;              //num of wolf on hills
    sumOfWolf+=a;
    sumOfAnimals+=a;
    sumOfCarnivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Wolf(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on hills
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='^')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    a=terrainSize;      //num of bear on hills
    sumOfBear+=a;
    sumOfAnimals+=a;
    sumOfCarnivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Bear(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on hills
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='^')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

//-------------------------//animals on meadow

    a=terrainSize*2;              //num of deer on meadow
    sumOfDeer+=a;
    sumOfAnimals+=a;
    sumOfHerbivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Deer(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='"')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    a=terrainSize*2;              //num of Rabbit on meadow
    sumOfRabbit+=a;
    sumOfAnimals+=a;
    sumOfHerbivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Rabbit(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='"')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    a=terrainSize*2;              //num of groundhog on meadow
    sumOfGroundHog+=a;
    sumOfAnimals+=a;
    sumOfHerbivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new GroundHog(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='"')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    a=terrainSize;              //num of fox on meadow
    sumOfFox+=a;
    sumOfAnimals+=a;
    sumOfCarnivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Fox(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='"')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();

    a=terrainSize;              //num of wolf on meadow
    sumOfWolf+=a;
    sumOfAnimals+=a;
    sumOfCarnivores+=a;
    for(i=1;i<=a;i++)
    {
        Animals.push_back(new Wolf(ADULT));
    }
    for(i=0;i<Animals.size();i++)       //placing on meadow
    {
        do
        {
            canPlace=false;
            x=rand()%(terrainSize);
            y=rand()%(terrainSize);
            if(terrain[x][y].getToken()=='"')
            {
                canPlace=true;
            }
        }while(canPlace==false);
        terrain[x][y].setAnimal(Animals[i]);
    }
    Animals.clear();
}

void Ecosystem::PrintTerrain()
{
    int i,j;
    for(i=0;i<terrainSize;i++)
    {
        for(j=0;j<terrainSize;j++)
        {
            terrain[j][i].printToken();
            cout<<"  ";
        }
        cout<<endl;
    }
}

void Ecosystem::PrintPlants()
{
    for(int i=0;i<terrainSize;i++)
    {
        for(int j=0;j<terrainSize;j++)
        {
            if(terrain[j][i].getPlant()==NULL)
            {
                terrain[j][i].printToken();
                cout<<"  ";
            }
            else
            {
                terrain[j][i].printPlantToken();
                cout<<"  ";
            }
        }
        cout<<endl;
    }
}

void Ecosystem::PrintSumOfEntities()
{
    //num of plants in ecosystem
    cout << "Sum of Plants : " << sumOfPlants  << endl;
    cout << "Sum of Animals: " << sumOfAnimals << endl;
    cout << "       Sum of Herbivores: " << sumOfHerbivores << endl;
    cout << "       Sum of Carnivores: " << sumOfCarnivores << endl;
    cout << endl;
    cout << endl;
    cout << "Plants :" << endl;
    cout << "--------" << endl;
    cout << "Grass     : " << sumOfGrass  << endl;
    cout << "Algae     : " << sumOfAlgae  << endl;
    cout << "Maple     : " << sumOfMaple  << endl;
    cout << "Pine      : " << sumOfPine   << endl;
    cout << "Oak       : " << sumOfOak    << endl;

    //num o animals in ecosystem
    cout << "Animals:" << endl;
    cout << "--------" << endl;
    cout << "Deer      : " << sumOfDeer       << endl;
    cout << "Rabbit    : " << sumOfRabbit     << endl;
    cout << "Groundhog : " << sumOfGroundHog  << endl;
    cout << "Salmon    : " << sumOfSalmon     << endl;
    cout << "Fox       : " << sumOfFox        << endl;
    cout << "Wolf      : " << sumOfWolf       << endl;
    cout << "Bear      : " << sumOfBear       << endl; 
}

void Ecosystem::PrintNumOfAnimals()
{
    for(int y=0;y<terrainSize;y++)
    {
        for(int x=0;x<terrainSize;x++)
        {
            if(terrain[x][y].getNumberofAnimals()<10)
            {
                cout<<0<<terrain[x][y].getNumberofAnimals()<<" ";
            }
            else
            {
                cout<<terrain[x][y].getNumberofAnimals()<<" ";
            }
        }
        cout<<endl;
    }
}

void Ecosystem::PrintSystem()
{
    cout << "Terrain" << endl;
    PrintTerrain();
    cout << endl;
    cout << "Plants"  << endl;
    PrintPlants();
    cout << endl;
    cout<<"Animals"<<endl;
    PrintNumOfAnimals();
    cout<<endl;
    cout << "Entities"<< endl;
    PrintSumOfEntities();
    cout << endl;
}

int Ecosystem::getTerrainSize()
{
    return terrainSize;
}

Tile*** Ecosystem::getTerrain()
{
    return &terrain;
}
void Ecosystem::MapGenerator()
{
    terrain=new Tile*[terrainSize];
    for(int i=0;i<terrainSize;i++)
    {
        terrain[i]=new Tile[terrainSize];
    }
    for(int x=0;x < terrainSize;x++)
    {
        for(int y=0;y < terrainSize;y++)
        {
            terrain[x][y].setCoordinates(x,y);
        }
    }
    GenerateRiver();
    GenerateLake();
    GenerateHills();
    GenerateMeadow();
}

void Ecosystem::PlaceEntities()
{
    PlacePlants();
    PlaceAnimals();
}

void Ecosystem::AnimalsGrowth()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].AnimalsGrowth();
        }
    }
}

void Ecosystem::PlantGrowth()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].PlantGrowth();
        }
    }
}

void Ecosystem::PlantBreeding()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].PlantBreeding();
        }
    }
}

void Ecosystem::HerbivoresBreeding()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].HerbivoresBreeding();
        }
    }
}

void Ecosystem::CarnivoresBreeding()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].CarnivoresBreeding();
        }
    }
}

void Ecosystem::DailyReset()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].DailyReset();
        }
    }
}

void Ecosystem::Eat()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].Eat();
        }
    }
}

void Ecosystem::CheckDeadEntities()
{
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            terrain[x][y].DeleteDeadEntities();
        }
    }
}

void Ecosystem::ApplySeason()
{
    Season++;
    if(Season==5)
    {
        Season=1;
    }
    if(Season==1)
    {
        for(int x=0;x<terrainSize;x++)
        {
            for(int y=0;y<terrainSize;y++)
            {
                terrain[x][y].setHiberation(true);
            }
        }
    }
    if(Season==2)
    {
        for(int x=0;x<terrainSize;x++)
        {
            for(int y;y<terrainSize;y++)
            {
                terrain[x][y].setHiberation(false);
            }
        }
    }

        if(Season==1){
        growthPeriodPlants = 10;
        growthPeriodAnimals = 30;
        breedingRepPeriodPlants = 0;
        breedingRepPeriodHerb = 18;
        breedingRepPeriodCarn = 10;
    }
    else if(Season==2){
        growthPeriodPlants = 5;
        growthPeriodAnimals = 20;
        breedingRepPeriodPlants = 10;
        breedingRepPeriodHerb = 12;
        breedingRepPeriodCarn = 11;
    }
    else if(Season==3){
        growthPeriodPlants = 10;
        growthPeriodAnimals = 30;
        breedingRepPeriodPlants = 10;
        breedingRepPeriodHerb = 8;
        breedingRepPeriodCarn = 9;
    }
    else{
        growthPeriodPlants = 0;
        growthPeriodAnimals = 15;
        breedingRepPeriodPlants = 20;
        breedingRepPeriodHerb = 5;
        breedingRepPeriodCarn = 9;
    }   
}

void Ecosystem::Move()
{
    vector <Animal*> animals;
    for(int x=0;x<terrainSize;x++)
    {
        for(int y=0;y<terrainSize;y++)
        {
            animals=terrain[x][y].Move();
            for(int i=0;i<animals.size();i++)
            {
                terrain[animals[i]->getposition().x][animals[i]->getposition().y].setAnimal(animals[i]);
            }
            animals.clear();
        }
    }
}

void Ecosystem::RunEcosystem(int days,int season)
{
    Season=(season-1);
    ApplySeason();
    for(dayOfYear=1;dayOfYear<=days;dayOfYear++)
    {
        DailyReset();
        if(dayOfYear)
        {
            if(growthPeriod!=0)
            {
                if(dayOfYear%growthPeriodPlants==0)
                {
                    PlantGrowth();
                }
            }
            if(dayOfYear%growthPeriodAnimals==0)
            {
                AnimalsGrowth();
            }
            if(Season!=1)               //Winter
            {
                if(dayOfYear%breedingRepPeriodPlants==0)
                {
                    PlantBreeding();
                }
            }
            if(dayOfYear%breedingRepPeriodHerb==0)
            {
                //HerbivoresBreeding();
            }
            if(dayOfYear%breedingRepPeriodCarn==0)
            {
                CarnivoresBreeding();
            }
        }
        for(int i=0;i<24;i++)
        {
            Move();
            Eat();
            CheckDeadEntities();
            
        }
        cout<<"DAY "<<dayOfYear<<endl;
        PrintSystem();
        if(dayOfYear)
            if(dayOfYear%90==0)
            {
                ApplySeason();
            }
    }    
}

//---------------------------------------------ANIMAL FUNCTIONS

//-------------------------class Herbivores Functions

//------------------Deer----------------

coordinates* Deer::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        x=rand()%3;
        y=rand()%3;
        x-=1;
        y-=1;
    }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
    (x+getposition().x)<0 ||                                    //DO-WHILE
    (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
    (y+getposition().y)<0);                                    //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//-----------------Rabbit---------------

coordinates* Rabbit::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        do
        {
            x=rand()%3;
            y=rand()%3;
            x-=1;
            y-=1;
        }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
        (x+getposition().x)<0 ||                                    //DO-WHILE
        (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
        (y+getposition().y)<0);                                   //
    }while(Ecosys->terrain[x+getposition().x][y+getposition().y].getToken()=='^');               //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//----------------GroundHog-------------

coordinates* GroundHog::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        do
        {
            x=rand()%3;
            y=rand()%3;
            x-=1;
            y-=1;
        }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
        (x+getposition().x)<0 ||                                    //DO-WHILE
        (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
        (y+getposition().y)<0 );               //
    }while(Ecosys->terrain[x+getposition().x][y+getposition().y].getToken()=='#');
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//-----------------Salmon---------------

coordinates* Salmon::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        do
        {
            x=rand()%3;
            y=rand()%3;
            x-=1;
            y-=1;
        }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
        (x+getposition().x)<0 ||                                    //DO-WHILE
        (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
        (y+getposition().y)<0);                                   //
    }while(Ecosys->terrain[x+getposition().x][y+getposition().y].getToken()!='#');               //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//-------------------------class Carnivores Functions

//------------------Fox-----------------

coordinates* Fox::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        x=rand()%3;
        y=rand()%3;
        x-=1;
        y-=1;
    }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
    (x+getposition().x)<0 ||                                    //DO-WHILE
    (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
    (y+getposition().y)<0);                                    //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//------------------Wolf----------------

coordinates* Wolf::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        x=rand()%3;
        y=rand()%3;
        x-=1;
        y-=1;
    }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
    (x+getposition().x)<0 ||                                    //DO-WHILE
    (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
    (y+getposition().y)<0);                                    //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//------------------Bear----------------

coordinates* Bear::Move()
{
    int x,y;
    //srand(time(NULL));
    do
    {
        x=rand()%3;
        y=rand()%3;
        x-=1;
        y-=1;
    }while((x+getposition().x)> (Ecosys->getTerrainSize())-1 ||   //
    (x+getposition().x)<0 ||                                    //DO-WHILE
    (y+getposition().y)>(Ecosys->getTerrainSize())-1 ||           //Conditions
    (y+getposition().y)<0);                                    //
    setposition(getposition().x+x,getposition().y+y);
    return PositionPointer();
}

//---------------------------------------------TILE FUNCTINIONS

void Tile::PlantBreeding()
{
    bool placed=false;
    if(plant!=NULL)
    {
        srand(time(NULL));
        if(token=='#')
        {
            if((position.x-1)>=0)
            {
                if(Ecosys->terrain[position.x-1][position.y].token=='#' && Ecosys->terrain[position.x-1][position.y].plant==NULL)
                {
                    if(((rand()%101)/100.0)<=0.25)
                    {
                        Ecosys->terrain[position.x-1][position.y].plant=new algae();
                        placed=true;
                        Ecosys->sumOfAlgae++;
                        Ecosys->sumOfPlants++;
                    }
                }
            }
            if((position.x+1)<(Ecosys->getTerrainSize()) && placed==false)
            {
                if(Ecosys->terrain[position.x+1][position.y].token=='#' && Ecosys->terrain[position.x+1][position.y].plant==NULL)
                {
                    if(((rand()%101)/100.0)<=0.25)
                    {
                        Ecosys->terrain[position.x+1][position.y].plant=new algae();
                        placed=true;
                        Ecosys->sumOfAlgae++;
                        Ecosys->sumOfPlants++;
                    }
                }
            }
            if((position.y+1)<(Ecosys->getTerrainSize()) && placed==false)
            {
                if(Ecosys->terrain[position.x][position.y+1].token=='#' && Ecosys->terrain[position.x][position.y+1].plant==NULL)
                {
                    if(((rand()%101)/100.0)<=0.25)
                    {
                        Ecosys->terrain[position.x][position.y+1].plant=new algae();
                        placed=true;
                        Ecosys->sumOfAlgae++;
                        Ecosys->sumOfPlants++;
                    }
                }
            }
            if((position.y-1)>=0 && placed==false)
            {
                if(Ecosys->terrain[position.x][position.y-1].token=='#' && Ecosys->terrain[position.x][position.y-1].plant==NULL)
                {
                    if(((rand()%101)/100.0)<=0.25)
                    {
                        Ecosys->terrain[position.x][position.y-1].plant=new algae();
                        placed=true;
                        Ecosys->sumOfAlgae++;
                        Ecosys->sumOfPlants++;
                    }
                }
            }
        }
        else 
        {
            if(plant->getToken()=='G')
            {
                if((position.x-1)>=0 && placed==false)
                {
                    if(Ecosys->terrain[position.x-1][position.y].token=='"' && Ecosys->terrain[position.x-1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x-1][position.y].plant=new grass();
                            placed=true;
                            Ecosys->sumOfGrass++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }
                if((position.x+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if(Ecosys->terrain[position.x+1][position.y].token=='"' && Ecosys->terrain[position.x+1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x+1][position.y].plant=new grass();
                            placed=true;
                            Ecosys->sumOfGrass++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if(Ecosys->terrain[position.x][position.y+1].token=='"' && Ecosys->terrain[position.x][position.y+1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x][position.y+1].plant=new grass();
                            placed=true;
                            Ecosys->sumOfGrass++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y-1)>=0 && placed==false)
                {
                    if(Ecosys->terrain[position.x][position.y-1].token=='"' && Ecosys->terrain[position.x][position.y-1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x][position.y-1].plant=new grass();
                            placed=true;
                            Ecosys->sumOfGrass++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

            }
            else if(plant->getToken()=='O')
            {
                if((position.x-1)>=0 && placed==false)
                {
                    if(Ecosys->terrain[position.x-1][position.y].token=='"' && Ecosys->terrain[position.x-1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.20)
                        {
                            Ecosys->terrain[position.x-1][position.y].plant=new oak();
                            placed=true;
                            Ecosys->sumOfOak++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }
                if((position.x+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if(Ecosys->terrain[position.x+1][position.y].token=='"' && Ecosys->terrain[position.x+1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.20)
                        {
                            Ecosys->terrain[position.x+1][position.y].plant=new oak();
                            placed=true;
                            Ecosys->sumOfOak++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if(Ecosys->terrain[position.x][position.y+1].token=='"' && Ecosys->terrain[position.x][position.y+1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.20)
                        {
                            Ecosys->terrain[position.x][position.y+1].plant=new oak();
                            placed=true;
                            Ecosys->sumOfOak++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y-1)>=0 && placed==false)
                {
                    if(Ecosys->terrain[position.x][position.y-1].token=='"' && Ecosys->terrain[position.x][position.y-1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.20)
                        {
                            Ecosys->terrain[position.x][position.y-1].plant=new oak();
                            placed=true;
                            Ecosys->sumOfOak++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }
            }


            else if(plant->getToken()=='M')
            {
                if((position.x-1)>=0 && placed==false)
                {
                    if((Ecosys->terrain[position.x-1][position.y].token=='"' || Ecosys->terrain[position.x-1][position.y].token=='^') && Ecosys->terrain[position.x-1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.05)
                        {
                            Ecosys->terrain[position.x-1][position.y].plant=new maple();
                            placed=true;
                            Ecosys->sumOfMaple++;
                            Ecosys->sumOfPlants++;
                        }            
                    }
                }
                if((position.x+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if((Ecosys->terrain[position.x+1][position.y].token=='"' || Ecosys->terrain[position.x+1][position.y].token=='^') && Ecosys->terrain[position.x+1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.05)
                        {
                            Ecosys->terrain[position.x+1][position.y].plant=new maple();
                            placed=true;
                            Ecosys->sumOfMaple++;
                            Ecosys->sumOfPlants++;
                        }            
                    }
                }

                if((position.y+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if((Ecosys->terrain[position.x][position.y+1].token=='"' || Ecosys->terrain[position.x][position.y+1].token=='^') && Ecosys->terrain[position.x][position.y+1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.05)
                        {
                            Ecosys->terrain[position.x][position.y+1].plant=new maple();
                            placed=true;
                            Ecosys->sumOfMaple++;
                            Ecosys->sumOfPlants++;
                        }            
                    }
                }

                if((position.y-1)>=0 && placed==false)
                {
                    if((Ecosys->terrain[position.x][position.y-1].token=='"' || Ecosys->terrain[position.x][position.y-1].token=='^') && Ecosys->terrain[position.x][position.y-1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.05)
                        {
                            Ecosys->terrain[position.x][position.y-1].plant=new maple();
                            placed=true;
                            Ecosys->sumOfMaple++;
                            Ecosys->sumOfPlants++;
                        }            
                    }
                }
            }
            
            else if(plant->getToken()=='P')
            {
                if((position.x-1)>=0 && placed==false)
                {
                    if((Ecosys->terrain[position.x-1][position.y].token=='"' || Ecosys->terrain[position.x-1][position.y].token=='^') && Ecosys->terrain[position.x-1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x-1][position.y].plant=new pine();
                            placed=true;
                            Ecosys->sumOfPine++;
                            Ecosys->sumOfPlants++;
                        }

                    }
                }
                if((position.x+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if((Ecosys->terrain[position.x+1][position.y].token=='"' || Ecosys->terrain[position.x+1][position.y].token=='^') && Ecosys->terrain[position.x+1][position.y].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x+1][position.y].plant=new pine();
                            placed=true;
                            Ecosys->sumOfPine++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y+1)<(Ecosys->getTerrainSize()) && placed==false)
                {
                    if((Ecosys->terrain[position.x][position.y+1].token=='"' || Ecosys->terrain[position.x][position.y+1].token=='^') && Ecosys->terrain[position.x][position.y+1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x][position.y+1].plant=new pine();
                            placed=true;
                            Ecosys->sumOfPine++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }

                if((position.y-1)>=0 && placed==false)
                {
                    if((Ecosys->terrain[position.x][position.y-1].token=='"' || Ecosys->terrain[position.x][position.y-1].token=='^') && Ecosys->terrain[position.x][position.y-1].plant==NULL)
                    {
                        if(((rand()%101)/100.0)<=0.15)
                        {
                            Ecosys->terrain[position.x][position.y-1].plant=new pine();
                            placed=true;
                            Ecosys->sumOfPine++;
                            Ecosys->sumOfPlants++;
                        }
                    }
                }
            }            
        }    
    }
    
}

void Tile::DeleteDeadEntities()
{
    if(plant!=NULL)
    {   
        if(plant->getIfAlive()==false)
        {
            if(plant->getToken()=='G')
            {
                Ecosys->sumOfGrass-=1;
            }
            if(plant->getToken()=='A')
            {
                Ecosys->sumOfAlgae-=1;
            }
            if(plant->getToken()=='M')
            {
                Ecosys->sumOfMaple-=1;
            }
            if(plant->getToken()=='P')
            {
                Ecosys->sumOfPine-=1;
            }
            if(plant->getToken()=='O')
            {
                Ecosys->sumOfOak-1;
            }
            Ecosys->sumOfPlants-=1;

            delete plant;
            plant=NULL;
        }
    }
    vector <int> n;
    for(int i=0;i<animals.size();i++)
    {  
        if(animals[i]->getIfAlive()==false)
        {
            n.push_back(i);
        }
    }
    for(int i=n.size()-1;i>=0;i--)
    {
        if(animals[n[i]]->getName()=="Deer")
        {
            Ecosys->sumOfDeer-=1;
            Ecosys->sumOfHerbivores-=1;
        }
        else if(animals[n[i]]->getName()=="Rabbit")
        {
            Ecosys->sumOfRabbit-=1;
            Ecosys->sumOfHerbivores-=1;
        }
        else if(animals[n[i]]->getName()=="GroundHog")
        {
            Ecosys->sumOfGroundHog-=1;
            Ecosys->sumOfHerbivores-=1;
        }
        else if(animals[n[i]]->getName()=="Salmon")
        {
            Ecosys->sumOfSalmon-=1;
            Ecosys->sumOfHerbivores-=1;
        }
        else if(animals[n[i]]->getName()=="Fox")
        {
            Ecosys->sumOfFox-=1;
            Ecosys->sumOfCarnivores-=1;
        }
        else if(animals[n[i]]->getName()=="Wolf")
        {
            Ecosys->sumOfWolf-=1;
            Ecosys->sumOfCarnivores-=1;
        }
        else if(animals[n[i]]->getName()=="Bear")
        {
            Ecosys->sumOfBear-=1;
            Ecosys->sumOfCarnivores-=1;
        }
        Ecosys->sumOfAnimals-=1;
        animals.erase(animals.begin()+n[i]);
    }
}

void Tile::HerbivoresBreeding()
{
    int c=getNumberofAnimals();
    for(int i=0;i<c;i++)
    {   
        if(animals[i]->getIfinHibernation()==false)
        {
            if(animals[i]->getIfAdult()==true)
            {
                if(animals[i]->getName()=="Deer")
                {
                    setAnimal(new Deer(BABY));
                    Ecosys->sumOfDeer++;
                    Ecosys->sumOfHerbivores++;
                    Ecosys->sumOfAnimals++;
                }
                else if(animals[i]->getName()=="Rabbit")
                {
                    setAnimal(new Rabbit(BABY));
                    Ecosys->sumOfRabbit++;
                    Ecosys->sumOfHerbivores++;
                    Ecosys->sumOfAnimals++;
                }
                else if(animals[i]->getName()=="GroundHog")
                {
                    setAnimal(new GroundHog(BABY));
                    Ecosys->sumOfGroundHog++;
                    Ecosys->sumOfHerbivores++;
                    Ecosys->sumOfAnimals++;
                }
                else if(animals[i]->getName()=="Salmon")
                {
                    setAnimal(new Salmon(ADULT));
                    Ecosys->sumOfSalmon++;
                    Ecosys->sumOfHerbivores++;
                    Ecosys->sumOfAnimals++;
                }
            }
        }
    }

}

void Tile::CarnivoresBreeding()
{
    for(int i=0;i<getNumberofAnimals();i++)
    {
        if(animals[i]->getIfinHibernation()==false)
        {   
            if(animals[i]->getIfAdult()==true)
            {
                if(animals[i]->getName()=="Fox")
                {
                    setAnimal(new Fox(BABY));
                    Ecosys->sumOfFox++;
                    Ecosys->sumOfCarnivores++;
                    Ecosys->sumOfAnimals++;
                }
                else if(animals[i]->getName()=="Wolf")
                {
                    setAnimal(new Wolf(BABY));
                    Ecosys->sumOfWolf++;
                    Ecosys->sumOfCarnivores++;
                    Ecosys->sumOfAnimals++;
                }
                else if(animals[i]->getName()=="Bear")
                {
                    setAnimal(new Bear(BABY));
                    Ecosys->sumOfBear++;
                    Ecosys->sumOfCarnivores++;
                    Ecosys->sumOfAnimals++;
                }
            }
        }
    }
}