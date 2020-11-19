clc
clear

subject = 'noise';
datapath = 'e:\eegdata\p300speller\';
trainfiles = {
    [datapath 'p300speller_yutianyou_20171220_1.cnt'];
};

fs = 250;
order = 10;
fstop1 = 0;    % First Stopband Frequency
fpass1 = 0.5;  % First Passband Frequency
fpass2 = 20;   % Second Passband Frequency
fstop2 = 25;   % Second Stopband Frequency
wstop1 = 1;    % First Stopband Weight
wpass  = 1;    % Passband Weight
wstop2 = 2;    % Second Stopband Weight
dens  = 20;     % Density Factor
b  = firpm(order, [0 fstop1 fpass1 fpass2 fstop2 fs/2]/(fs/2), [0 0 1 1 0 ...
    0], [wstop1 wpass wstop2], {dens});
hdfilter = dfilt.dffir(b);

reflen = 0; % 200 ms reference
indexTrial = 1;
for ss = 1:length(trainfiles)
    trainfile = trainfiles{ss};
    [data,target] = readData(trainfile);
    for i = 1:length(data)
        dataRaw{indexTrial} = data{i};
        targetRaw(indexTrial,1) = target(i);
        indexTrial = indexTrial + 1;
    end
end

numTrials = length(dataRaw);
[numChars, numRepeats, numSamples, numChannels] = size(dataRaw{1});

channelSelected = [8:30];
numChannels = length(channelSelected);

dfs = 5;
segmentSelected = reflen+[25 125]; % 0-600 ms
numSamples = segmentSelected(2) - segmentSelected(1);

[dataAll, targetAll] = extractFeature(dataRaw, targetRaw, channelSelected, segmentSelected, dfs, hdfilter);

methods = {'flda','bayes'};
numMethods = length(methods);

numSamples = numSamples/dfs;
% e.g. group = [1 1 1 2 2 2 3 3 3 4 4 4]' indicates that there are 4 group with 3 members in each
groupChannel = reshape(repmat(1:numChannels,numSamples,1),1,numChannels*numSamples);
groupSample = reshape(repmat([1:numSamples]',1,numChannels),1,numChannels*numSamples);

featureTrain = [];
labelTrain = zeros(numTrials*numChars, 1);
for trial = 1:numTrials
    featureTrial = dataAll{trial};
    featureAveraged = squeeze(mean(featureTrial(:,1:numRepeats,:,:), 2));
    for i = 1:numChars
        featureNormalized(i,:) = featureAveraged(i,:)/norm(featureAveraged(i, :));
    end
    featureTrain = cat(1, featureTrain, featureNormalized);
    labelTrain((trial-1)*numChars+targetAll(trial)) = 1;
end

X = featureTrain;
% X = svmscale(X,[0 1],'models/range','s');
Y = labelTrain;
Y(find(Y==0)) = -1;

trained.fs = fs;
trained.dfs = dfs;
trained.numChars = numChars;
trained.numChannels = numChannels;
trained.channelSelected = channelSelected;
trained.timeStart = segmentSelected(1);
trained.timeStop = segmentSelected(2);
trained.freqStart = fpass1;
trained.freqStop = fpass2;
trained.coefA = 1;
trained.coefB = hdfilter.numerator;

disp('training models');
ws = zeros(size(X,2), numMethods);
for k = 1:numMethods
    disp([methods{k} ' ...']);
    modelfile = ['models/' subject '_p300_' methods{k} '_model'];
    switch(methods{k})
        case 'flda'
            fisher = FLDA(Y, X);
            model = fisher;
            ws(:,k) = model.b;
        case 'swlda'
            [b,se,pval,inmodel,stats,nextstep,history] = ...
                stepwisefit(X,Y,'penter',0.10,'premove',0.15,'scale','on','display','off');
            swlda.b = b;
            model = swlda;
            ws(:,k) = model.b;
        case 'svm'
            svmoption = ['-s 0 -t 0 -c 1 -g 0.001'];
            svmmodel = svmtrain(Y,X,svmoption);
            model = svmmodel;
            model.b = model.SVs' * model.sv_coef;
            model.b0 = 0;
            ws(:,k) = model.SVs' * model.sv_coef;
        case 'ridge'
            ridge = ridgereg(Y, X, 0.001);
            model = ridge;
            ws(:,k) = model.b;
        case 'lasso'
            lasso = lassoreg(Y, X, 0.001);
            model = lasso;
            ws(:,k) = model.b;
        case 'lassogroup'
            lassogroup = lassogroupreg(Y, X, groupChannel, 0.0001);
            model = lassogroup;
            ws(:,k) = model.b;
        case 'bayes'
            bayes = bayesreg(Y, X);
            model = bayes;
            ws(:,k) = model.b;
        case 'bard'
            bard = bardreg(Y, X);
            model = bard;
            ws(:,k) = model.b;
        case 'bardgroup'
            bardgroup = bardgroupreg(Y, X, groupChannel);
            model = bardgroup;
            ws(:,k) = model.b;
        otherwise
            disp('unknown method');
    end
    trained.model = model;
    trained.classifier = methods{k};
    saveTrained(trained, ['trained_' methods{k}]);
    save(modelfile,'model','hdfilter','channelSelected','segmentSelected');
end

figure;
chanlocs = readlocs('chanlocs30.locs');
for k = 1:numMethods
    w1 = ws(:,k);
    wgroup = reshape(w1, length(w1)/numChannels, numChannels);
    wtopo = mean(abs(wgroup), 1);
    
    subplot(2,3,k);
    topoplot(wtopo, chanlocs(channelSelected), 'maplimits', 'absmax', 'electrodes', 'on');
    title(methods{k});
end
