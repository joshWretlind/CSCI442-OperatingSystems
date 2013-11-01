# Makefile for Scheduler (SCHED)
PROG=	sched
SRCS=	main.c ospex.c schedule.c utility.c

DPADD+=	${LIBSYS} ${LIBTIMERS}
LDADD+=	-lsys -ltimers

MAN=

BINDIR?= /usr/sbin

CPPFLAGS.main.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.schedule.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.utility.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.ospex.c+=	-I${NETBSDSRCDIR}

.include <minix.bootprog.mk>
