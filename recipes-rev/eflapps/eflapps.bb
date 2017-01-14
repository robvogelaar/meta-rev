#

SUMMARY = "efl apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "efl"

SRC_URI = "file://evas-minimal.c \
           file://evas-box.c \
           file://evas-stacking.c \
           file://evas-keytest.c \
           file://red.png \
"

SRCREV = "${AUTOREV}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas-minimal.c -o evas-minimal `pkg-config --libs --cflags evas ecore ecore-evas eina`
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas-box.c -o evas-box `pkg-config --libs --cflags evas ecore ecore-evas eina`
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas-stacking.c -o evas-stacking `pkg-config --libs --cflags evas ecore ecore-evas eina`
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas-keytest.c -o evas-keytest `pkg-config --libs --cflags evas ecore ecore-evas eina`
}

do_install() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/red.png ${D}/usr/share/evas
    install -m 0755 ${S}/evas-minimal ${D}${bindir}
    install -m 0755 ${S}/evas-box ${D}${bindir}
    install -m 0755 ${S}/evas-stacking ${D}${bindir}
    install -m 0755 ${S}/evas-keytest ${D}${bindir}
}
