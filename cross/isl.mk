ISL_VERSION=0.18
isl.tar.xz: isl-$(ISL_VERSION).tar.xz
	mv $^ $@

isl-$(ISL_VERSION).tar.xz:
	wget http://isl.gforge.inria.fr/$@

gcc/isl/: gcc/ isl-$(ISL_VERSION)/
	mv isl-$(ISL_VERSION)/ $@

isl-$(ISL_VERSION)/: isl.tar.xz
	tar -xf $^

isl-patch:
	true

isl-build:
	true
