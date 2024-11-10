//
// Created by Michał Markuzel on 12/04/2024.
//

#ifndef PAMSI_PROJEKT02_FILE_H
#define PAMSI_PROJEKT02_FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdio.h>
#include <cstdio>

//=================== MOVIE =======================
// - struktura przechowująca poszczególne filmy,
//   wraz z indeksem i oceną
//=================================================
struct movie {
    std::string movie_name = "";
    float movie_rating = 0;

    // Operator przypisania =
    movie &operator=(const movie &a) = default;

    // Operator porównania <
    bool operator<(const movie &a) const {
        return this->movie_rating < a.movie_rating;
    }

    // Operator porównania >
    bool operator>(const movie &a) const {
        return this->movie_rating > a.movie_rating;
    }

    // Operator porównania >=
    bool operator>=(const movie &a) const {
        return this->movie_rating >= a.movie_rating;
    }

    // Operator porównania <=
    bool operator<=(const movie &a) const {
        return this->movie_rating <= a.movie_rating;
    }

    // Operator porównania ==
    bool operator==(const movie &a) const {
        return this->movie_rating == a.movie_rating;
    }
};

// enum pomocny przy imporcie rankingu
enum rating {
    true_double, true_single, no_rating, true_rating
};

// struktura pomocna przy zwracaniu min i max
struct min_max {
    float min;
    float max;
};

//================= FILE READER =====================
// - czyta filmy z pliku
// - przechowuje je w wektorze
// - wyświetla listę filmów
// - przekazuje vektor przez referencję
//===================================================
class file_reader {
    const std::string file_name;
    const int key_pos;
    const int inputs_amount;
    std::vector<movie> movie_list;
    float min_value, max_value;

    // pyta użytkownika o dane
    void ask_for_movie();

    // odczyt pliku z daszkami
    bool read_any_file();

    // sprawdza właściwy rating i zwraca input do vectora
    bool find_rating(std::string line, movie &movie_input) const;

public:
    file_reader(std::string file_name, int inputs_amount, int key_pos);

    // odczyt w zależności od nazwy
    void read_input();

    // wypisanie listy filmów
    void print_movie_list();

    // zwracanie vektora filmów jako referencji
    std::vector<movie> &get_vector();

    // getter zwracający min, max do bucket sort
    min_max get_min_max();
};

#endif //PAMSI_PROJEKT02_FILE_H
