SUMMARY = "RDK image containing efl"

require ../meta-rdk/recipes-core/images/rdk-image-weston.bb

IMAGE_INSTALL += "packagegroup-rdk-efl"

IMAGE_INSTALL += "packagegroup-rdk-debug-extra"
