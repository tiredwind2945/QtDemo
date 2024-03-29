greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET 			 = OBJImporter
TEMPLATE 		 = app
UI_DIR      	+= .build
RCC_DIR     	+= .build
MOC_DIR     	+= .build
OBJECTS_DIR 	+= .build
DEFINES 		+= QT_DEPRECATED_WARNINGS

INCLUDEPATH += /usr/local/include/vtk-9.1/

LIBS += -L/usr/local/lib \
        -lvtkcgns-9.1 \
        -lvtkChartsCore-9.1 \
        -lvtkCommonColor-9.1 \
        -lvtkCommonComputationalGeometry-9.1 \
        -lvtkCommonCore-9.1 \
        -lvtkCommonDataModel-9.1 \
        -lvtkCommonExecutionModel-9.1 \
        -lvtkCommonMath-9.1 \
        -lvtkCommonMisc-9.1 \
        -lvtkCommonSystem-9.1 \
        -lvtkCommonTransforms-9.1 \
        -lvtkDICOMParser-9.1 \
        -lvtkDomainsChemistry-9.1 \
        -lvtkDomainsChemistryOpenGL2-9.1 \
        -lvtkdoubleconversion-9.1 \
        -lvtkexodusII-9.1 \
        -lvtkexpat-9.1 \
        -lvtkFiltersAMR-9.1 \
        -lvtkFiltersCore-9.1 \
        -lvtkFiltersExtraction-9.1 \
        -lvtkFiltersFlowPaths-9.1 \
        -lvtkFiltersGeneral-9.1 \
        -lvtkFiltersGeneric-9.1 \
        -lvtkFiltersGeometry-9.1 \
        -lvtkFiltersHybrid-9.1 \
        -lvtkFiltersHyperTree-9.1 \
        -lvtkFiltersImaging-9.1 \
        -lvtkFiltersModeling-9.1 \
        -lvtkFiltersParallel-9.1 \
        -lvtkFiltersParallelImaging-9.1 \
        -lvtkFiltersPoints-9.1 \
        -lvtkFiltersProgrammable-9.1 \
        -lvtkFiltersSelection-9.1 \
        -lvtkFiltersSMP-9.1 \
        -lvtkFiltersSources-9.1 \
        -lvtkFiltersStatistics-9.1 \
        -lvtkFiltersTexture-9.1 \
        -lvtkFiltersTopology-9.1 \
        -lvtkFiltersVerdict-9.1 \
        -lvtkfmt-9.1 \
        -lvtkfreetype-9.1 \
        -lvtkGeovisCore-9.1 \
        -lvtkgl2ps-9.1 \
        -lvtkglew-9.1 \
        -lvtkGUISupportQt-9.1 \
        -lvtkGUISupportQtSQL-9.1 \
        -lvtkhdf5-9.1 \
        -lvtkhdf5_hl-9.1 \
        -lvtkImagingColor-9.1 \
        -lvtkImagingCore-9.1 \
        -lvtkImagingFourier-9.1 \
        -lvtkImagingGeneral-9.1 \
        -lvtkImagingHybrid-9.1 \
        -lvtkImagingMath-9.1 \
        -lvtkImagingMorphological-9.1 \
        -lvtkImagingSources-9.1 \
        -lvtkImagingStatistics-9.1 \
        -lvtkImagingStencil-9.1 \
        -lvtkInfovisCore-9.1 \
        -lvtkInfovisLayout-9.1 \
        -lvtkInteractionImage-9.1 \
        -lvtkInteractionStyle-9.1 \
        -lvtkInteractionWidgets-9.1 \
        -lvtkIOAMR-9.1 \
        -lvtkIOAsynchronous-9.1 \
        -lvtkIOCGNSReader-9.1 \
        -lvtkIOChemistry-9.1 \
        -lvtkIOCityGML-9.1 \
        -lvtkIOCONVERGECFD-9.1 \
        -lvtkIOCore-9.1 \
        -lvtkIOEnSight-9.1 \
        -lvtkIOExodus-9.1 \
        -lvtkIOExport-9.1 \
        -lvtkIOExportGL2PS-9.1 \
        -lvtkIOExportPDF-9.1 \
        -lvtkIOGeometry-9.1 \
        -lvtkIOHDF-9.1 \
        -lvtkIOImage-9.1 \
        -lvtkIOImport-9.1 \
        -lvtkIOInfovis-9.1 \
        -lvtkIOIOSS-9.1 \
        -lvtkIOLegacy-9.1 \
        -lvtkIOLSDyna-9.1 \
        -lvtkIOMINC-9.1 \
        -lvtkIOMotionFX-9.1 \
        -lvtkIOMovie-9.1 \
        -lvtkIONetCDF-9.1 \
        -lvtkIOOggTheora-9.1 \
        -lvtkIOParallel-9.1 \
        -lvtkIOParallelXML-9.1 \
        -lvtkIOPLY-9.1 \
        -lvtkIOSegY-9.1 \
        -lvtkIOSQL-9.1 \
        -lvtkioss-9.1 \
        -lvtkIOTecplotTable-9.1 \
        -lvtkIOVeraOut-9.1 \
        -lvtkIOVideo-9.1 \
        -lvtkIOXML-9.1 \
        -lvtkIOXMLParser-9.1 \
        -lvtkjpeg-9.1 \
        -lvtkjsoncpp-9.1 \
        -lvtkkissfft-9.1 \
        -lvtklibharu-9.1 \
        -lvtklibproj-9.1 \
        -lvtklibxml2-9.1 \
        -lvtkloguru-9.1 \
        -lvtklz4-9.1 \
        -lvtklzma-9.1 \
        -lvtkmetaio-9.1 \
        -lvtknetcdf-9.1 \
        -lvtkogg-9.1 \
        -lvtkParallelCore-9.1 \
        -lvtkParallelDIY-9.1 \
        -lvtkpng-9.1 \
        -lvtkpugixml-9.1 \
        -lvtkRenderingAnnotation-9.1 \
        -lvtkRenderingContext2D-9.1 \
        -lvtkRenderingContextOpenGL2-9.1 \
        -lvtkRenderingCore-9.1 \
        -lvtkRenderingFreeType-9.1 \
        -lvtkRenderingGL2PSOpenGL2-9.1 \
        -lvtkRenderingImage-9.1 \
        -lvtkRenderingLabel-9.1 \
        -lvtkRenderingLOD-9.1 \
        -lvtkRenderingOpenGL2-9.1 \
        -lvtkRenderingQt-9.1 \
        -lvtkRenderingSceneGraph-9.1 \
        -lvtkRenderingUI-9.1 \
        -lvtkRenderingVolume-9.1 \
        -lvtkRenderingVolumeOpenGL2-9.1 \
        -lvtkRenderingVtkJS-9.1 \
        -lvtksqlite-9.1 \
        -lvtksys-9.1 \
        -lvtkTestingRendering-9.1 \
        -lvtktheora-9.1 \
        -lvtktiff-9.1 \
        -lvtkverdict-9.1 \
        -lvtkViewsContext2D-9.1 \
        -lvtkViewsCore-9.1 \
        -lvtkViewsInfovis-9.1 \
        -lvtkViewsQt-9.1 \
        -lvtkWrappingTools-9.1 \
        -lvtkzlib-9.1

SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

FORMS += \
        widget.ui
