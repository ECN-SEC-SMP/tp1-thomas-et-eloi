SRCDIR := src
INCDIR := include
BUILDDIR := build

all: $(BUILDDIR)/main.out

# Build the final executable
$(BUILDDIR)/main.out: $(BUILDDIR)/main.o $(BUILDDIR)/utilitaire.o
	g++ -o $@ $^

# Build main.o
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/utilitaire.cpp $(INCDIR)/utilitaire.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o

# Build utilitaire.o
$(BUILDDIR)/utilitaire.o: $(SRCDIR)/utilitaire.cpp $(INCDIR)/utilitaire.hpp | $(BUILDDIR)
	g++ -I$(INCDIR) -c $(SRCDIR)/utilitaire.cpp -o $(BUILDDIR)/utilitaire.o

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rfv $(BUILDDIR)