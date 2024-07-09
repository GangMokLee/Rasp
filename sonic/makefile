CC = gcc
CFLAG = -Wall
TARGET = us
OBJS = us0.o us1.o us2.o us3.o
LIBS = wiringPi

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -l$(LIBS)

us0.o : us0.c
	gcc -c -o us0.o us0.c
	
us1.o : song.c
	gcc -c -o us1.o song.c
	
us2.o : us.c
	gcc -c -o us2.o us.c
	
us3.o : Trig.c
	gcc -c -o us3.o Trig.c
	
d :
	rm -f *.o

song : song.c
	gcc -o song song.c -l$(LIBS)
