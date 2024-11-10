#include "file_reader.h"
#include "sorting_algorithms.h"
#include "time_printer.h"


int main(int argc, char *argv[]) {
    bool temp_bool;

    if (argc < 6) {
        std::cerr << "UWAGA! Za mało argumentów wywołania.";
        return 0;
    }

    std::string input_file_name = argv[1]; // 1) nazwa pliku do pobierania danych
    int sort_key_pos = std::stoi(argv[2]); // 2) pole wedlug ktorego sortujemy
    int n_items = std::stoi(argv[3]); // 3) ilosc wczytanych elementow
    std::string algo_name = argv[4]; // 4) nazwa algorytmu do uzycia
    int shuffle_passes = 0;
    if (argc == 6)
        shuffle_passes = std::stoi(argv[5]); // 5) opcjonalny, ilosc mieszan
    //int shuffle_seed = std::stoi(argv[6]); // 6) opcjonalny, mieszanie ziarna - brak implementacji


    // inicjacja struktury ranking
    file_reader ranking(input_file_name, n_items, sort_key_pos);

    // odczyt z pliku/terminalu
    ranking.read_input();
    min_max min_max_values = ranking.get_min_max();

    // inicjalizacja struktury algorytmy
    sorting_algorithms algorytmy(sort_key_pos, min_max_values.min, min_max_values.max, ranking.get_vector());
    algorytmy.shuffle(shuffle_passes);

    // mierzenie czasu sortowania
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    temp_bool = algorytmy.sort(algo_name);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();


    // wypisanie czasu sortowania i rankingu
    const long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    if (temp_bool) {
        // wypisanie rankingu
        ranking.print_movie_list();

        print_time(algo_name, time);
    }

    return 0;
}
