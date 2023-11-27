# ------------------- Required for MSVC nmake ---------------------------------
# This file should be included at the top of a MAKEFILE as follows:


CPU = AMD64

MODEL     = line_follower
TARGET      = sfun
MODULE_SRCS   = c2_line_follower.cpp half_type.cpp
MODEL_SRC  = line_follower_sfun.cpp
MODEL_REG = line_follower_sfun_registry.cpp
MAKEFILE    = line_follower_sfun.mak
MATLAB_ROOT  = C:\Program Files\MATLAB\R2021a
BUILDARGS   =

#--------------------------- Tool Specifications ------------------------------
#
#
MSVC_ROOT1 = $(MSDEVDIR:SharedIDE=vc)
MSVC_ROOT2 = $(MSVC_ROOT1:SHAREDIDE=vc)
MSVC_ROOT  = $(MSVC_ROOT2:sharedide=vc)

# Compiler tool locations, CC, LD, LIBCMD:
CC     = cl.exe
LD     = link.exe
LIBCMD = lib.exe
#------------------------------ Include/Lib Path ------------------------------

USER_INCLUDES   =  /I "C:\OneDrive\onedrive - mathworks\shared with everyone\Internal\community\GitHub\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src" /I "C:\OneDrive\onedrive - mathworks\shared with everyone\Internal\community\GitHub\ai-robotics-workshop\work" /I "C:\OneDrive\onedrive - mathworks\shared with everyone\Internal\community\GitHub\ai-robotics-workshop\src\003_system_integration"
AUX_INCLUDES   = 
MLSLSF_INCLUDES = \
    /I "C:\Program Files\MATLAB\R2021a\extern\include" \
    /I "C:\Program Files\MATLAB\R2021a\simulink\include" \
    /I "C:\Program Files\MATLAB\R2021a\simulink\include\sf_runtime" \
    /I "C:\Program Files\MATLAB\R2021a\stateflow\c\mex\include" \
    /I "C:\Program Files\MATLAB\R2021a\rtw\c\src" \
    /I "C:\OneDrive\OneDrive - MathWorks\Shared with Everyone\Internal\Community\GitHub\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src" 

COMPILER_INCLUDES = /I "$(MSVC_ROOT)\include"

THIRD_PARTY_INCLUDES   =  /I "C:\Program Files\MATLAB\R2021a\extern\include\mkldnn"
INCLUDE_PATH = $(USER_INCLUDES) $(AUX_INCLUDES) $(MLSLSF_INCLUDES)\
 $(THIRD_PARTY_INCLUDES)
LIB_PATH     = "$(MSVC_ROOT)\lib"

CFLAGS = /c /Zp8 /GR /W3 /EHs /D_CRT_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_DEPRECATE /D_SECURE_SCL=0 /DMX_COMPAT_64 /DMATLAB_MEXCMD_RELEASE=R2018a /DMATLAB_MEX_FILE /nologo /MD  
LDFLAGS = /nologo /dll /MANIFEST /OPT:NOREF /export:mexFunction /export:mexfilerequiredapiversion  
#----------------------------- Source Files -----------------------------------

REQ_SRCS  =  $(MODEL_SRC) $(MODEL_REG) $(MODULE_SRCS)

USER_OBJS =

AUX_ABS_OBJS =

THIRD_PARTY_OBJS     = \
     "MWAvgPoolingLayer.obj" \
     "MWCNNLayer.obj" \
     "MWConvLayer.obj" \
     "MWElementwiseAffineLayer.obj" \
     "MWFCLayer.obj" \
     "MWFusedConvReLULayer.obj" \
     "MWInputLayer.obj" \
     "MWMaxPoolingLayer.obj" \
     "MWOutputLayer.obj" \
     "MWTensorBase.obj" \
     "MWAvgPoolingLayerImpl.obj" \
     "MWConvLayerImpl.obj" \
     "MWElementwiseAffineLayerImpl.obj" \
     "MWFCLayerImpl.obj" \
     "MWFusedConvReLULayerImpl.obj" \
     "MWInputLayerImpl.obj" \
     "MWMaxPoolingLayerImpl.obj" \
     "MWOutputLayerImpl.obj" \
     "MWCNNLayerImpl.obj" \
     "MWTargetNetworkImpl.obj" \
     "MWMkldnnUtils.obj" \
     "MWCustomLayerForMKLDNN.obj" \
     "c_mexapi_version.obj" \

