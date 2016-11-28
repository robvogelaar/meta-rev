#

SUMMARY = "efl apps"
LICENSE = "CLOSED"

DEPENDS = "efl elementary"

SRC_URI = "file://evas_box.c"
SRCREV = "${AUTOREV}"

inherit pkgconfig

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/evas_box.c -o evas_box `pkg-config --libs --cflags evas ecore ecore-evas eina`
}
