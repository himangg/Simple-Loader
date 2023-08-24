#Compile the launch.c by linking it with the lib_simpleloader.so
all:  
	gcc -m32 -o launch launch.c ../bin/lib_simpleloader.so 
	@cp -p ./launch ../bin/launch
#Provide the command for cleanup
clean:
	-@rm -f launch
