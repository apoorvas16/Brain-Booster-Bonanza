#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <random> 

using namespace std;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

// Define a class for the number pattern game
class NumberPatternGame {
    private:
        vector<int> sequence;
        int missingIndex;
    public:
        int missingNumber;
        NumberPatternGame(vector<int> seq, int index, int number) : sequence(seq), missingIndex(index), missingNumber(number) {}
    
        void displayPatternWithMissingNumber() {
            for (int i = 0; i < sequence.size(); ++i) {
                if (i == missingIndex) cout << " ? ";
                else cout << sequence[i] << " ";
            }
            cout << endl;
        }
    
        int checkAnswer(int answer) {
            return answer == missingNumber;
        }
    };

    class MathGame {
        public:
            void start() {
                int totalQuestions = 0;
                int score = 0;
        
                cout << RED << "\n\n \t\t\t Welcome to the Arithmetic Math Game! \n\n" << RESET;
        
            level_reset:
                cout << "Select difficulty level:\n";
                cout << "1) Easy level\n";
                cout << "2) Medium level\n";
                cout << "3) Hard level\n\n";
        
                int numQuestions;
                int difficulty;
        
                cout << "Enter your choice (1-3): ";
                cin >> difficulty;
        
                if (difficulty == 1) {
                    numQuestions = 5;
                } else if (difficulty == 2) {
                    numQuestions = 7;
                } else if (difficulty == 3) {
                    numQuestions = 10;
                } else {
                    cout << RED << "Invalid difficulty level! Please choose a level between 1 and 3.\n\n\n" << RESET;
                    goto level_reset;
                }
        
                score += playLevel(difficulty, numQuestions);
                totalQuestions += numQuestions;
        
                cout << RED << "\t\t\t Game over! \n" << RESET;
                cout << "Your score: " << score << " out of " << totalQuestions << "." << endl;
            }
        
        private:
            vector<int> levels = {1, 2, 3};
        
            int generateRandomNumberFromFile(const string& filename) {
                ifstream file(filename);
                int randomNumber;
                int numLines = 0;
        
                if (file.is_open()) {
                    while (file >> randomNumber) numLines++;
        
                    file.clear();
                    file.seekg(0, ios::beg);
                    int lineNumber = rand() % numLines;
        
                    for (int i = 0; i <= lineNumber; ++i) {
                        file >> randomNumber;
                    }
        
                    file.close();
                    return randomNumber;
                } else {
                    cout << RED << "Error opening file: " << filename << RESET << endl;
                    return 0;
                }
            }
        
            char generateRandomOperation() {
                char operations[] = {'+', '-', '*', '/'};
                int index = rand() % 4;
                return operations[index];
            }
        
            void generateQuestion(int difficulty, int& num1, int& num2, char& operation) {
                string filename;
                if (difficulty == 1) filename = "easynum.txt";
                else if (difficulty == 2) filename = "mednum.txt";
                else filename = "hardnum.txt";
        
                num1 = generateRandomNumberFromFile(filename);
                num2 = generateRandomNumberFromFile(filename);
                operation = generateRandomOperation();
            }
        
            float calculateAnswer(int num1, int num2, char operation) {
                switch (operation) {
                    case '+': return num1 + num2;
                    case '-': return num1 - num2;
                    case '*': return num1 * num2;
                    case '/': return static_cast<float>(num1) / num2;
                }
                return 0;
            }
        
            void displayQuestion(int num1, int num2, char operation) {
                cout << BLUE << "Question: " << num1 << " " << operation << " " << num2 << " = \n" << RESET;
                cout << "Your answer: ";
            }
        
            int playLevel(int difficulty, int numQuestions) {
                int score = 0;
        
                for (int i = 0; i < numQuestions; ++i) {
                    int num1, num2;
                    char operation;
                    float correctAnswer;
        
                    // Ensure we get a non-fraction result for division
                    while (true) {
                        generateQuestion(difficulty, num1, num2, operation);
                        correctAnswer = calculateAnswer(num1, num2, operation);
                        if (operation != '/' || correctAnswer == static_cast<int>(correctAnswer)) break;
                    }
        
                    cout << endl;
                    displayQuestion(num1, num2, operation);
        
                    int userAnswer;
                    cin >> userAnswer;
        
                    if (userAnswer == static_cast<int>(correctAnswer)) {
                        cout << GREEN << "Correct!" << RESET << endl;
                        score++;
                    } else {
                        cout << RED << "Incorrect!\n" << RESET;
                        cout << "The correct answer is " << correctAnswer << "." << endl;
                    }
                }
        
                return score;
            }
        };
        

