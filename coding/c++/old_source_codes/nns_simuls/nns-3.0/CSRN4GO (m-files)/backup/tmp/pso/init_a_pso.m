function pso=init_apso(pso),

% init_apso              Initialize associates in PSO (Particle Swarm Intelligence)
%
% See also init_pso

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%         pso.a(ssociate)           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
pso.associate.g_fitness      = pso.p.g_fitness;
pso.associate.A_fitness      = zeros( 1,pso.cfg.a.size );
for pp=1:pso.cfg.p.size,
    pso.a(pp).H_o    = rand( pso.cfg.N_h,pso.cfg.a.size );
    pso.a(pp).A_BEST = zeros( pso.cfg.a.d,pso.cfg.a.size );
    pso.a(pp).G_BEST = zeros( pso.cfg.a.d,1 );
    pso.a(pp).L_ID   = rand( pso.cfg.a.d,pso.cfg.N_s );
    pso.a(pp).V_ID   = rand( size(pso.a(pp).L_ID) );
end;