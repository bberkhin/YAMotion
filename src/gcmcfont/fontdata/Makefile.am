
GENSOURCE = \
	font_hsans_1.c \
	font_hsans_1_rs.c \
	font_hsans_2.c \
	font_hscript_1.c \
	font_hscript_2.c \
	font_htimes.c \
	font_htimes_bold.c \
	font_htimes_italic.c \
	font_htimes_italic_bold.c
EXTRA_DIST = \
	font_hsans_1.glyph \
	font_hsans_1_rs.glyph \
	font_hsans_2.glyph \
	font_hscript_1.glyph \
	font_hscript_2.glyph \
	font_htimes.glyph \
	font_htimes_bold.glyph \
	font_htimes_italic.glyph \
	font_htimes_italic_bold.glyph \
	$(GENSOURCE) \
	mkfonts.sh

all-local:
	./mkfonts.sh

$(GENSOURCE):
	cd .. && $(MAKE) all

dist-local: all-local

distclean-local:
	$(RM) font_*.svg
