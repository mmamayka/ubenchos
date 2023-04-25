# CONFIGURE STAGE
_OFILE := $(EXECUTABLE)

_doiflib = $(if $(filter 1, $(shell make -sC $1 is-library 2>/dev/null)), $2,)

_LIB_DIRS := $(foreach DEP, $(DEPS), \
	$(foreach DEPPATH, $(DEPSPATH), \
		$(call _doiflib, $(DEPPATH)/$(DEP), $(DEPPATH)/$(DEP)) \
	) \
)

# OBJECTS BUILD STAGE
include $(UBENCHOS_MAKE_DIR)/build-support.mk

# LIBRARIES
$(foreach LIB_DIR, $(_LIB_DIRS), \
	$(ODIR)/$(shell make -sC $(LIB_DIR) get-name):; \
		$(_FANCY_LIBRARY_PREFIX) make ODIR=$(ODIR) -C $(LIB_DIR) build \
)
_LIBS := $(foreach LIB_DIR, $(_LIB_DIRS), \
	$(ODIR)/$(shell make -sC $(LIB_DIR) get-name))

# LINK STAGE
ifdef NEED_STRIPPING
$(ODIR)/$(EXECUTABLE_UNSTRIPPED): $(_OBJECTS) $(_LIBS)
	$(_FANCY_LD_PREFIX) \
		$(LD) -T $(LINKER_SCRIPT) -o $@ $^ $(LDFLAGS)

$(ODIR)/$(EXECUTABLE): $(ODIR)/$(EXECUTABLE_UNSTRIPPED)
	$(_FANCY_STRIP_PREFIX) objcopy --strip-debug $< $@

$(ODIR)/$(EXECUTABLE_SYMBOLS): $(ODIR)/$(EXECUTABLE_UNSTRIPPED)
	$(_FANCY_SYMBOLS_PREFIX) objcopy --only-keep-debug $< $@
endif

.PHONY: build
build: $(ODIR)/$(EXECUTABLE) $(ODIR)/$(EXECUTABLE_SYMBOLS)

ifndef NEED_STRIPPING
$(ODIR)/$(EXECUTABLE): $(_OBJECTS) $(_LIBS)
	$(_FANCY_LD_PREFIX) \
		$(LD) -T $(LINKER_SCRIPT) -o $@ $^ $(LDFLAGS)

.PHONY: build
build: $(ODIR)/$(EXECUTABLE)

endif

.PHONY: clean
clean:
	@-rm -rf $(_OFILE)
	@-rm -rf $(_OBJDIR)
ifdef NEED_STRIPPING
	@-rm -rf $(EXECUTABLE_SYMBOLS)
	@-rm -rf $(EXECUTABLE_UNSTRIPPED)
endif

.PHONY: is-executable
is-executable:
	@echo 1

.PHONY: is-library
is-library:
	@echo 0
