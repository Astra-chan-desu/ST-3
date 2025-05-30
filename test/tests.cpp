// Copyright 2021 GHA Test Team

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <thread>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
 public:
  MOCK_METHOD(void, Timeout, (), (override));
};

class  ST3_Strakhov : public::testing::Test {
 protected:
  TimedDoor * testDoor;
  MockTimerClient * testMockClient;

  void SetUp() override {
    testDoor = new TimedDoor(50);
    testMockClient = new MockTimerClient();
  }

  void TearDown() override {
    delete testDoor;
    delete testMockClient;
  }
};

TEST_F(ST3_Strakhov, startState) {
    EXPECT_FALSE(testDoor->isDoorOpened());
}

TEST_F(ST3_Strakhov, unlock1) {
    testDoor->unlock();
    EXPECT_TRUE(testDoor->isDoorOpened());
}
TEST_F(ST3_Strakhov, unlock2) {
    testDoor->unlock();
    testDoor->unlock();
    EXPECT_TRUE(testDoor->isDoorOpened());
}

TEST_F(ST3_Strakhov, lock1) {
    testDoor->unlock();
    testDoor->lock();
    EXPECT_FALSE(testDoor->isDoorOpened());
}
TEST_F(ST3_Strakhov, lock2) {
    testDoor->unlock();
    testDoor->lock();
    testDoor->lock();
    EXPECT_FALSE(testDoor->isDoorOpened());
}


TEST_F(ST3_Strakhov, throwState1) {
    testDoor->unlock();
    EXPECT_THROW(testDoor->throwState(), std::runtime_error);
}
TEST_F(ST3_Strakhov, throwState2) {
    testDoor->unlock();
    testDoor->lock();
    EXPECT_THROW(testDoor->throwState(), std::runtime_error);
}

TEST_F(ST3_Strakhov, Timeout1) {
  DoorTimerAdapter testAdapter(* testDoor);
  testDoor->unlock();
  EXPECT_THROW(testAdapter.Timeout(), std::runtime_error);
}
TEST_F(ST3_Strakhov, Timeout2) {
  DoorTimerAdapter testAdapter(* testDoor);
  testDoor->unlock();
  testDoor->lock();
  EXPECT_NO_THROW(testAdapter.Timeout(), std::runtime_error);
}
TEST_F(ST3_Strakhov, throwState3) {
  testDoor->unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(70));
  EXPECT_THROW(testDoor->throwState(), std::runtime_error);
}

//проверки запуститесь

