#

SUMMARY = "efl apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "efl"

SRC_URI = "file://evas_box.c"
SRCREV = "${AUTOREV}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas_box.c -o evas_box `pkg-config --libs --cflags evas ecore ecore-evas eina`
}

do_install() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 ${S}/evas_box ${D}${bindir}
}
