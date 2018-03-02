# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.test3.Debug:
PostBuild.io.Debug: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Debug/test3
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Debug/test3
PostBuild.wrl.Debug: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Debug/test3
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Debug/test3:\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/Debug/libio.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/Debug/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Debug/test3


PostBuild.test3.Release:
PostBuild.io.Release: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Release/test3
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Release/test3
PostBuild.wrl.Release: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Release/test3
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Release/test3:\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/Release/libio.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/Release/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/Release/test3


PostBuild.test3.MinSizeRel:
PostBuild.io.MinSizeRel: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/MinSizeRel/test3
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/MinSizeRel/test3
PostBuild.wrl.MinSizeRel: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/MinSizeRel/test3
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/MinSizeRel/test3:\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/MinSizeRel/libio.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/MinSizeRel/test3


PostBuild.test3.RelWithDebInfo:
PostBuild.io.RelWithDebInfo: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/RelWithDebInfo/test3
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/RelWithDebInfo/test3
PostBuild.wrl.RelWithDebInfo: /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/RelWithDebInfo/test3
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/RelWithDebInfo/test3:\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/RelWithDebInfo/libio.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/test/RelWithDebInfo/test3




# For each target create a dummy ruleso the target does not have to exist
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/Debug/libio.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/MinSizeRel/libio.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/RelWithDebInfo/libio.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/io/Release/libio.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/Debug/libutil.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/MinSizeRel/libutil.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/util/Release/libutil.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/Debug/libwrl.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/MinSizeRel/libwrl.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/RelWithDebInfo/libwrl.a:
/Users/niko/Documents/Courses/C++/12_Naifan_Gao/build/wrl/Release/libwrl.a:
