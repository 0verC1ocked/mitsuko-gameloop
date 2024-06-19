#pragma once
#include <string>
#include <chrono>

struct EventMessage {
    bool processed = false;
    std::string message;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> created_at;
    
    EventMessage() = default;

    EventMessage(const std::string& message) : message(message) {
        created_at = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    }

    ~EventMessage() = default;

    bool checkIfExpired() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - created_at).count() > 7;
    }
};
