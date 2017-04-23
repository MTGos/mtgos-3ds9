GCC_VERSION=6.3.0
GCC_MAJOR_VERSION=6.3.0
gcc.tar.bz2: gcc-$(GCC_VERSION).tar.bz2
	mv $^ $@

gcc-$(GCC_VERSION).tar.bz2:
	wget https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_MAJOR_VERSION)/$@

gcc/: gcc-$(GCC_VERSION)/
	mv $^ $@

gcc-$(GCC_VERSION)/: gcc.tar.bz2
	tar -xf $^

gcc-patch:
	true #Todo: Replace this with the sed that enables libstdc++

gcc-build: gcc-install
	rm -rf builddir

gcc-configure:
	mkdir builddir
	cd builddir; \
	../gcc/configure --prefix=$(CROSSPATH) --target=$(TARGET) --disable-nls --enable-languages=c,c++ --without-headers

gcc-make: gcc-configure
	$(MAKE) -C builddir all-gcc all-target-libgcc

gcc-install: gcc-make
	$(MAKE) -C builddir install-gcc install-target-libgcc
