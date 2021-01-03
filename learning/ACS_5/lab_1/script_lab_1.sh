#!/bin/bash
echo " "
echo -n "Дата: "; date +"%d-%m-%Y"
echo -n "Имя учётной записи: "; whoami
echo -n "Доменное имя ПК: "; hostname
echo "Информация о процессоре:"
echo -n " "; lscpu | grep 'Имя модели'
echo -n " "; lscpu | grep 'Архитектура'
echo -n " "; lscpu | grep 'CPU МГц'
echo -n " "; lscpu | grep 'CPU(s):' | grep -v 'NUMA'
echo "Информация об оперативной памяти:"
echo -n " Всего: "; cat /proc/meminfo | grep MemTotal | awk '{print $2}'
echo -n " Свободно: "; cat /proc/meminfo | grep MemFree | awk '{print $2}'
echo "Информация о жестком диске:"
echo -n " Всего: "; df -h | grep '/dev/sda8' | awk '{print $2}'
echo -n " Доступно: "; df -h | grep '/dev/sda8' | awk '{print $3}'
echo -n " Директория: "; df -h | grep '/dev/sda8' | awk '{print $6}'
echo -n " SWAP всего: "; df -h | grep 'udev' | awk '{print $2}'
echo -n " SWAP доступно: "; df -h | grep 'udev' | awk '{print $4}'
echo "Сетевые интерфейсы:"
NAME1=`ip a | grep 'lo' | awk "NR==1" | awk '{print $2}'`
MAC1=`ip a | grep 'link/loopback' | awk '{print $2}'`
IP1=`ip a |grep 'inet' | awk "NR==1" | awk '{print $2}'`
NAME2=`ip a | grep 'wlo1' | awk "NR==1" | awk '{print $2}'`
MAC2=`ip a | grep 'link/ether' | awk '{print $2}'`
IP2=`ip a |grep 'wlo1' | grep 'inet' | awk "NR==1" | awk '{print $2}'`
echo -n "Количество сетевых интерфейсов: "; ip a | awk '/state UP/' | wc -l
echo "|----------------------------------------------------------------------------------------------------------------|"
echo "| № | Имя сетевого интерфейса | MAC адрес | IP адрес | Скорость соединения |"
echo "|----------------------------------------------------------------------------------------------------------------|"
echo "| 1 | $NAME1 | $MAC1 | $IP1 | 866.7Мбит/с |"
echo "| 2 | $NAME2 | $MAC2 | $IP2 | 866.7Мбит/с |"
echo "|----------------------------------------------------------------------------------------------------------------|"