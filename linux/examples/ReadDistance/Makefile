# Copyright (C) 2023, Simon D. Levy
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
# * Neither the name of STMicroelectronics nor the
# names of its contributors may be used to endorse or promote products
# derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
# NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
# IN NO EVENT SHEXE STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.#include <Arduino.h>

  
EXE = readDistance

LIB_SRC = ../../../src

ST_SRC = $(LIB_SRC)/st_src

LINUX_SRC = ../../src

all: $(EXE)

readDistance: readDistance.o vl53l1x_linux.o \
		vl53l1_api.o \
		vl53l1_api_calibration.o \
		vl53l1_api_core.o \
		vl53l1_api_debug.o \
		vl53l1_api_preset_modes.o \
		vl53l1_api_strings.o \
		vl53l1_core.o \
		vl53l1_core_support.o \
		vl53l1_error_strings.o \
		vl53l1_helpers.o \
		vl53l1_register_funcs.o \
		vl53l1_silicon_core.o

	g++ -o readDistance readDistance.o vl53l1x_linux.o \
		vl53l1_api.o \
		vl53l1_api_calibration.o \
		vl53l1_api_core.o \
		vl53l1_api_debug.o \
		vl53l1_api_preset_modes.o \
		vl53l1_api_strings.o \
		vl53l1_core.o \
		vl53l1_core_support.o \
		vl53l1_error_strings.o \
		vl53l1_helpers.o \
		vl53l1_register_funcs.o \
		vl53l1_silicon_core.o \
	    -li2c

readDistance.o: readDistance.cpp $(LINUX_SRC)/vl53l1x_linux.hpp 
	g++ -std=c++11 -Wall -I$(LIB_SRC) -I$(LINUX_SRC) -c readDistance.cpp

vl53l1x_linux.o: $(LINUX_SRC)/vl53l1x_linux.cpp 
	g++ -std=c++11 -Wall -I$(LIB_SRC) -c $(LINUX_SRC)/vl53l1x_linux.cpp


FOO = -DVL53L1_NOCALIB

vl53l1_api.o : $(ST_SRC)/vl53l1_api.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api.c 

vl53l1_api_calibration.o : $(ST_SRC)/vl53l1_api_calibration.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api_calibration.c 

vl53l1_api_core.o : $(ST_SRC)/vl53l1_api_core.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api_core.c 

vl53l1_api_debug.o : $(ST_SRC)/vl53l1_api_debug.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api_debug.c 

vl53l1_api_preset_modes.o : $(ST_SRC)/vl53l1_api_preset_modes.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api_preset_modes.c 

vl53l1_api_strings.o : $(ST_SRC)/vl53l1_api_strings.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_api_strings.c 

vl53l1_core.o : $(ST_SRC)/vl53l1_core.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_core.c 

vl53l1_core_support.o : $(ST_SRC)/vl53l1_core_support.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_core_support.c 

vl53l1_error_strings.o : $(ST_SRC)/vl53l1_error_strings.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_error_strings.c 

vl53l1_helpers.o : $(ST_SRC)/vl53l1_helpers.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_helpers.c 

vl53l1_register_funcs.o : $(ST_SRC)/vl53l1_register_funcs.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_register_funcs.c 

vl53l1_silicon_core.o : $(ST_SRC)/vl53l1_silicon_core.c 
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_silicon_core.c 

vl53l1_wait.o : $(ST_SRC)/vl53l1_wait.c
	gcc -Wall $(FOO) -c -I$(ST_SRC) $(ST_SRC)/vl53l1_wait.c 


run: readDistance
	./readDistance

edit:
	vim readDistance.cpp

clean:
	rm -f $(EXE) *.o *~
