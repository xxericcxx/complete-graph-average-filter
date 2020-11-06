EXE=$(BDIR)/addconst $(BDIR)/deriche $(BDIR)/ppm2pgm $(BDIR)/pgm2ppm
DOC=$(DOCDIR)/tutorialEnglish.html

CCFLAGS = -g -DUNIXIO -Wall

IDIR = ./include
ODIR = ./obj
BDIR = ./bin
CDIR = ./src/com
LDIR = ./src/lib
DOCDIR = ./doc
CC = cc

# Documentation, if not already comiled, can be compiled thanks to 'make doc'
# You can also do a 'make clean' if you want

all:	$(EXE)
doc:    $(DOC)


rgb.o:		rgb.c		$(CDIR)/mcimage.h	$(CDIR)/laddconst.h
	gcc -c rgb.c -Wall

rgb:		rgb.o obj/mcimage.o obj/laddconst.o
	gcc rgb.o obj/mcimage.o obj/laddconst.o -o rgb -Wall

run: 
	./rgb


clean:
	rm *.o


$(BDIR)/addconst:	$(CDIR)/addconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/laddconst.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/addconst.c $(ODIR)/laddconst.o $(ODIR)/mcimage.o -o $(BDIR)/addconst

$(BDIR)/deriche:	$(CDIR)/deriche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lderiche.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/deriche.c $(ODIR)/lderiche.o $(ODIR)/mcimage.o -lm -o $(BDIR)/deriche

# ===============================================================
# Library functions 
# ===============================================================

# Basic ones:
# ===============================================================

$(ODIR)/mcimage.o:	$(LDIR)/mcimage.c $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/mcimage.c -o $(ODIR)/mcimage.o

# Operators:
# ===============================================================

$(ODIR)/laddconst.o:	$(LDIR)/laddconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/laddconst.c -o $(ODIR)/laddconst.o

$(ODIR)/lderiche.o:	$(LDIR)/lderiche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lderiche.c -o $(ODIR)/lderiche.o

$(BDIR)/ppm2pgm:	$(CDIR)/ppm2pgm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/ppm2pgm.c  $(ODIR)/mcimage.o -o $(BDIR)/ppm2pgm

$(BDIR)/pgm2ppm:	$(CDIR)/pgm2ppm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/pgm2ppm.c $(ODIR)/mcimage.o -o $(BDIR)/pgm2ppm

# Documentation
# ===============================================================
$(DOCDIR)/tutorialEnglish.html: $(DOCDIR)/tutorialEnglish.tex
	cd $(DOCDIR); htlatex ./tutorialEnglish; cd ..

clean:
	Rm -rf *~ $(ODIR)/* $(IDIR)/*~ $(CDIR)/*~ $(LDIR)/*~ $(DOCDIR)/*~ 
	cd $(DOCDIR); rm -rf *.4ct *.4tc *.aux *.dvi *.idv *.lg *.log *.tmp *.xref 
