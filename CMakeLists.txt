cmake_minimum_required(VERSION 2.8) #Проверка версии CMake.

set(PROJECT_NAME Algebra_of_polynomials) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта

set (library Library) #Переменная с именем библиотеки
set (test Test)	#Переменная с именем приложения
set (samples Samples)
set (testLib gtest)
 
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #Создается переменная CMAKE_CONFIGURATION_TYPES со значением "Debug;Release" и меткой/разделом Configs, переменная сохраниется в специальном файле доступном из всех файлов,
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Library) #Добавляем директорию "${CMAKE_CURRENT_SOURCE_DIR}/vectorlib" в дополняемые каталоги включаемых файлов

add_subdirectory(gtest) #Добавляем директорию с под-CMakeList-ом, и выполняем под-CMakeList
add_subdirectory(Library)
add_subdirectory(Samples)
add_subdirectory(Test)