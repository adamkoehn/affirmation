bin_PROGRAMS = affirmation
affirmation_SOURCES = main.c notification.c
affirmation_CFLAGS = $(LIBNOTIFY_CFLAGS) -D'SYSCONFDIR="$(sysconfdir)"'
affirmation_LDADD = $(LIBNOTIFY_LIBS)