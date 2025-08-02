########################################################
# Files


########################################################
# Build


########################################################
# Continue on to subdirs
add_subdirectory(icons)
add_subdirectory(themes)
add_subdirectory(svg)


qt_add_binary_resources(icon_pack images.qrc DESTINATION ${QGIS_OUTPUT_DIRECTORY}/images.rcc)
qt_add_binary_resources(icon_pack2 images.qrc)
