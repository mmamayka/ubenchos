cp bootstrap/bootstrap.elf iso/boot/bootstrap.elf
cp kernel/kernel.elf iso/boot/kernel.elf
grub-mkrescue -o ubenchos.iso iso
