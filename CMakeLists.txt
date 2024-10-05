cmake_minimum_required(VERSION 3.10)  # Устанавливаем минимальную версию CMake, необходимую для проекта

project(IFilterProject VERSION 0.1.0)  # Определяем название проекта и его версию

# Найти Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)  # Ищем библиотеку Boost, необходимую для юнит-тестирования

# Создание библиотеки и исполняемого файла
add_library(ip_filter ip_filter.cpp)  # Создаем библиотеку из файла ip_filter.cpp
add_executable(test_ip_filter test_ip_filter.cpp)  # Создаем исполняемый файл для тестов из файла test_ip_filter.cpp

# Установка стандартов C++
set_target_properties(ip_filter test_ip_filter PROPERTIES  # Устанавливаем свойства для библиотек и исполняемых файлов
    CXX_STANDARD 14  # Указываем стандарт C++14
    CXX_STANDARD_REQUIRED ON  # Обязательно использовать указанный стандарт
)

# Установка директорий для заголовочных файлов
target_include_directories(ip_filter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")  # Указываем директорию с заголовочными файлами для библиотеки
target_include_directories(test_ip_filter PRIVATE ${Boost_INCLUDE_DIRS})  # Указываем директории с заголовками Boost только для тестов

# Связывание библиотек
target_link_libraries(test_ip_filter PRIVATE ${Boost_LIBRARIES} ip_filter)  # Связываем исполняемый файл тестов с библиотеками Boost и ip_filter

# Включение тестирования
enable_testing()  # Включаем поддержку тестирования в проекте
add_test(NAME test_ip_filter COMMAND test_ip_filter)  # Добавляем тест с именем test_ip_filter, который запускает исполняемый файл test_ip_filter

# Копирование ресурсов (если необходимо)
set(RESOURCE_FILES 
    resources/ic.icns  # Определяем список ресурсов для копирования (например, иконки)
    # resources/info.plist  # Закомментируйте эту строку, если файл не нужен
)

foreach(RESOURCE ${RESOURCE_FILES})  # Итерируемся по каждому ресурсу в списке
    configure_file(${RESOURCE} ${CMAKE_BINARY_DIR}/${RESOURCE} COPYONLY)  # Копируем ресурс в директорию сборки без изменений
endforeach()

# Включение CPack для создания пакетов
include(CPack)  # Подключаем модуль CPack для создания пакетов

# Настройки для CPack
set(CPACK_PACKAGE_NAME "ip_filter")  # Устанавливаем имя пакета
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")  # Устанавливаем версию пакета, равную версии проекта
set(CPACK_PACKAGE_DESCRIPTION "A description of your package.")  # Описание пакета
set(CPACK_PACKAGE_LICENSE "MIT")  # Замените на вашу лицензию (например, MIT)
set(CPACK_GENERATOR "DEB")  # Указываем генератор пакета, здесь - DEB для Debian/Ubuntu; можно использовать "Bundle" для macOS

# Установка файлов в пакет (если необходимо)
install(TARGETS ip_filter DESTINATION bin)  # Устанавливаем библиотеку в директорию bin пакета
install(TARGETS test_ip_filter DESTINATION bin)  # Если хотите включить тесты в пакет, устанавливаем их в директорию bin

# Установка ресурсов в пакет (если необходимо)
install(FILES ${RESOURCE_FILES} DESTINATION resources)  # Устанавливаем ресурсы в директорию resources пакета

message("Configured PROJECT_VERSION: ${PROJECT_VERSION}")  # Выводим сообщение с настроенной версией проекта в консоль