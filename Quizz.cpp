#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <chrono>

double truncateToTwo(double v) {
    return std::floor(v * 100.0) / 100.0;
}

std::string formatDecimal(double v) {
    std::ostringstream o;
    if (std::fabs(v - std::round(v)) < 1e-9)
        o << static_cast<long long>(std::round(v));
    else {
        o << std::fixed << std::setprecision(2) << v;
        std::string s = o.str();
        size_t p = s.find_last_not_of('0');
        if (s[p] == '.') p--;
        return s.substr(0, p + 1);
    }
    return o.str();
}

std::string formatTime(long long secs) {
    long long m = secs / 60;
    long long s = secs % 60;
    if (m > 0) {
        std::ostringstream o;
        o << m << " min " << s << " sec";
        return o.str();
    }
    return std::to_string(s) + " sec";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int max_x = 0, max_y = 0;
    while (true) {
        std::cout << "Enter maximum numerator and denominator values (both >= 1), separated by space: ";
        if (std::cin >> max_x >> max_y && max_x >= 1 && max_y >= 1) break;
        clearInput();
    }
    clearInput();

    std::vector<std::pair<int,int>> pool;
    for (int i = 1; i <= max_x; ++i)
        for (int j = 1; j <= max_y; ++j)
            pool.emplace_back(i,j);

    std::mt19937 gen(std::random_device{}());
    std::shuffle(pool.begin(), pool.end(), gen);

    size_t idx = 0;
    int correctCount = 0, wrongCount = 0;
    long long totalSecs = 0;

    std::cout << "\n📘 Fraction Quiz Game Started! Type 'q', 'quit', or 'result'.\n\n";

    auto quizStart = std::chrono::high_resolution_clock::now();

    while (idx < pool.size()) {
        int x = pool[idx].first;
        int y = pool[idx].second;
        ++idx;

        double correct = truncateToTwo((100.0 * x) / y);
        std::string correctStr = formatDecimal(correct);

        std::cout << "Calculate: " << x << " / " << y << " = ";
        auto t1 = std::chrono::high_resolution_clock::now();
        std::string in;
        std::getline(std::cin, in);
        auto t2 = std::chrono::high_resolution_clock::now();
        long long qSecs = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
        totalSecs += qSecs;

        if (in == "q" || in == "quit") break;

        if (in == "result") {
            int total = correctCount + wrongCount;
            double pct = total ? truncateToTwo(100.0 * correctCount / total) : 0.0;
            std::cout << "Answered: " << total
                      << ", Correct: " << correctCount
                      << ", Wrong: " << wrongCount
                      << ", Accuracy: " << formatDecimal(pct) << "%\n"
                      << "Total Time: " << formatTime(totalSecs) << "\n\n";
            --idx;
            continue;
        }

        std::istringstream iss(in);
        double userVal;
        if (!(iss >> userVal)) {
            std::cout << "❌ Invalid input. Time: " << formatTime(qSecs) << "\n\n";
            --idx;
            continue;
        }

        userVal = truncateToTwo(userVal);
        if (std::fabs(userVal - correct) < 1e-9) {
            std::cout << "✔️ Correct! Time: " << formatTime(qSecs) << "\n\n";
            ++correctCount;
        } else {
            std::cout << "❌ Wrong! Time: " << formatTime(qSecs) << "\n";
            std::cout << "The correct answer is " << correctStr << "\n\n";
            ++wrongCount;
        }
    }

    auto quizEnd = std::chrono::high_resolution_clock::now();
    long long overallSecs = std::chrono::duration_cast<std::chrono::seconds>(quizEnd - quizStart).count();
    int total = correctCount + wrongCount;
    double pct = total ? truncateToTwo(100.0 * correctCount / total) : 0.0;
    std::cout << "📊 Quiz Complete! Total: " << total
              << ", Correct: " << correctCount
              << ", Wrong: " << wrongCount
              << ", Accuracy: " << formatDecimal(pct) << "%\n"
              << "Total Time: " << formatTime(totalSecs) << "\n"
              << "Overall Time: " << formatTime(overallSecs) << "\n";
    return 0;
}
