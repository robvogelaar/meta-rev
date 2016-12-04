SUMMARY = "Packagegroup containing rev components"

LICENSE = "MIT"

inherit packagegroup

RDEPENDS_${PN} = "\
    tditracer gles2apps efl elementary nodejs eflapps elementaryapps elev8-plugins lgioui lgias \
"
