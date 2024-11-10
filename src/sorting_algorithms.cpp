//
// Created by Michał Markuzel on 12/04/2024.
//

#include "sorting_algorithms.h"


sorting_algorithms::sorting_algorithms(int value, float min_value, float max_value, std::vector<movie> &movie_list)
    : movie_list{movie_list}, sort_key_pos{value}, min_rating(min_value), max_rating(max_value) {
}


// funkcja pomocnicza do zamieniania filmów miejscami w vektorze
void movie_swap(std::vector<movie> &vector, int index_1, int index_2) {
    movie temp_movie = vector[index_1];
    vector[index_1] = vector[index_2];
    vector[index_2] = temp_movie;
}


//================= BUBBLE SORT =====================
void sorting_algorithms::bubble_sort() {
    int n = movie_list.size();
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (movie_list[i - 1] > movie_list[i]) {
                movie_swap(movie_list, i - 1, i);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}


//================= QUICK SORT =====================

// funkcja partition wykonuje operację podziału na podstawie elementu pivot
// oraz zwraca indeks, na którym pivot jest już na swojej prawidłowej pozycji
int sorting_algorithms::partition(int start, int end) {
    // ustawienie pivot na środku
    movie pivot = movie_list[start];

    int middle = start;

    // wartość pivota jako średnia z 3 środkowych ratingów
    if (end - start >= 3) {
        middle = start + (end - start) / 2;
        float median = (movie_list[middle - 1].movie_rating + movie_list[middle].movie_rating + movie_list[middle + 1].
                        movie_rating) / 3;
        pivot.movie_rating = median;
    }

    bool all_equal = true;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (movie_list[i] < pivot) {
            all_equal = false;
            count++;
        }
        if (movie_list[i] == pivot) {
            count++;
        }
    }

    // skraca ilosc rekurencji dla takich samych elementów
    if (all_equal)
        return middle;

    // ustawienie pivot w jego prawidłowej pozycji
    int pivot_index = start + count;
    movie_swap(movie_list, pivot_index, start);

    // sortowanie lewej i prawej części elementu pivot
    int i = start, j = end;

    while (i < pivot_index && j > pivot_index) {
        while (movie_list[i] <= pivot) {
            i++;
        }

        while (movie_list[j] > pivot) {
            j--;
        }

        if (i < pivot_index && j > pivot_index) {
            movie_swap(movie_list, i++, j--);
        }
    }

    return pivot_index;
}

// funkcja quick_sort_algorithm wykonuje sortowanie rekurencyjnie
void sorting_algorithms::quick_sort_algorithm(int start, int end, std::vector<movie> &movie_vector) {
    // przypadek bazowy
    if (start >= end)
        return;

    // wykonanie podziału tablicy
    int p = partition(start, end);

    // sortowanie lewej części
    quick_sort_algorithm(start, p - 1,movie_vector);

    // sortowanie prawej części
    quick_sort_algorithm(p + 1, end,movie_vector);
}

// funkcja quick_sort inicjuje sortowanie dla całego vectora
void sorting_algorithms::quick_sort() {
    quick_sort_algorithm(0, movie_list.size() - 1,movie_list);
}


//================= MERGE SORT =====================

