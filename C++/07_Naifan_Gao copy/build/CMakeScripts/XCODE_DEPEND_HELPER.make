# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.calc7.Debug:
/Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/Debug/calc7:
	/bin/rm -f /Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/Debug/calc7


PostBuild.calc7.Release:
/Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/Release/calc7:
	/bin/rm -f /Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/Release/calc7


PostBuild.calc7.MinSizeRel:
/Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/MinSizeRel/calc7:
	/bin/rm -f /Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/MinSizeRel/calc7


PostBuild.calc7.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/RelWithDebInfo/calc7:
	/bin/rm -f /Users/niko/Documents/Courses/C++/07_Naifan_Gao/build/RelWithDebInfo/calc7




# For each target create a dummy ruleso the target does not have to exist
