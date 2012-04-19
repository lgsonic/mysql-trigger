CC=gcc
CXX=g++
CPPFLAGS = -fPIC -I./mysql/ 
LDFLAGS = 
STDCPLUS = -lstdc++
LDLIBS = 
DY_LDFLAGS = -shared -fPIC 
ST_LDFLAGS = cr

COMPILE.CXX = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
COMPILE.C = $(CC) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.SHARE = $(CXX) $(DEBUGFLAG) $(DY_LDFLAGS) $(LDFLAGS)
LINK.STATIC = $(AR) $(ST_LDFLAGS) 

OBJS=mysqltrigger.o

TARGET=libmysqltrigger.so

all: $(TARGET)

.cpp.o:
	$(COMPILE.CXX) $< -o $@

$(TARGET): $(OBJS)
	$(LINK.SHARE) $(OBJS) -o $@ $(LINKDMC) $(LDLIBS) $(STDCPLUS)


clean:
	rm -f $(OBJS) $(TARGET)
