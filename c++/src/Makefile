#Author: Nabil Rahiman
#Date:27/Dec/2017


#Reference
#http://makepp.sourceforge.net/1.19/makepp_tutorial.html

CC       = c++ -c

# compiling flags here
CFLAGS   = -Wall -I.   -std=c++11

LINKER   = c++ -o
# linking flags here
LFLAGS   = -Wall

OBJDIR	 = ../obj

OBJECTS  := $(OBJDIR)/test.o

#Program name
TARGET   = $(OBJDIR)/test

rm       = rm -f

$(OBJDIR)/%.o: %.cc
	$(CC) $(CFLAGS)  $< -o $@
	@echo "Compilation complete!"



$(TARGET): $(OBJECTS)
	$(LINKER)  $@  $(OBJECTS) 
	@echo "Link complete!"

#$(TARGET): $(OBJS)
#	@echo $(SOURCES)
#	@echo $(OBJS)
##	#@$(LINKER) $(TARGET)  $^
#	@echo "Linking complete!" 
#

clean:
	@$(rm) $(TARGET) $(OBJECTS)
	@echo $(OBJECTS)
	@echo "Cleanup complete!"

$(OBJDIR):
	mkdir $(OBJDIR)
