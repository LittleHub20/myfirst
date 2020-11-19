function [output,result,state] = P300Speller_Round_Processing_Asyn(input,param,state)

output = -1;
result = 0;

event = input.event;
signalEpoch = input.epoch; % channels by samples
% if (state.roundIndex < 1)
%     save(['data/' num2str(event) '.dat'], 'signalEpoch');
% end

if (event > 0 && event <= param.n_characters)
    signalFiltered = filtfilt(param.hdfilter.numerator,1,signalEpoch(param.channelSelected,:)');
    % signalFiltered = filter(param.hdfilter,signalEpoch(param.channelSelected,:)');
    signalFiltered = signalFiltered(param.n_segment1+1:param.n_segment2,:);
    signalDownsampled = downsample(signalFiltered,param.dfs);
    for c = 1:param.n_channels
        signalNormalized(:,c) = zscore(signalDownsampled(:,c));
    end

    state.featureAccumulated(event,:) = state.featureAccumulated(event,:) + signalNormalized(:)';
    state.charRepeated(event) = state.charRepeated(event) + 1;
end

state.charIndex = state.charIndex + 1;
if (state.charIndex >= param.n_characters)
    state.charIndex = 0;
    state.roundIndex = state.roundIndex + 1;
    [output,result,state] = P300Speller_Round_Evaluate_Asyn(param,state);
else
    result = 0;
end
 
output = 1;