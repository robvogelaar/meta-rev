SUMMARY = "RDK image containing efl"

require rdk-image-weston.bb

IMAGE_INSTALL += "packagegroup-rdk-efl"

IMAGE_INSTALL += "packagegroup-rdk-debug-extra"
