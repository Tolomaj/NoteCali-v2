make:
	@cd src/ && qmake -makefile && make CFLAGS=-DEBUG=0
# remove all tmp files
	@rm -rf output/tmp src/.qmake.stash src/Makefile
#run compiled file
	cd output && ./main

clear:
	@rm -rf output/tmp src/.qmake.stash src/Makefile output/main  output/main.exe output/platforms output/styles
	@rm output/*.dll

windows:
#todo celé dodělat
	@cd src/ && x86_64-w64-mingw32-qmake-qt6 -makefile && make
	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/bin/*.dll ./output/
	@mkdir ./output/platforms ./output/styles
	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/lib/qt6/plugins/platforms/*.dll ./output/platforms
	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/lib/qt5/plugins/styles/*.dll ./output/styles
	@rm -rf  output/tmp src/*.Debug src/*.Release src/Makefile