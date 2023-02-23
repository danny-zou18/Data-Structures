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
float AverageDistanceToDiningCar(TrainCar* train){
    float total_distance = 0;
    int num_passenger_cars = 0;
    while (train != nullptr){
        if (train->isPassengerCar()){
            bool found_forward = false;
            bool engine_forward = false;
            int front_dist = 0;
            TrainCar* temp = train;
            while (temp != nullptr){
                if (temp->isEngine() && temp->next != nullptr){
                    engine_forward = true;
                    break;
                }
                if (temp->isDiningCar()){
                    found_forward = true;
                    break;
                }
                front_dist += 1;
                temp = temp->next;
            }
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
int ClosestEngineToSleeperCar(TrainCar* train){
    TrainCar* temp;
    int smallest_dist;
    while(train != nullptr){
        if (train->isSleepingCar()){
            int temp_val = 0;
            int tmp_front_dist = 0;
            temp = train;
            while (temp != nullptr){
                if (temp->isEngine()){
                    break;
                }
                if (temp->next == nullptr){
                    tmp_front_dist = 32949;
                }
                tmp_front_dist += 1;
                temp = temp->next;
            }
            int tmp_back_dist = 0;
            temp = train;
            while (temp != nullptr){
                if (temp->isEngine()){
                    break;
                }
                if (temp->prev == nullptr){
                    tmp_back_dist = 46463;
                }
                tmp_back_dist += 1;
                temp = temp->prev;
            }

            temp_val = std::min(tmp_front_dist,tmp_back_dist);
            if (temp->prev == nullptr){
                smallest_dist = temp_val;
            }
            smallest_dist = std::min(smallest_dist,temp_val);
        }
        train = train->next;
    }
    return smallest_dist;
}
int count_cars(TrainCar* train){
    int count = 0;
    while (train != nullptr){
        count += 1;
        train = train->next;
    }
    return count;
}
int count_engines(TrainCar* train){
     int count = 0;
    while (train != nullptr){
        if (train->isEngine()){
            count += 1;
        }
        train = train->next;
    }
    return count;
}
TrainCar* PopFront(TrainCar*& train) {
    TrainCar* ptr = train;
    if (train == nullptr) {
        return nullptr;
    }
    else if (train->next == nullptr) {
        train = nullptr;
        return ptr;
    }
    train = train->next;
    train->prev = nullptr;
    ptr->next = nullptr;
    return ptr;
}
void PushBack(TrainCar* &head, TrainCar* car){
    if (head == nullptr){
        head = car;
        head->next = nullptr;
        return;
    } else {
        if (head->next == nullptr){
            car->prev = head;
        }
        PushBack(head->next,car);
    }
}
void AddCarBack(TrainCar *& train, TrainCar *& car) {
    if (car != NULL) {
    
        if (train == NULL) {
            train = car;
            train->next = NULL;
            train->prev = NULL;
            
        } else {
            TrainCar* nxt = car->next;   
            PushBack(train, car);
            
            if (nxt != NULL) {
                nxt->prev = NULL;
                car = nxt;
                
            } else {car = NULL;}
        }
    }
}
void AddCarFront(TrainCar *& train, TrainCar *& car) {
    if (car != NULL) {
    
        TrainCar* nxt = car->next;
        
        // If this is the first node, then we need to do things a bit differently
        if (train == NULL) {
            train = car;
            train->next = NULL;
            train->prev = NULL;
            
        } else {
            TrainCar* second = train;     // used to be the first car in the train, now it will be the second
            train = car;
            train->prev = NULL;
            train->next = second;
            
            if (second != NULL) {
                second->prev = train;
            }
        }
        
          // next car after the first one (which will be taken out)
        if (nxt != NULL) {
            nxt->prev = NULL;
            car = nxt;
            
        } else {car = NULL;}
    }
}
void DeleteAllCars(TrainCar*& train) {
    if (train == NULL) return;
    TrainCar *ptr = train;
    while (ptr->next != NULL) {
        ptr = ptr->next;
        delete ptr->prev;
    }
    delete ptr;
    train = NULL;
}
std::vector<TrainCar*> ShipFreight(TrainCar* engines, TrainCar* freights, const int min_speed, const int max_cars){
    std::vector<TrainCar*> trains;

    while (engines != nullptr && freights != nullptr){
        TrainCar* current_train = nullptr;
        PushBack(current_train, PopFront(engines));

        int current_cars = count_cars(current_train);
        float current_speed = CalculateSpeed(current_train);

        while (current_speed > min_speed && current_cars < max_cars){
            if (CalculateSpeedAdded(current_train, freights) > min_speed){
                AddCarBack(current_train, freights);
                current_cars = count_cars(current_train);
                current_speed = CalculateSpeed(current_train);
            } else if (max_cars - current_cars >=  2 && engines != nullptr){
                AddCarFront(current_train, engines);
                AddCarBack(current_train, freights);
                current_cars = count_cars(current_train);
                current_speed = CalculateSpeed(current_train);
            } else {
                break;
            }
        }
        trains.push_back(current_train);
        
    }
    return trains;
}