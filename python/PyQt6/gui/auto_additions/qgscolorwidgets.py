# The following has been generated automatically from src/gui/qgscolorwidgets.h
QgsColorWidget.Multiple = QgsColorWidget.ColorComponent.Multiple
QgsColorWidget.Red = QgsColorWidget.ColorComponent.Red
QgsColorWidget.Green = QgsColorWidget.ColorComponent.Green
QgsColorWidget.Blue = QgsColorWidget.ColorComponent.Blue
QgsColorWidget.Hue = QgsColorWidget.ColorComponent.Hue
QgsColorWidget.Saturation = QgsColorWidget.ColorComponent.Saturation
QgsColorWidget.Value = QgsColorWidget.ColorComponent.Value
QgsColorWidget.Alpha = QgsColorWidget.ColorComponent.Alpha
QgsColorWidget.Cyan = QgsColorWidget.ColorComponent.Cyan
QgsColorWidget.Magenta = QgsColorWidget.ColorComponent.Magenta
QgsColorWidget.Yellow = QgsColorWidget.ColorComponent.Yellow
QgsColorWidget.Black = QgsColorWidget.ColorComponent.Black
# monkey patching scoped based enum
QgsColorWidget.ComponentUnit.Scaled0to255.__doc__ = "Values in the range 0-255"
QgsColorWidget.ComponentUnit.Percent.__doc__ = "Percent values in the range 0-100"
QgsColorWidget.ComponentUnit.Degree.__doc__ = "Degree values in the range 0-359"
QgsColorWidget.ComponentUnit.__doc__ = """Specified the color component unit

* ``Scaled0to255``: Values in the range 0-255
* ``Percent``: Percent values in the range 0-100
* ``Degree``: Degree values in the range 0-359

"""
# --
QgsColorWidget.ComponentUnit.baseClass = QgsColorWidget
QgsColorRampWidget.Horizontal = QgsColorRampWidget.Orientation.Horizontal
QgsColorRampWidget.Vertical = QgsColorRampWidget.Orientation.Vertical
QgsColorTextWidget.HexRgb = QgsColorTextWidget.ColorTextFormat.HexRgb
QgsColorTextWidget.HexRgbA = QgsColorTextWidget.ColorTextFormat.HexRgbA
QgsColorTextWidget.Rgb = QgsColorTextWidget.ColorTextFormat.Rgb
QgsColorTextWidget.Rgba = QgsColorTextWidget.ColorTextFormat.Rgba
QgsColorTextWidget.ColorTextFormat.baseClass = QgsColorTextWidget
try:
    QgsColorWidget.__attribute_docs__ = {'colorChanged': "Emitted when the widget's color changes\n\n:param color: new widget color\n", 'hovered': 'Emitted when mouse hovers over widget.\n'}
    QgsColorWidget.createDragIcon = staticmethod(QgsColorWidget.createDragIcon)
    QgsColorWidget.componentUnit = staticmethod(QgsColorWidget.componentUnit)
    QgsColorWidget.alterColor = staticmethod(QgsColorWidget.alterColor)
    QgsColorWidget.alterColorF = staticmethod(QgsColorWidget.alterColorF)
    QgsColorWidget.__virtual_methods__ = ['setColor', 'setComponent', 'setComponentValue', 'setComponentValueF']
    QgsColorWidget.__overridden_methods__ = ['dragEnterEvent', 'dropEvent', 'mouseMoveEvent', 'mousePressEvent', 'mouseReleaseEvent']
    QgsColorWidget.__signal_arguments__ = {'colorChanged': ['color: QColor']}
except (NameError, AttributeError):
    pass
try:
    QgsColorWidgetAction.__attribute_docs__ = {'colorChanged': 'Emitted when a color has been selected from the widget\n\n:param color: selected color\n'}
    QgsColorWidgetAction.__signal_arguments__ = {'colorChanged': ['color: QColor']}
except (NameError, AttributeError):
    pass
try:
    QgsColorRampWidget.__attribute_docs__ = {'valueChanged': "Emitted when the widget's color component value changes\n\n:param value: new value of color component in the range between 0 and\n              the value returned by\n              :py:func:`~QgsColorRampWidget.componentRange`\n\n.. deprecated:: 3.40\n\n   Use :py:func:`~QgsColorRampWidget.valueChangedF` instead.\n", 'valueChangedF': "Emitted when the widget's color component value changes\n\n:param value: new value of color component in the range 0.0-1.0\n\n.. versionadded:: 3.40\n"}
    QgsColorRampWidget.__overridden_methods__ = ['sizeHint', 'paintEvent', 'mouseMoveEvent', 'wheelEvent', 'mousePressEvent', 'mouseReleaseEvent', 'keyPressEvent']
    QgsColorRampWidget.__signal_arguments__ = {'valueChangedF': ['value: float']}
except (NameError, AttributeError):
    pass
try:
    QgsColorPreviewWidget.__virtual_methods__ = ['setColor2']
    QgsColorPreviewWidget.__overridden_methods__ = ['paintEvent', 'sizeHint', 'mousePressEvent', 'mouseReleaseEvent', 'mouseMoveEvent']
except (NameError, AttributeError):
    pass
try:
    QgsColorWheel.__overridden_methods__ = ['sizeHint', 'paintEvent', 'setColor', 'resizeEvent', 'mouseMoveEvent', 'mousePressEvent', 'mouseReleaseEvent']
except (NameError, AttributeError):
    pass
try:
    QgsColorBox.__overridden_methods__ = ['sizeHint', 'paintEvent', 'setComponent', 'setColor', 'resizeEvent', 'mouseMoveEvent', 'mousePressEvent', 'mouseReleaseEvent']
except (NameError, AttributeError):
    pass
try:
    QgsColorSliderWidget.__overridden_methods__ = ['setComponent', 'setComponentValueF', 'setColor']
except (NameError, AttributeError):
    pass
try:
    QgsColorTextWidget.__overridden_methods__ = ['setColor', 'resizeEvent']
except (NameError, AttributeError):
    pass
