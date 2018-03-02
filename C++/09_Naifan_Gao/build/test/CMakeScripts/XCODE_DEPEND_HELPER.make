# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.ifsTest.Debug:
PostBuild.util.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest
PostBuild.ifs.Debug: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Debug/ifsTest


PostBuild.ifsTest.Release:
PostBuild.util.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest
PostBuild.ifs.Release: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/Release/ifsTest


PostBuild.ifsTest.MinSizeRel:
PostBuild.util.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest
PostBuild.ifs.MinSizeRel: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/MinSizeRel/ifsTest


PostBuild.ifsTest.RelWithDebInfo:
PostBuild.util.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest
PostBuild.ifs.RelWithDebInfo: /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest:\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a\
	/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a
	/bin/rm -f /Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/test/RelWithDebInfo/ifsTest




# For each target create a dummy ruleso the target does not have to exist
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Debug/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/MinSizeRel/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/RelWithDebInfo/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/ifs/Release/libifs.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Debug/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/MinSizeRel/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/RelWithDebInfo/libutil.a:
/Users/niko/Documents/Courses/C++/09_Naifan_Gao/build/util/Release/libutil.a:
