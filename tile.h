#include "animals.h"

class Tile
{
        char token;
        Plant* plant;
        vector <Animal*> animals;
        coordinates position;
    public:
        Tile();
        ~Tile();
        static Ecosystem* Ecosys;
        int getNumberofAnimals();
        void setToken(char t);
        void setCoordinates(int x,int y);
        char getToken();
        void printToken();
        void printPlantToken();
        void setPlant(Plant* p);
        Plant* getPlant();
        void setAnimal(Animal* a);
        void DeleteDeadEntities(); //Implementation in ecosystem.cpp
        void AnimalsGrowth();
        void PlantGrowth();
        void PlantBreeding();     //Impementation in ecosystem.cpp
        void HerbivoresBreeding();  //Implementation in ecosystem.cpp
        void CarnivoresBreeding();  //Implementation in ecosystem.cpp
        void Eat();
        Animal* getHerbivore();
        Animal* getCarnivore(int n);
        vector <Animal*> Move();
        void setHiberation(bool h);
        void DailyReset();
};