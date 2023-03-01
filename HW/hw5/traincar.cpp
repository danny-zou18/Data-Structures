

// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

//Function for calculating the total weight of the train and how many engines, freights cars, passengers cars, 
//dining cars and sleeping cars the train has
void TotalWeightAndCountCars(TrainCar* train, int& total_weight, int& num_engines, int& num_freight_cars, int& num_passenger_cars, int& num_dining_cars, int& num_sleeping_cars){
    total_weight = 0;
    num_engines = 0;
    num_freight_cars = 0;
    num_passenger_cars = 0;
    num_dining_cars = 0;
    num_sleeping_cars = 0;
    while (train != nullptr){
        total_weight += train->getWeight();
        if (train->isDiningCar()){
            num_dining_cars++;
        } else if (train->isEngine()){
            num_engines++;
        } else if (train->isFreightCar()){
            num_freight_cars++;
        } else if (train->isPassengerCar()){
            num_passenger_cars++;
        } else if (train->isSleepingCar()){
            num_sleeping_cars++;
        }
        train = train->next;
    }
}
//Function that calculates the speed of the train based on the given formula
float CalculateSpeed(TrainCar* train){
    float speed;
    int total_horsepower = 0;
    int total_weight = 0;
    while (train != nullptr){
        total_weight += train->getWeight();
        if (train->isEngine()){
            total_horsepower += 3000;
        }
        train = train->next;
    }
    speed = (float(total_horsepower) * 550 * 3600) / ((20/.01) * 0.02 * 5280 * float(total_weight));
    return speed;
}
//Function that calculates the speed of the train if we add the given car to the train
float CalculateSpeedAdded(TrainCar* train, TrainCar* car){
    float speed;
    int total_horsepower = 0;
    int total_weight = 0;
    while (train!= nullptr){
        total_weight += train->getWeight();
        if (train->isEngine()){
            total_horsepower += 3000;
        }
        train = train->next;
    }
    if (car != nullptr){
        total_weight += car->getWeight();
    }
    speed = (float(total_horsepower) * 550 * 3600) / ((20/.01) * 0.02 * 5280 * float(total_weight));
    return speed;
}
//Function that calculates the average distance to a dining car
float AverageDistanceToDiningCar(TrainCar* train){
    float total_distance = 0;
    int num_passenger_cars = 0;
    while (train != nullptr){ 
        if (train->isPassengerCar()){
            bool found_forward = false; //Boolean for keeping track of if we have found a dining car iterating forward
            bool engine_forward = false; //Boolean for keeping track of if we have found a engine iterating forward
            int front_dist = 0; //Keeps track of the distance iterating forward from a passenger car
            TrainCar* temp = train;
            while (temp != nullptr){
                if (temp->isEngine() && temp->next != nullptr){
                    engine_forward = true; //If we have found a engine and it is not the last car in the train
                    break;                 //,then set that we have found a engine iterating forwards
                }
                if (temp->isDiningCar()){ //If we have found a dining car, set that we have found a dining car
                    found_forward = true; //iterating forwards
                    break;
                }
                front_dist += 1;
                temp = temp->next;
            }
            //If we did not find a dining car or we have run into a engine iterating forwards, then we iterate 
            // backwards instead and check if there is a dining car.
            // If there is no dining car or a engine is blocking the way going backwards as well, return a negative value
            if (found_forward == false || engine_forward){ 
                int back_dist = 0;
                TrainCar* temp = train;
                while(temp != nullptr){
                    if (temp->isEngine() && temp->prev != nullptr){
                        return -1.1;
                    }
                    if (temp->isDiningCar()){
                        break;
                    }
                    back_dist += 1;
                    temp = temp->prev;
                }
                total_distance += back_dist;
                num_passenger_cars += 1;
                
            } else {
                total_distance += front_dist;
                num_passenger_cars += 1;
            }
        }
        train = train->next;
    }
    float average = total_distance/num_passenger_cars;
    return average;
}
//Functon for finding the closest sleeper car to a engine
int ClosestEngineToSleeperCar(TrainCar* train){
    TrainCar* temp;
    int smallest_dist = 9882; //set the initial value to a absurdly big number so we can find the minimum
    bool found_passenger = false;
    bool found_engine = false;
    while(train != nullptr){
        //If the car is a sleeping car, we look for a engine iterating forwards and backwards
        if (train->isSleepingCar()){
            found_passenger = true; 
            int temp_val = 0;
            int tmp_front_dist = 0;
            temp = train;
            while (temp != nullptr){
                if (temp->isEngine()){ //Found a engine going forwards
                    found_engine = true;
                    break;
                }
                if (temp->next == nullptr){ //if we don't find a engine, set front dist
                    tmp_front_dist = 32949; //to a big number 
                    break;
                }
                tmp_front_dist += 1;
                temp = temp->next;
            }
            int tmp_back_dist = 0;
            temp = train;
            while (temp != nullptr){
                if (temp->isEngine()){ //Found a engine going backwards
                    found_engine = true;
                    break;
                }
                if (temp->prev == nullptr){ //If we don't find a engine, set back dist
                    tmp_back_dist = 46463;  // to a big number
                    break;
                }
                tmp_back_dist += 1;
                temp = temp->prev;
            }
            temp_val = std::min(tmp_front_dist,tmp_back_dist);  //Compare the distances of reaching a engine from a passenger car going backwards and forwards
            if (temp->prev == nullptr){                         // and pick the smallest value
                smallest_dist = temp_val; 
            }
            smallest_dist = std::min(smallest_dist,temp_val); //Compare the current candidate for smallest distance to the temporary value we just                     
        }                                                      // we just got and choose the smallest one
        train = train->next;
    }
    if (found_engine == false || found_passenger == false){ //If there is no sleeping cars or engines, return a negative value
        return -1;
    }
    return smallest_dist;
}
//Helper function that calculates the amount of cars a train has
int count_cars(TrainCar* train){
    int count = 0;
    while (train != nullptr){
        count += 1;
        train = train->next;
    }
    return count;
}
//Push back function that links the given car to the back of the train recursively
void PushBack(TrainCar* &train, TrainCar* car){
    if (train == nullptr){
        train = car;
        train->next = nullptr;
        return;
    } else {
        if (train->next == nullptr){
            car->prev = train;
        }
        PushBack(train->next,car);
    }
}
//Function that adds the first car from the second train to the back of the train from the first argument
//We use it to add either freight cars or engines, taking it from a train that only has engines or freights
void AddCarBack(TrainCar *& train, TrainCar *& car) {
    if (car != nullptr) {
        if (train == nullptr) {
            train = car;
            train->prev = nullptr;
            train->next = nullptr;
        } else {
            TrainCar* next = car->next;  
            PushBack(train, car);
            if (next != nullptr) {
                next->prev = nullptr;
                car = next;
            } else {
                car = nullptr;
            }
        }
    }
}
//Function that adds the first car from the second train to the front of the train from the first argument
//Same purpose as addcarback
void AddCarFront(TrainCar *& train, TrainCar *& car) {
    if (car != nullptr) {
        TrainCar* next = car->next;
        if (train == nullptr) {
            train = car;
            train->next = nullptr;
            train->prev = nullptr;
        } else {
            TrainCar* next1 = train;
            train = car;
            train->prev = nullptr;
            train->next = next1;
            if (next1 != nullptr) {
                next1->prev = train;
            }
        }
        if (next != nullptr) {
            next->prev = nullptr;
            car = next;
        } else {
            car = nullptr;
        }
    }
}
//Function that removes the first car in a train and returns it
TrainCar* PopFront(TrainCar*& train) {
    TrainCar* current = train;
    if (train == nullptr) return nullptr;
    else if (train->next == nullptr) {
        train = nullptr;
        return current;
    }
    train = train->next;
    train->prev = nullptr;
    current->next = nullptr;
    return current;
}
//Function that returns a specific car from a train based on the given index
TrainCar* getTrain(TrainCar*& train, int index){
    TrainCar* current_car = train;
    int cur_index = 0;
    while (current_car != nullptr && cur_index != index){
        current_car = current_car->next;
        cur_index += 1;
    }
    return current_car;
}
//Function that moves a specific car in a train to the wanted index
void moveCar(TrainCar*& train, TrainCar* car, int index) {
    // If the car is already at the specified index, return
    if (car == nullptr || car->next == nullptr || car->prev == nullptr) {
        return;
    }

    // Delink the car from its current position in the train
    car->prev->next = car->next;
    car->next->prev = car->prev;

    // Go through the train and find the wanted car
    TrainCar* current = train;
    int currentIndex = 0;
    while (current != nullptr && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    // Insert the car into its new spot
    if (current == nullptr) {
        car->prev = current->prev;
        current->prev->next = car;
        car->next = current;
    } else {
        car->next = current;
        car->prev = current->prev;
        current->prev = car;
        if (car->prev == nullptr) {
            train = car;
        } else {
            car->prev->next = car;
        }
    }
}
//Deletes all the memorys associated with the train recursively
void DeleteAllCars(TrainCar*& train) {
    if (train == nullptr){
        return;
    }
    DeleteAllCars(train->next);
    delete train;
}
//Ship freight algorithm
std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freights, const int min_speed, const int max_cars){
    if (engines == nullptr || freights == nullptr || min_speed <= 0 || max_cars <= 0){
        return std::vector<TrainCar*> (); //initialize a empty vector to be returned if any conditions are not acceptable
    }
    std::vector<TrainCar*> trains;
    
    while (engines != nullptr && freights != nullptr){ //While there are still trains and freight cars
        TrainCar* current_train = nullptr;
        AddCarFront(current_train, engines);

        int current_cars = count_cars(current_train);
        float current_speed = CalculateSpeed(current_train);
        
        //While the cars speed is above the minimum speed, the number of cars are below the max number of cars and there are still freights cars 
        // and engines, calculate the speed of the train if we add the current freight car, if it is greater then the minimum speed, the the freight
        // car to the train. If the speed is lower, check if we can add a engine and another train or else stop the loop and add the completed train
        // to all the trains
        while (current_speed > min_speed && current_cars < max_cars && freights != nullptr && engines != nullptr){
            if (CalculateSpeedAdded(current_train, freights) > min_speed){
                AddCarBack(current_train, freights);
            } else if (max_cars - current_cars >=  2 && engines != nullptr){
                AddCarFront(current_train, engines);
                AddCarBack(current_train, freights);
            } else {
                break;
            }
            current_cars = count_cars(current_train);
            current_speed = CalculateSpeed(current_train);
        }
        trains.push_back(current_train); 
    }
    return trains;
}
//Seperate Function that seperates a train optimally
void Separate(TrainCar*& train1, TrainCar*& train2, TrainCar*& train3){
    //Counts the number of engines in the original train
    train2 = nullptr;
    train3 = nullptr;
    int engine_cars = 0;
    TrainCar* check_eng = train1;
    while (check_eng != nullptr){
        if (check_eng->isEngine()){
            engine_cars += 1;
        }
        check_eng = check_eng->next;
    }
    //Checks if there are more than 2 engines atleast, if not, break
    if (engine_cars < 2){
        std::cerr << "Not enough engines to be split" << std::endl;
        return;
    }

    int original_length = count_cars(train1); //Calculates the original trains length
    int first_length; //The length of the first train to be made
    int second_length; //The length of the second train to be made

    //Calculates the train lengths based on if the original trains length is odd or even
    if (original_length % 2 == 0){
        first_length = original_length / 2;
        second_length = original_length / 2;
    } else {
        first_length = original_length / 2;
        second_length = (original_length / 2) + 1;
    }

    int first_engines; //The amount of engines that should be in the first train to be made
    int second_engines; //The amount of engines that should be in the second train to be made
    //Calculates the amount of engines to be distributed to each train based on how many engines 
    //are in the original train
    if (engine_cars % 2 == 0){
        first_engines = engine_cars / 2;
        second_engines = engine_cars / 2;
    } else {
        first_engines = engine_cars / 2;
        second_engines = (engine_cars / 2) + 1;
    }
    int engines_in_first = 0; //The amount of engines that is in the first half of the original train
    int engines_in_second = 0; //The amount of engines that is in the second half of the original train
    TrainCar* ptr = train1;
    //Calculates the amount of engines
    for (int i = 0; i < first_length; i++){
        if (ptr->isEngine()){
            engines_in_first += 1;
        }
        ptr = ptr->next;
    }
    
    for (int i = first_length; i < second_length + first_length; i++){
        if (ptr->isEngine()){
            engines_in_second += 1;
        }
        ptr = ptr->next;
    }

    int move_engines;
    int track;
    //If there are more engines then there should be in the first train to be made, then we want
    // to move the correct number of engines to the second train
    if (engines_in_first > first_engines){
        move_engines = engines_in_first - first_engines; //The amount of engines to be moved
 
        track = 0; //Tracks how many engines were moved
        int engine_pos = first_length - 1; //Engine position
        TrainCar* temp = train1; 
        //Go to the middle of the train
        for (int i = 0; i < first_length - 1; i++){
            temp = temp->next;
        }
        //Insert spot basically tells us where to move the engines to. It is based on how many we want to move
        int insert_spot = first_length + move_engines - 1; 
        //While there are still engines to be moved, we iterate through the first half of the original train backwards to find
        //the closest engine to be added to the second train to be made
        while (track < move_engines){ 
            for ( ;engine_pos != 0; engine_pos-- ){
                if (temp->isEngine()){
                    temp = temp->prev;
                    TrainCar* swap_engine = getTrain(train1, engine_pos);
                    moveCar(train1, swap_engine, insert_spot);
                    track += 1;
                    if (track == move_engines){
                        break;
                    }
                    continue;
                }
                temp = temp->prev;
            }
        }
    } else if (engines_in_second > second_engines){
        //Basically the same thing as the code above but moves from the second train to the first train
        //if the second train has more engines then it should have
        move_engines = engines_in_second - second_engines;
        track = 0;
        int engine_pos = first_length;
        TrainCar* temp = train1;
        for (int i = 0; i < first_length;i++){
            temp = temp->next;
        }
        int insert_spot = first_length - move_engines;
        while (track < move_engines){
            for ( ;engine_pos < first_length + second_length; engine_pos++){
                if (temp->isEngine() && engine_cars == 2 && engine_pos == insert_spot + move_engines && original_length % 2 != 0){
                    first_length += 1; // Test case if the extra engine is right in the middle of a odd original train
                    second_length -= 1;
                    track += 1;
                    break;
                }
                if (temp->isEngine()){
                    TrainCar* engine_swap = getTrain(train1, engine_pos);
                    moveCar(train1, engine_swap, insert_spot);
                    track += 1;
                    if (track == move_engines){
                        break;
                    }
                }
                temp = temp->next;
            }
        }
    }
    //Build the 2 trains based on original trains
    TrainCar* temp1 = train1;
    for (int i = 0; i < first_length; i++){
        PushBack(train2, PopFront(temp1));
    }
    for (int i = 0; i < second_length; i++){
        PushBack(train3, PopFront(temp1));
    }
    train1 = nullptr;
}