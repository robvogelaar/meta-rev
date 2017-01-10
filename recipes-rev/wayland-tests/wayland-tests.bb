#
SUMMARY = "wayland tests"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "nodejs"

SRC_URI = "file://wayland-client1/src/wayland-client1.c \
           file://wayland-client2/src/wayland-client2.c \
           file://wayland-server1/src/wayland-server1.c \
"

SRCREV = "${AUTOREV}"

do_compile() {
    ${CC} ${CCFLAGS} ${LDFLAGS} ${WORKDIR}/wayland-client1/src/wayland-client1.c -o wayland-client1 -O2 -fPIC `pkg-config --libs --cflags wayland-client`
    ${CC} ${CCFLAGS} ${LDFLAGS} ${WORKDIR}/wayland-client2/src/wayland-client2.c -o wayland-client2 -O2 -fPIC `pkg-config --libs --cflags wayland-client`
    ${CC} ${CCFLAGS} ${LDFLAGS} ${WORKDIR}/wayland-server1/src/wayland-server1.c -o wayland-server1 -O2 -fPIC `pkg-config --libs --cflags wayland-server`
}

do_install() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 ${S}/wayland-client1 ${D}${bindir}
    install -m 0755 ${S}/wayland-client2 ${D}${bindir}
    install -m 0755 ${S}/wayland-server1 ${D}${bindir}
}
