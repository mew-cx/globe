# Makefile for Linux
# http://mew.cx/ 2016-03-23

# OBJ is a Wavefront OBJ 3D geometry file, _not_ a compiled object file.

EXE = globe
OBJ = ${EXE}.obj

all : ${OBJ}

${EXE} : ${EXE}.cpp

${OBJ} : ${EXE}
	./${EXE} > $@

clean :
	-rm ${EXE}

clobber : clean
	-rm ${OBJ}

#EOF
