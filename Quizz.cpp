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

// Truncates a double to two decimal places without rounding
double truncateToTwo(double v) {
    return std::floor(v * 100.0) / 100.0;
}

// Formats a double for display, removing trailing zeros
std::string formatDecimal(double v) {
    std::ostringstream o;
    // Check if the number is effectively an integer
    if (std::fabs(v - std::round(v)) < 1e-9) {
        o << static_cast<long long>(std::round(v));
    } else {
        o << std::fixed << std::setprecision(2) << v;
        std::string s = o.str();
        // Remove trailing zeros and decimal point if not needed
        size_t p = s.find_last_not_of('0');
        if (s[p] == '.') {
            p--;
        }
        return s.substr(0, p + 1);
    }
    return o.str();
}

// Formats seconds into a more readable string (e.g., "1 min 30 sec" or "45 sec")
std::string formatTime(long long secs) {
    if (secs < 0) secs = 0;
    long long m = secs / 60;
    long long s = secs % 60;
    if (m > 0) {
        std::ostringstream o;
        o << m << " min " << s << " sec";
        return o.str();
    }
    return std::to_string(s) + " sec";
}

// Clears the input buffer in case of invalid input
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int max_numerator = 0, max_denominator = 0;
    // Loop until valid maximums for numerator and denominator are entered
    while (true) {
        std::cout << "Enter maximum numerator and denominator values (e.g., 10 10): ";
        if (std::cin >> max_numerator >> max_denominator && max_numerator >= 1 && max_denominator >= 1) {
            break;
        }
        std::cout << "Invalid input. Please enter two numbers greater than or equal to 1.\n";
        clearInput();
    }
    clearInput(); // Clear the buffer after successful input

    // Create a pool of all possible fractions
    std::vector<std::pair<int, int>> question_pool;
    for (int i = 1; i <= max_numerator; ++i) {
        for (int j = 1; j <= max_denominator; ++j) {
            question_pool.emplace_back(i, j);
        }
    }

    // Shuffle the questions for a random order
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(question_pool.begin(), question_pool.end(), gen);

    size_t question_index = 0;
    int correct_count = 0, wrong_count = 0;
    long long total_question_time_secs = 0;

    std::cout << "\n🎮 Fraction Quiz Started! Type 'q', 'quit', or 'result' anytime.\n\n";
    auto session_start_time = std::chrono::high_resolution_clock::now();

    while (question_index < question_pool.size()) {
        int x = question_pool[question_index].first;
        int y = question_pool[question_index].second;

        // Calculate the correct answer as a percentage
        double correct_answer = truncateToTwo((100.0 * x) / y);
        std::string correct_answer_str = formatDecimal(correct_answer);

        std::cout << "❓ Calculate: " << x << " / " << y << " = ";
        auto question_start_time = std::chrono::high_resolution_clock::now();
        
        std::string user_input;
        std::getline(std::cin, user_input);
        
        auto question_end_time = std::chrono::high_resolution_clock::now();
        long long question_duration_secs = std::chrono::duration_cast<std::chrono::seconds>(question_end_time - question_start_time).count();

        // Handle special commands
        if (user_input == "q" || user_input == "quit") {
            break; // Exit the quiz loop
        }

        if (user_input == "result") {
            int total_answered = correct_count + wrong_count;
            double accuracy = total_answered ? truncateToTwo(100.0 * correct_count / total_answered) : 0.0;
            std::cout << "🔹 Answered: " << total_answered
                      << ", Correct: " << correct_count
                      << ", Wrong: " << wrong_count
                      << ", Accuracy: " << formatDecimal(accuracy) << "%\n";
            std::cout << "🔹 Total Time: " << formatTime(total_question_time_secs) << "\n\n";
            continue; // Ask the same question again
        }

        // Process the user's answer
        std::istringstream iss(user_input);
        double user_value;
        if (!(iss >> user_value)) {
            std::cout << "❌ Invalid input! Please enter a number. ⏱️ " << formatTime(question_duration_secs) << "\n\n";
            continue; // Ask the same question again
        }
        
        // The user's answer is processed, so add time and move to the next question
        total_question_time_secs += question_duration_secs;
        question_index++;

        user_value = truncateToTwo(user_value);
        if (std::fabs(user_value - correct_answer) < 1e-9) {
            std::cout << "✅ Correct! ⏱️ " << formatTime(question_duration_secs) << "\n\n";
            correct_count++;
        } else {
            std::cout << "❌ Wrong! ⏱️ " << formatTime(question_duration_secs) << "\n";
            std::cout << "🔹 The correct answer was " << correct_answer_str << "\n\n";
            wrong_count++;
        }
    }

    auto session_end_time = std::chrono::high_resolution_clock::now();
    long long overall_session_secs = std::chrono::duration_cast<std::chrono::seconds>(session_end_time - session_start_time).count();
    
    int total_questions = correct_count + wrong_count;
    double final_accuracy = total_questions ? truncateToTwo(100.0 * correct_count / total_questions) : 0.0;

    // Display final results
    std::cout << "\n🏁 Quiz Complete!\n";
    std::cout << "🔹 Total Questions: " << total_questions << "\n";
    std::cout << "✅ Correct: " << correct_count << "\n";
    std::cout << "❌ Wrong: " << wrong_count << "\n";
    std::cout << "🎯 Accuracy: " << formatDecimal(final_accuracy) << "%\n";
    std::cout << "⏱️ Total Time: " << formatTime(total_question_time_secs) << "\n";
    std::cout << "🕒 Overall Session Time: " << formatTime(overall_session_secs) << "\n";

    return 0;
}
