function saveTrained(trained, filename)


model = trained.model;
model.w = model.b;
model.b = model.b0;
model = rmfield(model, 'b0');
saved.model = model;
modelfile = [filename '.model'];
struct2xml(saved, modelfile);

saved = [];
trained = rmfield(trained, 'model');
trained.modelfile = modelfile;
saved.trained = trained;
struct2xml(saved, [filename '.xml']);