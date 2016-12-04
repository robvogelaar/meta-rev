SUMMARY = "RDK image containing rev"

require rdk-image-efl.bb

IMAGE_INSTALL += "packagegroup-rdk-rev"

IMAGE_INSTALL += "packagegroup-rdk-debug-extra"
