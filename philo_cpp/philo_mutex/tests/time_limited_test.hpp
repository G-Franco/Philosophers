#pragma once

#include <atomic>
#include <chrono>
#include <future>
#include <gtest/gtest.h>
#include <thread>

template <typename Func>
void RunTestWithTimeLimit(Func func, int seconds, bool expect_failure, data &data) {
  std::atomic<bool> stop_flag(false);
  auto future = std::async(std::launch::async, [&]() {
    while (!stop_flag.load()) {
      func();
      return;
    }
  });

  if (future.wait_for(std::chrono::seconds(seconds)) ==
      std::future_status::timeout) {
    stop_flag.store(true); // Signal the test function to stop
    if (expect_failure) {
      SUCCEED();
    } else {
      FAIL() << "Test did not complete within the time limit";
    }
  } else {
    try {
      future.get();
      if (expect_failure) {
        FAIL() << "Test completed before reaching the time limit";
      } else {
        SUCCEED();
      }
    } catch (...) {
      if (expect_failure) {
        SUCCEED();
      } else {
        throw;
      }
    }
  }
}