// Function to read number patterns from a file
vector<NumberPatternGame> readPatternsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << RED << "Error: Unable to open file " << filename << RESET << endl;
        exit(1);
    }

    vector<NumberPatternGame> patterns;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int number;
        vector<int> sequence;
        while (iss >> number) {
            sequence.push_back(number);
        }

        if (!sequence.empty()) {
            int index = rand() % sequence.size(); // Random missing index
            int missingNumber = sequence[index];
            patterns.push_back(NumberPatternGame(sequence, index, missingNumber));
        }
    }

    file.close();

    // Shuffle the patterns
    shuffle(patterns.begin(), patterns.end(), default_random_engine(time(nullptr)));

    return patterns;
}

// Function to show the user's score
void showScore(int correctAnswers, int totalQuestions) {
    cout << GREEN << "Your score: " << correctAnswers << " / " << totalQuestions << RESET << endl;
}

// Function to generate a random number within a range
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to create a word puzzle with random empty spaces
string createPuzzle(const string& word, int level) {
    string puzzle = word;
    int numEmptySpaces = 0;

    if (level == 1)
        numEmptySpaces = generateRandomNumber(1, 2);
    else if (level == 2)
        numEmptySpaces = generateRandomNumber(2, 3);
    else
        numEmptySpaces = generateRandomNumber(3, 4);

    vector<int> positions;
    for (int i = 0; i < word.size(); ++i) positions.push_back(i);
    shuffle(positions.begin(), positions.end(), default_random_engine(time(nullptr)));

    for (int i = 0; i < numEmptySpaces && i < positions.size(); ++i)
        puzzle[positions[i]] = '_';

    return puzzle;
}

// Function to display the word puzzle and prompt the user for their answer
bool playWordPuzzle(const string& word, int level) {
    string puzzle = createPuzzle(word, level);
    string answer;

    cout << BLUE << "Fill in the missing letter(s) to complete the word: " << puzzle << RESET << endl;
    cout << "Your answer: " << flush;
    getline(cin, answer); // safer than cin >> answer

    // Convert both to lowercase
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    string original = word;
    transform(original.begin(), original.end(), original.begin(), ::tolower);

    if (answer == original) {
        cout << GREEN << "Correct!" << RESET << endl;
        return true;
    } else {
        cout << RED << "Incorrect! The correct word was: " << word << RESET << endl;
        return false;
    }
}


// Function to select a random word from a list
string selectWord(const vector<string>& wordList) {
    int index = generateRandomNumber(0, wordList.size() - 1);
    return wordList[index];
}

// Function to generate a random sentence from a file
string generateRandomSentence(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file " + fileName);
    }

    vector<string> sentences;
    string sentence;
    while (getline(file, sentence)) {
        sentences.push_back(sentence);
    }
    file.close();

    if (sentences.empty())
        return "";

    int index = generateRandomNumber(0, sentences.size() - 1);
    return sentences[index];
}

