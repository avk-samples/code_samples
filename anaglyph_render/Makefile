PROGNAME = anaglyph_render

RM=/bin/rm -f
CXX=g++

# if boost is not in standard include, set your boost include path here 
BOOST_ROOT?=. 

INCLUDES=  -I. -I$(BOOST_ROOT)
LIBS = -lGL -lGLU -lglut

DEFINES= $(INCLUDES) 
CFLAGS= -O3 -g -Wall $(DEFINES)
SOURCES = main.cpp anaglyph_app.cpp
HEADERS = anaglyph_app.h

OBJS = $(SOURCES:.cpp=.o) 

.cpp.o:
	$(RM) $@
	$(CXX) $(CFLAGS) -c $*.cpp -o $@

all: $(PROGNAME) 

$(PROGNAME) : $(OBJS) $(HEADERS) 
	$(CXX) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(PROGNAME) *~
