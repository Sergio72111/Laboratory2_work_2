#define BOOST_TEST_MODULE PrintIPTests // Определяем имя модуля тестирования для фреймворка Boost Test
#include <boost/test/included/unit_test.hpp> // Включаем заголовок фреймворка Boost Test
#include <sstream> // Включаем строковый поток для захвата вывода
#include <vector> // Включаем вектор для динамических массивов
#include <string> // Включаем функции для обработки строк

// Функция для печати IP-адресов с первым и вторым байтами
void printIPsWithFirstAndSecondByte(const std::vector<std::vector<std::string>>& ip_pool, int first_byte, int second_byte) {
    // Итерируемся по каждому IP-адресу в пуле
    for (const auto& ip : ip_pool) {
        // Проверяем, что IP имеет как минимум две части и что они соответствуют указанным байтам
        if (ip.size() >= 2 && std::stoi(ip[0]) == first_byte && std::stoi(ip[1]) == second_byte) {
            // Итерируемся по каждой части соответствующего IP-адреса
            for (size_t i = 0; i < ip.size(); ++i) {
                if (i != 0) { // Если не первая часть, выводим точку перед выводом части
                    std::cout << ".";
                }
                std::cout << ip[i]; // Выводим текущую часть IP-адреса
            }
            std::cout << std::endl; // Переход на новую строку после вывода каждого адреса
        }
    }
}

// Тесты для функции printIPsWithFirstAndSecondByte
BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte) {
    std::ostringstream output; // Создаем строковый поток для захвата вывода
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Перенаправляем стандартный вывод в строковый поток

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = { // Инициализируем тестовые данные с примерами IP-адресов
        {"192", "168", "1", "1"},
        {"192", "168", "1", "2"},
        {"10", "0", "0", "1"},
        {"10", "0", "0", "2"},
        {"172", "16", "0", "1"}
    };

    // Вызов функции с параметрами 192 и 168
    printIPsWithFirstAndSecondByte(ip_pool, 192, 168); // Вызываем функцию с конкретными параметрами
    BOOST_CHECK_EQUAL(output.str(), "192.168.1.1\n192.168.1.2\n"); // Проверяем, что вывод соответствует ожидаемому результату

    output.str(""); // Сбрасываем вывод для следующего теста
    output.clear(); // Очищаем поток вывода для следующего теста

    // Проверка с первым байтом 10 и вторым 0
    printIPsWithFirstAndSecondByte(ip_pool, 10, 0); // Вызываем функцию с другими параметрами
    BOOST_CHECK_EQUAL(output.str(), "10.0.0.1\n10.0.0.2\n"); // Проверяем, что вывод соответствует ожидаемому результату

    output.str(""); // Сбрасываем вывод для следующего теста
    output.clear(); // Очищаем поток вывода для следующего теста

    // Проверка с первым байтом 172 и вторым 16
    printIPsWithFirstAndSecondByte(ip_pool, 172, 16); // Вызываем функцию с другим набором параметров
    BOOST_CHECK_EQUAL(output.str(), "172.16.0.1\n"); // Проверяем, что вывод соответствует ожидаемому результату

    output.str(""); // Сбрасываем вывод для следующего теста
    output.clear(); // Очищаем поток вывода для следующего теста

    // Проверка с параметрами, которые не совпадают ни с одним IP
    printIPsWithFirstAndSecondByte(ip_pool, 8, 8); // Вызываем функцию с неподходящими параметрами
    BOOST_CHECK_EQUAL(output.str(), ""); // Проверяем, что нет вывода, так как ни один IP не совпадает

    std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер стандартного вывода
}

// Дополнительные тесты для различных сценариев
BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte_AdditionalCases) {
    std::ostringstream output; // Создаем строковый поток для захвата вывода
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Перенаправляем стандартный вывод в строковый поток

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = { // Инициализируем тестовые данные с примерами IP-адресов
        {"192", "168", "1", "1"},
        {"192", "168", "1", "2"},
        {"10", "0", "0", "1"},
        {"10", "0", "0", "2"},
        {"172", "16", "0", "1"}
    };

    // Вызов функции с первым байтом 192 и вторым 0 (ожидаем пустой вывод)
    printIPsWithFirstAndSecondByte(ip_pool, 192, 0); // Вызываем функцию ожидая отсутствие совпадений
    BOOST_CHECK_EQUAL(output.str(), ""); // Проверяем, что нет вывода

    output.str(""); // Сбрасываем вывод для следующего теста
    output.clear(); // Очищаем поток вывода для следующего теста

    // Вызов функции с пустым пулом IP-адресов
    std::vector<std::vector<std::string>> empty_ip_pool; // Создаем пустой пул IP-адресов
    printIPsWithFirstAndSecondByte(empty_ip_pool, 192, 168); // Вызываем функцию на пустом пуле ожидая отсутствие совпадений
    BOOST_CHECK_EQUAL(output.str(), ""); // Проверяем, что нет вывода

    std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер стандартного вывода

}

// Дополнительные случаи тестирования различных сценариев и крайних случаев.
BOOST_AUTO_TEST_CASE(TestPrintIPsWithFirstAndSecondByte_ExtraCases) {
    std::ostringstream output; // Создаем строковый поток для захвата вывода
    auto cout_buf = std::cout.rdbuf(output.rdbuf()); // Перенаправляем стандартный вывод в строковый поток

    // Подготовка данных для тестирования
    std::vector<std::vector<std::string>> ip_pool = { 
        {"192", "168", "1", "1"}, 
        {"192", "168", "1", "2"}, 
        {"10", "0", "0", "1"}, 
        {"10", "0", "0"},   // IP с недостаточным количеством байтов (не хватает частей)
        {"172", "16", "0", "1"} 
    };

    // Вызов функции с первым байтом 192 и вторым 168 
    printIPsWithFirstAndSecondByte(ip_pool, 192, 168); 
    BOOST_CHECK_EQUAL(output.str(), "192.168.1.1\n192.168.1.2\n"); // Проверяем, что ожидаемый вывод правильный

    output.str(""); // Сбрасываем вывод для следующего теста 
    output.clear(); 

   // Вызов функции с первым байтом 10 и вторым 1 (ожидаем пустой вывод)
   printIPsWithFirstAndSecondByte(ip_pool, 10, 1); 
   BOOST_CHECK_EQUAL(output.str(), ""); // Ожидаем отсутствия вывода 

   output.str(""); // Сбрасываем вывод для следующего теста 
   output.clear(); 

   // Вызов функции с первым байтом 172 и вторым 16 
   printIPsWithFirstAndSecondByte(ip_pool, 172, 16); 
   BOOST_CHECK_EQUAL(output.str(), "172.16.0.1\n"); // Ожидаем правильный вывод 

   std::cout.rdbuf(cout_buf); // Восстанавливаем старый буфер стандартного вывода 
}