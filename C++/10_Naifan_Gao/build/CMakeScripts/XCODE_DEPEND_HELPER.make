# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.io.Debug:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Debug/libio.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Debug/libio.a


PostBuild.util.Debug:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Debug/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Debug/libutil.a


PostBuild.wrl.Debug:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Debug/libwrl.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Debug/libwrl.a


PostBuild.wrltest.Debug:
PostBuild.io.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Debug/wrltest
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Debug/wrltest
PostBuild.wrl.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Debug/wrltest
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Debug/wrltest:\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Debug/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Debug/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Debug/wrltest


PostBuild.WrlViewer1.Debug:
PostBuild.io.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Debug/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Debug/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.wrl.Debug: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Debug/WrlViewer1.app/Contents/MacOS/WrlViewer1
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Debug/WrlViewer1.app/Contents/MacOS/WrlViewer1:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Debug/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Debug/libwrl.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Debug/WrlViewer1.app/Contents/MacOS/WrlViewer1


PostBuild.io.Release:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Release/libio.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Release/libio.a


PostBuild.util.Release:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Release/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Release/libutil.a


PostBuild.wrl.Release:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Release/libwrl.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Release/libwrl.a


PostBuild.wrltest.Release:
PostBuild.io.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Release/wrltest
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Release/wrltest
PostBuild.wrl.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Release/wrltest
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Release/wrltest:\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Release/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Release/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/Release/wrltest


PostBuild.WrlViewer1.Release:
PostBuild.io.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Release/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Release/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.wrl.Release: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Release/WrlViewer1.app/Contents/MacOS/WrlViewer1
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Release/WrlViewer1.app/Contents/MacOS/WrlViewer1:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Release/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Release/libwrl.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/Release/WrlViewer1.app/Contents/MacOS/WrlViewer1


PostBuild.io.MinSizeRel:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/MinSizeRel/libio.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/MinSizeRel/libio.a


PostBuild.util.MinSizeRel:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/MinSizeRel/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/MinSizeRel/libutil.a


PostBuild.wrl.MinSizeRel:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a


PostBuild.wrltest.MinSizeRel:
PostBuild.io.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/MinSizeRel/wrltest
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/MinSizeRel/wrltest
PostBuild.wrl.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/MinSizeRel/wrltest
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/MinSizeRel/wrltest:\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/MinSizeRel/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/MinSizeRel/wrltest


PostBuild.WrlViewer1.MinSizeRel:
PostBuild.io.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/MinSizeRel/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/MinSizeRel/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.wrl.MinSizeRel: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/MinSizeRel/WrlViewer1.app/Contents/MacOS/WrlViewer1
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/MinSizeRel/WrlViewer1.app/Contents/MacOS/WrlViewer1:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/MinSizeRel/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/MinSizeRel/WrlViewer1.app/Contents/MacOS/WrlViewer1


PostBuild.io.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/RelWithDebInfo/libio.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/RelWithDebInfo/libio.a


PostBuild.util.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/RelWithDebInfo/libutil.a


PostBuild.wrl.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a:
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a


PostBuild.wrltest.RelWithDebInfo:
PostBuild.io.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/RelWithDebInfo/wrltest
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/RelWithDebInfo/wrltest
PostBuild.wrl.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/RelWithDebInfo/wrltest
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/RelWithDebInfo/wrltest:\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/RelWithDebInfo/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/test/RelWithDebInfo/wrltest


PostBuild.WrlViewer1.RelWithDebInfo:
PostBuild.io.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/RelWithDebInfo/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/RelWithDebInfo/WrlViewer1.app/Contents/MacOS/WrlViewer1
PostBuild.wrl.RelWithDebInfo: /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/RelWithDebInfo/WrlViewer1.app/Contents/MacOS/WrlViewer1
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/RelWithDebInfo/WrlViewer1.app/Contents/MacOS/WrlViewer1:\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/RelWithDebInfo/libio.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/viewer/RelWithDebInfo/WrlViewer1.app/Contents/MacOS/WrlViewer1




# For each target create a dummy ruleso the target does not have to exist
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Debug/libio.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/MinSizeRel/libio.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/RelWithDebInfo/libio.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/io/Release/libio.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Debug/libutil.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/MinSizeRel/libutil.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/util/Release/libutil.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Debug/libwrl.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a:
/Users/niko/Documents/Courses/C++/10_Naifan_Gao/build/wrl/Release/libwrl.a:
/Users/niko/Qt/5.10.0/clang_64/lib/QtCore.framework/QtCore:
/Users/niko/Qt/5.10.0/clang_64/lib/QtGui.framework/QtGui:
/Users/niko/Qt/5.10.0/clang_64/lib/QtSvg.framework/QtSvg:
/Users/niko/Qt/5.10.0/clang_64/lib/QtWidgets.framework/QtWidgets:
