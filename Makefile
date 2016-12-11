
LLVM_SRCDIR = ../llvm
LLVM_BUILDDIR = ../build

CC = $(LLVM_BUILDDIR)/bin/clang
CXX = $(LLVM_BUILDDIR)/bin/clang++
CXXFLAGS = -std=c++1z -Xclang -freflection -isystem $(LLVM_SRCDIR)/tools/clang/reflection

all: is_base_of_test

is_base_of_test: is_base_of_test.o

is_base_of_test.o: is_base_of_test.cpp is_base_of.h
