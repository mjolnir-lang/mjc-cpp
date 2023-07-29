################################################################
# C++ Makefile Utilities
#
# Author: Wesley Dahar (wesleydahar@gmail.com)
# Modified: 01/14/2022
#
#
# Targets
#
# Use the target templates to generate Makefile targets. In addition to the
# template parameters, the following fields may be set before calling.
#
# <target>.cppflags  these will be set for prerequisite targets as well
# <target>.cflags    "
# <target>.ldflags   use <target>.libs instead of raw flags
# <target>.ldlibs    "
#
# <target>.deps     dependencies
# <target>.defs     defines (-D)
# <target>.incdirs  include file search paths (-I)
# <target>.srcs     source files
# <target>.srcdirs  source file directories (enumerated recursively)
# <target>.arcs     statically linked libraries (lib*.a)
# <target>.libs     libraries (-l)
# <target>.libdirs  library search paths (-L)
#
#
# Toolchain Configuration
#
# CROSS_COMPILE  compiler toolchain prefix
# CXX            compiler
# AR             archiver
# CPPFLAGS       preprocessor flags: -D -I
# CXXFLAGS       compiler flags: -W -O -std= -f
# LDFLAGS        linker flags: -L
# LDLIBS         libraries: -l
# ARFLAGS        static object library archive flags
#
################################
ifndef MAKE_CPP_INCLUDE
MAKE_CPP_INCLUDE := 1


################################################################
# Makefile Includes
################################
include $(dir $(lastword $(MAKEFILE_LIST)))common.mk


################################################################
# C++ Objects
################################
CPP_EXTS := cpp cc cxx C
CPP_DEP_FLAGS_HEADERS := $(if $(DEPEND_ON_SYSTEM_HEADERS),-MD,-MMD)
CPP_DEP_FLAGS = -MP -MT $@ -MF $@.dt $(CPP_DEP_FLAGS_HEADERS)

define make_cpp_compile_rule
$(OUT)/%.o: %.$1 $(OUT)/%.o.d
	printf "$(TXT_BOLD)Compiling '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(CXX) $$(CPPFLAGS) $$(CXXFLAGS) $(CPP_DEP_FLAGS) -c -o $$@ $$<
	$$(MV) $$@.dt $$@.d && $$(TOUCH) $$@

$(OUT)/%.lo: %.$1 $(OUT)/%.lo.d
	printf "$(TXT_BOLD)Compiling '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(CXX) -fPIC $$(CPPFLAGS) $$(CXXFLAGS) $(CPP_DEP_FLAGS) -c -o $$@ $$<
	$$(MV) $$@.dt $$@.d && $$(TOUCH) $$@
endef
$(foreach ext,$(CPP_EXTS),$(eval $(call make_cpp_compile_rule,$(ext))))


################################################################
# Target Templates
################################


################################################################
# Usage:                          1      2
#   $(eval $(call prep_cpp_target,target,lib))
################################
define prep_cpp_target
$1.cppflags += $$(addprefix -D,$$($1.defs)) $$(addprefix -I,$$($1.incdirs))
$1.ldflags += $$(addprefix -L,$$($1.libdirs))
$1.ldlibs += $$(addprefix -l,$$($1.libs))
$1.srcs += $$(call make_match_exts,$$($1.srcdirs),$(CPP_EXTS))
$1.objs := $$(patsubst %,$(OUT)/%.o,$$(basename $$($1.srcs)))
ifneq ($2,)
$1.lobjs := $$(patsubst %,$(OUT)/%.lo,$$(basename $$($1.srcs)))
endif
$1.objs.deps = $$(addsuffix .d,$$($1.objs) $$($1.lobjs))
$$($1.objs.deps):
-include $$(wildcard $$($1.objs.deps))
endef


################################################################
# Usage:                                  1      2
#   $(eval $(call make_cpp_program_target,target,help))
################################
define make_cpp_program_target
ifneq (,$2)
help.targets += $1
$1.help := $(TAG_PROGRAM) $2
endif
$$(eval $$(call prep_cpp_target,$1))

.PHONY: $1
$1: $($1)

$($1): CPPFLAGS += $$($1.cppflags)
$($1): CXXFLAGS += $$($1.cxxflags)
$($1): $$($1.objs) $$($1.arcs) $$($1.deps)
	printf "$(TXT_BOLD)Linking '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(CXX) $$(LDFLAGS) $$($1.ldflags) -o $$@ $$($1.objs) $$($1.arcs) $$(LDLIBS) $$($1.ldlibs)
endef


################################################################
# Usage:                                  1      2
#   $(eval $(call make_cpp_library_target,target,help))
################################
define make_cpp_library_target
ifneq (,$2)
help.targets += $1
$1.help := $(TAG_LIBRARY) $2
endif
$$(eval $$(call prep_cpp_target,$1,1))

.PHONY: $1
$1: $$($1).a $$($1).so

$$($1).a: CPPFLAGS += $$($1.cppflags)
$$($1).a: CXXFLAGS += $$($1.cxxflags)
$$($1).a: $$($1.objs) $$($1.arcs) $$($1.deps)
	printf "$(TXT_BOLD)Archiving '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(AR) $$(ARFLAGS) $$@ $$($1.objs) $$($1.arcs)

$$($1).so: CPPFLAGS += $$($1.cppflags)
$$($1).so: CXXFLAGS += $$($1.cxxflags)
$$($1).so: $$($1.lobjs) $$($1.arcs) $$($1.deps)
	printf "$(TXT_BOLD)Linking '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(CXX) -shared $$(LDFLAGS) $$($1.ldflags) -o $$@ $$($1.lobjs) $$($1.arcs) $$(LDLIBS) $$($1.ldlibs)
endef


################################################################
# Default Toolchain Configuration
################################
ifdef CXX_DEFAULT_COMPILER

# Set the default cross compiler toolchain.
CROSS_COMPILE ?=

CC ?= $(CROSS_COMPILE)gcc
AR ?= $(CROSS_COMPILE)gcc-ar

# Add the project flags.
ifdef CROSS_COMPILE
CPPFLAGS +=
CXXFLAGS +=
LDFLAGS +=
LDLIBS +=
else
CPPFLAGS +=
CXXFLAGS +=
LDFLAGS +=
LDLIBS +=
endif

CPPFLAGS += -pedantic -Wall
CXXFLAGS += -std=c++11
LDFLAGS +=
LDLIBS +=

# Set the archive flags.
ARFLAGS := -rcs


endif

