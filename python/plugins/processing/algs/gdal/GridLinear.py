"""
***************************************************************************
    GridLinear.py
    ---------------------
    Date                 : September 2017
    Copyright            : (C) 2017 by Alexander Bruy
    Email                : alexander dot bruy at gmail dot com
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************
"""

__author__ = "Alexander Bruy"
__date__ = "September 2017"
__copyright__ = "(C) 2017, Alexander Bruy"

import os

from qgis.PyQt.QtGui import QIcon

from qgis.core import (
    QgsRasterFileWriter,
    QgsProcessing,
    QgsProcessingException,
    QgsProcessingParameterDefinition,
    QgsProcessingParameterFeatureSource,
    QgsProcessingParameterEnum,
    QgsProcessingParameterField,
    QgsProcessingParameterNumber,
    QgsProcessingParameterString,
    QgsProcessingParameterRasterDestination,
)
from processing.algs.gdal.GdalAlgorithm import GdalAlgorithm
from processing.algs.gdal.GdalUtils import GdalUtils

pluginPath = os.path.split(os.path.split(os.path.dirname(__file__))[0])[0]


class GridLinear(GdalAlgorithm):

    INPUT = "INPUT"
    Z_FIELD = "Z_FIELD"
    RADIUS = "RADIUS"
    NODATA = "NODATA"
    OPTIONS = "OPTIONS"
    CREATION_OPTIONS = "CREATION_OPTIONS"
    EXTRA = "EXTRA"
    DATA_TYPE = "DATA_TYPE"
    OUTPUT = "OUTPUT"

    TYPES = [
        "Byte",
        "Int16",
        "UInt16",
        "UInt32",
        "Int32",
        "Float32",
        "Float64",
        "CInt16",
        "CInt32",
        "CFloat32",
        "CFloat64",
        "Int8",
    ]

    def __init__(self):
        super().__init__()

    def initAlgorithm(self, config=None):
        self.addParameter(
            QgsProcessingParameterFeatureSource(
                self.INPUT,
                self.tr("Point layer"),
                [QgsProcessing.SourceType.TypeVectorPoint],
            )
        )

        z_field_param = QgsProcessingParameterField(
            self.Z_FIELD,
            self.tr("Z value from field"),
            None,
            self.INPUT,
            QgsProcessingParameterField.DataType.Numeric,
            optional=True,
        )
        z_field_param.setFlags(
            z_field_param.flags() | QgsProcessingParameterDefinition.Flag.FlagAdvanced
        )
        self.addParameter(z_field_param)

        self.addParameter(
            QgsProcessingParameterNumber(
                self.RADIUS,
                self.tr("Search distance "),
                type=QgsProcessingParameterNumber.Type.Double,
                minValue=-1.0,
                defaultValue=-1.0,
            )
        )
        self.addParameter(
            QgsProcessingParameterNumber(
                self.NODATA,
                self.tr("NODATA marker to fill empty points"),
                type=QgsProcessingParameterNumber.Type.Double,
                defaultValue=0.0,
            )
        )

        # backwards compatibility parameter
        # TODO QGIS 4: remove parameter and related logic
        options_param = QgsProcessingParameterString(
            self.OPTIONS,
            self.tr("Additional creation options"),
            defaultValue="",
            optional=True,
        )
        options_param.setFlags(
            options_param.flags() | QgsProcessingParameterDefinition.Flag.Hidden
        )
        options_param.setMetadata({"widget_wrapper": {"widget_type": "rasteroptions"}})
        self.addParameter(options_param)

        creation_options_param = QgsProcessingParameterString(
            self.CREATION_OPTIONS,
            self.tr("Additional creation options"),
            defaultValue="",
            optional=True,
        )
        creation_options_param.setFlags(
            creation_options_param.flags()
            | QgsProcessingParameterDefinition.Flag.FlagAdvanced
        )
        creation_options_param.setMetadata(
            {"widget_wrapper": {"widget_type": "rasteroptions"}}
        )
        self.addParameter(creation_options_param)

        extra_param = QgsProcessingParameterString(
            self.EXTRA,
            self.tr("Additional command-line parameters"),
            defaultValue=None,
            optional=True,
        )
        extra_param.setFlags(
            extra_param.flags() | QgsProcessingParameterDefinition.Flag.FlagAdvanced
        )
        self.addParameter(extra_param)

        dataType_param = QgsProcessingParameterEnum(
            self.DATA_TYPE,
            self.tr("Output data type"),
            self.TYPES,
            allowMultiple=False,
            defaultValue=5,
        )
        dataType_param.setFlags(
            dataType_param.flags() | QgsProcessingParameterDefinition.Flag.FlagAdvanced
        )
        self.addParameter(dataType_param)

        self.addParameter(
            QgsProcessingParameterRasterDestination(
                self.OUTPUT, self.tr("Interpolated (Linear)")
            )
        )

    def name(self):
        return "gridlinear"

    def displayName(self):
        return self.tr("Grid (Linear)")

    def group(self):
        return self.tr("Raster analysis")

    def groupId(self):
        return "rasteranalysis"

    def icon(self):
        return QIcon(os.path.join(pluginPath, "images", "gdaltools", "grid.png"))

    def commandName(self):
        return "gdal_grid"

    def getConsoleCommands(self, parameters, context, feedback, executing=True):
        input_details = self.getOgrCompatibleSource(
            self.INPUT, parameters, context, feedback, executing
        )

        arguments = ["-l", input_details.layer_name]
        fieldName = self.parameterAsString(parameters, self.Z_FIELD, context)
        if fieldName:
            arguments.append("-zfield")
            arguments.append(fieldName)

        params = "linear"
        params += f":radius={self.parameterAsDouble(parameters, self.RADIUS, context)}"
        params += f":nodata={self.parameterAsDouble(parameters, self.NODATA, context)}"

        arguments.append("-a")
        arguments.append(params)

        data_type = self.parameterAsEnum(parameters, self.DATA_TYPE, context)
        if self.TYPES[data_type] == "Int8" and GdalUtils.version() < 3070000:
            raise QgsProcessingException(
                self.tr("Int8 data type requires GDAL version 3.7 or later")
            )

        arguments.append("-ot " + self.TYPES[data_type])

        out = self.parameterAsOutputLayer(parameters, self.OUTPUT, context)
        self.setOutputValue(self.OUTPUT, out)

        output_format = QgsRasterFileWriter.driverForExtension(os.path.splitext(out)[1])
        if not output_format:
            raise QgsProcessingException(self.tr("Output format is invalid"))

        arguments.append("-of")
        arguments.append(output_format)

        if input_details.open_options:
            if GdalUtils.version() < 3070000:
                raise QgsProcessingException(
                    self.tr(
                        "Open options are not supported by gdal_grid version {} (requires GDAL version 3.7 or later)"
                    ).format(GdalUtils.readableVersion())
                )

            arguments.extend(input_details.open_options_as_arguments())

        options = self.parameterAsString(parameters, self.CREATION_OPTIONS, context)
        # handle backwards compatibility parameter OPTIONS
        if self.OPTIONS in parameters and parameters[self.OPTIONS] not in (None, ""):
            options = self.parameterAsString(parameters, self.OPTIONS, context)
        if options:
            arguments.extend(GdalUtils.parseCreationOptions(options))

        if self.EXTRA in parameters and parameters[self.EXTRA] not in (None, ""):
            extra = self.parameterAsString(parameters, self.EXTRA, context)
            arguments.append(extra)

        arguments.append(input_details.connection_string)
        arguments.append(out)

        if input_details.credential_options:
            arguments.extend(input_details.credential_options_as_arguments())

        return [self.commandName(), GdalUtils.escapeAndJoin(arguments)]
