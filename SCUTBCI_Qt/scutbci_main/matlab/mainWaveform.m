clc
clear

subject = 'noise';
datapath = 'E:\eegdata\p300speller\';
datafile = [datapath 'p300speller_huangqiyun_20161125_1.cnt'];

fs = 250;
order = 20;
fstop1 = 0;    % First Stopband Frequency
fpass1 = 0.5;  % First Passband Frequency
fpass2 = 10;   % Second Passband Frequency
fstop2 = 11;   % Second Stopband Frequency
wstop1 = 1;    % First Stopband Weight
wpass  = 1;    % Passband Weight
wstop2 = 2;    % Second Stopband Weight
dens  = 20;     % Density Factor
b  = firpm(order, [0 fstop1 fpass1 fpass2 fstop2 fs/2]/(fs/2), [0 0 1 1 0 ...
           0], [wstop1 wpass wstop2], {dens});
Hd = dfilt.dffir(b);

reflen = 50; % 200 ms reference
t1 = 0.0; % second
t2 = 0.8; % second
t = 1000*(t1*fs+1:t2*fs)/fs; % ms
T = t - 1000*reflen/fs; % 200ms pre-stimulus signal base

[data,target,clab] = readData(datafile, Hd, reflen);

dataAll = data;
targetAll = target;
numTrials = length(dataAll);
[numChars, numRepeats, numSamples, numChannels] = size(dataAll{1});

signalTarget = [];
signalNontarget = [];
for i = 1:numTrials
    dataTrial = dataAll{i};
    signalTarget1 = reshape(dataTrial(targetAll(i),:,:,:),numRepeats,numSamples,numChannels);
    signalNontarget1 = reshape(dataTrial(setdiff([1:numChars],targetAll(i)),:,:,:), ...
        (numChars-1)*numRepeats,numSamples,numChannels);
    signalTarget = cat(1,signalTarget,signalTarget1);
    signalNontarget = cat(1,signalNontarget,signalNontarget1);
end

signalTarget = signalTarget(:,t1*fs+1:t2*fs,:);
signalNontarget = signalNontarget(:,t1*fs+1:t2*fs,:);
signalAvgTarget = squeeze(mean(signalTarget,1))';
signalStdTarget = squeeze(std(signalTarget,1))';
signalAvgNontarget = squeeze(mean(signalNontarget,1))';
signalStdNontarget = squeeze(std(signalNontarget,1))';

%% plot ERP image
mkdir(datafile(1:end-4))
for n = 1:numChannels
    gcf = figure('Visible','off');
    subplot(211);
    imagesc(squeeze(signalTarget(:,:,n)));
    % xlabel('Time');
    ylabel('Trial');
    title(clab{n});
    
    subplot(212);
    hold on;
    stdshaded(T, signalAvgTarget(n,:), signalStdTarget(n,:), 'm', 'r');
    % stdshaded(T, signalAvgNontarget(n,:), signalStdNontarget(n,:), 'k', [0.6,0.6,0.6]);
    plot(T, signalAvgTarget(n,:), 'm', 'LineWidth', 2);
    plot(T, signalAvgNontarget(n,:), 'k', 'LineWidth', 2);
    % plot(t, signalTarget(n,:)-signalNontarget(n,:), 'b', 'LineWidth', 2);
    axis tight;
    xlabel('Time');
    ylabel('Amplitude');
    
    imagefile = [datafile(1:end-4) '\' num2str(n) '.jpg'];
    saveas(gcf, imagefile);
    close(gcf);
end