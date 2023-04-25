#include $(UBENCHOS_MAKE_DIR)/gmtt.mk

.PHONY: all
all: build

AS := gcc -x assembler-with-cpp -DASM_FILE
CC := gcc -c
LD := gcc

ODIR ?= $(PWD)/build

_INCLUDE_DIRS := $(foreach DEP, $(DEPS), \
	$(foreach DEPPATH, $(DEPSPATH), \
		$(if $(wildcard $(DEPPATH)/$(DEP)/Makefile), \
			-I$(DEPPATH)/$(DEP)/include,) \
	) \
)
CPPFLAGS += $(_INCLUDE_DIRS)

FANCY_PRINT ?= 1
ifeq ($(FANCY_PRINT), 1)
_FANCY_C_PREFIX = @echo "Compiling C file $<";
_FANCY_S_PREFIX = @echo "Assembling file $<";
_FANCY_CXX_PREFIX = @echo "Compiling CXX file $<";
_FANCY_LD_PREFIX = @echo "Linking executable $@";
_FANCY_AR_PREFIX = @echo "Building library $@";
_FANCY_DEP_PREFIX = @echo "Creating depfile database";
_FANCY_COMPILE_COMMANDS_PREFIX = @echo "Generating compile commands for YCM";
_FANCY_STRIP_PREFIX = @echo "Stripping binary $<";
_FANCY_SYMBOLS_PREFIX = @echo "Extracting symbols from $<";
_FANCY_LIBRARY_PREFIX = @echo "Building library $@";
endif

_SOURCES := $(foreach DIR, $(SOURCE_DIRS) . , \
	$(wildcard $(DIR)/*.c) $(wildcard $(DIR)/*.cpp) $(wildcard $(DIR)/*.s))

_OBJDIR := $(ODIR)/obj/$(_OFILE)

_OBJECTS_C := \
	$(patsubst %.c, $(_OBJDIR)/%.o, $(filter %.c, $(_SOURCES)))
_OBJECTS_S := \
	$(patsubst %.s, $(_OBJDIR)/%.o, $(filter %.s, $(_SOURCES)))
_OBJECTS_CXX := \
	$(patsubst %.cpp, $(_OBJDIR)/%.o, $(filter %.cpp, $(_SOURCES)))

_OBJECTS := $(_OBJECTS_C) $(_OBJECTS_S) $(_OBJECTS_CXX)

_DEPFLAGS = -MT $@ -MMD -MP -MF $(_OBJDIR)/$*.d
_DEPFILES := $(patsubst $(_OBJDIR)/%.o, $(_OBJDIR)/%.d, $(_OBJECTS))

COMPILE.c = $(_FANCY_C_PREFIX) \
    $(CC) $(_DEPFLAGS) $(CFLAGS) $(CPPFLAGS) -c

COMPILE.s = $(_FANCY_S_PREFIX) \
    $(AS) $(_DEPFLAGS) $(ASFLAGS) $(CPPFLAGS) -c

COMPILE.cpp = $(_FANCY_CXX_PREFIX) \
    $(CXX) $(_DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c

$(_OBJECTS_C): $(_OBJDIR)/%.o: %.c $(_OBJDIR)/%.d | $(_OBJDIR)
	$(COMPILE.c) $< -o $@

$(_OBJECTS_S): $(_OBJDIR)/%.o: %.s $(_OBJDIR)/%.d | $(_OBJDIR)
	$(COMPILE.s) $< -o $@

$(_OBJECTS_CXX): $(_OBJDIR)/%.o: %.cpp $(_OBJDIR)/%.d | $(_OBJDIR)
	$(COMPILE.cpp) $< -o $@

$(_OBJDIR): 
	$(_FANCY_DEP_PREFIX) \
		for D in $(dir $(_OBJECTS)); do mkdir -p $$D; done

$(_DEPFILES):;
include $(wildcard $(_DEPFILES))

.PHONY: list-variables
list-variables:
	@echo $(foreach VAR, $(.VARIABLES), "$(VAR)=$($(VAR))\n") | sort

.PHONY: list-sources
list-sources:
	@echo $(call map-tbl, \
		$(call join-tbl, \
			$(call join-tbl, 1 $(_SOURCES), 1 $(_OBJECTS)), \
			1 $(_DEPFILES)), \
		"$$1 -> $$2 $$3;") | sed 's/;/\n/g' | sort

.PHONY: compile-commands
compile-commands:
	$(_FANCY_COMPILE_COMMANDS_PREFIX) \
	make --always-make --dry-run build \
 		| grep -wE 'gcc|g\+\+' \
 		| grep -w '\-c' \
 		| jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$").string[1:]}]' \
 		> compile_commands.json

.PHONY: get-name
get-name:
	@echo $(_OFILE)