// Function to jumble the words of a sentence
string jumbleWords(const string& sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    shuffle(words.begin(), words.end(), default_random_engine(time(nullptr)));

    string jumbledSentence;
    for (const string& w : words) {
        jumbledSentence += w + " ";
    }

    return jumbledSentence;
}
// Function to play the sentence jumble game
int playSentenceJumble(const string& sentence, int difficulty) {
    string jumbledSentence = jumbleWords(sentence);

    cout << BLUE << "\nUnscramble the following words to form a sentence:\n\n" << RESET;
    cout << jumbledSentence << endl;

    int score = 0;
    for (int i = 0; i < 3; ++i) {
        cout << "Enter your guess (" << i + 1 << "/3): ";
        string guess;
        getline(cin, guess);

        // Normalize: remove extra spaces and case differences
        string trimmedGuess = guess;
        trimmedGuess.erase(remove(trimmedGuess.begin(), trimmedGuess.end(), ' '), trimmedGuess.end());

        string trimmedSentence = sentence;
        trimmedSentence.erase(remove(trimmedSentence.begin(), trimmedSentence.end(), ' '), trimmedSentence.end());

        transform(trimmedGuess.begin(), trimmedGuess.end(), trimmedGuess.begin(), ::tolower);
        transform(trimmedSentence.begin(), trimmedSentence.end(), trimmedSentence.begin(), ::tolower);

        if (trimmedGuess == trimmedSentence) {
            cout << GREEN << "Congratulations! You unscrambled the sentence correctly.\n" << RESET;
            score += 10 * difficulty;
            break;
        } else {
            cout << RED << "Incorrect guess. Try again.\n" << RESET;
        }
    }

    if (score == 0) {
        cout << RED << "Sorry, you couldn't unscramble the sentence.\n" << RESET;
        cout << "The correct sentence is: " << sentence << endl;
    }

    return score;
}

// Function to shuffle questions
void shuffleQuestions(vector<pair<string, string>>& questions) {
    shuffle(questions.begin(), questions.end(), default_random_engine(time(nullptr)));
}

// Function to play the capitals and countries game
void playCapitalsCountriesGame(const vector<pair<string, string>>& questions, int numQuestions) {
    int score = 0;
    for (int i = 0; i < numQuestions; ++i) {
        const string& country = questions[i].first;
        const string& capital = questions[i].second;

        cout << "\nQuestion " << i + 1 << ": What is the capital of " << country << "?" << endl;
        string guess;
        cout << "Your answer: ";
        getline(cin, guess);

        // Normalize case
        string userAnswer = guess;
        string correctAnswer = capital;
        transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
        transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), ::tolower);

        if (userAnswer == correctAnswer) {
            cout << GREEN << "Correct!\n" << RESET;
            score++;
        } else {
            cout << RED << "Incorrect. The correct answer is: " << capital << "\n" << RESET;
        }
    }
    cout << GREEN << "\nYour score: " << score << "/" << numQuestions << RESET << endl;
}

// Function to play the animal quiz game
void playAnimalQuizGame(const vector<pair<string, string>>& animalQuestions) {
    int score = 0;
    for (const auto& question : animalQuestions) {
        const string& description = question.first;
        const string& animal = question.second;

        cout << "Question: " << description << endl;
        cout << "Your answer: ";
        string guess;
        getline(cin, guess);

        string userAnswer = guess;
        string correctAnswer = animal;
        transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
        transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), ::tolower);

        if (userAnswer == correctAnswer) {
            cout << GREEN << "Correct!\n" << RESET;
            score++;
        } else {
            cout << RED << "Incorrect. The correct answer is: " << animal << "\n" << RESET;
        }
    }

    cout << GREEN << "Your score: " << score << "/" << animalQuestions.size() << RESET << endl;
}


