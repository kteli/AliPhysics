//This is the macro to include the FMD analysis in the train.
//It depends on two libraries: libFMDanalysis.so in AliRoot and 
//libPhysics.so in ROOT. It has been tested to work with the 
//example scripts in the ANALYSIS webpages.
// Author: Hans Hjersing Dalsgaard, hans.dalsgaard@cern,ch


AliFMDAnalysisTaskSE* AddTaskFMD() {

  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTaskESDFilter", "No analysis manager to connect to.");
    return NULL;
  }   
  
  
  AliFMDAnalysisTaskSE *taskfmd = new AliFMDAnalysisTaskSE("TaskFMD");
  mgr->AddTask(taskfmd);
  
  AliFMDAnaParameters* pars = AliFMDAnaParameters::Instance();
  pars->Init();
  pars->SetProcessPrimary(kFALSE);
  pars->SetProcessHits(kFALSE);
  pars->SetEnergy(AliFMDAnaParameters::k900);
  pars->SetCentralTriggerSelection(kTRUE);

  TString outputfile = AliAnalysisManager::GetCommonFileName();
  outputfile += Form(":%s",pars->GetDndetaAnalysisName());

  AliAnalysisDataContainer *cout_fmd = mgr->CreateContainer("BackgroundCorrected", TList::Class(), AliAnalysisManager::kOutputContainer,outputfile);                             
  mgr->ConnectInput(taskfmd, 0, mgr->GetCommonInputContainer());
  mgr->ConnectOutput(taskfmd, 1, cout_fmd);

  return taskfmd;
}
