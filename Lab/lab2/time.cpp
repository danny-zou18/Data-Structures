#include <iostream>
#include "time.h"

using std::cout; using std::endl; using std::string;

Time::Time(){
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond){
    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::setHour(int h){
    hour = h;
}

void Time::setMinute(int m){
    minute = m;
}

void Time::setSecond(int s){
    second = s;
}

void Time::PrintAMPM() const {
    int new_hour = hour;
    string new_minute = std::to_string(minute);
    string new_second = std::to_string(second);
    if (hour == 0){
        new_hour = 12;
    }
    if (hour > 12){
        new_hour = new_hour - 12;
    } 
    if (minute < 10){
        new_minute = "0" + new_minute;
    } 
    if (second < 10){
        new_second = "0" + new_second;
    }
    if (hour > 12) {
        cout << new_hour << ":" << new_minute << ":" << new_second << " pm" << endl;
    } else {
        cout << new_hour << ":" << new_minute << ":" << new_second << " am" << endl;
    }
}

bool IsEarlierThan(const Time& t1, const Time& t2){
    int total_seconds1 = 0;
    int hour_seconds1 = t1.getHour() * 60 * 60;
    int minute_seconds1 = t1.getMinute() * 60;
    total_seconds1 += hour_seconds1 + minute_seconds1 + t1.getSecond();

    int total_seconds2 = 0;
    int hour_seconds2 = t2.getHour() * 60 * 60;
    int minute_seconds2 = t2.getMinute() * 60;
    total_seconds2 += hour_seconds2 + minute_seconds2 + t2.getSecond();

    if (total_seconds1 < total_seconds2){
        return true;
    } else {
        return false;
    }
 
}