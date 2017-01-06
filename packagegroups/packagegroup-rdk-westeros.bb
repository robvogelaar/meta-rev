SUMMARY = "Packagegroup containing RDK Weston components"

LICENSE = "MIT"

inherit packagegroup

RDEPENDS_${PN} = "\
    weston westeros tditracer gles2apps \
"
