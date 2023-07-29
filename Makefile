################################################################
# Makefile Template
#
# Author: Wesley Dahar (wesleydahar@gmail.com)
# Modified: 08/23/2021
#
################################


################################################################
# Make Configuration
################################
include lib/make/common.mk
include lib/make/cpp.mk


################################################################
# C Toolchain Configuration
################################

# Set the default cross compiler toolchain.
CROSS_COMPILE ?=

ifdef CROSS_COMPILE

# Override the compiler toolchain from the environment.
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)gcc-ar

# Add the cross compiler flags.
CPPFLAGS +=
CXXFLAGS +=
LDFLAGS +=
LDLIBS +=
endif

# Set the default compiler toolchain if unset.
CXX ?= g++
AR ?= gcc-ar

# Add the project flags.
CPPFLAGS += -pedantic -Wall
CFLAGS += -std=c++20
LDFLAGS +=
LDLIBS +=

# Set the archive flags.
ARFLAGS := -rcs


################################################################
# Project Structure
################################
bin := $(BUILD)/bin
lib := $(BUILD)/lib
test := $(BUILD)/test


################################################################
# Default Target
################################
$(eval $(call make_default_target,mjc))


################################################################
# example
################################
mjc := mjc
mjc.incdirs := include
mjc.srcdirs := src
$(eval $(call make_cpp_program_target,mjc,The Mjolnir compiler))
