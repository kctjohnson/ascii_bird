#include <chrono>
#include <thread>

class Clock {
private:
    std::chrono::_V2::system_clock::time_point m_start;
    std::chrono::_V2::system_clock::time_point m_end;

public:
    void Start() { this->m_start = std::chrono::high_resolution_clock::now(); }
    void Sleep(std::chrono::duration<int64_t, std::milli> sleepTime) { std::this_thread::sleep_for(sleepTime); }
    void CapFPS(double fps) {
        // Sleep for the amount of leftover time for the frame
        this->m_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = this->m_end - this->m_start;
        double leftoverTime = (1000.0 / fps) - elapsed.count();
        this->Sleep(std::chrono::milliseconds((long)leftoverTime));

        // Start the timer again
        this->Start();
    }
};
