#include <string>

class Animal{
public:
    
    Animal(); //Default constructor
    Animal(std::string aName); //Constuctor with name

    //ACCESSORS
    std::string get_name() const; //Returns the name of the animal
    int get_weight() const; //Returns the weight of the animal
    bool live_land() const; //Returns true if the animal lives on land
    bool live_water() const; //Returns true if the animal lives in water
    bool eat_meat() const; //Returns true if the animal eats meat
    bool eat_grass() const; //Returns true if the animal eats grass

    //MODIFIERS
    void setWeight(int aWeight); //Sets the weight of the animal
    void setLand(); //Set animal to be able to live on land
    void setWater();//Set animal to be able to live in water
    void setMeat(); //Set animal to eat meat
    void setPlants(); //Set animal to eat grass

    bool is_omnivore(const Animal& animal1); //Returns true if animal eats both meat and grass
    bool is_amphibious(const Animal& animal1); //Returns true if animal can live in both water and land

private:
    std::string name;
    int weight;
    bool onLand;
    bool onWater;
    bool eatMeat;
    bool eatPlant;

};
