#!/usr/bin/perl 
# NOTE: The above path is machine dependent!!!

#------------------------------------------------------------------------

#   * 
#

# version number
$version = "0.9   [07-Jan-2003]";


# machine dependent variables
#  (none at present)

# load packages
use Getopt::Long;   # allow the extended processing of command line options

# set default options

# get the command-line options
GetOptions("help", "version", "outfile=s" => \$outfile);

# print out version if requested, then quit
if ($opt_version) {
   print "\nVersion number: $version\n";
   exit 1;
}

# print out help if requested, then quit
if ($opt_help) {
   print_help();
   exit 1;
}

# check for file names; quit if none specified
if (!$ARGV[0]) { 
   print "You must specify at least one file to merge.\n"; 
   print "Usage: pdfmerge.pl [--help] [--version] [--outfile=filename] ";
   print "pdffile(s)\n";
   exit 1;
} else {
  $files = "";
#  foreach $nextfile <@ARGV> {
  foreach (@ARGV) {
     $files = $files . " " . $_;
  }
}

# check for output file; ask for one if none specified
if (!$outfile) {
  print "Output file = ";
  chop ($outfile = <STDIN>);
  print "\n";
} 

#       run ghostscript with appropriate options, capturing STDERR
print "Merging $files to $outfile . . . \n";
my $gs_result = `gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -sOutputFile=$outfile $files 2>&1`;
print "Merge is complete!\n";



#*************************************************************************
#*************************************************************************


# ====================================================================
# name: print_help
# This subroutine prints the help info.
# ====================================================================
sub print_help{        # print the help info
   print <<END;
   
 The script pdfmerge.pl merges any number of pdf or ps files 
  entered on the command line into a single file (with name given).
  It uses gs with the pdfwrite device option (that means version 6.0 or later).

 Usage: pdfmerge.pl [--help] [--version] [--outfile=filenname] pdffile(s)
  
 The only mandatory command-line arguments are the names of the files
  to be combined.  Wildcards are allowed (e.g. *.tex will process all
  of the TeX files.)
  
 The options are
   --help                print this help
   --version             version number
   --outfile=filename    combine pdf or files to filename
 
END
}


