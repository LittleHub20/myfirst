function [output,param,state] = P300Speller_Thread_Initialization_Asyn(input)

output = -1;

% param.classifier = 'svm';
param.classifier = 'bayes';

param.subject = 'noise';
param.fs = 250;
param.dfs = 5;
param.n_characters = 40;
param.n_epochlen = 150;

modelfile = ['models/' param.subject '_p300_' param.classifier '_model'];
modelstruct = load(modelfile);
param.model = modelstruct.model;
param.hdfilter = modelstruct.hdfilter;
param.channelSelected = modelstruct.channelSelected;
param.n_channels = length(param.channelSelected);
param.n_segment1 = modelstruct.segmentSelected(1);
param.n_segment2 = modelstruct.segmentSelected(2);
param.n_timepoints = ceil((param.n_segment2 - param.n_segment1)/param.dfs);
param.n_features = param.n_timepoints * param.n_channels;

%%%%%%%%%%%%%%%%%
param.lmin = 5;
param.lmax = 8;
param.nta = 0.2;

state.featureAccumulated = zeros(param.n_characters, param.n_features);
state.charRepeated = zeros(1, param.n_characters);
state.featureRounds = zeros(param.lmax, param.n_characters, param.n_features);
state.charIndex = 0;
state.roundIndex = 0;
state.trialIndex = 0;
state.fscoreDelta = [];
state.roundUse = [];
state.kr = 0;
state.reset = 0;

output=1;