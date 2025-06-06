# The following has been generated automatically from src/core/qgstemporalnavigationobject.h
try:
    QgsTemporalNavigationObject.__attribute_docs__ = {'stateChanged': 'Emitted whenever the animation ``state`` changes.\n', 'navigationModeChanged': 'Emitted whenever the navigation ``mode`` changes.\n', 'temporalExtentsChanged': 'Emitted whenever the temporalExtent ``extent`` changes.\n', 'temporalFrameDurationChanged': 'Emitted whenever the frameDuration ``interval`` of the controller\nchanges.\n', 'totalMovieFramesChanged': 'Emitted whenever the total number of ``frames`` in the movie is changed.\n\n.. note::\n\n   This is only used when the :py:func:`~QgsTemporalNavigationObject.navigationMode` is set to :py:class:`Qgis`.TemporalNavigationMode.Movie.\n\n.. seealso:: :py:func:`setTotalMovieFrames`\n\n.. seealso:: :py:func:`totalMovieFrames`\n\n.. versionadded:: 3.36\n'}
    QgsTemporalNavigationObject.__overridden_methods__ = ['createExpressionContextScope']
    QgsTemporalNavigationObject.__signal_arguments__ = {'stateChanged': ['state: Qgis.AnimationState'], 'navigationModeChanged': ['mode: Qgis.TemporalNavigationMode'], 'temporalExtentsChanged': ['extent: QgsDateTimeRange'], 'temporalFrameDurationChanged': ['interval: QgsInterval'], 'totalMovieFramesChanged': ['frames: int']}
except (NameError, AttributeError):
    pass
