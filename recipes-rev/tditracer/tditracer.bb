#

SUMMARY = "tditracer applications"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://git@github.com/robvogelaar/tditracer.git;protocol=ssh;branch=master"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"

inherit autotools pkgconfig

PACKAGECONFIG ??= ""
PACKAGECONFIG[egl] = "--enable-egl,--disable-egl,libegl"
PACKAGECONFIG[gles2] = "--enable-gles2,--disable-gles2,libgles2"
PACKAGECONFIG[libc] = "--enable-libc,--disable-libc,,"
PACKAGECONFIG[libpthread] = "--enable-libpthread,--disable-libpthread,,"


do_compile_append() {
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi/libtdim.cpp -O3 -fPIC -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -ldl -shared -pthread -o libtdim.so
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi/tdim.cpp -O3 -fPIC -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-aggressive-loop-optimizations -ldl -pthread -o tdim
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/procsmaps.cpp -Wall -o procsmaps
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/membench.cpp -Wall -o membench
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/sleeper.cpp -Wall -pthread -o sleeper
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/simserver.cpp -Wall -ldl -o simserver
    ${CXX} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/simclient.cpp -Wall -o simclient
    ${CC} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/smemcap.c -Wall -Wno-unused-variable -o smemcap
    ${CC} ${CFLAGS} ${LDFLAGS} ${S}/minimal-tdi-tests/fincore.c -Wall -lm -o fincore
}

do_install_append() {
    install -m 0755 -d ${D}${bindir}
    install -m 0755 -d ${D}${libdir}
    install -m 0755 ${S}/tdim ${D}${bindir}
    install -m 0755 ${S}/libtdim.so ${D}${libdir}
    install -m 0755 ${S}/sleeper ${D}${bindir}
    install -m 0755 ${S}/fincore ${D}${bindir}
}
