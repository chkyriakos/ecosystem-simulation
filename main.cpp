#include "ecosystem.h"

Ecosystem* Animal::Ecosys=NULL;
Ecosystem* Tile::Ecosys=NULL;


int main()
{
    int TerrainSize,Season,Cycles;
    cout<<"Give size of Terrain (>=10)."<< endl;
    cin>>TerrainSize;
    while(TerrainSize<10)
      {
        cout<<"Give size of Terrain (>=10)."<< endl;
        cin>>TerrainSize;  
      }
    cout<<"Give starting season 1=Winter,2=Spring,3=Summer,4=Autumn" << endl;
    cin>>Season;
    while(Season<1 && Season>4)
    {
        cout<<"Give starting season 1=Winter,2=Spring,3=Summer,4=Autumn" << endl;
        cin>>Season; 
    }
    cout<<"Give days of simulation(>=1)" <<endl;
    cin>>Cycles;
    while(Cycles<1)
    {
        cout<<"Give days of simulation(>=1)" <<endl;
        cin>>Cycles;
    }
    Ecosystem E(TerrainSize);
    Animal::Ecosys=&E;
    Tile::Ecosys=&E;
    E.RunEcosystem(Cycles,Season);
}

