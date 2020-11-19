function [varargout] = readData(datasource, hdfilter, reflen)

if isstruct(datasource)
    S = datasource.S;
    eventStruct = datasource.eventStruct;
    clab = datasource.clab;
else
    [S,eventStruct,clab] = readcnt(datasource);
end

SEEG = S;

%% Regress out EOG
% SEOG = S(:,1:2);
% SEEG = S-SEOG*(SEOG'*SEOG)^(-1)*(SEOG'*S);

%% Adaptive filtering
% SEOG = S(:,1:2);
% M = 3; % order
% gamma = 0.99; % RLS forgetting factor
% P0 = eye(M);
% ha = adaptfilt.rls(M,gamma,P0);
% SEEG = S - filter(ha,SEOG(:,1),S);
% SEEG = SEEG - filter(ha,SEOG(:,2),S);

% Re-reference
% S_filtered = S - kron(mean(S,2), ones(1, size(S,2))); % CAR
if exist('hdfilter','var')
    % S_filtered = filter(hdfilter, SEEG);
    S_filtered = filtfilt(hdfilter.numerator,1,SEEG);
else
   S_filtered = S;
end

if exist('reflen','var')
    numRef = reflen;
else
    numRef = 0;
end

cue_pos = find(eventStruct.type>=41 & eventStruct.type<=80);
numTrials = length(cue_pos)-1; % The last character may not be complete.
numChars = length(unique(eventStruct.type(cue_pos(1)+1:cue_pos(2)-1)));
numResponse = 150;
numSamples = numRef + numResponse;
numRepeats = round((cue_pos(2)-cue_pos(1))/numChars);
numChannels = size(S, 2);

data = cell(numTrials, 1);
target = zeros(numTrials, 1);
for i = 1:numTrials
    
    repeat = zeros(1, numChars);
    signalTrial = zeros(numChars, numRepeats, numSamples, numChannels);
    for j = 1:numRepeats
        for k = cue_pos(i)+(j-1)*numChars+(1:numChars)
            event = eventStruct.type(k);
            if ( event > 0 && event <= numChars )
                repeat(event) = repeat(event) + 1;
                signalEpoch = S_filtered(eventStruct.pos(k)+(-numRef:numResponse-1),:);
                if (numRef >= 25)
                    signalDebased = signalEpoch - repmat(mean(signalEpoch(1:25,:)), size(signalEpoch,1), 1);
                else
                    signalDebased = signalEpoch;
                end
                signalTrial(event, repeat(event), :, :) = signalDebased;
            end
        end
    end
    
    data{i} = signalTrial;
    target(i) = eventStruct.type(cue_pos(i)) - numChars;
end

if nargout == 2
    varargout{1} = data;
    varargout{2} = target;
elseif nargout == 3
    varargout{1} = data;
    varargout{2} = target;
    varargout{3} = clab;
end