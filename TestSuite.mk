##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TestSuite
ConfigurationName      :=Debug
IntermediateDirectory  :=Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/Users/FOldenburg/dev"
ProjectPath            := "/Users/FOldenburg/dev/CGRayTracer"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Felix Oldenburg
Date                   :=01/03/11
CodeLitePath           :="/Users/FOldenburg/Library/Application Support/codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
C_CmpOptions           := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)$(UNIT_TEST_PP_SRC_DIR)/src" "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)UnitTest++ 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)$(UNIT_TEST_PP_SRC_DIR)" 


##
## User defined environment variables
##
CodeLiteDir:=/Applications/CodeLite.app/Contents/SharedSupport/
UNIT_TEST_PP_SRC_DIR:=/Users/FOldenburg/dev/UnitTest++
Objects=$(IntermediateDirectory)/tests_main$(ObjectSuffix) $(IntermediateDirectory)/tests_test_octree$(ObjectSuffix) $(IntermediateDirectory)/tests_test_triangle$(ObjectSuffix) $(IntermediateDirectory)/src_cube$(ObjectSuffix) $(IntermediateDirectory)/src_rect$(ObjectSuffix) $(IntermediateDirectory)/src_triangle$(ObjectSuffix) $(IntermediateDirectory)/src_vectormath$(ObjectSuffix) $(IntermediateDirectory)/tests_test_vector3d$(ObjectSuffix) $(IntermediateDirectory)/tests_test_cube$(ObjectSuffix) $(IntermediateDirectory)/src_octree$(ObjectSuffix) \
	$(IntermediateDirectory)/src_object$(ObjectSuffix) $(IntermediateDirectory)/src_sphere$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d Debug || $(MakeDirCommand) Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/tests_main$(ObjectSuffix): tests/main.cpp $(IntermediateDirectory)/tests_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/tests/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tests_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_main$(DependSuffix): tests/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_main$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_main$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/tests/main.cpp"

$(IntermediateDirectory)/tests_main$(PreprocessSuffix): tests/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_main$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/tests/main.cpp"

$(IntermediateDirectory)/tests_test_octree$(ObjectSuffix): tests/test_octree.cpp $(IntermediateDirectory)/tests_test_octree$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/tests/test_octree.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_octree$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_octree$(DependSuffix): tests/test_octree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_octree$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_octree$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/tests/test_octree.cpp"

$(IntermediateDirectory)/tests_test_octree$(PreprocessSuffix): tests/test_octree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_octree$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/tests/test_octree.cpp"

$(IntermediateDirectory)/tests_test_triangle$(ObjectSuffix): tests/test_triangle.cpp $(IntermediateDirectory)/tests_test_triangle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/tests/test_triangle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_triangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_triangle$(DependSuffix): tests/test_triangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_triangle$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_triangle$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/tests/test_triangle.cpp"

$(IntermediateDirectory)/tests_test_triangle$(PreprocessSuffix): tests/test_triangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_triangle$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/tests/test_triangle.cpp"

$(IntermediateDirectory)/src_cube$(ObjectSuffix): src/cube.cpp $(IntermediateDirectory)/src_cube$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/cube.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_cube$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_cube$(DependSuffix): src/cube.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_cube$(ObjectSuffix) -MF$(IntermediateDirectory)/src_cube$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/cube.cpp"

$(IntermediateDirectory)/src_cube$(PreprocessSuffix): src/cube.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_cube$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/cube.cpp"

$(IntermediateDirectory)/src_rect$(ObjectSuffix): src/rect.cpp $(IntermediateDirectory)/src_rect$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/rect.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_rect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_rect$(DependSuffix): src/rect.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_rect$(ObjectSuffix) -MF$(IntermediateDirectory)/src_rect$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/rect.cpp"

$(IntermediateDirectory)/src_rect$(PreprocessSuffix): src/rect.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_rect$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/rect.cpp"

