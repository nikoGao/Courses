# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.QtCalc2.Debug:
/Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/Debug/QtCalc2.app/Contents/MacOS/QtCalc2:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/Debug/QtCalc2.app/Contents/MacOS/QtCalc2


PostBuild.QtCalc2.Release:
/Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/Release/QtCalc2.app/Contents/MacOS/QtCalc2:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/Release/QtCalc2.app/Contents/MacOS/QtCalc2


PostBuild.QtCalc2.MinSizeRel:
/Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/MinSizeRel/QtCalc2.app/Contents/MacOS/QtCalc2:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/MinSizeRel/QtCalc2.app/Contents/MacOS/QtCalc2


PostBuild.QtCalc2.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/RelWithDebInfo/QtCalc2.app/Contents/MacOS/QtCalc2:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/08_Gabriel_Taubin/QtCalc2/build/RelWithDebInfo/QtCalc2.app/Contents/MacOS/QtCalc2




# For each target create a dummy ruleso the target does not have to exist
/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore:
/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui:
/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg:
/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets:
