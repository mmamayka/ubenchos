# CONFIGURE STAGE
_OFILE := $(LIBRARY)

# OBJECTS BUILD STAGE
include $(UBENCHOS_MAKE_DIR)/build-support.mk

# LINK STAGE
$(ODIR)/$(LIBRARY): $(_OBJECTS)
	$(_FANCY_AR_PREFIX) \
		$(AR) $(ARFLAGS) $@ $^

.PHONY: build
build: $(ODIR)/$(LIBRARY)

.PHONY: clean
clean:
	@-rm -rf $(_OFILE)
	@-rm -rf $(_OBJDIR)

.PHONY: is-executable
is-executable:
	@echo 0

.PHONY: is-library
is-library:
	@echo 1
