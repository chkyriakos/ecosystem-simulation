#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;


struct coordinates
{
    int x;
    int y;
};

#define BABY false
#define ADULT true

//Herbivores-------------------------------------------------------------

//Deer---------------------------------------

#define BABY_DEER_SIZE 2
#define BABY_DEER_SPEED 4
#define BABY_DEER_NEEDED_FOOD 4    //per day

#define DEER_SIZE 5
#define DEER_SPEED 8
#define DEER_NEEDED_FOOD 8    //per day

#define DEER_CAN_CLIMB  false
#define DEER_EAT_COUNT 2
#define DEER_HIBERNATION false
//Rabbit--------------------------------------

#define BABY_RABBIT_SIZE 1
#define BABY_RABBIT_SPEED 2
#define BABY_RABBIT_NEEDED_FOOD 2    //per day

#define RABBIT_SIZE 2
#define RABBIT_SPEED 6
#define RABBIT_NEEDED_FOOD 4    //per day

#define RABBIT_CAN_CLIMB  false
#define RABBIT_EAT_COUNT 1
#define RABBIT_HIBERNATION false

//GroundHog-----------------------------------

#define BABY_GROUNDHOG_SIZE 2
#define BABY_GROUNDHOG_SPEED 3
#define BABY_GROUNDHOG_NEEDED_FOOD 3    //per day

#define GROUNDHOG_SIZE 3
#define GROUNDHOG_SPEED 5
#define GROUNDHOG_NEEDED_FOOD 5    //per day

#define GROUNDHOG_CAN_CLIMB  true
#define GROUNDHOG_EAT_COUNT 1

#define GROUNDHOG_HIBERNATATION true

//Salmon--------------------------------------

#define SALMON_SIZE 1
#define SALMON_SPEED 5
#define SALMON_NEEDED_FOOD 1

#define SALMON_CAN_CLIMB false
#define SALMON_EAT_COUNT 1

//Carnivores-------------------------------------------------------------

//Fox-----------------------------------------

#define BABY_FOX_SIZE 1
#define BABY_FOX_ATTACK 1
#define BABY_FOX_DEFENCE 1
#define BABY_FOX_SPEED 1
#define BABY_FOX_NEEDED_FOOD 2      //per day

#define FOX_SIZE 4
#define FOX_ATTACK 5
#define FOX_DEFENCE 5
#define FOX_SPEED 6
#define FOX_NEEDED_FOOD 6       //per day

#define FOX_HIBERNATION false


//Wolf----------------------------------------

#define BABY_WOLF_SIZE 1
#define BABY_WOLF_ATTACK 2
#define BABY_WOLF_DEFENCE 2
#define BABY_WOLF_SPEED 2
#define BABY_WOLF_NEEDED_FOOD 2     //per day

#define WOLF_SIZE 7
#define WOLF_ATTACK 8
#define WOLF_DEFENCE 6
#define WOLF_SPEED 8
#define WOLF_NEEDED_FOOD 8      //per day

#define WOLF_HIBERNATION false

//Bear----------------------------------------

#define BABY_BEAR_SIZE 3
#define BABY_BEAR_ATTACK 6
#define BABY_BEAR_DEFENCE 6
#define BABY_BEAR_SPEED 4
#define BABY_BEAR_NEEDED_FOOD 5     //per day

#define BEAR_SIZE 10
#define BEAR_ATTACK 10
#define BEAR_DEFENCE 10
#define BEAR_SPEED 4
#define BEAR_NEEDED_FOOD 10     //per day

#define BEAR_HIBERNATION true