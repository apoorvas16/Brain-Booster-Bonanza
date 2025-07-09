# 🧠 Brain Booster Bonanza

**Brain Booster Bonanza** is a terminal-based C++ game designed for children to improve their knowledge and IQ in various subjects like:

- 🧮 **Mathematics**: Number patterns, arithmetic quizzes  
- ✍️ **English**: Word puzzles, sentence jumbles  
- 🌍 **General Knowledge**: Country capitals, animal quizzes  

### 💡 Features

- Three subject areas with multiple games  
- Easy, Medium, and Hard difficulty levels  
- Colorful terminal output for better UX  
- Randomized content using external `.txt` files  
- Score tracking per round  

### 📂 Files Included

- `new.cpp` — Main game code  
- `easy_patterns.txt`, `medium_patterns.txt`, `hard_patterns.txt` — Number patterns  
- `easynum.txt`, `mednum.txt`, `hardnum.txt` — Math quiz numbers  
- `easy.txt`, `medium.txt`, `hard.txt` — Sentence jumble sources  
- `countries.txt` — Country-capital pairs  
- `aquestions.txt` — Animal quiz questions  

### ▶️ How to Run

```bash
g++ new.cpp -o game
./game
