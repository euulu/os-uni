gcc main.c -o lab1_task1
./lab1_task1 &
lab1_task1_pid=$(echo $!)
pstree -A -p "$lab1_task1_pid"