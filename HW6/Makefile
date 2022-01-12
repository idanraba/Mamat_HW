# Defining constants

CXX=g++
CXXLINK=$(CXX)
CXXFLAGS=-Wall -g -std=c++11
OBJS=ip.o port.o field.o string.o
RM=-rf *.o libfirewall.so firewall.exe


#exe file
firewall.exe: main.o libfirewall.so
	$(CXXLINK) main.o -o firewall.exe -lfirewall -linput -L.

#create library
libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o  libfirewall.so -L.


#will compile the objects if the o file is older than the c and h files
main.o: main.cpp field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp string.h field.h ip.h 
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp string.h field.h port.h 
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

field.o: field.cpp string.h field.h  
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

string.o: string.cpp string.h  
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

	

# clean o file and libgrades.so
clean:
	rm $(RM)