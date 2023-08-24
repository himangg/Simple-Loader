#invoke make inside following directories and in this order: loader, launch, fib
all:
	@mkdir -p bin/
	$(MAKE) -C loader
	$(MAKE) -C launcher
	$(MAKE) -C test
	
#move the lib_simpleloader.so and launch binaries inside bin directory
	@cp -p launcher/launch bin/launch
#Provide the command for cleanupp
clean:
	@rm -rf bin
	@rm -f loader/lib_simpleloader.so
	@rm -f launcher/launch
	@rm -f test/fib


