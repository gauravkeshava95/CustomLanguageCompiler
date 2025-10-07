#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace Mini
{

    class ErrorReporter
    {
    public:
        static ErrorReporter &instance()
        {
            static ErrorReporter e;
            return e;
        }
        void error(int line, int col, const std::string &msg)
        {
            hadError_ = true;
            messages_.push_back("Error[" + std::to_string(line) + ":" + std::to_string(col) + "]: " + msg);
        }
        bool hadError() const { return hadError_; }
        void printAllAndClear()
        {
            for (auto &m : messages_)
                std::cerr << m << "\n";
            messages_.clear();
            hadError_ = false;
        }

    private:
        bool hadError_{false};
        std::vector<std::string> messages_;
    };

} // namespace Mini
