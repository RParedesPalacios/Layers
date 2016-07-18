###############################################################################
#  File to perform successfully the tasks of compilation, loading and editing #
#  links of the different parts of the project.       <jmbenedi@prhlt.upv.es> #
###############################################################################
CC_OPT = -pedantic

# FOR LINUX:
CC_LIB = -lfl

# FOR MAC:
#CC_LIB = -ll

CC_FLG = $(CC_LIB) $(CC_OPT)
OBJ    = alex.o asin.o nettable.o

cmc:	$(OBJ)
	gcc -o cmc $(OBJ) $(CC_FLG)
nettable.o: nettable.c
	gcc -c nettable.c $(CC_OPT)
asin.o:	asin.c
	gcc -c asin.c  $(CC_OPT)
alex.o:	alex.c asin.c
	gcc -c alex.c  $(CC_OPT)
#asin.c:	asin.y
#	bison -oasin.c -d asin.y
#alex.c:	alex.l
#	flex -oalex.c alex.l

clean:
	rm -f ./*.o
###############################################################################
