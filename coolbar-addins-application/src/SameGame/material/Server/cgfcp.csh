#! /bin/csh -f

rm -rf ./$argv[1]/0
rm -rf ./$argv[1]/1
rm -rf ./$argv[1]/2
rm -rf ./$argv[1]/3
rm -rf ./$argv[1]/4
rm -rf ./$argv[1]/5
rm -rf ./$argv[1]/6
cp -rf 0 1 2 3 4 5 6 ./$argv[1]/
cd $argv[1]/
cd 0 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../1 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../2 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../3 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../4 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../5 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 
cd ../6 ; rm -f 0.cgf 1.cgf 2.cgf ; ln -s *10.cgf 2.cgf ; ln -s *12.cgf 1.cgf ; ln -s *16.cgf 0.cgf 

