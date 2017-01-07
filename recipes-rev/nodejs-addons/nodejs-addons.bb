#

SUMMARY = "nodejs addons"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "nodejs"

SRC_URI = "file://addon1.cpp \
           file://test1.js \
		   file://addon2.cpp \
           file://test2.js \
"

SRCREV = "${AUTOREV}"

do_compile() {
    ${CXX} ${CXXFLAGS} ${LDFLAGS} ${WORKDIR}/addon1.cpp -shared -Wl,-soname,addon1.node -o addon1.node -Wall -Werror -O2 -fPIC -fno-exceptions -fno-rtti -std=c++0x
    ${CXX} ${CXXFLAGS} ${LDFLAGS} ${WORKDIR}/addon2.cpp -shared -Wl,-soname,addon2.node -o addon2.node -Wall -Werror -O2 -fPIC -fno-exceptions -fno-rtti -std=c++0x -lutils
}

do_install() {
    install -m 0755 -d ${D}${libdir}/node_modules
    install -m 0755 ${S}/addon1.node ${D}${libdir}/node_modules
    install -m 0755 ${WORKDIR}/test1.js ${D}${libdir}/node_modules
    install -m 0755 ${S}/addon2.node ${D}${libdir}/node_modules
    install -m 0755 ${WORKDIR}/test2.js ${D}${libdir}/node_modules
}
