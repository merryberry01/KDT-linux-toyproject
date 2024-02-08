OBJS = main.o system_server.o gui.o input.o web_server.o
INCLUDES = -Isystem -Iui -Iweb_server
TARGET = toy_system

$(TARGET): $(OBJS)
	mkdir bin
	gcc -o bin/$(TARGET) ./*.o system/*.o ui/*.o web_server/*.o
	make clean
main.o:
	gcc $(INCLUDES) -c -o main.o main.c
system_server.o:
	gcc $(INCLUDES) -c -o system/system_server.o system/system_server.c
gui.o:
	gcc $(INCLUDES) -c -o ui/gui.o ui/gui.c
input.o:
	gcc $(INCLUDES) -c -o ui/input.o ui/input.c
web_server.o:
	gcc $(INCLUDES) -c -o web_server/web_server.o web_server/web_server.c
clean:
	rm -f ./*.o system/*.o ui/*.o web_server/*.o
