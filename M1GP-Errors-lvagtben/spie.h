#ifndef ERRORS_SPIE_H
#define ERRORS_SPIE_H

#include <iostream>
#include <vector>
using namespace std;

class SPIE_Game {
private:
    vector<int> winning_numbers;
    const int MAX_NUMBERS = 12;
public:
    /*
     * Default Constructor
     * Requires: nothing
     * Modifies: winning_numbers
     * Effects: Sets winning_numbers to two randomly chosen integers
     */
    SPIE_Game();

    /*
     * Add a winning number
     * Requires: nothing
     * Modifies: winning_numbers
     * Effects: Adds a random integer to winning_numbers if there is room.
     *          Does not allow for duplicate values in winning_numbers.
     *          Returns true if value is added, false otherwise.
     */
    bool add_winning_number();

    /*
     * Get player choice
     * Requires: nothing
     * Modifies: outs and ins
     * Effects: Prints the options to outs and gets user input. Checks for validity.
     */
    static char get_player_choice(ostream &outs, istream &ins);

    /*
     * Matches winning number
     * Requires: nothing
     * Modifies: nothing
     * Effects: Returns true if roll matches any number in winning_numbers. Returns false otherwise.
     */
    bool matches_winning_number(int roll) const;

    /*
     * Print options
     * Requires: nothing
     * Modifies: outs
     * Effects: Prints the options to outs
     */
    static void print_options(std::ostream &outs);

    /*
     * Print rules
     * Requires: nothing
     * Modifies: outs
     * Effects: Prints the game's rules to outs
     */
    static void print_rules(std::ostream &outs);

    /*
     * Print winning numbers
     * Requires: nothing
     * Modifies: outs
     * Effects: Prints the winning numbers to outs
     */
    void print_winning_numbers(ostream &outs) const;

    /*
     * Roll dice
     * Requires: nothing
     * Modifies: nothing
     * Effects: Simulates rolling two dice. Returns the sum of the rolls.
     */
    static int roll_dice();

    /*
     * Scramble
     * Requires: nothing
     * Modifies: winning_numbers, outs
     * Effects: Rolls dice five times. If any rolls match a winning_number, that winning_number is replaced.
     */
    void scramble(std::ostream &outs);
};


#endif //ERRORS_SPIE_H
