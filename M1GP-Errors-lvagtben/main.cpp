#include "spie.cpp"
using namespace std;

int main() {
    spie game = spie();
    game.print_rules(cout);
    game.print_winning_numbers(cout);

    int score = 5;
    char choice = 'p';

    while (choice != 'e') {
        choice = game.get_player_choice(cout);

        switch(choice) {
            case 's':
                game.scramble(cout);
            break;
            case 'i':
                game.print_rules(cout);
            break;
            case 'p':
                cout << "Your score is " << score << endl;
            game.print_winning_numbers(cout);
            int dice_roll = game.roll_dice();
            cout << "Your dice roll is: " << dice_roll << endl;
            if (dice_roll == 2 || dice_roll == 12) {
                game.add_winning_number();
                cout << "You added a winning number!" << endl;
                game.print_winning_numbers(cout);
            }
            if (game.matches_winning_number(dice_roll)) {
                cout << "You won this round!" << endl;
                score += 5;
            } else {
                cout << "You lost this round!" << endl;
                --score;
                if (score == 0) {
                    choice = 'e';
                }
            }
        }
                cout << "Your new score is " << score << endl;
        }
    if (score == 0) {
        cout << "You lost the game!" << endl;
    }else {
        cout << "Play again soon!" << endl;
    }

    return 0;
}
