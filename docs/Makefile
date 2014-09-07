
MARKDOWNS = $(wildcard *.md)
HTMLS = $(MARKDOWNS:.md=.html)

.SUFFIXES: .md .html

all: $(HTMLS)

.md.html:
	markdown $< > $@
