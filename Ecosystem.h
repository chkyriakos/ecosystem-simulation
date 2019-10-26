#include"tile.h"

class Ecosystem
{
        
        int terrainSize;
        int lakeSize;
        int dayOfYear;
        int growthPeriod;
        int breedingRepPeriod;
        int water;
        int hills;
        int meadow;
        int Season;        //1:Winter 2:Spring 3:Summer 4:Autumn

        //growth and breeding variables
        int growthPeriodPlants;
        int growthPeriodAnimals;
        int breedingRepPeriodPlants;
        int breedingRepPeriodHerb;
        int breedingRepPeriodCarn;

        void PrintTerrain();
        void PrintPlants();
        void PrintSumOfEntities();
        void PrintNumOfAnimals();
        void GenerateRiver();
        void GenerateLake();
        void GenerateHills();
        void GenerateMeadow();
        void PlacePlants();
        void PlaceAnimals();
        void ApplySeason();
        void Move();
        void AnimalsGrowth();
        void PlantGrowth();
        void PlantBreeding();     
        void HerbivoresBreeding();
        void CarnivoresBreeding();
        void DailyReset();
        void Eat();
        void CheckDeadEntities();
        void MapGenerator();
        void PlaceEntities();
        void PrintSystem();
    public:
        Ecosystem(int s);
        ~Ecosystem();
        Tile** terrain;
        int getTerrainSize();
        Tile*** getTerrain();
        void RunEcosystem(int days,int season);
        //num of plants in ecosystem
            int sumOfPlants;
            int sumOfGrass;
            int sumOfAlgae;
            int sumOfMaple;
            int sumOfPine;
            int sumOfOak;

        //num o animals in ecosystem
            int sumOfAnimals;
            int sumOfHerbivores;
            int sumOfCarnivores;
            int sumOfDeer;
            int sumOfRabbit;
            int sumOfGroundHog;
            int sumOfSalmon;
            int sumOfFox;
            int sumOfWolf;
            int sumOfBear;
};