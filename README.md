# Compilation Instructions for the Entire Package

## Introduction

This document provides instructions for compiling and running the driver within this package.

## Instructions

1. Navigate to the project's root directory.
2. Import the text file for testing the package.
3. In the terminal, open the folder containing the package.
4. Compile the package using the following command and create the executable file "myprogram". Note that the program includes features available in the newer version of C++, so we need to include the `-std=c++11` flag.

    ```bash
    $ g++ -std=c++17 main.cpp file_reader.cpp sorting_algorithms.cpp time_printer.cpp -o myprogram
    ```

5. Run the executable with your own arguments.

    ```bash
    $ ./myprogram input_file_name sort_key_pos n_items algo_name shuffle_passes shuffle_seed
    ```

6. Example of running the executable.

    ```bash
    $ ./myprogram projekt2_dane_daszek.csv 3 1000 QUICK 1
    ```
