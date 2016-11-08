#

SUMMARY = "gles2 applications"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://git@github.com/robvogelaar/tditracer.git;protocol=ssh;branch=master"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig
