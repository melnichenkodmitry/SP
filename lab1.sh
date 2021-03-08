#!/bin/bash

echo "Что выполняет программа?"
echo "1. Выводит имя текущего каталога"
echo "2. Запрашивает имя файла"
echo "3. Запрашивает дату"
echo "4. Изменялся ли файл после введенной даты"

echo "Выполнил: Мельниченко Дмитрий 737-1 " 

while true
do
location=$(pwd)
echo "Текущая диретория: $location"

while true
do
echo "Введите имя файла"
read file
if find "$location" "$file" -name "$file"
then
echo "Файл $file существует"
break
else echo "Ошибка! Файл $file не существует"
fi
done

while true
do
datef=$(date -r "$file" +"%d%m%Y")
echo "Введите дату:"
read datev
if ["datev" -le "datef"]
then
echo "Файл изменялся"
break
else
echo "Файл не изменялся"
fi
done

while true
do
echo "Желаете повторить скрипт? (Y\N) "
read yn
case "$yn" in 
[Yy]* )
break;;
[Nn]* )
exit;;
* );;
esac
done
done
