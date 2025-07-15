
---

🎯 Fraction Quiz (C++)

A console-based quiz game that sharpens your fraction-to-percentage calculation skills while tracking accuracy and time with a clean workflow.


---

✨ Features

✅ Randomized fraction questions up to your chosen max numerator & denominator
✅ Clean truncation to 2-decimal percentages for answers
✅ Tracks:

Correct / Wrong counts

Per-question time

Total active answering time

Overall session time


✅ User-friendly commands:

q, quit – Exit the quiz

result – View your current score and time stats anytime


✅ Clear end summary for your progress tracking and improvement.


---

⚡ Quick Start

1️⃣ Clone the repository

git clone https://github.com/SamirYMeshram/Fraction-quiz-in-c-.git
cd Fraction-quiz-in-c-

2️⃣ Compile

g++ Quizz.cpp -std=c++17 -O2 -o quiz

3️⃣ Run the Quiz 🚀

./quiz

Follow on-screen instructions and start sharpening your fraction percentage speed!


---

🛠️ How It Works

🔹 Input: Max numerator & denominator (≥ 1) to generate all fraction combinations.
🔹 Shuffling: Uses a high-quality random generator for non-repeating questions.
🔹 User Answer: Provide your percentage value truncated to two decimals.
🔹 Commands: Check progress or quit anytime without losing prior data.
🔹 Timing: Measures:

Time per question

Total answer time

Total elapsed time


🔹 Formatting: Removes unnecessary trailing zeros for clean display.


---

🖥️ Example Session

Enter maximum numerator and denominator values (both >= 1), separated by space: 4 5

🎮 Fraction Quiz Started! Type 'q', 'quit', or 'result' anytime.

❓ Calculate: 1 / 2 = 50
✅ Correct! ⏱️ 3 sec

❓ Calculate: 2 / 5 = result
🔹 Answered: 1, Correct: 1, Wrong: 0, Accuracy: 100%
🔹 Total Time: 3 sec

❓ Calculate: 2 / 5 = 40
✅ Correct! ⏱️ 2 sec

...
🏁 Quiz Complete!
🔹 Total Questions: 15
✅ Correct: 14
❌ Wrong: 1
🎯 Accuracy: 93%
⏱️ Total Time: 85 sec
🕒 Overall Session Time: 92 sec


---

🚀 Potential Extensions

✨ Multiple-choice mode for quick learning
✨ Difficulty levels with adaptive timing
✨ Export results to .csv for tracking progress
✨ GUI or web-based adaptation using the same logic


---

📜 License

Apache License 2.0. See LICENSE.


---

👤 Author

Samir Yogendra Meshram
✉️ Email: sameerymeshram@gmail.com
🐙 GitHub: SamirYMeshram


---

If you want, I can also prepare a clean LICENSE file and GitHub labels and workflow badge suggestions to further professionalize your repository, or design a project logo badge for the top of your README. Let me know if you need these next to make your repo fully professional for your portfolio and internship applications.

