function [output,result,state]=P300Speller_Round_Evaluate_Asyn(param,state)

output = -1;

feature_round_row = param.n_characters;
feature_round_column = param.n_features;

state.kr = state.kr + 1;
state.featureRounds(2:end,:,:) = state.featureRounds(1:end-1,:,:);
state.featureRounds(1,:,:) = state.featureAccumulated;

if (state.kr >= param.lmin)
    if(state.kr > param.lmax)
        state.kr = param.lmax;
    end

    feature_accumulate_rounds = zeros(feature_round_row,feature_round_column);
    feature_accumulate_rounds = squeeze(sum(state.featureRounds(1:state.kr,:,:), 1));

    for i = 1:param.n_characters
        if (state.charRepeated(i) > 0)
            feature_normalized(i,:) = feature_accumulate_rounds(i,:)/norm(feature_accumulate_rounds(i,:));
        else
            feature_normalized(i,:) = zeros(1,param.n_features);
        end
    end

    X = feature_normalized;
    % X = svmscale(X,[0 1],'models/range','r');
    Y = ones(size(X,1),1);
    switch(param.classifier)
        case 'flda'
            Y_predict = X*param.model.b + param.model.b0;
        case 'swlda'
            Y_predict = X*param.model.b;
        case 'svm'
            [dummy1,dummy2,predict_decvalue] = svmpredict(Y,X, param.model);
            Y_predict = param.model.Label(1)*predict_decvalue;
            % Y_predict = predict_decvalue;
        case 'ridge'
            Y_predict = X*param.model.b + param.model.b0;
        case 'lasso'
            Y_predict = X*param.model.b + param.model.b0;
        case 'lassogroup'
            Y_predict = X*param.model.b + param.model.b0;
        case 'bayes'
            Y_predict = X*param.model.b + param.model.b0;
        case 'bard'
            Y_predict = X*param.model.b + param.model.b0;
        case 'bardgroup'
            Y_predict = X*param.model.b + param.model.b0;
        otherwise
            disp('unknown method');
    end

    fscore_raw = Y_predict;
    [dummy,index] = max(fscore_raw);

    fscore_normalized = (fscore_raw-min(fscore_raw))/(max(fscore_raw)-min(fscore_raw));
    fscore_normalized = sort(fscore_normalized,'descend');
    fscore_delta = fscore_normalized(1) - fscore_normalized(2);
    state.fscoreDelta(state.trialIndex+1,state.kr) = fscore_delta;

    if (state.kr >= param.lmax)
        state.trialIndex = state.trialIndex + 1;
        state.roundUse(state.trialIndex) = state.kr;
        state.kr = 0;
        result = index;
    else
        if (fscore_delta >= param.nta)
            state.trialIndex = state.trialIndex + 1;
            state.roundUse(state.trialIndex) = state.kr;
            state.kr = 0;
            result = index;
        else
            result = 0;
        end
    end

else
    result = 0;
end

[output,state] = P300Speller_Round_Initialization_Asyn(param,state);
    
output = 1;
