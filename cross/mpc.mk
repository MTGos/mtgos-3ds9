MPC_VERSION=1.0.3
mpc.tar.gz: mpc-$(MPC_VERSION).tar.gz
	mv $^ $@

mpc-$(MPC_VERSION).tar.gz:
	wget https://ftp.gnu.org/gnu/mpc/$@

gcc/mpc/: gcc/ mpc-$(MPC_VERSION)/
	mv mpc-$(MPC_VERSION)/ $@

mpc-$(MPC_VERSION)/: mpc.tar.gz
	tar -xf $^

mpc-patch:
	true

mpc-build:
	true
