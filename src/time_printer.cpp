//
// Created by michal on 04.05.24.
//

#include "time_printer.h"

// funkcja pomocnicza do wypisywania czasu w odpowiednich jednostkach
void print_time(std::string name, long time) {
    std::cout << std::endl << "Czas sortowania " << name << ": " << std::setprecision(3) << std::fixed;

    if (time < 1000)
        std::cout << time << "[ms]" << std::endl << std::endl;
    else if (time < 60000)
        std::cout << (float) time / 1000 << "[s]" << std::endl << std::endl;
    else if (time < 3600000)
        std::cout << (float) time / 60000 << "[min]" << std::endl << std::endl;
    else
        std::cout << (float) time / 3600000 << "[h]" << std::endl << std::endl;
}

