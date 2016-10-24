#pragma once
#include <utils/Timer.h>

const int TIMER_RESOLUTION = 1000000;
const double TIMER_ONE_SECOND = 1.0;

class FixedStepTimer : public Timer {
public:
    FixedStepTimer(float targetFPS) {
        mTarget = 1.0/targetFPS;
    }

    void reset() {
        glfwSetTime(0.0);
        mLeftOver = mLastTime = mTotalTime = 0.0;
        mSecondCounter = mFPS = mFrameCounter = 0;
    }

    unsigned int getFPS() const { return mFPS; }

    void update(const std::function<void(double)>& update) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - mLastTime;
        mLastTime = currentTime;

        // Second counter tracks whether we have crossed one second
        mSecondCounter += (unsigned int)(deltaTime * TIMER_RESOLUTION);

        // deltaTime between two frames shouldn't be greater than one second
        // for mathematical reasons
        if (deltaTime > TIMER_ONE_SECOND)
            deltaTime = TIMER_ONE_SECOND;

        // Do not accumulate small errors
        if (fabs(deltaTime - mTarget) < 1.0 / 40000.0f)
            deltaTime = mTarget;

        // Add left over time from previous update
        mLeftOver += deltaTime;

        // If target time has passed, we shall update new frame
        // so increment the frame counter
        if (mLeftOver >= mTarget)
            ++mFrameCounter;

        // If more than target time has passed, update as much
        // as needed with fixed time-step
        while (mLeftOver >= mTarget) {
            mTotalTime += mTarget;
            mLeftOver -= mTarget;
            update(mTarget);
        }

        if (mSecondCounter >= TIMER_RESOLUTION) {
            mFPS = mFrameCounter;
            mFrameCounter = 0;
            mSecondCounter %= TIMER_RESOLUTION;
        }
    }

private:
    double mLastTime, mTarget, mLeftOver, mTotalTime;
    unsigned int mFPS, mFrameCounter, mSecondCounter;
};