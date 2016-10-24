#pragma once

class Timer {
 public:
    virtual void reset() = 0;
    virtual void update(const std::function<void(double)>& update) = 0;
    virtual unsigned int getFPS() const = 0;
};