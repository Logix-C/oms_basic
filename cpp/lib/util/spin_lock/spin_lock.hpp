#pragma once

#include <emmintrin.h>

#include <atomic>
#include <thread>

struct SpinLock {
    void lock() {
        while (true) {
            while (mu_.test(std::memory_order_acquire)) {
                _mm_pause();
            }

            if (!mu_.test_and_set(std::memory_order_acquire)) {
                return;
            }

            std::this_thread::yield();
        }
    }

    void unlock() {
        mu_.clear();
    }
private:
    std::atomic_flag mu_ = ATOMIC_FLAG_INIT;
};