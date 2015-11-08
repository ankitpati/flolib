# Makefile
# Makefile for Debug-Capable Floating-Point Library Implementation
#
# Copyright 2015 Ankit Pati <ankitpati@gmail.com>
#
# This library is free software;  you can redistribute it and/or modify it under
# the  terms of the GNU Lesser General Public License  as published by the  Free
# Software Foundation;  either version 3 of the License, or (at your option) any
# later version.
#
# This  library is distributed in the hope that it will be useful,  but  WITHOUT
# ANY WARRANTY;  without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License  for more
# details.
#
# You  should  have received a copy of the GNU  Lesser  General  Public  License
# along with this program; if not, see <http://www.gnu.org/licenses/>.

CC=cc
CFLAGS=-c
LDFLAGS=
SOURCES=src/demo.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=flolib-demo

all: $(SOURCES) $(EXECUTABLE) done

$(EXECUTABLE): $(OBJECTS)
	@echo Linking...
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	@echo Compiling...
	$(CC) $(CFLAGS) $< -o $@

clean:
	@echo Cleaning...
	find . -name "*.o" -type f -delete
	find . -name "*.gch" -type f -delete
	strip $(EXECUTABLE)

done:
	@echo Done!

# end of Makefile
