for %%n in (0 1 2 3 4 5 6) do igfmake -new %%n0.cgf -gif temp -bmp 32 32 -1 %%n_0.bmp
for %%n in (0 1 2 3 4 5 6) do igfmake -new %%n1.cgf -gif temp -bmp 24 24 -1 %%n_1.bmp
for %%n in (0 1 2 3 4 5 6) do igfmake -new %%n2.cgf -gif temp -bmp 20 20 -1 %%n_2.bmp
..\scrpack3.exe -odata.dat list.txt