int main() {
    srand(time(0));

    vector<pair<string, string>> questions;
    ifstream file("countries.txt");
    if (!file.is_open()) {
        cerr << RED << "Unable to open file countries.txt" << RESET << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string country, capital;
        if (getline(ss, country, ',') && getline(ss, capital)) {
            questions.push_back(make_pair(country, capital));
        }
    }
    file.close();

    char playAgainChoice;
    do {
        cout << RED;
        cout << "\n\t\t\t==================================\n";
        cout << "\t\t\t      BRAIN BOOSTER BONANZA       \n";
        cout << "\t\t\t==================================\n" << RESET;

    subject_menu:
        cout << GREEN << "CHOOSE THE SUBJECT\n";
        cout << "1. MATHEMATICS\n";
        cout << "2. ENGLISH\n";
        cout << "3. GENERAL KNOWLEDGE\n";
        cout << "Enter your choice (1-3): ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
            math:
                cout << RED << "\n\nWELCOME TO GAME OF MATHEMATICS\n\n" << RESET;
                cout << BLUE << "Choose the game you want to play...\n" << RESET;
                cout << "1. Number Pattern Game\n";
                cout << "2. Mathematical Quiz Game\n";
                cout << "3. Back\n";
                cout << "Enter your choice (1-3): ";
                int ch;
                cin >> ch;
                cin.ignore();

                switch (ch) {
                    case 1: {
                        int level;
                        cout << "Choose the difficulty level:\n1. Easy\n2. Medium\n3. Hard\nEnter your choice: ";
                        cin >> level;
                        cin.ignore();

                        string filename;
                        int numPatterns;
                        if (level == 1) {
                            filename = "easy_patterns.txt";
                            numPatterns = 5;
                        } else if (level == 2) {
                            filename = "medium_patterns.txt";
                            numPatterns = 7;
                        } else if (level == 3) {
                            filename = "hard_patterns.txt";
                            numPatterns = 10;
                        } else {
                            cout << RED << "Invalid difficulty level!\n" << RESET;
                            break;
                        }

                        vector<NumberPatternGame> patterns = readPatternsFromFile(filename);
                        int correctAnswers = 0;

                        cout << "\nComplete the number patterns:\n";
                        sleep(1);
                        for (int i = 0; i < numPatterns; ++i) {
                            cout << GREEN << "Pattern " << i + 1 << ":\n" << RESET;
                            cout << BLUE;
                            patterns[i].displayPatternWithMissingNumber();
                            cout << RESET;

                            int answer;
                            while (true) {
                                cout << "Enter the missing number: ";
                                cin >> answer;
                                if (cin.fail()) {
                                    cin.clear();
                                    while (cin.get() != '\n') continue;
                                    cout << RED << "Invalid input! Please enter a number.\n" << RESET;
                                } else {
                                    break;
                                }
                            }

                            if (patterns[i].checkAnswer(answer)) {
                                cout << GREEN << "Correct!\n" << RESET;
                                correctAnswers++;
                            } else {
                                cout << RED << "Incorrect!\n" << RESET;
                                cout << "The correct answer is " << patterns[i].missingNumber << ".\n";
                            }
                            cout << endl;
                        }

                        showScore(correctAnswers, numPatterns);
                        cout << RED << "\nThanks for playing!\n" << RESET;
                        break;
                    }

                    case 2: {
                        MathGame game;
                        game.start();
                        break;
                    }

                    case 3:
                        goto subject_menu;

                    default:
                        cout << RED << "YOU ENTERED A WRONG CHOICE, ENTER AGAIN\n" << RESET;
                        goto math;
                }
                break;
            }

            case 2: {
            eng:
                cout << RED << "\n\nWELCOME TO GAME OF ENGLISH\n\n" << RESET;
                cout << BLUE << "Choose the game you want to play...\n" << RESET;
                cout << "1. Word Puzzle Game\n";
                cout << "2. Sentence Jumble Game\n";
                cout << "3. Back\n";
                cout << "Enter your choice (1-3): ";
                int ch;
                cin >> ch;
                cin.ignore();

                switch (ch) {
                    case 1: {
                        int level;
                        cout << "\nChoose the level you want to play:" << endl;
                        cout << "1. Easy" << endl;
                        cout << "2. Medium" << endl;
                        cout << "3. Hard" << endl;
                        cout << "Enter your choice (1-3): ";
                        cin >> level;
                        cin.ignore(); // Ignore leftover newline
            
                        // Word lists for each level
                        vector<string> easyWords = {"apple", "orange", "mango", "fruit", "house"};
                        vector<string> mediumWords = {"explore", "garden", "mountain", "puzzle", "rocket"};
                        vector<string> hardWords = {"watermelon", "happiness", "decision", "butterfly", "chocolate"};
            
                        int totalScore = 0;
                        for (int i = 0; i < 5; ++i) {
                            string word;
                            if (level == 1) {
                                word = selectWord(easyWords);
                            } else if (level == 2) {
                                word = selectWord(mediumWords);
                            } else {
                                word = selectWord(hardWords);
                            }
            
                            if (playWordPuzzle(word, level)) {
                                totalScore += 1;
                                cout << GREEN << "Correct!" << RESET << endl;
                            } else {
                                cout << RED << "Incorrect!" << RESET << endl;
                            }
                        }
            
                        cout << GREEN << "Total Score: " << totalScore << "/5" << RESET << endl;
                        break;
                    }        

                    case 2: {
                        int difficulty;
                        cout << "Choose the difficulty level (1-3): ";
                        cin >> difficulty;
                        cin.ignore();

                        int score = 0;
                        for (int i = 0; i < 5; ++i) {
                            string sentence;
                            if (difficulty == 1)
                                sentence = generateRandomSentence("easy.txt");
                            else if (difficulty == 2)
                                sentence = generateRandomSentence("medium.txt");
                            else
                                sentence = generateRandomSentence("hard.txt");

                            score += playSentenceJumble(sentence, difficulty);
                        }

                        cout << GREEN << "Total Score: " << score << "/50\n" << RESET;
                        break;
                    }

                    case 3:
                        goto subject_menu;

                    default:
                        cout << RED << "YOU ENTERED A WRONG CHOICE, ENTER AGAIN\n" << RESET;
                        goto eng;
                }
                break;
            }

            case 3: {
            gk:
                cout << RED << "\n\nWELCOME TO GENERAL KNOWLEDGE GAME\n\n" << RESET;
                cout << BLUE << "Choose the game you want to play...\n" << RESET;
                cout << "1. Capitals and Countries Game\n";
                cout << "2. Animal Quiz Game\n";
                cout << "3. Back\n";
                cout << "Enter your choice (1-3): ";
                int ch;
                cin >> ch;
                cin.ignore();

                switch (ch) {
                    case 1: {
                        shuffleQuestions(questions);
                        int num;
                        cout << "Enter number of questions: ";
                        cin >> num;
                        cin.ignore();

                        playCapitalsCountriesGame(questions, num);
                        break;
                    }

                    case 2: {
                        ifstream animalFile("aquestions.txt");
                        if (!animalFile.is_open()) {
                            cerr << RED << "Could not open aquestions.txt\n" << RESET;
                            break;
                        }
                        vector<pair<string, string>> animalQuestions;
                        string question, answer;
                        while (getline(animalFile, question) && getline(animalFile, answer)) {
                            animalQuestions.push_back({question, answer});
                        }
                        playAnimalQuizGame(animalQuestions);
                        break;
                    }

                    case 3:
                        goto subject_menu;

                    default:
                        cout << RED << "YOU ENTERED A WRONG CHOICE, ENTER AGAIN\n" << RESET;
                        goto gk;
                }
                break;
            }

            default:
                cout << RED << "YOU ENTERED A WRONG CHOICE, ENTER AGAIN\n" << RESET;
                goto subject_menu;
        }

        cout << BLUE << "\n\nDo you want to play again? (Y/N): " << RESET;
        cin >> playAgainChoice;
        cin.ignore();

    } while (playAgainChoice == 'Y' || playAgainChoice == 'y');

    cout << RED;
    cout << "\n\t\t  THANK YOU FOR PLAYING......\n";
    cout << "\n\t\t  HOPE YOU LIKED IT..........\n";
    cout << "\n\t\t  HAVE A NICE DAY AHEAD  " << (char)3 << " " << (char)3 << "  \n\n\n";
    cout << RESET;

    return 0;
} 