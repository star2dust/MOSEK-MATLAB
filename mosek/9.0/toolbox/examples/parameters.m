%
%  Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.
%
%  File :      parameters.m
%
%  Purpose:    Demonstrates a very simple example about how to get/set
%              parameters with MOSEK Matlab Toolbox
%

function r = parameters()

fprintf('Test MOSEK parameter get/set functions\n\n');

% Get default parameter values
[r,resp]=mosekopt('param'); 
fprintf('Default value for parameter MSK_IPAR_LOG = %d\n', resp.param.MSK_IPAR_LOG);
    
% Set log level (integer parameter)
param.MSK_IPAR_LOG = 1;
% Select interior-point optimizer... (integer parameter)
param.MSK_IPAR_OPTIMIZER = 'MSK_OPTIMIZER_INTPNT';
% ... without basis identification (integer parameter)
param.MSK_IPAR_INTPNT_BASIS = 'MSK_BI_NEVER';
% Set relative gap tolerance (double parameter)
param.MSK_DPAR_INTPNT_CO_TOL_REL_GAP = 1.0e-7;

% Use in mosekopt
[r,resp] = mosekopt('minimize', [], param);
    
% Set incorrect value
param.MSK_IPAR_LOG = -1;

try
    % Perform the optimization, but it should fail because of wrong parameter
    [r,resp] = mosekopt('minimize', [] , param); 
catch 
    fprintf('The value -1 for parameter MSK_IPAR_LOG has been correctly detected as wrong!');
    r = 0;
    return 
end

fprintf('The value -1 for parameter MSK_IPAR_LOG has NOT been correctly detected as wrong!');
r = 1;

% Demonstrate information items after optimization
[~,res] = mosekopt('minimize info', []);

res.info.MSK_DINF_OPTIMIZER_TIME
res.info.MSK_IINF_INTPNT_ITER

end