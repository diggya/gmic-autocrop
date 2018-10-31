# Pre-requirements
#   apt install libgd-dev

autocrop: autocrop.c
	gcc -lgd -lpng -lz -ljpeg -lfreetype -lm $< -o $@

clean:
	if [ -f autocrop ] ; then rm autocrop ; fi
