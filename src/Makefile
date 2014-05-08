
OBJS = main.o
INC = metlib.h

LIBS = -lsqlite3

OBJLIB = metlib-get.o metlib-store.o metlib-access.o

libtest: $(OBJS) $(OBJLIB)
	$(CC) -o $@ $(OBJS) $(OBJLIB) $(LIBS)

main.o: main.c $(INC)

metlib-get.o: metlib-get.c $(INC)
metlib-store.o: metlib-store.c $(INC)

metlib-access.o: metlib-access.c
