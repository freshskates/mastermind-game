#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <fstream> 
bool play(int game);
bool validate(string guess);
char convert(int num);
const int MAX = 100;
char convert(int num) 
{
    char color;
    switch (num)  //blue = 0, green = 1, red = 2, white = 3, count = 0;
    {
    case 0: color = 'B'; break;
    case 1: color = 'G'; break;
    case 2: color = 'R'; break;
    case 3: color = 'W'; break;
    }
    return color; //dont need default because number generator will only make 0 - 3
}
bool validate(string guess) 
{
    bool valid = true; 
    if (guess.length() > 4) return false; 
    for (int i = 0; i < 4; i++) 
    {
        if (toupper(guess[i]) != 'W' && toupper(guess[i]) != 'R' && toupper(guess[i]) != 'G' && toupper(guess[i]) != 'B') return false;
    }
}
bool play(int game) {
 
    ifstream fin; 
    ofstream fout;
    string inputfile = "scores.txt";
    string outputfile = "scores.txt";
    int lcount = 0;
    int storage[MAX];
    fin.open(inputfile);
    while (fin.good()) {
        int line; 
        fin >> line;
        storage[lcount] = line; 
        lcount++;
    }
    fin.close();
    int temp, max = -999, min = 999;

    for (int i = 0; i < lcount; i++) {

        if (storage[i] < min) {

            min = storage[i];
        }

        if (storage[i] > max) {
            max = storage[i];

        }

    }


    char cpu_key1 = convert(rand() % 4);
    char cpu_key2 = convert(rand() % 4);
    char cpu_key3 = convert(rand() % 4);
    char cpu_key4 = convert(rand() % 4);
    cout << "(For Testing) Cheat Code: " << cpu_key1 << cpu_key2 << cpu_key3 << cpu_key4 << endl; //used this to troubleshoot, was troubleshooting for about 2 hours because of a dumb mistake
    bool firsthalf, secondhalf, overall;
    char again; 
    int count = 0; 

    cout << "Game #" << game + 1 << endl << endl;
    cout << "The best score to date is: " << min << endl; //its min because lower numbers means less times to guess
    cout << "Lowest Score: " << max << endl; 
    cout << "Welcome to MasterMind, the rules are simply try to guess the master code" << endl << "The code is only 4 Colors, and they consist of blue, green, red and white" << endl << "B) Blue" << endl << "G) Green" << endl << "R) Red" << endl << "W) White" << endl;
    cout << "Make sure to enter each color with no space in between!" << endl;
    cout << "You only get 10 attempts! Have fun and good luck!" << endl;

    cout << "Press Enter to continue: " << endl;
    cin.ignore(1000, 10);

    do 
    {
        string guess;
        cout << "Try #" << count + 1 << " | Your guess: ";
        cin >> guess;
        while (validate(guess) == false) 
        {
            cout << "Invalid Entry, Please try again." << endl;
            cout << "Try #" << count + 1 << " | Your guess: ";
            cin >> guess;

        }
        if (toupper(guess[0]) == cpu_key1) firsthalf = true;
        else firsthalf = false;
        if (toupper(guess[1]) == cpu_key2) firsthalf = true;
        if (toupper(guess[2]) == cpu_key3) secondhalf = true;
        else secondhalf = false;
        if (toupper(guess[3]) == cpu_key4) secondhalf = true;
        if (toupper(guess[0]) == cpu_key1 && toupper(guess[1]) == cpu_key2 && toupper(guess[2]) == cpu_key3 && toupper(guess[3]) == cpu_key4) 
        {
            cout << "Congrats! You have beaten mastermind!" << endl;
            break;
        }
        else overall = false;
        if (firsthalf == true) cout << "Something in first half is correct" << endl;
        else cout << "Nothing right first half" << endl;
        if (secondhalf == true) cout << "Something in second half is correct" << endl;
        else cout << "Nothing right second half" << endl;
        count++;
        if (count == 10) break;

    } while (overall == false);
    if (count == 10) cout << "You had 10 chances and YOU LOST!" << endl;

    
    storage[lcount] = count;
    lcount++;


    fout.open(outputfile);
    for (int i = 0; i < lcount; i++) {
        fout << storage[i] << endl;
    }
    fout.close();



    cout << "Play again? [Y/N]: ";
    cin >> again;
    cin.ignore(1000, 10);
    if (toupper(again) == 'Y') 
    {
        cout << endl;
        return true;
    }
    else 
    {
        cout << "Thank you for playing MasterMind! Goodbye!" << endl;
        return false;
    }

}
int main()
{
    bool again;
    int game = 0;
    srand(time(0));
    do 
    {
        again = play(game);
        game++;
    } while (again == true);
    


}