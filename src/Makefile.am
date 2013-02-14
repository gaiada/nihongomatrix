bin_PROGRAMS = nihongo_matrix
nihongo_matrix_SOURCES = database.cpp kanji.cpp misc.cpp nihongo_matrix.cpp

# set the include path found by configure
AM_CPPFLAGS =  $(LIBSDL_CFLAGS) $(all_includes)

# the library search path.
nihongo_matrix_LDFLAGS = $(all_libraries) $(LIBSDL_RPATH)
nihongo_matrix_LDADD = $(LIBSDL_LIBS)
noinst_HEADERS = database.h kanji.h misc.h
