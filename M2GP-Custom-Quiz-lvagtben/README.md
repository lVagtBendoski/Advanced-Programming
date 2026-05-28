# Custom Quiz

Create your own quiz to test your knowledge!

For this project, you will use C++ classes with Has-A (component) relationships.

Note that the starter code for this project does not compile. You will need to start completing TODOs before the program will run.

You may work individually or with a partner of your choosing.

## Setup
Use this Guided Project template to create a new repository (see [GitHub-with-CLion](https://github.com/uvmcs2300f2024/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Custom-Quiz-netid**, where netid is your UVM NetID username.
* If you are collaborating, the format is Custom-Quiz-netid1-netid2. Have one partner create the repository and give the other partner access on GitHub: on the repository page, go to the Settings tab, choose Manage Access, and add the person with their GitHub username.

Remember to commit and push frequently.

## Has-A Relationship
Two classes in C++ have a Has-A relationship when at least one object of one class is a field of the other class.
The class whose object is a field is called a *component* class.

For this project, you will complete the Quiz program which stores `Question` objects as components inside a `Quiz` class.
* Note that this project has vectors of components, but it is possible to have a component be a single object.

### Question Class
Look through the `Question` header and .cpp files. Notice that a `Question` has a vector of `answer`s (where `answer` is a struct).

### Quiz Class
Look through the `Quiz` header and .cpp files. Complete the TODO comments in the header file and finish implementing the .cpp file.
* Your constructor should use an initializer list like the `Question` default constructor does.
* The `removeQuestion` methods should have similar functionality as the `Question` class `removeAnswer` methods.
* Note that the methods should be defined in the same order in the .cpp file as they are declared in the header file.
* Note that the two longer methods have been partially implemented for you.

### Main program
The main program declares a `Quiz` object and makes a single call to `takeQuiz`.

**Create your own quiz data file** and modify the `takeQuiz` method call so that the program runs your own custom quiz.
* Your quiz should have at least five questions.
* Your quiz questions should have at least two different numbers of answers and at least two different point values.

### Testing program
Create a `testing.cpp` file and put a `main` function in it that creates `Question` and `Quiz` objects and calls their methods (especially the methods not used in `takeQuiz`) to ensure that all the functionality works correctly.
* Once you create `testing.cpp`, uncomment the line in `CMakeLists.txt` that will create an executable for the testing program. You will be able to choose between the main program and the testing program through the dropdown menu between the Build and Run buttons in CLion.

## Questions
Answer the following prompts here in your `README.md` file:
* Give three examples of classes that would make sense to implement with the Has-A relationship (e.g. Car has an Engine):
  1.  
  2. 
  3. 
* Describe in your own words the benefit(s) of the component relationship.


## Grading

If you are collaborating, both partners have to submit on Gradescope.

### Grading Rubric
- [ ] (8 pts) Complete `Quiz` class
- [ ] (4 pts) Create custom Quiz and use it in the main program
- [ ] (5 pts) Testing program
- [ ] (3 pts) Answer questions in `README.md`