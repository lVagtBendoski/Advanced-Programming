# CS 2300 Module 1 Applied Project: Input Validation

For this project, you will create a C++ program that validates all types of input in a user friendly manner.

## Requirements
You must work individually on this project.

* Use this template repository to create a **private** GitHub repository in the course organization.
  * **Your repository must be named with the convention: M1AP-netid**, where netid is your UVM NetID username.
* Your main program must prompt the user for the following types of data:

| Type of input | Definition                                                        |
|---------------|-------------------------------------------------------------------|
| Character | A string of length 1                                              |
| Word | A string with no whitespace                                       |
| Sentence | A string that is read in until the user hits enter/newline        |
| Integer | A valid integer value with nothing else on the same line of input |
| Floating-Point Number | A valid floating-point number (which can be an integer, it isn't required to have a decimal part) and nothing else on the same line of input |

* Your program must validate all input, reprompting the user when invalid input is received or no input is received. There should be different reprompt messages for each (see sample output below).
* Your program must not have any runtime errors, no matter what the user enters.
* Your program must utilize a function for each type of input, to keep your code organized.
* All of the above must be pushed to your GitHub repository.
* **Any C++ concepts that are from outside the course materials must be cited in your README.md file.**
  * **No `goto` commands are allowed in this project.**
* Submit the URL of the GitHub repository. 

## Grading
The project is out of 50 points.

| Points Possible | Description of requirement   |
|-----------------|------------------------------|
| 10 pts          | Character input              |
| 10 pts          | Word input                   |
| 5 pts           | Sentence input               |
| 15 pts          | Integer input                |
| 10 pts          | Floating point number input  |

It is expected that your program will compile, run, and have good style. If your project does not, you may receive point deductions.

## Some useful tips
* Remember the difference between these two ways to input strings:
  ```cpp
  string input;
  
  // This will skip leading whitespace 
  // and read until the next whitespace
  cin >> input; 
  
  // This will not skip leading whitespace
  // and will read until a newline character
  // but it will not store the newline character in the string
  getline(cin, input);
  ```
* You can get the number of characters in a string by calling the `length` method.
* There is a function called `isspace` that takes in a character and returns true if the character is whitespace (space, tab, newline) and false otherwise. It is included in the `<ctype>` library which is already included in the starter code.
* There is an object called a `stringstream` that you may find useful. It is included in the `sstream` library which is included in the starter code. Here is how it is used:
  ```cpp
  string input;
  int num;
  stringstream ss;
  
  // Copy the string into the string stream
  ss << input;
  
  // Read from the string stream into an integer
  ss >> num;
  ```
  If the string `input` does not start with a valid integer, the `ss >> num` statement will return false and the string stream will be in a bad state (meaning you can't read from it again until the stream is cleared).

## Sample Output
The user input is in bold font.
<pre>
Enter a single character: <b>no</b>
Invalid input. Enter a single character: <b>NO</b>
Invalid input. Enter a single character: <b>but why?</b>
Invalid input. Enter a single character: <b>Ok here it is: a</b>
Invalid input. Enter a single character: <b>12345</b>
Invalid input. Enter a single character:
No input. Enter a single character: <b>1n2m3</b>
Invalid input. Enter a single character: <b>k</b>
You entered the character k
Enter a single word: <b>Here's a sentence instead</b>
Invalid input. Enter a single word:
No input. Enter a single word: <b>Ok wow</b>
Invalid input. Enter a single word: <b>butterfly</b>
You entered the word butterfly
Enter a sentence:
No input. Enter a sentence:
No input. Enter a sentence:
No input. Enter a sentence:
No input. Enter a sentence: <b>Peekaboo!</b>
You entered the sentence: Peekaboo!
Enter a number: <b>ok</b>
Invalid input. Enter a number: <b>five</b>
Invalid input. Enter a number:
No input. Enter a number: <b>123 abc</b>
Invalid input. Enter a number: <b>abc 123</b>
Invalid input. Enter a number: <b>1 1</b>
Invalid input. Enter a number: <b>-4bc</b>
Invalid input. Enter a number: <b>-4</b>
You entered the number -4
Enter a floating-point number: <b>nope</b>
Invalid input. Enter a number:
No input. Enter a number: <b>123 abc</b>
Invalid input. Enter a number: <b>3.1415926535something</b>
Invalid input. Enter a number: <b>525,600 minutes</b>
Invalid input. Enter a number: <b>10 4</b>
Invalid input. Enter a number: <b>7.8</b>
You entered the floating-point number 7.8
</pre>