REQ_OBJS = $(REQ_SRCS:.cpp=.obj)
REQ_OBJS2 = $(REQ_OBJS:.c=.obj)
OBJS = $(REQ_OBJS2) $(USER_OBJS) $(AUX_ABS_OBJS) $(THIRD_PARTY_OBJS)
OBJLIST_FILE = line_follower_sfun.mol
SFCLIB = 
AUX_LNK_OBJS =     
USER_LIBS = 
#--------------------------------- Rules --------------------------------------

MEX_FILE_NAME_WO_EXT = $(MODEL)_$(TARGET)
MEX_FILE_NAME = $(MEX_FILE_NAME_WO_EXT).mexw64
MEX_FILE_CSF =
all : $(MEX_FILE_NAME) $(MEX_FILE_CSF)

$(MEX_FILE_NAME) : $(MAKEFILE) $(OBJS) $(SFCLIB) $(AUX_LNK_OBJS) $(USER_LIBS) $(THIRD_PARTY_LIBS)
 @echo ### Linking ...
 $(LD) $(LDFLAGS) /OUT:$(MEX_FILE_NAME) /map:"$(MEX_FILE_NAME_WO_EXT).map"\
  $(USER_LIBS) $(SFCLIB) $(AUX_LNK_OBJS)\
  $(DSP_LIBS) $(THIRD_PARTY_LIBS)\
  @$(OBJLIST_FILE)
     mt -outputresource:"$(MEX_FILE_NAME);2" -manifest "$(MEX_FILE_NAME).manifest"
	@echo ### Created $@

.c.obj :
	@echo ### Compiling "$<"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "$<"

.cpp.obj :
	@echo ### Compiling "$<"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "$<"


MWAvgPoolingLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayer.cpp"
MWCNNLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayer.cpp"
MWConvLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayer.cpp"
MWElementwiseAffineLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayer.cpp"
MWFCLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayer.cpp"
MWFusedConvReLULayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayer.cpp"
MWInputLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayer.cpp"
MWMaxPoolingLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayer.cpp"
MWOutputLayer.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayer.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayer.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayer.cpp"
MWTensorBase.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTensorBase.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTensorBase.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTensorBase.cpp"
MWAvgPoolingLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWAvgPoolingLayerImpl.cpp"
MWConvLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWConvLayerImpl.cpp"
MWElementwiseAffineLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWElementwiseAffineLayerImpl.cpp"
MWFCLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFCLayerImpl.cpp"
MWFusedConvReLULayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWFusedConvReLULayerImpl.cpp"
MWInputLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWInputLayerImpl.cpp"
MWMaxPoolingLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMaxPoolingLayerImpl.cpp"
MWOutputLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWOutputLayerImpl.cpp"
MWCNNLayerImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayerImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayerImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCNNLayerImpl.cpp"
MWTargetNetworkImpl.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTargetNetworkImpl.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTargetNetworkImpl.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWTargetNetworkImpl.cpp"
MWMkldnnUtils.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMkldnnUtils.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMkldnnUtils.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWMkldnnUtils.cpp"
MWCustomLayerForMKLDNN.obj :  "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCustomLayerForMKLDNN.cpp"
	@echo ### Compiling "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCustomLayerForMKLDNN.cpp"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "c:\onedrive\onedrive - mathworks\shared with everyone\internal\community\github\ai-robotics-workshop\work\slprj\_sfprj\line_follower\_self\sfun\src\MWCustomLayerForMKLDNN.cpp"
c_mexapi_version.obj :  "C:\Program Files\MATLAB\R2021a\extern\version\c_mexapi_version.c"
	@echo ### Compiling "C:\Program Files\MATLAB\R2021a\extern\version\c_mexapi_version.c"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "C:\Program Files\MATLAB\R2021a\extern\version\c_mexapi_version.c"
