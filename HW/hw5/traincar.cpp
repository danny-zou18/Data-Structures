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
void AddFront(TrainCar* &head, TrainCar* car){
    if (head == nullptr){
        head = car;
        head->prev = nullptr;
        return;
    } else {
        if (head->prev == nullptr){
            car->next = head;
        }
        AddFront(head->prev,car);
    }
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
TrainCar* RemoveFront(TrainCar*& train){
    if (train == nullptr){
        return nullptr;
    }
    if (train->next == nullptr){
        train = nullptr;
        TrainCar* temp = train;
        return temp;
    }
    TrainCar* temp = train;
    train = train->next;
    train->prev = nullptr;
    temp->next = nullptr;
    return temp;
}
TrainCar* RemoveBack(TrainCar*& train){
    if (train == nullptr){
        return nullptr;
    }
    if (train->next == nullptr){
        train = nullptr;
        TrainCar* temp = train;
        return temp;
    }
    TrainCar* temp = train;
    while (temp->next != nullptr){
        temp = temp->next;
    }
    temp->prev->next = nullptr;
    temp->prev = nullptr;
    return temp;
}
TrainCar* Erase(TrainCar*& train, TrainCar*& ptr) {
    // Do nothing if train is empty
    if (train == NULL || ptr == NULL) return NULL;
    TrainCar *tmp = ptr;
    // If there is only 1 elements in train, train would become empty and
    // ptr is supposed to set to NULL.
    if (ptr->prev == NULL && ptr->next == NULL) {
        train = NULL;
    } else if (ptr->next == NULL) {
        ptr->prev->next = NULL;
    } // Tail
    else if (ptr->prev == NULL) {
        // Head: Modify 1 pointer and set train and ptr to new head.
        ptr->next->prev = NULL;
        train = train->next;
    } else {
        // If ptr is not head nor tail of list, we are going to modify 2 pointers
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }
    ptr = ptr->next;
    // Make sure tmp is not connect to anything so that no unexpectted things
    // would happen.
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}
void DeleteAllCars(TrainCar*& head){
    if (head == nullptr){
        delete head;
    } else {
        DeleteAllCars(head->next);
        delete head;
    }
}

std::vector<TrainCar*> ShipFreight(TrainCar*& engines, TrainCar*& freights, int min_speed, int max_cars){
    std::vector<TrainCar*> trains;
    while (engines != nullptr && freights != nullptr){
        TrainCar* new_train = nullptr;
        PushBack(new_train, RemoveFront(engines));
        int current_cars = 1;
        
        TrainCar* check = freights;
        while (check != nullptr && current_cars < max_cars){
            TrainCar* temp = new_train;
            PushBack(temp,check);
            if (CalculateSpeed(temp) >= min_speed){
                current_cars += 1;
                PushBack(new_train,Erase(freights,check));
            } else if (max_cars - current_cars >= 2 && engines != nullptr){
                AddFront(new_train, RemoveFront(engines));
                PushBack(new_train, Erase(freights, check));
                //std::cout << check->getID() << std::endl;


                current_cars += 2;
            } else {
                break;
            }
            //check = check->next;

        }
    trains.push_back(new_train);
    }
    return trains;
}