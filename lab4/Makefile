TARGET = output
CC = gcc

$(TARGET) : main.o additional.o execute_commands.o
	$(CC) main.o additional.o execute_commands.o -o $(TARGET)

main.o : main.c
	$(CC) -c main.c -o main.o

additional.o : additional.c
	$(CC) -c additional.c -o additional.o

execute_commands.o : execute_commands.c
	$(CC) -c execute_commands.c -o execute_commands.o

clean :
	rm $(TARGET) *.o