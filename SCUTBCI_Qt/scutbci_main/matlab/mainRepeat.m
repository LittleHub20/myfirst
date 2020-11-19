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
    [data target] = readData(trainfile);
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

methods = {'flda','svm','bayes','bard','bardgroup'};
numMethods = length(methods);

numSamples = numSamples/dfs;
% e.g. group = [1 1 1 2 2 2 3 3 3 4 4 4]' indicates that there are 4 group with 3 members in each
groupChannel = reshape(repmat(1:numChannels,numSamples,1),1,numChannels*numSamples);
groupSample = reshape(repmat([1:numSamples]',1,numChannels),1,numChannels*numSamples);

numPerms = 1;
numFolds = 10;
numTotal = numTrials;
numTest = floor(numTotal/numFolds);
numTrain = numTotal - numTest;
accuracyTrain = zeros(numPerms, numFolds, numMethods, numRepeats);
disp([num2str(numPerms) '-' num2str(numFolds) ' fold cross-validation']);
for perm = 1:numPerms
    disp(['perm ' num2str(perm)]);
    indexTotal = randperm(numTotal); %
    for fold = 1:numFolds
        disp(['fold ' num2str(fold)]);
        
        indexTest = indexTotal((fold-1)*numTest+1:fold*numTest);
        indexTrain = setdiff(indexTotal,indexTest);
        
        dataTest = cell(length(indexTest),1);
        dataTrain = cell(length(indexTrain),1);
        for i = 1:length(indexTest)
            dataTest{i} = dataAll{indexTest(i)};
        end
        
        for i = 1:length(indexTrain)
            dataTrain{i} = dataAll{indexTrain(i)};
        end
        
        targetTest = targetAll(indexTest);
        targetTrain = targetAll(indexTrain);
        
        featureTrain = [];
        labelTrain = zeros(numTrain*numChars, 1);
        for trial = 1:numTrain
            featureTrial = dataTrain{trial};
            featureAveraged = squeeze(mean(featureTrial, 2));
            featureTrain = cat(1, featureTrain, featureAveraged);
            labelTrain((trial-1)*numChars+targetTrain(trial)) = 1;
        end
        
        X = featureTrain;
        X = svmscale(X,[0 1],'models/range','s');
        Y = labelTrain;
        Y(find(Y==0)) = -1;
        
        disp('training models');
        
        for k = 1:numMethods
            disp([methods{k} ' ...']);
            switch(methods{k})
                case 'flda'
                    fisher = FLDA(Y, X);
                    model = fisher;
                case 'swlda'
                    [b,se,pval,inmodel,stats,nextstep,history] = stepwisefit(X,Y,'penter',0.10,'premove',0.15,'scale','on','display','off');
                    swlda.b = b;
                    swlda.b0 = stats.intercept;
                    model = swlda;
                case 'svm'
                    svmoption = ['-s 0 -t 0 -c 1 -g 0.001'];
                    svmmodel = svmtrain(Y,X,svmoption);
                    model = svmmodel;
                case 'ridge'
                    ridge = ridgereg(Y, X, 0.001);
                    model = ridge;
                case 'lasso'
                    lasso = lassoreg(Y, X, 0.001);
                    model = lasso;
                case 'lassogroup'
                    lassogroup = lassogroupreg(Y, X, groupChannel, 0.0001);
                    model = lassogroup;
                case 'bayes'
                    bayes = bayesreg(Y, X);
                    model = bayes;
                case 'bard'
                    bard = bardreg(Y, X);
                    model = bard;
                case 'bardgroup'
                    bardgroup = bardgroupreg(Y, X, groupChannel);
                    model = bardgroup;
                otherwise
                    disp('unknown method');
            end
        end
        
        disp('classifying');
        
        targetTrue = targetTest;
        targetPredicted = zeros(numMethods, numRepeats, numTest);
        for trial = 1:numTest
            featureTrial = dataTest{trial};
            for repeat = 1:numRepeats
                featureAveraged = squeeze(mean(featureTrial(:,1:repeat,:),2));
                
                X = featureAveraged;
                X = svmscale(X,[0 1],'models/range','r');
                Y = zeros(numChars,1);
                
                for k = 1:numMethods
                    switch(methods{k})
                        case 'flda'
                            Y_predict = X*fisher.b + fisher.b0;
                        case 'swlda'
                            Y_predict = X*swlda.b + swlda.b0;
                        case 'svm'
                            [predict_label,predict_accuracy,predict_decvalue] = svmpredict(Y,X, svmmodel);
                            Y_predict = svmmodel.Label(1)*predict_decvalue;
                            % Y_predict = predict_decvalue;
                        case 'ridge'
                            Y_predict = X*ridge.b + ridge.b0;
                        case 'lasso'
                            Y_predict = X*lasso.b + lasso.b0;
                        case 'lassogroup'
                            Y_predict = X*lassogroup.b + lassogroup.b0;
                        case 'bayes'
                            Y_predict = X*bayes.b + bayes.b0;
                        case 'bard'
                            Y_predict = X*bard.b + bard.b0;
                        case 'bardgroup'
                            Y_predict = X*bardgroup.b + bardgroup.b0;
                        otherwise
                            disp('unknown method');
                    end
                    
                    [dummy predictIndex] = max(Y_predict);
                    targetPredicted(k,repeat,trial) = predictIndex;
                end
            end
        end
        
        for i = 1:numMethods
            for j = 1:numRepeats
                accuracyTrain(perm,fold,i,j) = length(find(squeeze(targetPredicted(i,j,:)) == targetTrue))/numTest;
            end
        end
    end
end

%% visualize
figure;
plotstyle = {'b','k','r','b--','k--','r--','g','g--'};
hold on; grid on;
for k = 1:numMethods
    plot(squeeze(mean(mean(accuracyTrain(:,:,k,:),1),2))*100,plotstyle{k},'LineWidth',2);
    axis([1 numRepeats 0 100]);
    xlabel('Repeat (n)');
    ylabel('Accuracy (%)');
end
h = legend(methods{1},methods{2},methods{3},methods{4},methods{5});
set(h,'Location','SouthEast');
title(subject);
saveas(gcf, ['results/' subject '_cv_accuracy_repeat.fig']);
