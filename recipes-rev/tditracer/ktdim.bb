#

SUMMARY = "ktdim"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

SRC_URI = "git://git@github.com/robvogelaar/tditracer.git;protocol=ssh;branch=master"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git/minimal-tdi"

inherit module
