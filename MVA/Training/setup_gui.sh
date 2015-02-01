#!/bin/bash

rootsys=$ROOTSYS/tmva/test/

if [ -f TMVAGui.C ];
then
   unlink TMVAGui.C 
   ln -s $rootsys/TMVAGui.C TMVAGui.C
else
   ln -s $rootsys/TMVAGui.C TMVAGui.C
fi



if [ -f tmvaglob.C ];
then
   unlink tmvaglob.C
   ln -s  gui/tmvaglob.v1.C tmvaglob.C 					 #modified
   # ln -s $ROOTSYS/tmva/test/tmvaglob.C tmvaglob.C 	# original
else
	ln -s  gui/tmvaglob.v1.C tmvaglob.C  				#modified
	# ln -s $ROOTSYS/tmva/test/tmvaglob.C tmvaglob.C 	# original
fi



