make:
	cd src/ && qmake -makefile && make
	[ -d output ] || mkdir output
	cp src/main output/

# remove all tmp files
	rm src/main
	rm src/main.o
	rm src/.qmake.stash
	rm src/Makefile
	rm src/moc_*
	cd output && ./main

clear:
	rm src/main
	rm src/main.o
	rm src/.qmake.stash
	rm src/Makefile
	rm src/moc_*