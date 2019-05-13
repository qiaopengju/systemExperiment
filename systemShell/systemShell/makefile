objects = main.o  proManager.o resManager.o 
hpp = systemExperiment.hpp proManager.hpp resManager.hpp 

myShell: $(objects) $(hpp) 
	clang++ -o myShell $(objects)

main.o: systemExperiment.hpp proManager.hpp resManager.hpp
proManager.o: systemExperiment.hpp proManager.hpp resManager.hpp
resManager.o: systemExperiment.hpp resManager.hpp proManager.hpp

run:
	./myShell
readFile:
	./myShell < test
clean:
	-rm $(objects)
