#include <cassert> // Для использования assert для отладки
#include <cstdlib> // Для стандартных функций, таких как std::exit
#include <iostream> // Для ввода и вывода
#include <fstream> // Для работы с файлами
#include <string> // Для работы со строками
#include <vector> // Для использования векторов
#include <algorithm> // Для стандартных алгоритмов, таких как std::sort
#include <tuple> // Для использования кортежей (хотя не используется в этом коде)
#include "ip_filter.h" // Подключение заголовочного файла ip_filter.h (предполагается, что он содержит необходимые объявления)

// Функция для разделения строки на части
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r; // Вектор для хранения частей строки

    // Проверка на пустую строку
    if (str.empty()) {
        return r; // Возвращаем пустой вектор, если строка пуста
    }

    std::string::size_type start = 0; // Начальная позиция для поиска
    std::string::size_type stop = str.find_first_of(d); // Находим первый разделитель

    // Цикл, пока не останется разделителей: запускает цикл, который продолжается до тех пор, пока в строке не будет найдено больше разделителей.
    while (stop != std::string::npos) {
        // Добавляем подстроку между разделителями
        r.push_back(str.substr(start, stop - start)); // Извлекаем подстроку и добавляем в вектор
        start = stop + 1; // Переход к следующему символу после разделителя
        stop = str.find_first_of(d, start); // Находим следующий разделитель
    }
    
    // Добавляем последнюю часть строки после последнего разделителя
    r.push_back(str.substr(start)); // Добавляем оставшуюся часть строки
    
    return r; // Возвращаем вектор с частями строки
}

// Функция сравнения IP-адресов: Объявляет функцию, которая сравнивает два вектора строк, представляющих IP-адреса. Она возвращает логическое значение, указывающее их порядок.
bool compareIPs(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    for (size_t i = 0; i < 4; ++i) { // Предполагаем, что IP-адрес состоит из 4 частей
        int partA = (i < a.size()) ? std::stoi(a[i]) : 0; // Преобразуем строку в целое число для первой части IP a
        int partB = (i < b.size()) ? std::stoi(b[i]) : 0; // Преобразуем строку в целое число для первой части IP b

        if (partA != partB) {
            return partA < partB; // Сравниваем части и возвращаем результат сравнения
        }
    }
    return false; // Если все части равны, возвращаем false (нет порядка)
}

// Объявление функции печати: объявляет функцию, которая выводит список IP-адресов, хранящихся в векторе векторов.
void printIPAddresses(const std::vector<std::vector<std::string>>& ip_pool) {
    for (const auto& ip : ip_pool) { // Итерируемся по каждому IP-адресу в пуле
        for (size_t i = 0; i < ip.size(); ++i) { // Итерируемся по каждой части IP-адреса
            if (i != 0) {
                std::cout << "."; // Если это не первая часть, выводим точку перед частью
            }
            std::cout << ip[i]; // Выводим текущую часть IP-адреса
        }
        std::cout << std::endl; // Переход на новую строку после каждого адреса
    }
}

// Функция для печати IP-адресов с первым байтом равным заданному значению
void printIPsWithFirstByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte) {
    for (const auto& ip : ip_pool) { // Итерируемся по каждому IP-адресу в пуле
        if (!ip.empty() && std::stoi(ip[0]) == first_byte) { // Проверяем первый байт IP-адреса
            for (size_t i = 0; i < ip.size(); ++i) { // Итерируемся по каждой части IP-адреса
                if (i != 0) {
                    std::cout << "."; // Если это не первая часть, выводим точку перед частью
                }
                std::cout << ip[i]; // Выводим текущую часть IP-адреса
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}

// Функция для печати IP-адресов с первым байтом равным 46 и вторым - 70
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte) {
    for (const auto& ip : ip_pool) { // Итерируемся по каждому IP-адресу в пуле
        if (ip.size() >= 2 && std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte) { 
            for (size_t i = 0; i < ip.size(); ++i) { // Итерируемся по каждой части IP-адреса
                if (i != 0) {
                    std::cout << "."; // Если это не первая часть, выводим точку перед частью
                }
                std::cout << ip[i]; // Выводим текущую часть IP-адреса
            }
            std::cout << std::endl; // Переход на новую строку после каждого адреса
        }
    }
}

// Функция для печати IP-адресов, где любой байт равен заданному значению
void printIPsWithAnyByte(const std::vector<std::vector<std::string>>& ip_pool, int byte_value) {
    for (const auto& ip : ip_pool) { 
        for (const auto& part : ip) { 
            if (std::stoi(part) == byte_value) { 
                for (size_t i = 0; i < ip.size(); ++i) { 
                    if (i != 0) {
                        std::cout << "."; 
                    }
                    std::cout << ip[i]; 
                }
                std::cout << std::endl; 
                break; // Выходим из внутреннего цикла, чтобы не дублировать вывод для одного IP 
            }
        }
    }
}

int main() {
    try {
        std::vector<std::vector<std::string>> ip_pool; 

        // Открываем файл для чтения 
        std::ifstream file("ip_filter.tsv"); 
        if (!file.is_open()) { 
            throw std::runtime_error("Не удалось открыть файл ip_filter.tsv"); 
        }

        // Чтение IP-адресов из файла 
        for (std::string line; std::getline(file, line); ) { 
            std::vector<std::string> v = split(line, '\t'); 
            ip_pool.push_back(split(v.at(0), '.')); 
        }

        file.close(); // Закрываем файл после чтения

        // Лексикографическая сортировка IP-адресов 
        std::sort(ip_pool.begin(), ip_pool.end(), compareIPs); 

        // Выводим отсортированные IP-адреса 
        std::cout << "Полный список адресов после сортировки:\n"; 
        printIPAddresses(ip_pool); 

        std::cout << "Вывод айпишек с 1" << "\n"; 
        printIPsWithFirstByte(ip_pool, 1); 

        std::cout << "Вывод айпишек с 46 и 70 " << "\n"; 
        printIPsWithFirstAndSecondByte(ip_pool, 46, 70); 

        std::cout << "Вывод айпишек с 46 " << "\n";     
        printIPsWithAnyByte(ip_pool, 46); 

    } catch (const std::exception &e) { 
        std::cerr << e.what() << std::endl; 
    }

    return 0; 
}