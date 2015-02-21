#-------------------------------------------------
#
# Project created by QtCreator 2015-02-12T16:45:57
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = detectCV
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ObjectExtractor.cpp \
    package_bgs/ae/KDE.cpp \
    package_bgs/ae/KernelTable.cpp \
    package_bgs/ae/NPBGmodel.cpp \
    package_bgs/ae/NPBGSubtractor.cpp \
    package_bgs/av/TBackground.cpp \
    package_bgs/av/TBackgroundVuMeter.cpp \
    package_bgs/av/VuMeter.cpp \
    package_bgs/bl/sdLaMa091.cpp \
    package_bgs/bl/SigmaDeltaBGS.cpp \
    package_bgs/ck/graph.cpp \
    package_bgs/ck/LbpMrf.cpp \
    package_bgs/ck/maxflow.cpp \
    package_bgs/ck/MEDefs.cpp \
    package_bgs/ck/MEHistogram.cpp \
    package_bgs/ck/MEImage.cpp \
    package_bgs/ck/MotionDetection.cpp \
    package_bgs/db/imbs.cpp \
    package_bgs/db/IndependentMultimodalBGS.cpp \
    package_bgs/dp/AdaptiveMedianBGS.cpp \
    package_bgs/dp/DPAdaptiveMedianBGS.cpp \
    package_bgs/dp/DPEigenbackgroundBGS.cpp \
    package_bgs/dp/DPGrimsonGMMBGS.cpp \
    package_bgs/dp/DPMeanBGS.cpp \
    package_bgs/dp/DPPratiMediodBGS.cpp \
    package_bgs/dp/DPTextureBGS.cpp \
    package_bgs/dp/DPWrenGABGS.cpp \
    package_bgs/dp/DPZivkovicAGMMBGS.cpp \
    package_bgs/dp/Eigenbackground.cpp \
    package_bgs/dp/Error.cpp \
    package_bgs/dp/GrimsonGMM.cpp \
    package_bgs/dp/Image.cpp \
    package_bgs/dp/MeanBGS.cpp \
    package_bgs/dp/PratiMediodBGS.cpp \
    package_bgs/dp/TextureBGS.cpp \
    package_bgs/dp/WrenGA.cpp \
    package_bgs/dp/ZivkovicAGMM.cpp \
    package_bgs/jmo/blob.cpp \
    package_bgs/jmo/BlobExtraction.cpp \
    package_bgs/jmo/BlobResult.cpp \
    package_bgs/jmo/CMultiLayerBGS.cpp \
    package_bgs/jmo/LocalBinaryPattern.cpp \
    package_bgs/jmo/MultiLayerBGS.cpp \
    package_bgs/lb/BGModel.cpp \
    package_bgs/lb/BGModelFuzzyGauss.cpp \
    package_bgs/lb/BGModelFuzzySom.cpp \
    package_bgs/lb/BGModelGauss.cpp \
    package_bgs/lb/BGModelMog.cpp \
    package_bgs/lb/BGModelSom.cpp \
    package_bgs/lb/LBAdaptiveSOM.cpp \
    package_bgs/lb/LBFuzzyAdaptiveSOM.cpp \
    package_bgs/lb/LBFuzzyGaussian.cpp \
    package_bgs/lb/LBMixtureOfGaussians.cpp \
    package_bgs/lb/LBSimpleGaussian.cpp \
    package_bgs/my/MyBGS.cpp \
    package_bgs/pl/BackgroundSubtractorLBSP.cpp \
    package_bgs/pl/BackgroundSubtractorLOBSTER.cpp \
    package_bgs/pl/BackgroundSubtractorSuBSENSE.cpp \
    package_bgs/pl/LBSP.cpp \
    package_bgs/pl/LOBSTER.cpp \
    package_bgs/pl/SuBSENSE.cpp \
    package_bgs/sjn/SJN_MultiCueBGS.cpp \
    package_bgs/tb/FuzzyChoquetIntegral.cpp \
    package_bgs/tb/FuzzySugenoIntegral.cpp \
    package_bgs/tb/FuzzyUtils.cpp \
    package_bgs/tb/MRF.cpp \
    package_bgs/tb/PerformanceUtils.cpp \
    package_bgs/tb/PixelUtils.cpp \
    package_bgs/tb/T2FGMM.cpp \
    package_bgs/tb/T2FGMM_UM.cpp \
    package_bgs/tb/T2FGMM_UV.cpp \
    package_bgs/tb/T2FMRF.cpp \
    package_bgs/tb/T2FMRF_UM.cpp \
    package_bgs/tb/T2FMRF_UV.cpp \
    package_bgs/AdaptiveBackgroundLearning.cpp \
    package_bgs/AdaptiveSelectiveBackgroundLearning.cpp \
    package_bgs/FrameDifferenceBGS.cpp \
    package_bgs/GMG.cpp \
    package_bgs/MixtureOfGaussianV1BGS.cpp \
    package_bgs/MixtureOfGaussianV2BGS.cpp \
    package_bgs/StaticFrameDifferenceBGS.cpp \
    package_bgs/WeightedMovingMeanBGS.cpp \
    package_bgs/WeightedMovingVarianceBGS.cpp \
    BGSConvertor.cpp

CONFIG += c++11
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib

LIBS += -lopencv_calib3d \
-lopencv_contrib \
-lopencv_core \
-lopencv_features2d \
-lopencv_flann \
-lopencv_gpu \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_legacy \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_video

