#include "spie.h"

#include <algorithm>
#include <time.h>
using namespace std;
class spie {
private:
    vector<int> winning_numbers;
    const int MAX_NUMBERS = 12;
public:
    spie() {
        srand(time(NULL));
        winning_numbers.clear();
        add_winning_number();
        add_winning_number();
    }

    bool add_winning_number() {
        if (winning_numbers.size() == MAX_NUMBERS) {
            return false;
        }
        int new_number = rand() % MAX_NUMBERS + 1;
        while (count(winning_numbers.begin(), winning_numbers.end(), new_number) > 0) {
                new_number = rand() % MAX_NUMBERS + 1;
        }
        winning_numbers.push_back(new_number);
        return true;
    }

    char get_player_choice(ostream &outs) {
        char choice;
        cin.clear();
        print_options(outs);
        cin >> choice;
        while (!(choice == 's' || choice == 'p' || choice == 'i' || choice == 'e')) {
            outs << endl << "Invalid option. " << endl;
            print_options(outs);
            cin.clear();
            cin >> choice;
        }
        return choice;
    }

    bool matches_winning_number(int roll) const {
        for (int w = 0; w < winning_numbers.size(); ++w) {
            if (roll == winning_numbers[w]) {
                return true;
            }
        }
        return false;
    }

    void print_options(ostream &outs) {
        outs << "Press (s) to scramble, (p) to play, (i) for info, or (e) to exit: ";
    }

    void print_rules(ostream &outs) {
        outs << "Rules of SPIE Game:" << endl;
        outs << "If you roll the dice and match a winning number, you will get five points." << endl;
        outs << "If you roll the dice and do not match the winning numbers, you will lose one point." << endl;
        outs << "If you roll a 12 or a 2, a winning number will be added." << endl;
        outs << "If you scramble, you will roll the dice five times. If any of your dice rolls match a winning number, that number will be replaced in the winning numbers list" << endl;
        outs << "If you run out of points, you lose." << endl;
    }

    void print_winning_numbers(ostream &outs) const {
        outs << "The winning numbers are: ";
        for (int i = 0; i < winning_numbers.size(); ++i) {
            outs << winning_numbers[i];
            if (i < winning_numbers.size() - 1) {
                outs << ", ";
            }
        }
        outs << endl;
    }

    int roll_dice() {
        return (rand() % 6) + (rand() % 6) + 2;
    }

    void scramble(ostream &outs) {
        vector<int> dice_rolls;
        outs << "You rolled: ";
        for (int i = 0; i < 5; ++i) {
            dice_rolls.push_back(roll_dice());
            outs << dice_rolls[i];
            if (i < 4) {
                outs << ", ";
            }
        }
        outs << endl;

        int replacements = 0;
        for (int w = 0; w < winning_numbers.size(); ++w) {
            for (int r = 0; r < dice_rolls.size(); ++r) {
                if (dice_rolls[r] == winning_numbers[w]) {
                    winning_numbers.erase(winning_numbers.begin() + w);
                    ++replacements;
                }
            }
        }

        outs << "You replaced " << replacements << " winning numbers!" << endl;

        for (int i = 0; i < replacements; ++i) {
            add_winning_number();
        }

        print_winning_numbers(outs);
    }
};