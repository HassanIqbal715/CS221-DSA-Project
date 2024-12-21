#include "include/Functions.hpp"

void printTitle() {
    cout << "         _____ _____            _   _  ____  _                _____\n";
    cout << "        / ____|  __ \\     /\\   | \\ | |/ __ \\| |        /\\    / ____|\n";       
    cout << "       | |  __| |__) |   /  \\  |  \\| | |  | | |       /  \\  | (___\n";         
    cout << "       | | |_ |  _  /   / /\\ \\ | . ` | |  | | |      / /\\ \\  \\___ \\\n";        
    cout << "       | |__| | | \\ \\  / ____ \\| |\\  | |__| | |____ / ____ \\ ____) |\n";      
    cout << "        \\_____|_|_ \\_\\/_/____\\_\\_| \\_|\\____/|______/_/____\\_\\_____/  _____\n";
    cout << "     /\\   |  __ \\ \\    / /  ____| \\ | |__   __| |  | |  __ \\|  ____|/ ____|\n";
    cout << "    /  \\  | |  | \\ \\  / /| |__  |  \\| |  | |  | |  | | |__) | |__  | (___\n";
    cout << "   / /\\ \\ | |  | |\\ \\/ / |  __| | . ` |  | |  | |  | |  _  /|  __|  \\___ \\\n"; 
    cout << "  / ____ \\| |__| | \\  /  | |____| |\\  |  | |  | |__| | | \\ \\| |____ ____) |\n";
    cout << " /_/    \\_\\_____/   \\/   |______|_| \\_|  |_|   \\____/|_|  \\_\\______|_____/\n"; 
    cout << '\n';                                                                           
}

void printUserBalance() {
    cout << "Balance: " << userBalance << " Rs\n";
}

void printHealthBar(int currentHealth, int maxHealth) {
    float percentage = float(float(currentHealth) / maxHealth) * 100;
    for (int i = 0; i < percentage; i += 5) {
        cout << "|";
    }
}

void fixStringCase(string& text) {
    if (text[0] >= 'a' && text[0] <= 'z') {
        text[0] -= 32;
    }

    for (int i = 1; i < text.size(); i++) {
        if (text[i - 1] != ' ') { 
            if (text[i] >= 'A' && text[i] <= 'Z') {
                text[i] += 32;
            }
        }
        else {
            if (text[i] >= 'a' && text[i] >= 'z') {
                text[i] -= 32;
            }
        }
    }
}