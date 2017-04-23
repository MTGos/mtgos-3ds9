GMP_VERSION=6.1.2
gmp.tar.xz: gmp-$(GMP_VERSION).tar.xz
	mv $^ $@

gmp-$(GMP_VERSION).tar.xz:
	wget https://ftp.gnu.org/gnu/gmp/$@

gcc/gmp/: gcc/ gmp-$(GMP_VERSION)/
	mv gmp-$(GMP_VERSION) $@

gmp-$(GMP_VERSION)/: gmp.tar.xz
	tar -xf $^

gmp-patch:
	true

gmp-build:
	true
