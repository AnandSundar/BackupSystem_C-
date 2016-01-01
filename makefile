compiler = g++ 
gtk = `pkg-config --cflags gtk+-2.0 --libs gtk+-2.0`
flags = -Wall -Wextra -g

all: bin/phase2

run: phase2
	./phase2

obj/phase2.o: hdr/phase2.h src/phase2.cpp
	${compiler} ${flags} -c src/phase2.cpp -o obj/phase2.o ${gtk}
bin/phase2: obj/main.o obj/phase2.o obj/comde.o obj/gtkmain.o
	${compiler} ${flags}  obj/comde.o obj/phase2.o obj/main.o obj/gtkmain.o -lz -o bin/phase2 ${gtk}
obj/comde.o: hdr/comde.h src/comde.cpp
	${compiler} ${flags} -c src/comde.cpp -o obj/comde.o ${gtk}
obj/main.o: src/main.cpp hdr/phase2.h hdr/comde.h
	${compiler} ${flags} -c src/main.cpp -o obj/main.o ${gtk}
obj/gtkmain.o: hdr/gtkmain.h src/gtkmain.cpp
	${compiler} ${flags} -c src/gtkmain.cpp -o obj/gtkmain.o ${gtk}

clean:
	rm -r -f *~ src/*~ hdr/*~ obj/*.o bin/phase2
