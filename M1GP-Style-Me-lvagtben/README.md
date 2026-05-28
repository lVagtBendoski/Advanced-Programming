# Style-Me
Transform this project to have great style!

## Setup
Use this Guided Project template to create a new repository (see [GitHub-with-CLion](https://github.com/uvmcs2300f2024/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Style-Me-netid**, where netid is your UVM NetID username.

Remember to commit and push frequently.

## Style main.cpp
* Read through main.cpp and figure out what the class and program are intended to do.
    * You can also run the program, if that helps you figure it out.
* Choose how you want to style the code. 
    * There are some style rules that everyone should follow:
        * Names should be readable and informative.
        * Variable and function names should start with a lowercase letter; class names should start with a capital letter.
        * Class methods should be defined in a .cpp file in the same order that they are declared in a header file.
        * Line comments should go before the line they address and should be included for any line of code that isn't easily readable, e.g.:
          ```cpp
          // Calculate the total distance in inches
          int total_distance_inches = (12 * feet) + inches;
          ```
        * If you reuse code logic more than once, consider putting the logic in a function.
    * There are some style standards that have multiple options, where you should choose one and consistently use it throughout the project:
        * Braces can either be hanging (where the open curly brace is on a line by itself, and the open and closing braces are at the same indent level) or Egyptian-style (where the open curly brace is at the end of the line which declares the new scope). In both cases, the ending curly brace should be on a line by itself.
          ```cpp
          void hanging()
          {
              cout << "This is an example of a function with hanging braces" << endl;
          }
          
          void egyptian() {
              cout << "This is an example of a function with Egyptian-style braces" << endl;
          }
          ```
        * For names, you can either use camel case (where the first letter of each word is capitalized, with the possible exception of the first word) or snake case (where everything is lowercase and there are underscores between words).
          ```cpp
          string camelCase, snake_case;
          ```
        * Comment blocks can either be in a large chunk at the top of the header file or as smaller blocks throughout.
          ```cpp
          /* 
           * Top-of-file comments include details such as:
           * what is declared in this file (including classes, fields, methods, structs, enums, etc.);
           * what are the known bugs in the file; 
           * TODO items for future work;
           */
          
          /*
           * Method comments include:
           * the inputs to the function (if not readable from type and name);
           * the return value (if any); and
           * a brief description of the method (if unclear).
           */
          ```
        * Variables in a class can optionally use a prefix notation, where fields begin with the letter `f`, parameters begin with `p`, and global variables begin with `g`.
          ```cpp
          enum cardSuit {club, diamond, heart, spade};
          cardSuit gSuit;
          
          class PlayingCard {          
          private:
              cardSuit fCardSuit;
              int fRank;
          public:
              PlayingCard(cardSuit pCardSuit, int pRank) {
                  fCardSuit = pCardSuit;
                  fRank = pRank;
              }
          };
          ```
* Modify main.cpp to have good style.
    * You can make commits / pushes to the repository as frequently as you want.
    * Note that you do NOT need to fix the bugs in the code for this project. However, if you do not fix them then you should have a comment (in good style) to that effect.
* Split the code into:
    * a header file with the class declaration;
    * a corresponding .cpp file with the class method definitions; and
    * main.cpp with the functioning program. The main.cpp file should have a global function that gets user input for an integer and validates it. It should be declared above the main function, called twice within the main function, and defined below the main function.
* Commit and push the changes to the repository.

### Grading Rubric
- [ ] (2 pts) Correct and consistent braces.
- [ ] (2 pts) Correct and consistent cases.
- [ ] (2 pts) Correct and consistent comments.
- [ ] (2 pts) Correct and consistent variables.
- [ ] (3 pts) All other style choices are correct and consistent.
- [ ] (3 pts) Create header file with appropriate code.
- [ ] (3 pts) Create corresponding .cpp file with appropriate code.
- [ ] (3 pts) Create a global function in main with consistent style.
