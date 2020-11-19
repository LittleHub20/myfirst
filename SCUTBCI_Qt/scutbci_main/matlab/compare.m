clc
clear

datafile = 'data/compare.cnt';
[S,es,clab] = readcnt(datafile);
eventpos = es.pos;
eventtype = es.type;

count = 40;
epochs1 = cell(count,1);
epochs2 = cell(count,1);
index = 1;
for i = 1:count
    epoch = load(['data/' num2str(index) '.dat'], '-mat');
    epochs1{index} = epoch.signalEpoch';
    if (eventtype(index) >= 1 && eventtype(index) <= 40)
        epochs2{eventtype(index)} = S(eventpos(index)+(1:150),:);   
    end
    index = index + 1;
end

figure;
target = 15;
chanpos = [2 4 6:30 32:34 1 5]; % SynAmps 2
T = 1:150;
for n = 1:30
    subplot(7,5,chanpos(n));
    hold on;
    plot(T, epochs1{target}(:,n)/6.7444e+03, 'm', 'LineWidth', 2);
    plot(T, epochs2{target}(:,n), 'k', 'LineWidth', 2);
end

param.subject = 'noise';
param.classifier = 'bayes';
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

epoch = epochs1{1};
signalFiltered = epoch(:,param.channelSelected);
signalFiltered = filtfilt(param.hdfilter.numerator,1,signalFiltered);

signalFiltered = signalFiltered(param.n_segment1+1:param.n_segment2,:);
signalDownsampled = downsample(signalFiltered,param.dfs);
for c = 1:param.n_channels
    signalNormalized(:,c) = zscore(signalDownsampled(:,c));
end