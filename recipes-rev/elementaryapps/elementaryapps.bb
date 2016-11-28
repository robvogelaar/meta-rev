#

SUMMARY = "elementary apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "elementary"

SRC_URI = "file://example.c"
SRCREV = "${AUTOREV}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/example.c -o example `pkg-config --libs --cflags elementary`
}

do_install() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 ${S}/example ${D}${bindir}
}
