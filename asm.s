.data
print_format:
.string "Сумма элементов массива = %d\n"

elements:
.byte 129, 213, 148, 175, 173, 235, 164, 252, 224, 135

elements_end:

bitmask:
.byte 128

.text
.global main

main:
movl $elements, %ebx # Указатель на текущий элемент массива
movl $0,%edx # Сумма элементов массива
movzbl (%ebx),%eax # Помещаем текущий элемент массива в регистр eax
for:
movl %eax,%ecx
and bitmask,%eax # Побитовое И
cmpl %eax,bitmask
je invert # если флаг zf == 1 или result == bitMask
addl %eax,%edx # суммирование
jmp less

invert:
notl %ecx
addl $1,%ecx
addl %ecx,%edx

less:
addl $1,%ebx # перемещаем указатель на следующий элемент массива
movzbl (%ebx),%eax # обновляем регистр eax следующим элементом массива

print:
cmpl $elements_end,%ebx # сравниваем адрес текущего элемента и адрес конца массива
jne for # если адреса не равны, то повторяем цикл for
pushl %edx
pushl $print_format
call printf
addl $8, %esp
ret
