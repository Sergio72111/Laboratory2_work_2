cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED) 

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp) 



#Устанавливает свойства для нескольких целевых объектов (helloworld_cli, helloworld и test_version) для обеспечения использования стандарта C ++ 14 во время компиляции. Опция CXX_STANDARD_REQUIRED ON гарантирует, что если C ++ 14 недоступен, будет выдана ошибка.
set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)


#Определяет включаемые каталоги для helloworld библиотеки, делая двоичный каталог доступным для нее частным образом (доступным только в пределах этого целевого объекта).
target_include_directories(helloworld PRIVATE "${CMAKE_BINARY_DIR}")




#Устанавливает свойства специально для test_version целевого объекта, определяя определение во время компиляции (BOOST_TEST_DYN_LINK) и включая каталог Boost include, который необходим для связывания с библиотеками Boost.
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli PRIVATE helloworld) #Связывает helloworld библиотеку с helloworld_cli исполняемым файлом, позволяя ему использовать функции и классы, определенные в этой библиотеке.
target_link_libraries(test_version ${Boost_LIBRARIES} helloworld) #Связывает библиотеки Boost и helloworld библиотеку с test_version исполняемым файлом, позволяя ему использовать как платформу тестирования Boost, так и любые функциональные возможности библиотеки.



#Устанавливает уровни предупреждения компилятора в зависимости от используемого компилятора:
#При использовании компилятора Microsoft Visual Studio (MSVC) он устанавливает уровень предупреждения 4 (/W4), который является довольно строгим.
#Для других компиляторов (таких как GCC или Clang) он включает различные предупреждающие флаги (-Wall, -Wextra и т.д.) И рассматривает предупреждения как ошибки (-Werror), обеспечивая высокое качество кода.
if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin) #Определяет правила установки для проекта, указывая, что при установке helloworld_cli исполняемый файл должен быть помещен в каталог с именем bin.

# Установка генератора CPack для macOS или Linux
if (APPLE)
    set(CPACK_GENERATOR "Bundle")  # Для создания .app или .pkg на macOS
else()
    set(CPACK_GENERATOR "DEB")  # Для создания .deb на Linux
endif()

# Установка имени пакета для CPack
set(CPACK_BUNDLE_NAME "LABABAB")  # Замените на имя вашего приложения

# Установка пути к Info.plist для CPack
set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/resources/Info.plist")  # Укажите правильный путь к вашему Info.plist

# Установка пути к иконке для CPack
set(CPACK_BUNDLE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/ic.icns")  # Укажите правильный путь к вашему файлу иконки

# Установка версии пакета для CPack
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "example@example.com")

# Дополнительные метаданные (по желанию)

include(CPack)

enable_testing() #Включает поддержку тестирования в этом проекте, позволяя вам определять и запускать тесты с помощью встроенной платформы тестирования CMake.

add_test(test_version test_version)