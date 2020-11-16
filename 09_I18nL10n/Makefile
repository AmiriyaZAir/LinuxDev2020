all: guess_number ru/LC_MESSAGES/guess_number.mo

ru/LC_MESSAGES/guess_number.mo: guess_number.po
	mkdir -p ru/LC_MESSAGES
	msgfmt $< -o $@

guess_number: guess_number.c
	gcc $< -o $@ 

guess_number.po: guess_number.pot
	msgmerge -U $@ $<

guess_number.pot: guess_number.c 
	xgettext -k_ -c guess_number.c -o new.pot
	msgmerge -U $@ new.pot

clean:
	rm -rf ru     
	rm new.pot 
	rm guess_number      
