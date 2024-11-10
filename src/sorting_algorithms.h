//
// Created by Michał Markuzel on 12/04/2024.
//

#ifndef PAMSI_PROJEKT_02_SORTING_ALGORITHMS_H
#define PAMSI_PROJEKT_02_SORTING_ALGORITHMS_H

#include "file_reader.h"
#include <time.h>

#include <algorithm>

// enum pomocniczy do komunikatów
enum sorting_output {sorted, wrong_alg};

//================= FILE READER =======================
// - sortuje przekazany wektor przez referencję
// - sortuje przy użyciu megre_sort,
//   quick_sort, bucket_sort i bubble_sort
//=====================================================
class sorting_algorithms {
    std::vector<movie> &movie_list;
    const int sort_key_pos;
    sorting_output message;
    std::string alg_name;
    const float min_rating, max_rating;

    // funkcja pomocnicza do quick sort
    int partition(int start, int end);

    // quick sort algorytm
    void quick_sort_algorithm(int start, int end, std::vector<movie> &movie_vector);

    // funkcja pomocnicza do merge sort
    void merge(int left, int mid, int right);

    // merge sort algorytm
    void merge_sort_algorithm(int begin, int end);

    // funkcja ułatwiająca wywołanie
    void merge_sort();

    // funkcja ułatwiająca wywołanie
    void quick_sort();

    // bucket sort algorytm
    void bucket_sort();

    // bubble sort algorytm
    void bubble_sort();

public:
    sorting_algorithms(int value, float min_value, float max_value, std::vector<movie> &movie_list);

    // sortowanie według zadanego algorytmu i zwracanie info o powodzeniu lub nie
    bool sort(const std::string& alg_name);

    // pomieszanie wektora "value" razy
    void shuffle(int value);

};


#endif //PAMSI_PROJEKT_02_SORTING_ALGORITHMS_H
