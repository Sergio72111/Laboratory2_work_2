cmake_minimum_required(VERSION 3.14)
project(IPFilterProject VERSION 1.0 LANGUAGES CXX)

# Укажите стандарт C++
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

# Устанавливаем флаги компоновщика для Windows, если необходимо
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")
endif()