DESCRIPTION = "Hello kernel module out of the kernel tree"
SECTION = "examples"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"
PR = "r0"

inherit module

SRC_URI =   "file://ktdim.c \
			file://Makefile \
			file://COPYING \
			"

S = "${WORKDIR}"