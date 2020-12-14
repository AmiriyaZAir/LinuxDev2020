BIN_PATH = /usr/bin/
RU_PATH = /usr/share/locale
LOCALE  = /ru/LC_MESSAGES/

ifdef DESTDIR
	BIN_PATH = $(DESTDIR)
	RU_PATH = $(DESTDIR)
endif

all: guess_number $(RU_PATH)$(LOCALE)guess_number.mo

$(RU_PATH)$(LOCALE)guess_number.mo: guess_number.po
	mkdir -p `dirname $@`
	msgfmt $< -o $(RU_PATH)$@

guess_number: guess_number.c
	gcc $< -o $(BIN_PATH)$@ 

guess_number.po: guess_number.pot
	msgmerge -U $@ $<

guess_number.pot: guess_number.c 
	xgettext -k_ -c guess_number.c -o new.pot
	msgmerge -U $@ new.pot

clean:
	rm -rf $(RU_PATH)ru     
	rm $(RU_PATH)new.pot 
	rm $(BIN_PATH)guess_number      
