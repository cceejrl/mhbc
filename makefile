#GMP_V = 6.1.2
#NTL_V = 9.9.1
COMPILER = g++

hbc : mkdir objects/he.o objects/helper_functions.o \
		objects/test_gates.o objects/test_circ_comb.o objects/test_circ_seq.o \
		objects/test_circ_arithm.o \
		objects/test_ksa.o \
		objects/main.o
	$(info )
	$(info Compiling hbc...)
	$(COMPILER) -std=c++11 -O3 objects/*.o HElib/src/fhe.a -o hbc -L/usr/local/lib -lntl -lgmp -lm -lrt

mkdir :
	mkdir -p objects
	
objects/he.o : src/he.cpp src/he.h
	$(COMPILER) -std=c++11 -c src/he.cpp -I HElib/src -o objects/he.o

objects/helper_functions.o : src/helper_functions.cpp src/helper_functions.h
	$(COMPILER) -std=c++11 -c src/helper_functions.cpp -o objects/helper_functions.o
	
objects/test_gates.o : src/TEST_GATES.cpp src/TEST_GATES.h
	$(COMPILER) -std=c++11 -c src/TEST_GATES.cpp -I HElib/src -o objects/test_gates.o
	
objects/test_circ_comb.o : src/TEST_CIRC_COMB.cpp src/TEST_CIRC_COMB.h
	$(COMPILER) -std=c++11 -c src/TEST_CIRC_COMB.cpp -I HElib/src -o objects/test_circ_comb.o
	
objects/test_circ_seq.o : src/TEST_CIRC_SEQ.cpp src/TEST_CIRC_SEQ.h
	$(COMPILER) -std=c++11 -c src/TEST_CIRC_SEQ.cpp -I HElib/src -o objects/test_circ_seq.o
	
objects/test_circ_arithm.o : src/TEST_CIRC_ARITHM.cpp src/TEST_CIRC_ARITHM.h
	$(COMPILER) -std=c++11 -c src/TEST_CIRC_ARITHM.cpp -I HElib/src -o objects/test_circ_arithm.o
	
objects/test_ksa.o : src/TEST_KSA.cpp src/TEST_KSA.h
	$(COMPILER) -std=c++11 -c src/TEST_KSA.cpp -I HElib/src -o objects/test_ksa.o

objects/main.o: src/main.cpp
	$(COMPILER) -std=c++11 -c src/main.cpp -I HElib/src -o objects/main.o
	
hbcNrun : hbc
	./hbc
	
	
clean :
	rm -fr objects *.exe *.o
	
deepclean :
	$(info Cleaning up everything !)
	rm -fr /usr/local/include/NTL
	rm -f /usr/local/include/gmp.h
	rm -f /usr/local/lib/libgmp.*
	rm -f /usr/local/lib/libntl.*
	rm -fr HElib
	apt-get remove -y --purge perl git $(COMPILER) libboost-all-dev

help : 
	@echo make hbc - Compiles the project source code into an executable "hbc"
	@echo make hbcNrun - Compiles the project source code and runs it.
	@echo make HElib - Downloads HElib and other libraries and installs them (alreaduy done in Vagrant)
	@echo make clean - Removes all executables .exe and objects .o
	@echo make deepclean - Removes all the libraries and packages installed. BE CAUTIOUS!
