CLOOG_VERSION=0.18.4
cloog.tar.gz: cloog-$(CLOOG_VERSION).tar.gz
	mv $^ $@

cloog-$(CLOOG_VERSION).tar.gz:
	wget http://www.bastoul.net/cloog/pages/download/$@

gcc/cloog/: gcc/ cloog-$(CLOOG_VERSION)/
	mv cloog-$(CLOOG_VERSION)/ $@

cloog-$(CLOOG_VERSION)/: cloog.tar.gz
	tar -xf $^

cloog-patch:
	true

cloog-build:
	true
