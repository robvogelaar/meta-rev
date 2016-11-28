#

SUMMARY = "elementary apps"
LICENSE = "CLOSED"

DEPENDS = "elementary"

SRC_URI = "file://example.c"
SRCREV = "${AUTOREV}"

inherit pkgconfig

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/example.c -o example `pkg-config --libs --cflags elementary`
}

