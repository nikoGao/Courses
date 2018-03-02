# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.calc5.Debug:
/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Debug/calc5:
	/bin/rm -f /Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Debug/calc5


PostBuild.calc5.Release:
/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Release/calc5:
	/bin/rm -f /Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/Release/calc5


PostBuild.calc5.MinSizeRel:
/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/MinSizeRel/calc5:
	/bin/rm -f /Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/MinSizeRel/calc5


PostBuild.calc5.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/RelWithDebInfo/calc5:
	/bin/rm -f /Users/niko/Documents/Courses/C++/05_Naifan_Gao/build/RelWithDebInfo/calc5




# For each target create a dummy ruleso the target does not have to exist
