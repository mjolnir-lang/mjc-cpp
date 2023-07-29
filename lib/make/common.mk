################################################################
# Common Makefile Utilities
#
# Author: Wesley Dahar (wesleydahar@gmail.com)
# Modified: 10/31/2021
#
################################
ifndef MAKE_COMMON_INCLUDE
MAKE_COMMON_INCLUDE := 1


################################################################
# Make Configuration
################################

# Set the default shell.
SHELL := /bin/bash

# Disable command printing.
.SILENT:

# Clear the suffix list.
.SUFFIXES:


################################################################
# Programs
################################
CMAKE := cmake -G "Unix Makefiles"
CP := cp -f
MKDIR := mkdir -p
MV := mv -f
RM := rm -rf
TOUCH := touch


################################################################
# Text Highlighting
################################
ESC := $(shell printf "\x1b")

TXT_BOLD    := $(ESC)[1m
TXT_RESET   := $(ESC)[m
TXT_RED     := $(ESC)[31m
TXT_GREEN   := $(ESC)[32m
TXT_YELLOW  := $(ESC)[33m
TXT_BLUE    := $(ESC)[34m
TXT_MAGENTA := $(ESC)[35m
TXT_CYAN    := $(ESC)[36m
TXT_WHITE   := $(ESC)[37m

TAG_DEFAULT  := $(TXT_BOLD)[$(TXT_YELLOW)Default$(TXT_WHITE)]$(TXT_RESET)
TAG_PROGRAM  := $(TXT_BOLD)[$(TXT_CYAN)Program$(TXT_WHITE)]$(TXT_RESET)
TAG_MODULE   := $(TXT_BOLD)[$(TXT_GREEN)Module$(TXT_WHITE)]$(TXT_RESET)
TAG_LIBRARY  := $(TXT_BOLD)[$(TXT_BLUE)Library$(TXT_WHITE)]$(TXT_RESET)
TAG_RESOURCE := $(TXT_BOLD)[$(TXT_GREEN)Resource$(TXT_WHITE)]$(TXT_RESET)
TAG_TARGET   := $(TXT_BOLD)[$(TXT_MAGENTA)Targets$(TXT_WHITE)]$(TXT_RESET)
TAG_ACTION   := $(TXT_BOLD)[$(TXT_RED)Action$(TXT_WHITE)]$(TXT_RESET)


################################################################
# Project Structure
################################

# Configure project directories.
BUILD := build
OUT := $(BUILD)/out


################################################################
# Utilities
################################

# Escape the pound symbol.
SPACE := $(empty) $(empty)

# Escape the pound symbol.
POUND := \#

# Recursively copy the given directory structure.
#
# Usage:                  1   2
#   $(call make_copy_dirs,dir,out)
make_copy_dirs = $(shell find $1 -type d -exec $(MKDIR) $2/{} \;)

# Recursively match all files in the given directory that have the given
# extension.
#
# Usage:                              1   2
#   sources := $(call make_match_exts,dir,exts)
make_match_exts = $(shell find $1 -type f -regex '.*\.\($(subst $(eval) ,\|,$2)\)')

make_match_srcs = $(shell find $1 -type f)
make_match_dirs = $(shell find $1 -type d)


################################################################
# Target Templates
################################


################################################################
# Usage:                              1      2
#   $(eval $(call make_default_target,target,help))
################################
define make_default_target
help.default_target := default
default.help := $(TAG_DEFAULT) $(if $2,$2,$1)

.DEFAULT_GOAL := default
.PHONY: default
default: $1
endef


################################################################
# Usage:                            1      2
#   $(eval $(call make_group_target,target,help))
################################
define make_group_target
help.targets += $1
$1.help := $(TAG_TARGET) $(if $2,$2,$1)

.PHONY: $1
$1: $($1)
endef


################################################################
# Usage:                               1      2
#   $(eval $(call make_resource_target,target,help))
################################
define make_resource_target
ifneq (,$2)
help.targets += $1
$1.help := $(TAG_RESOURCE) $2

.PHONY: $1
$1: $$($1)
endif
$$($1.srcs) := $$(call make_match_srcs,$$($1.srcs))
$($1) := $$(patsubst %,$($1)/%,$$($1.srcs))

$($1): $$($1.src)
	printf "$(TXT_BOLD)Copying '$$@'...$(TXT_RESET)\n"
	$$(MKDIR) $$(@D)
	$$(RM) $$@
	$$(CP) $$< $$@
endef
#$1.base := $$(join $$(addprefix $3, $$(dir $2)), $$(notdir $2))


################################################################
# Usage:                             1      2
#   $(eval $(call make_action_target,target,help))
################################
define make_action_target
help.targets += $1
$1.help := $(TAG_ACTION) $2

.PHONY: $1
$1:
	printf "$(TXT_BOLD)$($1.message)...$(TXT_RESET)\n"
	$($1)
endef


################################################################
# Generated File Management
################################
help.base_targets += clean
clean.help := $(TAG_ACTION) Delete all generated intermediate files

.PHONY: clean
clean:
	printf "$(TXT_BOLD)Deleting all generated intermediate files...$(TXT_RESET)\n"
	$(RM) $(OUT) $(clean.files)


################################################################
# Project Management
################################
help.base_targets += scrub
scrub.help := $(TAG_ACTION) Restore the project to its original state

.PHONY: scrub
scrub:
	printf "$(TXT_BOLD)Restoring the project to its original state...$(TXT_RESET)\n"
	$(RM) $(BUILD) $(scrub.files)


################################################################
# Makefile Target List
################################
help.base_targets += help
help.help := $(TAG_ACTION) List all targets

.PHONY: help
help: va = $(shell va=5; for t in $(help.default_target) $(help.targets); do [ $${$(POUND)t} -gt $$va ] && va=$${$(POUND)t}; done; printf "$$va")
help:
	printf "Usage: make [options] [target] ...\n"
	printf "Targets:\n"
	$(foreach target,$(help.default_target) $(help.targets) $(help.base_targets),printf "  %-$(va)s  %s\n" "$(target)" "$($(target).help)";)
	printf "\n"
	printf "Run 'make --help' for all Makefile options\n"


endif

