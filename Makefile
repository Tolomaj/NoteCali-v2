make:
	@cd src/ && qmake -makefile && make CFLAGS=-DEBUG=0
# remove all tmp files
#	@rm -rf output/tmp src/.qmake.stash src/Makefile
#run compiled file
	cd output && ./main

clear:
	@rm -rf output/tmp src/.qmake.stash src/Makefile output/main  output/main.exe output/platforms output/styles
	@rm output/*.dll

#windows:
##todo celé dodělat
#	@cd src/ && x86_64-w64-mingw32-qmake-qt6 -makefile && make
#	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/bin/*.dll ./output/
#	@mkdir ./output/platforms ./output/styles
#	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/lib/qt6/plugins/platforms/*.dll ./output/platforms
#	@cp /usr/x86_64-w64-mingw32/sys-root/mingw/lib/qt5/plugins/styles/*.dll ./output/styles
#	@rm -rf  output/tmp src/*.Debug src/*.Release src/Makefile




MINGW_ROOT := /usr/x86_64-w64-mingw32/sys-root/mingw

windows:
	@cd src && x86_64-w64-mingw32-qmake-qt6 -makefile main.pro && $(MAKE)
	@mkdir -p output/platforms output/styles

	# copy all runtime deps (avoids missing libfreetype/libpng/etc.)
	@cp -f $(MINGW_ROOT)/bin/*.dll output/

	# required Qt plugins
	@cp -f $(MINGW_ROOT)/lib/qt6/plugins/platforms/qwindows.dll output/platforms/
	@cp -f $(MINGW_ROOT)/lib/qt6/plugins/styles/qmodernwindowsstyle.dll output/styles/ || true

	@rm -rf output/tmp src/.qmake.stash src/*.Debug src/*.Release src/Makefile
