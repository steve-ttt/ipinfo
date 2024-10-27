# define the C compiler to use
CC       = g++
# define comipler flags
CFLAGS   = -std=c++23 -Wall -fmax-errors=10 -Wextra
# define library paths in addition to /usr/lib
LFLAGS   =  -lm -lboost_system -lboost_thread -lpthread
# define libraries to use
LIBS     = 
# define the object files that this project needs
OBJFILES = main.o  
# define the name of the executable file
MAIN     = ipinfo

# all of the below is generic - one typically only adjusts the above

all: $(MAIN)

$(MAIN): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES) $(LFLAGS) $(LIBS) 
    
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN)

run: $(MAIN)
	./$(MAIN)

install: $(MAIN)
	sudo cp $(MAIN) /usr/bin/$(MAIN)
