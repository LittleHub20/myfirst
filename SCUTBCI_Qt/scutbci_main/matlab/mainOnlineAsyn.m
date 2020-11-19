clc
clear

subject = 'noise';
datapath = 'F:\p300speller\';
trainfiles = {
    [datapath 'yutianyou_20151021_train_1.cnt'];
};

[S,event,clab] = readcnt(trainfiles{1});

input.subject = subject;
[output,param,state] = P300Speller_Thread_Initialization_Asyn(input);

cue_pos = find(event.type>=41 & event.type<=80);
totalNum = length(cue_pos) - 1;
numRepeats = round((cue_pos(2)-cue_pos(1))/param.n_characters);
errorNum=0;

for i = 1:totalNum
    targetSymbol = event.type(cue_pos(i)) - 40;
    
    for j = cue_pos(i)+1:cue_pos(i+1)-1
        input.code = event.type(j);
        input.epoch = S(event.pos(j):event.pos(j)+param.n_epochlen-1,:)';
        
        [output,result,state] = P300Speller_Round_Processing_Asyn(input,param,state);
        
        if (result >= 1 && result <= param.n_characters)
            disp(['Target: ' num2str(targetSymbol)  '  Estimated: ' num2str(result) '  Rounds: ' num2str(state.roundUse(state.trialIndex))]);
            if (targetSymbol ~= result)
                disp('=================> Wrong ');
                errorNum=errorNum+1;
            end
            break;
        end
    end
    
end

disp(['Error: ' num2str(errorNum) '  and Total :' num2str(totalNum)]);