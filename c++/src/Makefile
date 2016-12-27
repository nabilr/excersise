# project name (generate executable with this name)
TARGET   = test

CC       = c++ -c
# compiling flags here
CFLAGS   = -Wall -I.

LINKER   = c++ -o
# linking flags here
LFLAGS   = -Wall

#OBJDIR	 = ../obj
#OBJS    = $(OBJDIR)/%.o
rm       = rm -f

#$(OBJS): %.cc


%.o: %.cc
	@echo $@
	$(CC)   $< -o $@
#	$(CC)   $(input) -o $(output)
	@echo "Compilation complete!"

test: $(OBJECTS)
	@echo $<
#	$(LINKER) test  $(OBJECTS) 

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