$(IntermediateDirectory)/src_triangle$(ObjectSuffix): src/triangle.cpp $(IntermediateDirectory)/src_triangle$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/triangle.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_triangle$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_triangle$(DependSuffix): src/triangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_triangle$(ObjectSuffix) -MF$(IntermediateDirectory)/src_triangle$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/triangle.cpp"

$(IntermediateDirectory)/src_triangle$(PreprocessSuffix): src/triangle.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_triangle$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/triangle.cpp"

$(IntermediateDirectory)/src_vectormath$(ObjectSuffix): src/vectormath.cpp $(IntermediateDirectory)/src_vectormath$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/vectormath.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_vectormath$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vectormath$(DependSuffix): src/vectormath.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vectormath$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vectormath$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/vectormath.cpp"

$(IntermediateDirectory)/src_vectormath$(PreprocessSuffix): src/vectormath.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vectormath$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/vectormath.cpp"

$(IntermediateDirectory)/tests_test_vector3d$(ObjectSuffix): tests/test_vector3d.cpp $(IntermediateDirectory)/tests_test_vector3d$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/tests/test_vector3d.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_vector3d$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_vector3d$(DependSuffix): tests/test_vector3d.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_vector3d$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_vector3d$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/tests/test_vector3d.cpp"

$(IntermediateDirectory)/tests_test_vector3d$(PreprocessSuffix): tests/test_vector3d.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_vector3d$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/tests/test_vector3d.cpp"

$(IntermediateDirectory)/tests_test_cube$(ObjectSuffix): tests/test_cube.cpp $(IntermediateDirectory)/tests_test_cube$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/tests/test_cube.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tests_test_cube$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_test_cube$(DependSuffix): tests/test_cube.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_test_cube$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_test_cube$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/tests/test_cube.cpp"

$(IntermediateDirectory)/tests_test_cube$(PreprocessSuffix): tests/test_cube.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_test_cube$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/tests/test_cube.cpp"

$(IntermediateDirectory)/src_octree$(ObjectSuffix): src/octree.cpp $(IntermediateDirectory)/src_octree$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/octree.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_octree$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_octree$(DependSuffix): src/octree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_octree$(ObjectSuffix) -MF$(IntermediateDirectory)/src_octree$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/octree.cpp"

$(IntermediateDirectory)/src_octree$(PreprocessSuffix): src/octree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_octree$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/octree.cpp"

$(IntermediateDirectory)/src_object$(ObjectSuffix): src/object.cpp $(IntermediateDirectory)/src_object$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/object.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_object$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_object$(DependSuffix): src/object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_object$(ObjectSuffix) -MF$(IntermediateDirectory)/src_object$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/object.cpp"

$(IntermediateDirectory)/src_object$(PreprocessSuffix): src/object.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_object$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/object.cpp"

$(IntermediateDirectory)/src_sphere$(ObjectSuffix): src/sphere.cpp $(IntermediateDirectory)/src_sphere$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/Users/FOldenburg/dev/CGRayTracer/src/sphere.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_sphere$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_sphere$(DependSuffix): src/sphere.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_sphere$(ObjectSuffix) -MF$(IntermediateDirectory)/src_sphere$(DependSuffix) -MM "/Users/FOldenburg/dev/CGRayTracer/src/sphere.cpp"

$(IntermediateDirectory)/src_sphere$(PreprocessSuffix): src/sphere.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_sphere$(PreprocessSuffix) "/Users/FOldenburg/dev/CGRayTracer/src/sphere.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/tests_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tests_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tests_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_octree$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_octree$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_octree$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_triangle$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_triangle$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_triangle$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_cube$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_cube$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_cube$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_rect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_rect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_rect$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_triangle$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_triangle$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_triangle$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_vectormath$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_vectormath$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_vectormath$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_vector3d$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_vector3d$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_vector3d$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_cube$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_cube$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tests_test_cube$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_octree$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_octree$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_octree$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_object$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_object$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_object$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_sphere$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_sphere$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_sphere$(PreprocessSuffix)
	$(RM) $(OutputFile)


