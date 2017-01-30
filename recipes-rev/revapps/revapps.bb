#

SUMMARY = "revapps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = ""

SRC_URI = "file://revapp-mmap.c \
           file://revapp-membench.c \
           file://smemcap.c \
"

SRCREV = "${AUTOREV}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/revapp-mmap.c -o revapp-mmap
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/revapp-membench.c -o revapp-membench
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/smemcap.c -o smemcap
}

do_install() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 ${S}/revapp-mmap ${D}${bindir}
    install -m 0755 ${S}/revapp-membench ${D}${bindir}
    install -m 0755 ${S}/smemcap ${D}${bindir}
}
