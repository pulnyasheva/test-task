#!/bin/bash

TEST=0

if [ "$#" -eq 1 ] && [ "$1" = "test" ]; then
    TEST=1
fi

packages=("cmake" "g++" "python3-dev" "python3-pip")

for package in "${packages[@]}"; do
    if ! dpkg -l | grep -q "^ii  $package "; then
        echo "$package не установлен. Устанавливаю..."
        sudo apt-get install -y $package
    else
        echo "$package уже установлен."
    fi
done

packages=("pybind11" "conan")

for package in "${packages[@]}"; do
    if ! pip show "$package" > /dev/null 2>&1; then
        echo "$package не установлен. Устанавливаю..."
        pip install "$package"
    else
        echo "$package уже установлен."
    fi
done

BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR"

if ! conan profile list > /dev/null; then
    echo "Профиль default не установлен. Выполняем 'conan profile detect'."
    conan profile detect
else
    echo "Профиль для conan уже установлен."
fi

conan install .. --build=missing

cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "Ошибка при настройке проекта. Проверьте вывод выше."
    exit 1
fi

cmake --build .

if [ $? -eq 0 ]; then
    echo "Сборка завершена успешно."
else
    echo "Ошибка сборки."
    exit 1
fi

if [ "$TEST" -eq 1 ]; then
    echo "Запуск тестов"

    cd ..

    if ! pip show pytest > /dev/null 2>&1; then
        echo "pytest не установлен. Устанавливаю..."
        pip install pytest
    else
        echo "pytest уже установлен."
    fi

    pytest test/test.py
fi
