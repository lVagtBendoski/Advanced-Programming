# Monsters

Beware, this project is full of monsters!

For this project, you will be testing C++ classes and using polymorphism.

You may work individually or with a partner of your choosing.

## Setup
Use this Guided Project template to create a new repository (see [GitHub-with-CLion](https://github.com/uvmcs2300f2024/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Monsters-netid**, where netid is your UVM NetID username.
* If you are collaborating, the format is Monsters-netid1-netid2. Have one partner create the repository and give the other partner access on GitHub: on the repository page, go to the Settings tab, choose Manage Access, and add the person with their GitHub username.

Remember to commit and push frequently.

## Testing

Testing is a comprehensive way of demo-ing your code under different scenarios to ensure that there are no logic errors. It is good practice to write a test suite before you write the main program.
In a company setting, testing is a way to demonstrate that your code is fully functional before deployment.

Here is the general formula for what a test case looks like in code:
* Each test case includes a function call.
* You should have an expected outcome of each test case.
* You should print a helpful message upon failure of a test case.
* You should print a message if all test cases are passed.


## Polymorphism

Polymorphism is an important object-oriented programming concept. This project will give you practice with recognizing and writing code that uses polymorphism.

Polymorphism occurs when you have two (or more) objects of the same type, you call the same method on them, and different things happen. At first glance, this is not intuitive behavior. However it is very useful when, for example, you have a bunch of shape objects you want to draw, or you want to calculate your final grade in a bunch of different courses, or when you have a bunch of monsters that scare you in different ways! You can group objects of related classes together into a vector and have each one perform that overridden task (which will allow shapes to be drawn differently, courses to calculate their final grades differently, and monsters to scare differently). This is the glory of polymorphism!

To code polymorphism, you will need the following things:
1. At least two classes that are related through inheritance (e.g. a parent-child relationship, a sibling relationship, etc.).
1. At least two pointers or references to the parent type.
1. The pointers/references to point/refer to objects of different classes.
1. To call an overridden method on both objects.

In this project, you will have different types of Monsters with different subclasses, and you will use a vector of Monster pointers to demonstrate polymorphism. 

## Meet the Monsters

There is lots of starter code given to you for this project, so let's overview it all.

Firstly, you will not be running all of these files at the same time. If you use the dropdown menu between the Build and Run buttons in CLion, you will notice that there are four different executables: `Darkness_Monster`, `Darkness_Monster_Testing`, `Water_Monster`, and `Water_Monster_Testing`. This is because there are four different `add_executable` lines in `CMakeLists.txt`, each linking together a subset of the source files.

### Water Monsters
Three Water Monster classes are provided for you: 
* `Water_Monster` (superclass)
* `Lake_Monster` (subclass)
* `Sea_Monster` (subclass)

All three classes have been declared and defined in their own header and .cpp files and tested in `Water_Monster_Testing.cpp`. 
* You can run the test suite with the `Water_Monster_Testing` executable.

The main program has also been created in `Water_Monster_Main.cpp`. 
* You can run it using the `Water_Monster` executable.

The Water Monsters classes, testing, and main program contain lots of code that can be reused in the other classes, 
so it is highly recommended that you read through these files and understand them fully.

### Darkness Monsters

Three classes are provided for you: 
* `Darkness_Monster` (superclass)
* `Closet_Monster` (subclass)
* `Under_Bed_Monster` (subclass)

Each class has one method that hasn't been implemented. See TODO comments in the header and .cpp files to complete the classes.

**Complete the testing suite** in `Darkness_Monster_Testing.cpp` by adding test cases for the class methods you implemented.
* You should write at least two test cases for each method that you implemented.
* You can run the testing suite with the `Darkness_Monster_Testing` executable.

Complete the TODO comments in the main function in `Darkness_Monster_Main.cpp`.
    
### Sky Monsters
Two classes are provided for you: 
* `Cloud_Monster` (subclass)
* `Comet_Monster` (subclass)

**Write the superclass `Sky_Monster`** in header and .cpp files. Use the two subclasses and the testing suite to determine its contents.
Uncomment the `add_executable` line for `Sky_Monster_Testing` in `CMakeLists.txt`.
* Note: the testing suite in `Sky_Monster_Testing.cpp` will not compile and pass until you have implemented the superclass correctly.
* Note: **do not** modify the testing suite. Instead, figure out why test cases are failing based on their print 
statements and the conditions checked, and update the `Sky_Monster` class accordingly.

## Grading

If you are collaborating, both partners have to submit this project.

### Grading Rubric
Note that this project is out of 25 points instead of the usual 20. This is because it has more moving pieces and more tasks to complete.
- [ ] (6 pts) Darkness Monster parent and child methods
- [ ] (6 pts) Darkness Monster test cases
- [ ] (4 pts) Darkness Monster main program
- [ ] (9 pts) Sky Monster class
