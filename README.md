# tcpClient

Тестовый проект клиента, который обменивается данными по tcp. Проект написан с использованием Qt 6.5, QtQuick 2.15, C++17.

## Инструменты сборки

```bash
sudo apt install git cmake gcc g++ ninja-build
```

## Зависимости

## Boost:

Находим какую последнюю версию можно скачать 
apt-cache search boost | grep all 
Ищем что-то похожее - libboost1.81-all-dev 

Установка (<version> надо подставить из предыдущего пункта): 
```bash
sudo apt install libboost<version>-all-dev 
```

## Скачивание проекта

Создать папку, где будет лежать проект и перейти в неё 
```bash
mkdir -p <path_to_dir> && cd <path_to_dir>
```
Скачиваем проект по http через git
```bash
git clone https://github.com/Vadim7423/tcpServer.git .
```

## Сборка проекта (в консоли)

Создаём папку сборки 
```bash
mkdir build
```
Сборка
```bash
cmake .. -DQT_CMAKE_DIR=<path_to_qt_dir_with_cmake_files> 
make
```
## Настройки по умолчанию
Host: 127.0.0.1
Port: 12345
