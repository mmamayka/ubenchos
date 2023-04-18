qemu-system-x86_64 -S -s -cdrom ./ubenchos.iso -m 1G -cpu Skylake-Client &
gdb --eval-command "set architecture i386:x86-64:intel" \
    --eval-command "symbol-file bootstrap/bootstrap-unstripped.elf" \
    --eval-command "target remote localhost:1234" \
