

target : es01.c
	gcc -Wall -g es01.c -o myExe


install : myExe
	mkdir bin
	mv myExe bin/myExe


clean : 
	rm *.o

distclean : clean 
	rm -r bin