// funkcja merge łączy dwie posortowane części tablicy w jedną posortowaną.
void sorting_algorithms::merge(int left, int mid, int right) {
    auto const vector_1 = mid - left + 1;
    auto const vector_2 = right - mid;

    // tworzenie vectorów pomocniczych dla lewej i prawej części
    std::vector<movie> left_vector(vector_1);
    std::vector<movie> right_vector(vector_2);

    // przekopiowanie danych do vectorów pomocniczych
    for (auto i = 0; i < vector_1; i++)
        left_vector[i] = movie_list[left + i];
    for (auto j = 0; j < vector_2; j++)
        right_vector[j] = movie_list[mid + 1 + j];

    auto index_vector_1 = 0;
    auto index_vector_2 = 0;
    auto index_merged_array = left;

    // scalanie dwóch vectorów pomocniczych w jedną posortowaną tablicę
    while (index_vector_1 < vector_1 && index_vector_2 < vector_2) {
        if (left_vector[index_vector_1] <= right_vector[index_vector_2]) {
            movie_list[index_merged_array] = left_vector[index_vector_1];
            index_vector_1++;
        } else {
            movie_list[index_merged_array] = right_vector[index_vector_2];
            index_vector_2++;
        }
        index_merged_array++;
    }

    // kopiowanie pozostałych elementów z lewego vectora pomocniczego
    while (index_vector_1 < vector_1) {
        movie_list[index_merged_array] = left_vector[index_vector_1];
        index_vector_1++;
        index_merged_array++;
    }

    // kopiowanie pozostałych elementów z prawego vectora pomocniczego
    while (index_vector_2 < vector_2) {
        movie_list[index_merged_array] = right_vector[index_vector_2];
        index_vector_2++;
        index_merged_array++;
    }
}

// funkcja wykonuje sortowanie przez scalanie rekurencyjnie
void sorting_algorithms::merge_sort_algorithm(int begin, int end) {
    if (begin >= end)
        return;

    // znalezienie środka vectora
    auto mid = begin + (end - begin) / 2;

    // wywołanie merge_sort_algorithm dla lewej i prawej połowy vectora
    merge_sort_algorithm(begin, mid);
    merge_sort_algorithm(mid + 1, end);

    // scalanie dwóch posortowanych części
    merge(begin, mid, end);
}

// funkcja merge_sort inicjuje sortowanie przez scalanie dla całego vectora
void sorting_algorithms::merge_sort() {
    merge_sort_algorithm(0, movie_list.size() - 1);
}


//================= BUCKET SORT =====================

// sortowanie kubełkowe
void sorting_algorithms::bucket_sort() {
    int buckets_amount = 10;

    // liczenie przedziałów dla bucketów
    float difference = (max_rating - min_rating) / 10;

    std::vector<std::vector<movie>> b(buckets_amount);

    // rozdzielanie filmów do odpowiednich kubełków
    for (int i = 0; i < movie_list.size(); i++) {
        for (int j = 0; j < buckets_amount; j++) {
            if (movie_list[i].movie_rating >= min_rating + difference * j
                && movie_list[i].movie_rating <= min_rating + difference * (j + 1)) {
                b[j].push_back(movie_list[i]);
                break;
                }
        }
    }

    // posortowanie poszczególnych kubełków quicksortem
    for (int i = 0; i < buckets_amount; i++) {
        quick_sort_algorithm(0, b[i].size()-1, b[i]);
    }

    // połączenie wszystkich kubełków w movie_list
    int ideks = 0;
    for (int i = 0; i < buckets_amount; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            movie_list[ideks++] = b[i][j];
        }
    }
}


// funkcja miesza vector filmów "value" razy
void sorting_algorithms::shuffle(int value) {
    if (value == 0)
        return;

    srand(time(nullptr));
    int size = movie_list.size();
    int random_index_1, random_index_2;

    if (size < 2)
        return;

    for (int i = 0; i < value; i++) {
        for (int j = 0; j < size; j++) {
            random_index_1 = rand() % size;
            random_index_2 = rand() % size;

            movie_swap(movie_list, random_index_1, random_index_2);
        }
    }
}

// funkcja pomocnicza wywołująca odpowiednie sortowania
bool sorting_algorithms::sort(const std::string &alg_name) {
    this->alg_name = alg_name;

    if (alg_name == "BUBBLE" || alg_name == "bubble" || alg_name == "buble" || alg_name == "BUBLE") {
        bubble_sort();
    } else if (alg_name == "MERGE" || alg_name == "merge") {
        merge_sort();
    } else if (alg_name == "QUICK" || alg_name == "quick") {
        quick_sort();
    } else if (alg_name == "BUCKET" || alg_name == "bucket") {
        bucket_sort();
    } else {
        std::cerr << "UWAGA! Nie da sie posortować. Nieznany algorytm: " << alg_name << std::endl;
        return false;
    }

    return true;
}
