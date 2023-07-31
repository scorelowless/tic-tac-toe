#include <iostream>
#include <limits>

using namespace std;

void display(){
    cout << "\033[2J\033[H";
    cout << "     |     |     \n";
    cout << "  1  |  2  |  3  \n";
    cout << "     |     |     \n";
    cout << "-----------------\n";
    cout << "     |     |     \n";
    cout << "  4  |  5  |  6  \n";
    cout << "     |     |     \n";
    cout << "-----------------\n";
    cout << "     |     |     \n";
    cout << "  7  |  8  |  9  \n";
    cout << "     |     |     \n";
    cout << "Player 1, choose a field from 1 to 9 and confirm with enter: " << flush;
}

int table[9] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
// i used random numbers so check() won't trigger because there are 3 empty fields in one line
// and yes, i could write additional check that 3 fields aren't empty but i don't want to mess anymore with this if
bool player = false;

bool check(){
    // don't mind this condition, it just checks every single line on a 3x3 grid
    if((table[0] == table[3] && table[3] == table[6]) || (table[1] == table[4] && table[4] == table[7]) || (table[2] == table[5] && table[5] == table[8]) || (table[0] == table[1] && table[1] == table[2]) || (table[3] == table[4] && table[4] == table[5]) || (table[3] == table[4] && table[4] == table[5]) || (table[6] == table[7] && table[7] == table[8]) || (table[0] == table[4] && table[4] == table[8]) || (table[2] == table[4] && table[4] == table[6])){
        cout << "\033[13;1H" << "Player " << player+1 << " wins!" << flush;
        return true;
    }
    return false;
}

int main(){
    char map[2] = {'X', 'O'};
    display();
    int field;
    for(int i = 0; i < 9; i++){
        cin >> field;
        if (cin.fail()) { // if input isn't a number
            cout << "\033[13;1H" << "That's not a valid move! Try again.";
            cout << "\033[12;62H\033[K" << flush;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
            continue;
        }
        if(field > 9 || field < 0 || table[field-1] != field+10){ // if input is out of bounds or already used
            cout << "\033[13;1H" << "That's not a valid move! Try again.";
            cout << "\033[12;62H\033[K" << flush;
            i--;
            continue;
        }
        table[field-1] = player + 1;
        cout << "\033[" << (field-1)/3 * 4 + 2 << ";" << (field-1)%3 * 6 + 3 << "H" << map[player];
        if(check())
            return 0;
        player = !player; // change players
        cout << "\033[12;8H" << player+1; // change displayed player
        cout << "\033[13;1H2K"; // remove potentional "invalid move" warning
        cout << "\033[12;62H\033[0J" << flush; // remove the displayed input from previous player
    }
    cout << "\nDraw!";
}