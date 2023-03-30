# Makefile to compile C/C++ source files on Windows v1.0

# author: KLT
# date: 2023/03/09
version 		:= v.1.2
cc 				:= gcc
target 			:= main.c
appname 		:= main.exe 
extra_cflags	:= -fopenmp
cc_std 			:= -std=c11
cflags 			:= $(cc_std) -Wextra -Wall -I

bin_dir 		:= ./bin
src_dir 		:= ./src
obj_dir 		:= ./obj
include_dir 	:= ./include

target_path		:= $(addprefix $(src_dir)/,$(target))
source_files 	= $(wildcard $(src_dir)/*.c)
header_files 	= $(wildcard $(include_dir)/*.h)
obj_paths 		= $(patsubst $(include_dir)/%.h,$(obj_dir)/%.o,$(header_files))
obj				= $(notdir $(obj_paths))

.PHONY: all
all: compile run

.PHONY: run
run: $(bin_dir)/$(appname)
	$(bin_dir)/$(appname)

.PHONY: compile
compile: clean build
	@echo KLT's Makefile to compile C/C++ source files on Windows $(version)

.PHONY: build
build: $(obj)
	$(cc) $(extra_cflags) $(cflags) $(include_dir) $(src_dir)/$(target) -o $(bin_dir)/$(appname) $(obj_paths)

.PHONY: clean
clean:
	@del /q $(subst /,\,$(bin_dir))\*.* $(subst /,\,$(obj_dir))\*.*

.PHONY: %.o
%.o: $(src_dir)/%.c $(include_dir)/%.h
	$(cc) $(cflags) $(include_dir) -c ./$< -o $(obj_dir)/$@

.PHONY: %.c
%.c: clean
	$(cc) $(cflags) $(include_dir) $(extra_cflags) $@ -o $(bin_dir)/$(addsuffix .exe, $(basename $@)) $(obj_paths)
