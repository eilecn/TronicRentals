[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=15489889)

# Assignment 1

See the handout for instructions.

# Using the Debugger

If you are getting unexpected results, you can use the debugger to step through your code and see what is happening. Simply place a "breakpoint" on the line of code you want to start debugging from, and then click the "Debug" button. The debugger will start and you can step through your code line by line. You can also inspect the values of variables as you step through your code. This is extremely useful for finding out what is going wrong in your code.

You might find this helpful if it needs to be configured: 

  <https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/debug-launch.md>

Usually the easiest is to copy the contents of the `launch.json` file from the above link into the `.vscode/launch.json` file in your project. Which one you use depends on your setup. For example:

* gdb
* lldb
* msvc
* ctest

If you are using macOS or Linux, you will probably want to use `lldb`. If you are using Windows, you will probably want to use `msvc`.

If you aren't sure, just try one and see if it works. If it doesn't, try another one.

You should then be able to go to the `Run and Debug` tab on the left-hand side of the screen, and click the green play button to start debugging.


# How to use (terminal)

* **Build:** Create a `build` directory for the output (if it doesn't already exist), generate the build files in it, then run it:
  ```bash
  mkdir build
  cd build
  cmake ..          # generates the build files
  cmake --build .   # execute the build and creates the executable(s)
  ```

* **Run:** Run the program interactively:
  ```bash
  cd build
  ./tronicrentals
  ```

* **Test:** Run the test cases:
  ```bash
  cd build
  ctest     # minimal output
  ctest -V  # verbose output
  ctest --output-on-failure  # verbose for failing test cases, but minimal for tests that pass
  ctest -V -R Task_1_ZeroCars # run a single specific test case in verbose mode
  ```

# How to use (graphical interface)

When the project is opened in Visual Studio Code, at the bottom is a blue status bar with various CMake options: 
* `Build` will build the project. Do this every time the code is changed, and before running/debugging/testing.
* `Run` will run the project interactively (runs the `src/main.cpp` file). Be sure to build first if the code has changed. Also be sure to kill the previously-running program before running again.
* `Debug` will run the project in debug mode (runs the `src/main.cpp` file). This allows you to set breakpoints and step through the code. Be sure to build first if the code has changed. Also be sure to kill the previously-running program before running again.
* `Run CTest` will run the test cases (runs the `test/tester.cpp` file). In VS Code, this will open up the GUI Test Runner. Run the tests by pressing the triangle arrow (either run all test cases, or one at a time). A green tick appears for passed test cases, or red cross for failed, or red dot for some other error if it cannot finish the test case. For verbose output, go to the `TEST RESULTS` tab at the bottom, and click on the most recent test run on the right-hand side of that tab. The output should then appear. 
