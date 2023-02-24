

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
    int smallest_dist = 9882;
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
                    break;
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
                    break;
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
            } else {
                car = NULL;
            }
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
        } else {
            car = NULL;
        }
    }
}
TrainCar* PopFront(TrainCar*& train) {
    TrainCar* ptr = train;
    // If list is empty, do nothing and return a NULL pointer
    if (train == NULL) return NULL;
    else if (train->next == NULL) {
        // If there is only 1 element in list, no need to modify prev and next
        // pointers.
        train = NULL;
        return ptr;
    }
    // Otherwise, move pointer to next element
    train = train->next;
    // Modify 2 pointers so that the second element become new head
    train->prev = NULL;
    ptr->next = NULL;
    return ptr;
}
TrainCar* getTrain(TrainCar*& train, int index){
    TrainCar* current_car = train;
    int cur_index = 0;
    while (current_car != nullptr && cur_index != index){
        current_car = current_car->next;
        cur_index += 1;
    }
    return current_car;
}
void swapCars(TrainCar*& train, TrainCar* car1, TrainCar* car2) {
    TrainCar* temp = car1;
    TrainCar* temp2 = car2;
    TrainCar* previousCar = temp->prev;
    TrainCar* nextCar = temp->next;
    TrainCar* previousCar2 = temp2->prev;
    TrainCar* nextCar2 = temp2->next;

    if (nextCar != nullptr){
        nextCar->prev = temp2;
    }
    if (nextCar != nullptr){
        previousCar->next = temp2;
    }
    
    if (temp2->next != nullptr){
        temp2->next->prev = temp;
    }
    if (temp2->prev != nullptr){
        temp2->prev->next = temp;
    }
    temp->next = temp2->next;
    temp->prev = temp2->prev;

    temp2->next = nextCar;
    temp2->prev = previousCar;

}

void DeleteAllCars(TrainCar*& train) {
    if (train == nullptr){
        return;
    }
    DeleteAllCars(train->next);
    delete train;
}
std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freights, const int min_speed, const int max_cars){
    if (engines == nullptr || freights == nullptr || min_speed <= 0 || max_cars <= 0){
        return std::vector<TrainCar*> (); //initialize a empty vector to be returned
    }

    std::vector<TrainCar*> trains;

    while (engines != nullptr && freights != nullptr){
        TrainCar* current_train = nullptr;
        AddCarFront(current_train, engines);

        int current_cars = count_cars(current_train);
        float current_speed = CalculateSpeed(current_train);
        
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
    for (unsigned int i = 0; i < first_length; i++){
        if (ptr->isEngine()){
            engines_in_first += 1;
        }
        ptr = ptr->next;
    }
    
    for (unsigned int i = first_length; i < second_length + first_length; i++){
        if (ptr->isEngine()){
            engines_in_second += 1;
        }
        ptr = ptr->next;
    }

    int move_engines;
    int track;

    if (engines_in_first > first_engines){
        move_engines = engines_in_first - first_engines;

        track = 0;
        int first_engine_pos = 0;
        int second_engine_pos;
        TrainCar* temp = train1;
        bool did = false;
        int track_pos = first_length;
        while (track < move_engines){
            for ( ;first_engine_pos < first_length; first_engine_pos++ ){
                if (temp->isEngine() && track_pos == first_length){
                    temp = temp->next;
                    track_pos--;
                    continue;
                }
                if (temp->isEngine()){
                    second_engine_pos = first_engine_pos + track_pos;
                    TrainCar* first_swap = getTrain(train1, first_engine_pos);
                    TrainCar* second_swap = getTrain(train1, second_engine_pos);
                    if (second_swap->isEngine()){
                        temp = temp->next;
                        track_pos--;
                        if (track == move_engines){
                            break;
                        }
                        continue;
                    }
                    swapCars(train1, first_swap, second_swap);
                    track += 1;
                    if (track == move_engines){
                        break;
                    }
                }
                temp = temp->next;
                track_pos--;
            }
        }
    } else if (engines_in_second > second_engines){
        move_engines = engines_in_second - second_engines;

        track = 0;
        int first_engine_pos = first_length;
        int second_engine_pos;
        TrainCar* temp = train1;
        for (unsigned int i = 0; i < first_length;i++){
            temp = temp->next;
        }
        int track_pos = 1;
        while (track < move_engines){
            for ( ;first_engine_pos < first_length + second_length; first_engine_pos++){
                if (temp->isEngine() && track_pos == 1){
                    temp = temp->next;
                    track_pos++;
                    continue;
                }
                if (temp->isEngine()){
                    second_engine_pos = first_engine_pos - track_pos;
                    TrainCar* first_swap = getTrain(train1, first_engine_pos);
                    TrainCar* second_swap = getTrain(train1, second_engine_pos);
                    if (second_swap->isEngine()){
                        temp = temp->next;
                        track_pos++;
                        if (track == move_engines){
                            break;
                        }
                        continue;
                    }
                    swapCars(train1, first_swap, second_swap);
                    track += 1;
                    if (track == move_engines){
                        break;
                    }
                }
                temp = temp->next;
                track_pos++;
            }
        }
    }
    TrainCar* temp1 = train1;
    for (unsigned int i = 0; i < first_length; i++){
        PushBack(train2, PopFront(temp1));
    }
    for (unsigned int i = 0; i < second_length; i++){
        PushBack(train3, PopFront(temp1));
    }
    train1 = nullptr;
}