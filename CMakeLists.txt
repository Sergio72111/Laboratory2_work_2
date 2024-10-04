cmake_minimum_required(VERSION 3.10)

project(IPFilterProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найдите библиотеку Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Добавляем исполняемый файл для основной программы
add_executable(ip_filter ip_filter.cpp)

# Добавляем исполняемый файл для тестов
add_executable(test_ip_filter test_ip_filter.cpp)

# Линкуем Boost с исполняемым файлом тестов
target_link_libraries(test_ip_filter Boost::unit_test_framework)

# Копируем файл ip_filter.tsv в директорию сборки
configure_file(ip_filter.tsv ${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv COPYONLY)

# Включаем поддержку тестирования
enable_testing()

# Добавляем тесты
add_test(NAME TestIPFilter COMMAND test_ip_filter)  # Регистрация теста