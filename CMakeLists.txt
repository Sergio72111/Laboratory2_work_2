cmake_minimum_required(VERSION 3.10)

project(ip_filter)

# Установка C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(ip_filter ip_filter.cpp)

# Устанавливаем путь для тестов
add_executable(test_ip_filter test_ip_filter.cpp)

# Подключаем библиотеку Boost для тестирования
find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(test_ip_filter ${Boost_LIBRARIES})
endif()

enable_testing()

# Добавляем тест
add_test(NAME IPFilterTests COMMAND test_ip_filter)