bin_PROGRAMS = main
main_SOURCES = main.cpp unit.cpp map.cpp panel.cpp game.cpp player.cpp menu.cpp build_panel.cpp pathfind.cpp unit_type.cpp \
		../include/unit.h ../include/map.h ../include/panel.h ../include/game.h ../include/player.h ../include/menu.h \
		../include/build_panel.h ../include/pathfind.h ../include/unit_type.h
# CPPFLAGS are flags passed to the C preprocessor
main_CPPFLAGS = -I/usr/include/ncurses -Wall -Weffc++ -Wextra
# CXXFLAGS are flags to pass to the C++ compiler
main_CXXFLAGS = -pipe -O2
# LDFLAGS are passed to the linker
main_LDFLAGS = -lncurses
