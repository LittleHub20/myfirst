function [output,state] = P300Speller_Round_Initialization_Asyn(param,state)

output = -1;

state.featureAccumulated = zeros(param.n_characters, param.n_features);
state.charRepeated = zeros(1, param.n_characters);
state.reset = 0;

output = 1;
