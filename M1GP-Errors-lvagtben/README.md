# Errors

This project is riddled with errors. Please fix all the bugs!

## Setup

Use this Guided Project template to create a new repository (
see [GitHub-with-CLion](https://github.com/uvmcs2300f2024/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Errors-netid**, where netid is your UVM NetID username.

When you first put it into CLion, the Build and Run buttons will be grayed out and unclickable. This is intentional. You
will need to start fixing bugs before these buttons can be used.

Remember to commit and push frequently.

## Errors

There are three types of errors:

1. **Compiler errors** prevent your program from running. These are typically CMake or syntax errors.
1. **Runtime errors** occur while the program is running and prevent an exit code of zero. Examples of this include a
   non-zero exit code and an infinite loop.
1. **Logic errors** are when your program runs to completion (with exit code zero) but does not behave the way you
   intended. The best way to catch logic errors is through extensive testing and/or the use of the debugger.

For this project, you have been given a very broken program and it is your job to fix it. For each error you fix, log it
in the table below.

## Logging Errors

Every time you fix a bug, log it in the README file here:

| Type of error (compiler, runtime, logic) | File           | Description                                                 | Fix                              |
|------------------------------------------|----------------|-------------------------------------------------------------|----------------------------------|
| Example: compiler                        | CMakeLists.txt | "project PROJECT called with incorrect number of arguments" | Added the project name to line 2 |

The rest of this table is contained in this document https://docs.google.com/document/d/1-H_VHq8c_DEFXYJxWGHmmVH-q0YyWrZkXhItM1KJJuE/edit?usp=sharing


### Grading Rubric 

- [ ] (2 pts) Fix at least one CMake compiler error (not including the one already given).
- [ ] (3 pts) Fix at least one other compiler error.
- [ ] (3 pts) Fix at least one runtime error.
- [ ] (3 pts) Fix at least one logic error.
- [ ] (5 pts) The README table is populated fully and correctly.
- [ ] (4 pts) Fix at least 15 errors total (note: errors you create do not count).
