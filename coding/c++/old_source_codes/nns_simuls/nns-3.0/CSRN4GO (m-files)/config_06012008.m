% Configuration file
% This m-file is designed to be called in function run_simulations

% opt_test
if ( opt_test == 1 ),
    mm_max=1;   nn_max=10;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 2 ),
    mm_max=1;   nn_max=100;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 3 ),
    mm_max=1;   nn_max=1000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 4 ),
    mm_max=1;   nn_max=10000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 5 ),
    mm_max=1;   nn_max=100000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 6 ),
    mm_max=10;  nn_max=100;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 7 ),
    mm_max=10;  nn_max=1000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 8 ),
    mm_max=10;  nn_max=10000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 9 ),
    mm_max=100;  nn_max=1000;
    oo_max=5;  ii_max=10;
elseif ( opt_test == 10 ),
    mm_max=50;  nn_max=100000;
    oo_max=5;   ii_max=2;
elseif ( opt_test == 11 ),
    mm_max=50;  nn_max=100000;
    oo_max=2;   ii_max=10;
elseif ( opt_test == 12 ),
    mm_max=300;  nn_max=100000;
    oo_max=20;  ii_max=10;
elseif ( opt_test == 13 ),
    mm_max=100;  nn_max=100000;
    oo_max=5;  ii_max=10;
elseif ( opt_test == 14 ),
    mm_max=100;  nn_max=100000;
    oo_max=2;  ii_max=10;
end;

% opt_pso
if ( opt_pso==1 ),
    pso_size=20; pso_w=0.9;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==2 ),
    pso_size=20; pso_w=0.8;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==3 ),
    pso_size=20; pso_w=0.7;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==4 ),
    pso_size=20; pso_w=0.6;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==5 ),
    pso_size=20; pso_w=0.5;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==6 ),
    pso_size=30; pso_w=0.9;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==7 ),
    pso_size=30; pso_w=0.8;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==8 ),
    pso_size=30; pso_w=0.7;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==9 ),
    pso_size=30; pso_w=0.6;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==10 ),
    pso_size=30; pso_w=0.5;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==11 ),
    pso_size=20; pso_w=0.9;
    pso_c1=0.5; pso_c2=0.5;
elseif ( opt_pso==12 ),
    pso_size=20; pso_w=0.9;
    pso_c1=1; pso_c2=1;
elseif ( opt_pso==13 ),
    pso_size=20; pso_w=0.9;
    pso_c1=3; pso_c2=3;
elseif ( opt_pso==14 ),
    pso_size=20; pso_w=0.9;
    pso_c1=4; pso_c2=4;
elseif ( opt_pso==15 ),
    pso_size=20; pso_w=0.9;
    pso_c1=5; pso_c2=5;
elseif ( opt_pso==16 ),
    pso_size=20; pso_w=0.8;
    pso_c1=0.5; pso_c2=0.5;
elseif ( opt_pso==17 ),
    pso_size=20; pso_w=0.8;
    pso_c1=1; pso_c2=1;
elseif ( opt_pso==18 ),
    pso_size=20; pso_w=0.8;
    pso_c1=2; pso_c2=2;
elseif ( opt_pso==19 ),
    pso_size=20; pso_w=0.8;
    pso_c1=3; pso_c2=3;
elseif ( opt_pso==20 ),
    pso_size=20; pso_w=0.8;
    pso_c1=4; pso_c2=4;
elseif ( opt_pso==21 ),
    pso_size=20; pso_w=0.8;
    pso_c1=5; pso_c2=5;
end;
