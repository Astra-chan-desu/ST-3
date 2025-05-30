// Copyright 2021 GHA Test Team
#include "TimedDoor.h"
#include <chrono>
#include <thread>
#include <stdexcept>


DoorTimerAdapter::DoorTimerAdapter(TimedDoor & door) : door(door) {}

void DoorTimerAdapter::Timeout() {
    door.throwState();
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), isOpened(false) {
    adapter = new DoorTimerAdapter(* this);
}

bool TimedDoor::isDoorOpened() { 
    return isOpened;
}

void TimedDoor::unlock() {
    isOpened = true;
}

void TimedDoor::lock() { 
    isOpened = false;
}

int TimedDoor::getTimeOut() const {
    return iTimeout;
}

void TimedDoor::throwState() {
    if (isOpened) {
        throw std::runtime_error("opened");
    } else throw std::runtime_error("closed");
}

void Timer::sleep(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

void Timer::tregister(int timeout, TimerClient * client) {
  sleep(timeout);
  client->Timeout();
}