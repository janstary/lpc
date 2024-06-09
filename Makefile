PREFIX	= /usr/local
LIBDIR	= $(PREFIX)/lib/
INCDIR	= $(PREFIX)/include/
MANDIR	= $(PREFIX)/man/man3/
CFLAGS	= -Wall -pedantic -fPIC

LIB	= liblpc.so
INC	= lpc.h
MAN	= lpc.3

OBJS	= \
	analys.o	\
	bsynz.o		\
	chanwr.o	\
	dcbias.o	\
	decode.o	\
	deemp.o		\
	difmag.o	\
	dyptrk.o	\
	encode.o	\
	energy.o	\
	f2clib.o	\
	ham84.o		\
	hp100.o		\
	invert.o	\
	irc2pc.o	\
	ivfilt.o	\
	lpcdec.o	\
	lpcenc.o	\
	lpcini.o	\
	lpfilt.o	\
	mload.o		\
	onset.o		\
	pitsyn.o	\
	placea.o	\
	placev.o	\
	preemp.o	\
	prepro.o	\
	random.o	\
	rcchk.o		\
	synths.o	\
	tbdm.o		\
	voicin.o	\
	vparms.o

all: $(LIB)
$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -shared -o $(LIB) $(OBJS) -lm

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

lint: $(MAN)
	mandoc -Tlint $(MAN)

install: $(LIB) $(INC) $(MAN)
	install -d $(LIBDIR) && install -m 0644 $(LIB) $(LIBDIR)
	install -d $(INCDIR) && install -m 0644 $(INC) $(INCDIR)
	install -d $(MANDIR) && install -m 0644 $(MAN) $(MANDIR)

uninstall:
	( cd $(LIBDIR) && rm -f $(LIB) )
	( cd $(INCDIR) && rm -f $(INC) )
	( cd $(MANDIR) && rm -f $(MAN) )

clean:
	rm -f $(LIB) $(OBJS) *~
