# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.helloWorld.Debug:
/Users/niko/Documents/Courses/C++/Course_C/HelloWorld/Debug/helloWorld:
	/bin/rm -f /Users/niko/Documents/Courses/C++/Course_C/HelloWorld/Debug/helloWorld


PostBuild.helloWorld.Release:
/Users/niko/Documents/Courses/C++/Course_C/HelloWorld/Release/helloWorld:
	/bin/rm -f /Users/niko/Documents/Courses/C++/Course_C/HelloWorld/Release/helloWorld


PostBuild.helloWorld.MinSizeRel:
/Users/niko/Documents/Courses/C++/Course_C/HelloWorld/MinSizeRel/helloWorld:
	/bin/rm -f /Users/niko/Documents/Courses/C++/Course_C/HelloWorld/MinSizeRel/helloWorld


PostBuild.helloWorld.RelWithDebInfo:
/Users/niko/Documents/Courses/C++/Course_C/HelloWorld/RelWithDebInfo/helloWorld:
	/bin/rm -f /Users/niko/Documents/Courses/C++/Course_C/HelloWorld/RelWithDebInfo/helloWorld




# For each target create a dummy ruleso the target does not have to exist
