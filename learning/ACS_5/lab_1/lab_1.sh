#!/bin/bash
echo " "
echo -n "Дата: "; date +"%d-%m-%Y"
echo -n "Имя учётной записи: "; whoami
echo -n "Доменное имя ПК: "; hostname
echo "Процессор:"
echo -n " * Модель - "; lscpu | grep 'Имя модели:' |
    awk '{
            for(i = 3; i <= NF; i++) {
                printf("%s ", $i); 
            }
            printf("\n"); 
        }'
echo -n " * Архитектура - "; lscpu | grep 'Архитектура:' |
    awk '{
            for(i = 2; i <= NF; i++) {
                printf("%s ", $i); 
            }
            printf("\n"); 
        }'
echo -n " * Тактовая частота - "; lscpu | grep 'CPU МГц:' |
    awk '{
            for(i = 3; i <= NF; i++) {
                printf("%s ", $i); 
            }
            printf("\n"); 
        }'
echo -n " * Количество ядер - "; lscpu | grep 'CPU(s):' | grep -v 'NUMA' |
    awk '{
            for(i = 2; i <= NF; i++) {
                printf("%s ", $i); 
            }
            printf("\n"); 
        }'
echo -n " * Количество потоков на одно ядро - "; lscpu | grep 'Потоков на ядро:' |
    awk '{
            for(i = 4; i <= NF; i++) {
                printf("%s ", $i); 
            }
            printf("\n"); 
        }'
echo "Оперативная память:"
echo -n " * Всего - "; cat /proc/meminfo | grep MemTotal | awk '{print $2}'
echo -n " * Доступно - "; cat /proc/meminfo | grep MemFree | awk '{print $2}'
echo "Жесткий диск:"
echo -n " * Всего - "; df -h | grep '/dev/sda1' | awk '{print $2}'
echo -n " * Доступно - "; df -h | grep '/dev/sda1' | awk '{print $4}'
echo -n " * Смонтировано в корневую директорию / - "; df -h | grep '/dev/sda1' | awk '{print $1}'
echo -n " * SWAP всего - "; df -h | grep 'udev' | awk '{print $2}'
echo -n " * SWAP доступно - "; df -h | grep 'udev' | awk '{print $4}'
echo "Сетевые интерфейсы:"
NAME1=`ifconfig -a | grep 'enp' | awk "NR==1" | awk '{print $1}'`
MAC1=`ifconfig -a | grep 'ether' | awk "NR==1" | awk '{print $2}'`
IP1=`ifconfig -a | grep 'inet' | awk "NR==1" | awk '{print $2}'`
NAME2=`ifconfig -a | grep 'wlx' | awk "NR==1" | awk '{print $1}'`
MAC2=`ifconfig -a | grep 'ether' | awk "NR==2" | awk '{print $2}'`
IP2=`ifconfig -a |grep 'inet' | awk "NR==5" | awk '{print $2}'`
echo -n " * Количество сетевых интерфейсов - "; ip a | grep 'link/ether' | wc -l
echo "|--------------------------------------------------------------------------------------------------|"
echo "| № | Имя сетевого интерфейса |      MAC адрес               | IP адрес      | Скорость соединения |"
echo "|--------------------------------------------------------------------------------------------------|"
echo "| 1 | $NAME1                | $MAC1            | $IP1 | 91.32Мбит/с         |"
echo "| 2 | $NAME2        | $MAC2            | $IP2              | 0.0Мбит/с           |"
echo "|--------------------------------------------------------------------------------------------------|"