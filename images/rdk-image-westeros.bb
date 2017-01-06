SUMMARY = "RDK image containing westeros"

require ../meta-rdk/recipes-core/images/rdk-image-oss-noqt.bb

IMAGE_INSTALL += "packagegroup-rdk-westeros"

IMAGE_INSTALL += "packagegroup-rdk-debug-extra"

IMAGE_INSTALL += " \
    gles2apps \
    tditracer \
    efl \
    eflapps \
"
