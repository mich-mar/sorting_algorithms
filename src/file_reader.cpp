//
// Created by Michał Markuzel on 12/04/2024.
//

#include "file_reader.h"

file_reader::file_reader(std::string name, int inputs_amount, int key_pos) : file_name(name),
                                                                             inputs_amount(inputs_amount),
                                                                             key_pos(key_pos) {

}

// funckja do odczytu dowolnego pliku z daszkami
bool file_reader::read_any_file() {
    std::string temp_string;
    int counter = 0;
    movie temp_movie;

    std::ifstream input(file_name);


    // błąd podczas odczytu
    if (!input.is_open()) {
        std::cerr << "Nie można otworzyć pliku" << std::endl;
        return false;
    }

    // wcztywanie danych
    while (std::getline(input, temp_string) && counter < inputs_amount) {
        if (find_rating(temp_string, temp_movie) == true) {
            // wpidywanie danych do vecotra
            movie_list.push_back(temp_movie);

            // zapisnywanie min i max do bucket sort
            if (counter == 0) {
                min_value = temp_movie.movie_rating;
                max_value = temp_movie.movie_rating;
            }
            if (temp_movie.movie_rating < min_value)
                min_value = temp_movie.movie_rating;
            if (temp_movie.movie_rating > max_value)
                max_value = temp_movie.movie_rating;

            counter++;
        }
    }

    input.close();


    // blad dla brakujacych inputow
    if (movie_list.empty()) {
        std::cerr << "UWAGA! Brak pasujących pozycji w pliku do posorotowania";
        return false;
    }

    // nadpisanie danych wejsciowych
    for (int i = 0; i < inputs_amount - counter; i++)
        movie_list.push_back(movie_list[i]);


    // zwraca true dla poprawnego zapisu do vectora
    return true;
}

// funkcja szukajaca ratingu, zwraca bool i zmienia movie_input przez referencję
bool file_reader::find_rating(std::string line, movie &movie_input) const {
    int L_pos = -1;
    int R_pos = -1;
    int licznik = 0;
    std::string temp_string;

    // false dla pustej lini
    if (line.empty())
        return false;

    // flase dla pliku bez daszkow
    if (line.find('^') == std::string::npos)
        return false;

    // ułatwienie odczytu "między daszkami"
    std::string new_line = '^' + line;
    new_line = new_line + '^';

    // szukanie key_pos i key_pos+1
    for (int i = 0; i < new_line.length(); ++i) {
        if (new_line[i] == '^') {
            licznik++;
            if (licznik == key_pos) {
                L_pos = i;
            }
            if (licznik == key_pos + 1) {
                R_pos = i;
                break;
            }
        }
    }

    temp_string = new_line.substr(L_pos + 1, R_pos - L_pos - 1);

    // blad dla pustego miejca miedzy daszkami
    if (temp_string.empty())
        return false;


    // false przy błędzie konwersji
    try {
        std::stof(temp_string);
    } catch (const std::invalid_argument &error) {
        return false;
    }

    // zmiana movie_input
    movie_input.movie_name = new_line.substr(1, new_line.size() - 2);
    movie_input.movie_rating = std::stof(temp_string);

    return true;
}

// wypisanie listy
void file_reader::print_movie_list() {
    movie temp;

    for (int i = 0; i < movie_list.size(); i++) {
        temp = movie_list[i];
        std::cout << temp.movie_name << std::endl; // << ", rating: " << temp.movie_rating << std::endl;
    }
}

// zwracanie referencji do vectora
std::vector<movie> &file_reader::get_vector() {
    return movie_list;
}

// pytanie użytkownika o filmy
void file_reader::ask_for_movie() {
    std::cout << "UWAGA! Wybrales reczne wpisanie " << inputs_amount << " filmow." << std::endl;

    movie temp_movie;
    std::string temp_string;

    for (int i = 0; i < inputs_amount; i++) {
        std::cout << "Podaj wiersz nr " << i << " z " << inputs_amount << ": ";
        std::cin >> temp_string;
        if (find_rating(temp_string, temp_movie) == true)
            movie_list.push_back(temp_movie);
    }
}

// odczytuje zależnie od wpisanej nazwy filmu
void file_reader::read_input() {
    if (file_name == "-")
        ask_for_movie();
    else
        read_any_file();
}

min_max file_reader::get_min_max() {
    return {max_value, min_value};
}
