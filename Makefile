SRCDIR := src
INCDIR := include
BUILDDIR := build
ASSETSDIR := assets

all: $(BUILDDIR)/main.out

# Build the final executable
$(BUILDDIR)/main.out: $(BUILDDIR)/main.o $(BUILDDIR)/utilitaire.o $(BUILDDIR)/lexique.o $(BUILDDIR)/lexique_ligne.o
	g++ -o $@ $^

# Build main.o
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/utilitaire.cpp $(INCDIR)/utilitaire.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o

# Build utilitaire.o
$(BUILDDIR)/utilitaire.o: $(SRCDIR)/utilitaire.cpp $(INCDIR)/utilitaire.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/utilitaire.cpp -o $(BUILDDIR)/utilitaire.o

# Build lexique.o
$(BUILDDIR)/lexique.o: $(SRCDIR)/lexique.cpp $(INCDIR)/lexique.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/lexique.cpp -o $(BUILDDIR)/lexique.o

# Build lexique_ligne.o
$(BUILDDIR)/lexique_ligne.o: $(SRCDIR)/lexique_ligne.cpp $(INCDIR)/lexique_ligne.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/lexique_ligne.cpp -o $(BUILDDIR)/lexique_ligne.o

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rfv $(BUILDDIR) && rm -rfv $(ASSETSDIR)/lexique*