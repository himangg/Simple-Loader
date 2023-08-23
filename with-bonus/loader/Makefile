#Create lib_simpleloader.so from loader.c

all: lib_simpleloader.so

lib_simpleloader.so: loader.c
	gcc -m32 -shared -o lib_simpleloader.so loader.c

#Provide the command for cleanup
clean:
	-@rm -f lib_simpleloader.so