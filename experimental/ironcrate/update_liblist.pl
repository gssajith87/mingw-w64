#!/usr/bin/env perl
use strict;
use warnings;

# dirs that libironcrate lives in, add them here
my @src_dir = qw( error except locale memory misc sort threads );

#flags for tests
my @test_link_flags = qw( CPPFLAGS CFLAGS LDFLAG LDADD );

die "Rerun in the ironcrate source dir" if(!-f 'error/_ic_errno.c');

foreach my $dir (@src_dir){
  opendir(my $dh, $dir) || die "Can't open $dir";
  my @c_files = grep { m/\.c$/ } readdir($dh);
  close($dh);

  open(my $fh, '>', "$dir/list.am") || die "Can't write fragment for $dir";
  printf $fh "libironcrate_a_SOURCES += \\\n", $dir;
  foreach my $file (@c_files){
    print $fh "$dir/$file";
  } continue {
    print $fh " \\" if \$file != \$c_files[-1]; #except last entry
    print $fh "\n";
  }
  close $fh;
}

my @test_list;
opendir(my $testsuite, "testsuite") || die "can't open testsuite dir";
my @tests = grep { !m/testlib/ && !m/^\./ } readdir($testsuite); #exclude testlib

closedir($testsuite);
foreach my $test(@tests){
  next if( !-d "testsuite/$test" );
  opendir(my $test_cases, "testsuite/$test") || die "can't open $test";
  foreach(grep { m/\.c$/ } readdir($test_cases)){
    push(@test_list, "testsuite/$test/$_");
  }
  closedir($test_cases);

  open(my $test_list_am, '>', 'testsuite/list.am') || die "Can't write fragment for testsuite";
  print $test_list_am "check_PROGRAMS += \\\n";
  foreach (@test_list){
    my $check_PROGRAMS = $_;
    $check_PROGRAMS =~ s/\.c$//;
    printf $test_list_am $check_PROGRAMS;
  } continue {
    print $test_list_am " \\" if \$_ != \$test_list[-1]; #except last entry
    print $test_list_am "\n";
  }
  print $test_list_am "\n";

  foreach my $flag (@test_link_flags){
    foreach(@test_list){
      my $name = $_;
      $name =~ s/\.c$//;
      $name =~ s/\//_/g;
      printf $test_list_am '%s_%s=$(test_%s)'."\n",$name,$flag,lc($flag);
    }
  }
  close($test_list_am);
}
