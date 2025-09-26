#ifndef __CPU_PRED_BTB_MY_LP_HH__
#define __CPU_PRED_BTB_MY_LP_HH__

#include <array>
#include <queue>
#include <stack>
#include <utility> 
#include <vector>

#include "cpu/pred/btb/stream_struct.hh"
#include "cpu/pred/btb/timed_base_pred.hh"

namespace gem5
{

namespace branch_prediction
{

namespace btb_pred
{
  class MyLP : TimedBaseBTBPredictor
  {
    public:
      // parameters
      // loop table
      int loopTabEntryNum = 64;
      int loopTabAssoc    = 4;
      int setNum          = loopTabEntryNum / loopTabAssoc;
      int tagBits         = 20;
      int tripConfBits    = 3;
      int specConfBits    = 3;
      int cntBits         = 12;
      int ageBits         = 16;

      struct LoopTableEntry {
        uint32_t tag;
        uint32_t specCnt;
        uint32_t tripCnt;
        uint8_t  specConf;
        uint8_t  tripConf;
        uint32_t age;

        LoopTableEntry() : tag(0), specCnt(0), tripCnt(0), specConf(0), tripConf(0), age(0) {}
        LoopTableEntry(uint32_t theTag) : 
          tag(theTag), specCnt(0), tripCnt(0), specConf(0), tripConf(0), age(0) {}
      };

      MyLP(const Params& p);



      // override functions
      void tickStart() override;
      void tick() override;
      void putPCHistory(Addr startAddr, const boost::dynamic_bitset<> &history,
        std::vector<FullBTBPrediction> &stagePreds) override;
      std::shared_ptr<void> getPredictionMeta() override;
      void specUpdateHist(const boost::dynamic_bitset<> &history, FullBTBPrediction &pred) override;
      void recoverHist(const boost::dynamic_bitset<> &history, const FetchStream &entry,
        int shamt, bool cond_taken) override;
      void update(const FetchStream &entry) override;
      void commitBranch(const FetchStream &stream, const DynInstPtr &inst) override;

  }; // class MyLP


} // namespace btb_pred
} // namespace branch_prediction
} // namespace gem5

#endif // __CPU_PRED_BTB_MY_LP_HH__