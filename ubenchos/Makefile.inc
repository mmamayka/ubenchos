
SOURCE_FILES := $(wildcard *.[cs])

OBJECT_FILES := \
	$(patsubst %.c, %.o, $(filter %.c, $(SOURCE_FILES))) \
	$(patsubst %.s, %.o, $(filter %.s, $(SOURCE_FILES)))

DEP_FILES := $(patsubst %.o, %.d, $(OBJECT_FILES))

.PHONY: all
all: $(BINARY) $(SYMBOLS)

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf *.d
	@rm -rf *.elf
	@rm -rf *.sym

include $(DEP_FILES)

%.d: %.c
	@echo "Generating depfile $@ for $^."; set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.s
	@echo "Generating depfile $@ for $^."; set -e; rm -f $@; \
	$(AS) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(BINARY_UNSTRIPPED): $(OBJECT_FILES)
	@echo "Linking $@."; $(LD) -T $(LINKER) $(LDFLAGS) -o $@ $^

$(SYMBOLS): $(BINARY_UNSTRIPPED)
	@echo "Extracting symbols from $^ to $@"; objcopy --only-keep-debug $< $@

$(BINARY): $(BINARY_UNSTRIPPED)
	@echo "Stripping binary $@"; objcopy --strip-debug $< $@
	
