mkdir -p docs include src tests tmp 


touch LICENSE COPYING Makefile README.md FAQ INSTALL NOTICE


###########################################################


echo 'The MIT License (MIT)

Copyright (c) 2013 justinchou

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.' >> LICENSE

echo 'This Software Is Under The MIT License, Read LICENSE File To Get More Information.' >> COPYING


###########################################################


echo '## THIS IS A CPP COMPILE TEMPLATE Makefile ##

CCFLAGS  = 
# CFLAGS = -pedantic -O2 -Wall -DNEBUG -W $(CCFLAGS)
CFLAGS   = -pedantic -O0 -W -DDEBUG -g $(CCFLAGS)

# CC = gcc
CC = g++

CCVPATH	    = 
VPATH	    = include:src:tests:$(CCVPATH)

SOURCE      = src/
TESTPATH    = tests/
TMPPATH     = tmp/
INSTALLPATH = /usr/bin/

TARGET      = 
TESTS       = 
TARGETOBJS  = 
TESTSOBJS   = 
ALLOBJS     = $(TARGET) $(TESTS)

ALL: $(ALLOBJS)
	make tidy
$(TARGET): ${TARGETOBJS}
	$(CC) $(CFLAGS) -o $@ $^
$(TESTS): $(TESTSOBJS)
	$(CC) $(CFLAGS) -o $@ $^

tidy:
	mv ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} ${TMPPATH}
install:
	cp -rf ${TARGET} ${INSTALLPATH}
uninstall:
	cd ${INSTALLPATH} && rm -rf ${TARGET}

test:	$(TARGET)
		@./${TARGET}
check:	test
exec:	test
e:	test

clean:
	rm -rf ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} *.o
	cd ${TEMP_PATH} && rm -rf ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} *.o
clear: clean

dep:
	$(CC) -MM ${SOURCE}*.c ${SOURCE}*.cpp
.PHONY: tidy install uninstall test check exec e clean clear dep' >> Makefile


###########################################################


touch docs/index.html tests/main.cpp tests/tests.cpp


echo '<!DOCTYPE HTML>
<html lang="en-US">
<head>
	<meta charset="UTF-8">
	<title>Documentation</title>
</head>
<body>
	<h1>This Is The Documentation For ${PackageName}</h1>
	<ul>
		<li><a href="">Instruaction</a></li>
		<li><a href="">Quick Start</a></li>
		<li><a href="">Examples</a></li>
		<li><a href="">Wiki</a></li>
		<li><a href="">Advanced Usage</a></li>
		<li><a href="">About Us</a></li>
	</ul>
	<p>Instructions</p>
	<p>Quick Start</p>
	<p>Examples</p>
	<p>Wiki</p>
	<p>Advanced Usage</p>
	<p>About Us</p>
</body>
</html>' >> docs/index.html

echo '#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    return 0;
}
' >> tests/main.cpp

echo '#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    
    return 0;
}
' >> tests/tests.cpp

echo '
Software Instructions:

1. ProjectManger Is Just Used For Createing A Skeleton For CPP Projects Under Linux.
2. You Need To Edit Makefile File To Match Your Own Software.
3. You May Edit Some Other Files Like README.md, FAQ, INSTALL And NOTICE Of Your Own If Needed.
4. The include Folder Is Used For Sortage *.h File While The src Folder Is For *.cpp, *.c Or *.cc 

Many Thanks For Using Software ProjectManager.

Justin Chou And His Team Is Trying Everying To Make Things Better.

Wish Everything Be Easy! >>>
'