HEADERS += \
    ObjectExtractor.h \
    package_bgs/ae/KDE.h \
    package_bgs/ae/KernelTable.h \
    package_bgs/ae/NPBGmodel.h \
    package_bgs/ae/NPBGSubtractor.h \
    package_bgs/av/TBackground.h \
    package_bgs/av/TBackgroundVuMeter.h \
    package_bgs/av/VuMeter.h \
    package_bgs/bl/sdLaMa091.h \
    package_bgs/bl/SigmaDeltaBGS.h \
    package_bgs/bl/stdbool.h \
    package_bgs/ck/block.h \
    package_bgs/ck/graph.h \
    package_bgs/ck/LbpMrf.h \
    package_bgs/ck/MEDefs.hpp \
    package_bgs/ck/MEHistogram.hpp \
    package_bgs/ck/MEImage.hpp \
    package_bgs/ck/MotionDetection.hpp \
    package_bgs/db/imbs.hpp \
    package_bgs/db/IndependentMultimodalBGS.h \
    package_bgs/dp/AdaptiveMedianBGS.h \
    package_bgs/dp/Bgs.h \
    package_bgs/dp/BgsParams.h \
    package_bgs/dp/DPAdaptiveMedianBGS.h \
    package_bgs/dp/DPEigenbackgroundBGS.h \
    package_bgs/dp/DPGrimsonGMMBGS.h \
    package_bgs/dp/DPMeanBGS.h \
    package_bgs/dp/DPPratiMediodBGS.h \
    package_bgs/dp/DPTextureBGS.h \
    package_bgs/dp/DPWrenGABGS.h \
    package_bgs/dp/DPZivkovicAGMMBGS.h \
    package_bgs/dp/Eigenbackground.h \
    package_bgs/dp/Error.h \
    package_bgs/dp/GrimsonGMM.h \
    package_bgs/dp/Image.h \
    package_bgs/dp/MeanBGS.h \
    package_bgs/dp/PratiMediodBGS.h \
    package_bgs/dp/TextureBGS.h \
    package_bgs/dp/WrenGA.h \
    package_bgs/dp/ZivkovicAGMM.h \
    package_bgs/jmo/BackgroundSubtractionAPI.h \
    package_bgs/jmo/BGS.h \
    package_bgs/jmo/blob.h \
    package_bgs/jmo/BlobExtraction.h \
    package_bgs/jmo/BlobLibraryConfiguration.h \
    package_bgs/jmo/BlobResult.h \
    package_bgs/jmo/CMultiLayerBGS.h \
    package_bgs/jmo/LocalBinaryPattern.h \
    package_bgs/jmo/MultiLayerBGS.h \
    package_bgs/jmo/OpenCvDataConversion.h \
    package_bgs/lb/BGModel.h \
    package_bgs/lb/BGModelFuzzyGauss.h \
    package_bgs/lb/BGModelFuzzySom.h \
    package_bgs/lb/BGModelGauss.h \
    package_bgs/lb/BGModelMog.h \
    package_bgs/lb/BGModelSom.h \
    package_bgs/lb/LBAdaptiveSOM.h \
    package_bgs/lb/LBFuzzyAdaptiveSOM.h \
    package_bgs/lb/LBFuzzyGaussian.h \
    package_bgs/lb/LBMixtureOfGaussians.h \
    package_bgs/lb/LBSimpleGaussian.h \
    package_bgs/lb/Types.h \
    package_bgs/my/MyBGS.h \
    package_bgs/pl/BackgroundSubtractorLBSP.h \
    package_bgs/pl/BackgroundSubtractorLOBSTER.h \
    package_bgs/pl/BackgroundSubtractorSuBSENSE.h \
    package_bgs/pl/DistanceUtils.h \
    package_bgs/pl/LBSP.h \
    package_bgs/pl/LOBSTER.h \
    package_bgs/pl/RandUtils.h \
    package_bgs/pl/SuBSENSE.h \
    package_bgs/sjn/SJN_MultiCueBGS.h \
    package_bgs/tb/FuzzyChoquetIntegral.h \
    package_bgs/tb/FuzzySugenoIntegral.h \
    package_bgs/tb/FuzzyUtils.h \
    package_bgs/tb/MRF.h \
    package_bgs/tb/PerformanceUtils.h \
    package_bgs/tb/PixelUtils.h \
    package_bgs/tb/T2FGMM.h \
    package_bgs/tb/T2FGMM_UM.h \
    package_bgs/tb/T2FGMM_UV.h \
    package_bgs/tb/T2FMRF.h \
    package_bgs/tb/T2FMRF_UM.h \
    package_bgs/tb/T2FMRF_UV.h \
    package_bgs/AdaptiveBackgroundLearning.h \
    package_bgs/AdaptiveSelectiveBackgroundLearning.h \
    package_bgs/FrameDifferenceBGS.h \
    package_bgs/GMG.h \
    package_bgs/IBGS.h \
    package_bgs/MixtureOfGaussianV1BGS.h \
    package_bgs/MixtureOfGaussianV2BGS.h \
    package_bgs/StaticFrameDifferenceBGS.h \
    package_bgs/WeightedMovingMeanBGS.h \
    package_bgs/WeightedMovingVarianceBGS.h \
    BGSConvertor.h

OTHER_FILES += \
    testframe_3.jpg \
    package_bgs/pl/LBSP_16bits_dbcross_1ch.i \
    package_bgs/pl/LBSP_16bits_dbcross_3ch1t.i \
    package_bgs/pl/LBSP_16bits_dbcross_3ch3t.i \
    package_bgs/pl/LBSP_16bits_dbcross_s3ch.i
