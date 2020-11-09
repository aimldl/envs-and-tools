  set xlabel "x"
  set ylabel "y"
  set xrange [-1:1]
  set yrange [-1:1]
  set title "TEST"
  set xzeroaxis
  set yzeroaxis
  set output "/home/tk424/2008-2010.nns/nns-1.2/gnuplot_config_files/gnuplot_default_config.gp"
  set term postscript
  plot "/home/tk424/2008-2010.nns/nns-1.2/gnuplot_config_files/gnuplot_test_input.dat" using 1:2 with lines
  save "/home/tk424/2008-2010.nns/nns-1.2/gnuplot_config_files/gnuplot_test_output.ps"
