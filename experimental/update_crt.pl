#!/usr/bin/env perl

# Usage: update_crt.pl [list of dlls]
# Use this script in the mingw-w64-crt directory
# Point it to a system DLL, eg
#     update_crt.pl /cygdrive/c/Windows/SysWOW64/msvcrt.dll
# Check lib32/msvcrt.def.new for new symbols
# Check lib32/msvcrt.def.old for removed symbols
# Likewise for lib64/msvcrt.def.new/old for 64bit dlls

use strict;
use warnings;
use File::Basename;

my $file_prog = '/usr/bin/file';
my $gendef_prog = '/usr/bin/gendef';

sub build_symtabl {
  my @ret = ();
  open(FH,"<",$_[0]) || return @ret; #No such file?
  while(<FH>){
    chomp;
    s/^\s+//; # strip white space from the beginning
    s/\s+$//; # strip white space from the end
    next if($_ =~ m/EXPORTS.*/);
    next if($_ =~ m/LIBRARY/);
    next if($_ =~ m/^;/);
    my @entry = split(/(\ |\t)/,$_);
    push(@ret,shift(@entry));
  }
  close(FH);
  return @ret;
}

sub build_newsymtabl {
  my @ret = ();
  #Fixme: Assume stdcall
  open(FH,"-|:crlf","$gendef_prog -a $_[0] -") || return @ret;
    while(<FH>){
    chomp;
    s/^\s+//; # strip white space from the beginning
    s/\s+$//; # strip white space from the end
    next if($_ =~ m/EXPORTS.*/);
    next if($_ =~ m/LIBRARY/);
    next if($_ =~ m/^;/);
    my @entry = split(/(\ |\t)/,$_);
    push(@ret,shift(@entry));
  }
  close(FH);
  return @ret;
}

sub process_dll {
  my @curr_symtable;
  my @new_symtable;
  my %args = @_;
  my $mode = '';

  chomp(my $fileret = `$file_prog $args{'dllname'}`);
  $mode = 'lib32' if($fileret =~ m/PE32\ executable/);
  $mode = 'lib64' if($fileret =~ m/PE32\+\ executable/);
  # Error out if unrecognized
  if(!$mode){
    printf "Error: Unknown format %s - %s\n", $args{'dllname'}, $fileret;
    return 1;
  }
  my $basedllname = basename($args{'dllname'});
  my @dll = split(/\./, $basedllname);
  pop(@dll);
  my $base = join('.', @dll);
  @curr_symtable = build_symtabl("$mode/$base.def");
  @new_symtable = build_newsymtabl($args{'dllname'});
  #sort by alphabets
  @curr_symtable = sort @curr_symtable;
  @new_symtable = sort @new_symtable;
  # Compare and dump
  if(!open(FH, ">", "$mode/$base.def.new")){
    print "Cannot open $mode/$base.def.new for writing\n";
  } else {
    LINE: foreach(@new_symtable){
      foreach my $compare (@curr_symtable){
        next LINE if ($_ eq $compare);
        next LINE if ($_ eq $compare.'@0');
      }
      print FH "$_\n";
    }
  }
  close(FH);
  unlink "$mode/$base.def.new" if( -z "$mode/$base.def.new");

  #Print removed symbols
  if(!open(FH, ">", "$mode/$base.def.old")){
    print "Cannot open $mode/$base.def.old for writing\n";
  } else {
    LINE: foreach(@curr_symtable){
      foreach my $compare (@new_symtable){
        next LINE if ($_ eq $compare);
        next LINE if ($_.'@0' eq $compare);
      }
      print FH "$_\n";
    }
  }
  close(FH);
  unlink "$mode/$base.def.old" if( -z "$mode/$base.def.old");
  return 0;
}

sub main{
  if(!scalar @ARGV){
    print "Usage: update_crt.pl [list of dlls]\n";
    print "Use this script in the mingw-w64-crt directory\n";
    print "Point it to a system DLL, eg\n";
    print "    update_crt.pl /cygdrive/c/Windows/SysWOW64/msvcrt.dll\n";
    print "Check lib32/msvcrt.def.new for new symbols\n";
    print "Check lib32/msvcrt.def.old for removed symbols\n";
    print "Likewise for lib64/msvcrt.def.new/old for 64bit dlls\n";
    print "\n";
  }

  if(! -e $file_prog) { printf "Error: file(1) is missing\n"; exit 1}
  foreach(@ARGV) {
    process_dll ("dllname" => $_) || exit 1
  }
  exit 0;
}

main();

