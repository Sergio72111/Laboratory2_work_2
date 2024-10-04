cmake_minimum_required(VERSION 3.10)

project(IPFilterProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Установка пакета (например, .deb для Linux)
include(CPack)  # Включаем CPack для создания пакетов

set(CPACK_GENERATOR "DEB;DMG")  # Указываем генераторы для Debian и macOS
set(CPACK_PACKAGE_NAME "IPFilterProject")  # Имя пакета
set(CPACK_PACKAGE_VERSION "0.1.0")  # Версия пакета
set(CPACK_PACKAGE_DESCRIPTION "A project for filtering IP addresses")  # Описание пакета

# Установка зависимостей для Debian пакета
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-test-dev")  # Зависимости для Debian
set(CPACK_PACKAGE_CONTACT "your_email@example.com")  # Контактная информация

# Устанавливаем файлы в пакет
install(TARGETS ip_filter DESTINATION bin)  # Установка исполняемого файла в /usr/local/bin

# Включаем CPack
include(CPack)