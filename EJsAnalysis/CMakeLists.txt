# the name of the package:
atlas_subdir ( EJsAnalysis )

# declare the package's dependencies:
atlas_depends_on_subdirs ( PUBLIC
                                             xAODAnaHelpers )
					     
# component(s) of the package:
atlas_add_root_dictionary ( EJsAnalysisLib EJsAnalysisDictSource
					    ROOT_HEADERS EJsAnalysis/*.h Root/LinkDef.h
					    EXTERNAL_PACKAGES ROOT )

# add the library itself:
atlas_add_library ( EJsAnalysisLib
		              EJsAnalysis/*.h EJsAnalysis/*.ihh Root/*.cxx ${EJsAnalysisDictSource}
			      PUBLIC_HEADERS EJsAnalysis
			      INCLUDE_DIRS
			      LINK_LIBRARIES ${ROOT_LIBRARIES} xAODAnaHelpersLib
			      AsgAnalysisInterfaces EventLoop EventLoopAlgs
			      xAODBase xAODCore xAODEventInfo xAODJet
			      xAODRootAccess xAODTracking xAODTruth
			      JetInterface JetResolutionLib TrigDecisionToolLib TrigConfInterfaces
			      PRIVATE_LINK_LIBRARIES )

## find needed external(s):
### --> do we need this ???

# install files from the package:
atlas_install_python_modules ( python/*.py )
atlas_install_python_modules ( config/*py )
atlas_install_scripts ( scripts/*.py )
atlas_install_scripts ( scripts/*.sh )
atlas_install_data ( data/* )

#set ( CMAKE_CXX_STANDARD 11 )
### -->  do we want this ???
