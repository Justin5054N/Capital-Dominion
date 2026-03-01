#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

// Deklarasi Function
void showMenu();
void startGame();
void showHighScore();
void saveHighScore(string name, int score);
int getHighScore();

const int Total = 50;

string country[Total] = {
"Indonesia","Jepang","Thailand","Perancis","Brazil",
"Malaysia","Singapura","Filipina","Vietnam","India",
"China","KoreaSelatan","KoreaUtara","Australia","AmerikaSerikat",
"Kanada","Argentina","Italia","Jerman","Belanda",
"Spanyol","Portugal","Mesir","ArabSaudi","UniEmiratArab",
"Turki","Rusia","Ukraina","Pakistan","Bangladesh",
"Nepal","SriLanka","Myanmar","Kamboja","Laos",
"Brunei","Meksiko","Chili","Kolombia","Peru",
"Venezuela","AfrikaSelatan","Nigeria","Kenya","Maroko",
"Aljazair","Irak","Iran","Yordania","Swiss"
};

string capital[Total] = {
"Jakarta","Tokyo","Bangkok","Paris","Brasilia",
"Kuala Lumpur","Singapura","Manila","Hanoi","New Delhi",
"Beijing","Seoul","Pyongyang","Canberra","Washington",
"Ottawa","Buenos Aires","Roma","Berlin","Amsterdam",
"Madrid","Lisbon","Kairo","Riyadh","AbuDhabi",
"Ankara","Moskow","Kyiv","Islamabad","Dhaka",
"Kathmandu","Colombo","Naypyidaw","PhnomPenh","Vientiane",
"Bandar Seri Begawan","Mexico city","Santiago","Bogota","Lima",
"Caracas","Pretoria","Abuja","Nairobi","Rabat",
"Algiers","Baghdad","Tehran","Amman","Bern"
};

string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

int main() {
    srand(time(0));

    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus angka!\n";
            continue;
        }
        
        switch(choice) {
            case 1: 
                startGame();
                break;
            case 2:
                showHighScore();
                break;
            case 3:
                cout << "\nTerima Kasih Sudah Bermain Tebak Ibu Kota Dari Kami Kelompok PHP!\n";
                break;
            default:
                cout << "Pilihan Tidak Valid!";
        }
    } while(choice != 3);

    return 0;
}

void showMenu() {
    cout << "\n===== CAPITAL DOMINION=====\n";
    cout << "1. Start Game\n";
    cout << "2. High Score\n";
    cout << "3. Exit\n";
    cout << "Pilih: ";
}

void startGame() {
   char mainLagi;

   do {
     string name;
    cin.ignore();
    cout << "\nMasukan Nama Pemain: ";
    getline(cin, name);

    int score = 0;
    int lives = 5;
    bool used[Total] = {false};
    int questionCount = 0;

    while ( lives > 0 && questionCount < Total) {
        int index = rand() % Total;

        if(used[index])
            continue;

        used[index] = true;
        questionCount++;

        string answer;
        cout << "\n Apa ibukota dari " << country[index] << "?";
        getline(cin, answer);

        if(toLowerCase(answer) == toLowerCase(capital[index])) {
            cout << "\nBenar!";
            score += 2;
        } else {
            cout << "\nSalah! Jawaban: " << capital[index] <<endl;
            lives--;
            cout << "nyawa tersisa:  " << lives <<endl;
            
        }
    }
        cout << "\nGame Over";
        cout << "Score Akhir: " << score <<endl;
        saveHighScore(name, score);

        cout << "\nMain lagi? (y/n)";
        cin >> mainLagi;
   } while(mainLagi == 'Y' || mainLagi== 'y');
}


 void saveHighScore(string name, int score) {
        ifstream readFile("highScore.txt");
        string oldName;
        int oldScore = 0;

        if(readFile.is_open()) {
            readFile >> oldName >> oldScore;
            readFile.close();
        }

        if(score > oldScore) {
            ofstream writeFile("highScore.txt");
            writeFile << name << " " << score;
            writeFile.close();
            cout << "\nHighScore Baru!!\n";
        }
    }

    void showHighScore() {
        ifstream file("highScore.txt");

        if(file.is_open()) {
            string name;
            int score;
            file >> name >> score;
            cout << "\n=== HIGH SCORE ===\n";
            cout << "Name: " << name <<endl;
            cout << "Score: " << score <<endl;
            file.close();
        } else {
            cout << "\nBelum Ada High Score.\n";
        };
    }

