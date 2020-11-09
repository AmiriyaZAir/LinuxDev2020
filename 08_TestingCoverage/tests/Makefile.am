TESTS = test_init test_clear test_grow test_pop test_push
check_PROGRAMS = test_init test_clear test_grow test_pop test_push

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
