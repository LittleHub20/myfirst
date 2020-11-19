function [feature, label] = extractFeature(data, target, channel, segment, dfs, hdfilter)

numTrials = length(data);

if (numTrials >= 1)
    [numChars,numRepeats,numSamples,numChannels] = size(data{1});
else
    disp('no data available');
    return;
end

numUsedChannels = length(channel);

if ~exist('dfs','var')
    dfs = 6;
end

n_segment1 = segment(1);
n_segment2 = segment(2);
numUsedSamples = ceil((n_segment2 - n_segment1)/dfs);
numFeatures = numUsedSamples*numUsedChannels;

feature = cell(numTrials, 1);
label = zeros(numTrials, 1);
for trial = 1:numTrials
    signalTrial = data{trial};
    featureTrial = zeros(numChars, numRepeats, numFeatures);
    for char = 1:numChars
        for repeat = 1:numRepeats
            signalEpoch = squeeze(signalTrial(char,repeat,:,:));
            if exist('hdfilter','var')
                signalFiltered = filtfilt(hdfilter.numerator,1,signalEpoch(:,channel));
            else
                signalFiltered = signalEpoch(:,channel);
            end
            signalFiltered = signalFiltered(n_segment1+1:n_segment2,:);
            signalDownsampled = downsample(signalFiltered,dfs);
            for c = 1:numUsedChannels
                signalNormalized(:,c) = zscore(signalDownsampled(:,c));
            end
            featureTrial(char, repeat, :) = signalNormalized(:);
        end
    end
    feature{trial} = featureTrial;
end
label = target;
