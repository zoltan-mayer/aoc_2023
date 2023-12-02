SRCFILE ?= "defval"

build:
	g++ \
	-Wall \
	$(SRCFILE).cpp \
	-o r.exe

run:
	r.exe

clean:
	del r.exe
