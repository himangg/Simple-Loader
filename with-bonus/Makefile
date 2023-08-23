#invoke make inside following directories and in this order: loader, launch, fib
all:
	$(MAKE) -C loader
	$(MAKE) -C launcher
	$(MAKE) -C test
	
#move the lib_simpleloader.so and launch binaries inside bin directory
	@mkdir -p bin/
	@cp -p loader/lib_simpleloader.so bin/
	@cp -p launcher/launch bin/
#Provide the command for cleanupp
clean:
	@rm -rf bin
	@rm -f loader/lib_simpleloader.so
	@rm -f launcher/launch
	@rm -f test/fib


