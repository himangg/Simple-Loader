#Create lib_simpleloader.so from loader.c

all:
	gcc -m32 -shared -o lib_simpleloader.so loader.c
	@cp -p ./lib_simpleloader.so ../bin/lib_simpleloader.so

#Provide the command for cleanup
clean:
	-@rm -f lib_simpleloader.so
