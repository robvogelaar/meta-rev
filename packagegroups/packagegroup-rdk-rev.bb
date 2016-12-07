SUMMARY = "Packagegroup containing rev components"

LICENSE = "MIT"

inherit packagegroup

RDEPENDS_${PN} = "\
    tditracer gles2apps efl elementary nodejs nodejs-modules eflapps elementaryapps elev8-plugins lgioui lgias \
"
