vimCXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = main.o level.o block.o cell.o board.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -lX11 -o ${EXEC}
main.o : main.cc level.h block.h cell.h board.h textdisplay.h
level.o : level.cc level.h
	${CXX} ${CXXFLAGS} -c level.cc
block.o : block.cc block.h
	${CXX} ${CXXFLAGS} -c block.cc
cell.o : cell.cc cell.h
	${CXX} ${CXXFLAGS} -c cell.cc
board.o : board.cc board.h
	${CXX} ${CXXFLAGS} -c board.cc
textdisplay.o : textdisplay.cc textdisplay.h
	${CXX} ${CXXFLAGS} -c textdisplay.cc
.PHONY : clean
clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}
