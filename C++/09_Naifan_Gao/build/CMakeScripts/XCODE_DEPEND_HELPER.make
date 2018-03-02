# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ifs.Debug:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a


PostBuild.util.Debug:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a


PostBuild.ifsTest.Debug:
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest
PostBuild.ifs.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest


PostBuild.IfsViewer2017.Debug:
PostBuild.ifs.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Debug/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Debug/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Debug/IfsViewer2017.app/Contents/MacOS/IfsViewer2017:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Debug/IfsViewer2017.app/Contents/MacOS/IfsViewer2017


PostBuild.ifs.Release:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a


PostBuild.util.Release:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a


PostBuild.ifsTest.Release:
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest
PostBuild.ifs.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest


PostBuild.IfsViewer2017.Release:
PostBuild.ifs.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Release/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Release/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Release/IfsViewer2017.app/Contents/MacOS/IfsViewer2017:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/Release/IfsViewer2017.app/Contents/MacOS/IfsViewer2017


PostBuild.ifs.MinSizeRel:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a


PostBuild.util.MinSizeRel:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a


PostBuild.ifsTest.MinSizeRel:
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest
PostBuild.ifs.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest


PostBuild.IfsViewer2017.MinSizeRel:
PostBuild.ifs.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/MinSizeRel/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/MinSizeRel/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/MinSizeRel/IfsViewer2017.app/Contents/MacOS/IfsViewer2017:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/MinSizeRel/IfsViewer2017.app/Contents/MacOS/IfsViewer2017


PostBuild.ifs.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a


PostBuild.util.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a


PostBuild.ifsTest.RelWithDebInfo:
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest
PostBuild.ifs.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest


PostBuild.IfsViewer2017.RelWithDebInfo:
PostBuild.ifs.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/RelWithDebInfo/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/RelWithDebInfo/IfsViewer2017.app/Contents/MacOS/IfsViewer2017
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/RelWithDebInfo/IfsViewer2017.app/Contents/MacOS/IfsViewer2017:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/viewer/RelWithDebInfo/IfsViewer2017.app/Contents/MacOS/IfsViewer2017




# For each target create a dummy ruleso the target does not have to exist
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a:
/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore:
/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui:
/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg:
/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets:
