#ifndef __FUSION_P_H__
#define __FUSION_P_H__
#include "monty.h"
#include "mosektask_p.h"
#include "list"
#include "vector"
#include "unordered_map"
#include "fusion.h"
namespace mosek
{
namespace fusion
{
// mosek.fusion.BaseModel from file 'src/fusion/cxx/BaseModel_p.h'
// namespace mosek::fusion
struct p_BaseModel
{
  p_BaseModel(BaseModel * _pubthis);

  void _initialize( monty::rc_ptr<BaseModel> m);
  void _initialize( const std::string & name,
                    const std::string & licpath);

  virtual ~p_BaseModel() { /* std::cout << "~p_BaseModel()" << std::endl;*/  }

  static p_BaseModel * _get_impl(Model * _inst) { return _inst->_impl; }

  //----------------------

  bool synched;
  std::string taskname;

  monty::rc_ptr<SolutionStruct> sol_itr;
  monty::rc_ptr<SolutionStruct> sol_itg;
  monty::rc_ptr<SolutionStruct> sol_bas;

  //---------------------

  std::unique_ptr<Task> task;

  //---------------------
  void task_setLogHandler (const msghandler_t & handler);
  void task_setDataCallbackHandler (const datacbhandler_t & handler);
  void task_setCallbackHandler (const cbhandler_t & handler);

  int task_append_barvar(int size, int num);

  void task_var_name   (int index, const std::string & name);
  void task_con_name   (int index, const std::string & name);
  void task_cone_name  (int index, const std::string & name);
  void task_barvar_name(int index, const std::string & name);
  void task_objectivename(         const std::string & name);

  void task_format_var_names(const std::shared_ptr<monty::ndarray<int,1>> subj, const std::string & format,const std::shared_ptr<monty::ndarray<int,1>> dims, const std::shared_ptr<monty::ndarray<long long,1>> sp);
  void task_format_con_names(const std::shared_ptr<monty::ndarray<int,1>> subi, const std::string & format,const std::shared_ptr<monty::ndarray<int,1>> dims, const std::shared_ptr<monty::ndarray<long long,1>> sp);
  void task_format_cone_names(const std::shared_ptr<monty::ndarray<int,1>> subk, const std::string & format,const std::shared_ptr<monty::ndarray<int,1>> dims, const std::shared_ptr<monty::ndarray<long long,1>> sp);

  void task_break_solve();

  //--------------------------

  int task_numvar();
  int task_numcon();
  int task_numcone();
  int task_numbarvar();

  //--------------------------

  void task_put_param(const std::string & name, const std::string & value);
  void task_put_param(const std::string & name, int    value);
  void task_put_param(const std::string & name, double value);
  
  double    task_get_dinf (const std::string & name);
  int       task_get_iinf (const std::string & name);
  long long task_get_liinf(const std::string & name);
  
  //--------------------------

  void task_con_putboundlist_fr(const std::shared_ptr<monty::ndarray<int,1>> idxs);
  void task_con_putboundlist_lo(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_up(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_fx(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_con_putboundlist_ra(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & lb , 
                                const std::shared_ptr<monty::ndarray<double,1>> & ub );

  void task_var_putboundlist_fr(const std::shared_ptr<monty::ndarray<int,1>> idxs);
  void task_var_putboundlist_lo(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putboundlist_up(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putboundlist_fx(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & rhs);
  void task_var_putboundlist_ra(const std::shared_ptr<monty::ndarray<int,1>> idxs, const std::shared_ptr<monty::ndarray<double,1>> & lb , 
                                const std::shared_ptr<monty::ndarray<double,1>> & ub );
  
  void task_var_putintlist(const std::shared_ptr<monty::ndarray<int,1>> & idxs);
  void task_var_putcontlist(const std::shared_ptr<monty::ndarray<int,1>> & idxs); 
 
  //--------------------------

  void task_putbararowlist(const std::shared_ptr<monty::ndarray<int,1>>       subi,
                           const std::shared_ptr<monty::ndarray<long long,1>> ptr,
                           const std::shared_ptr<monty::ndarray<int,1>>       subj,
                           const std::shared_ptr<monty::ndarray<long long,1>> matidx);

  void task_putbaraijlist(const std::shared_ptr<monty::ndarray<int,1>> subi,
                          const std::shared_ptr<monty::ndarray<int,1>> subj,
                          std::shared_ptr<monty::ndarray<long long,1>> matidx);
  
  void task_putbarc(const std::shared_ptr<monty::ndarray<int,1>> subj,
                    const std::shared_ptr<monty::ndarray<int,1>> subl,
                    const std::shared_ptr<monty::ndarray<int,1>> subk,
                    const std::shared_ptr<monty::ndarray<double,1>> val);
  
  std::shared_ptr<monty::ndarray<long long,1>> task_appendsymmatlist (const std::shared_ptr<monty::ndarray<int,1>>       & dim, 
                                                                      const std::shared_ptr<monty::ndarray<long long,1>> & nz, 
                                                                      const std::shared_ptr<monty::ndarray<int,1>>       & subk, 
                                                                      const std::shared_ptr<monty::ndarray<int,1>>       & subl, 
                                                                      const std::shared_ptr<monty::ndarray<double,1>>    & val);
  int  task_barvar_dim(int j);
  void task_putbaraij (int i, int j, int k);
  void task_putbaraij (int i, int j, const std::shared_ptr<monty::ndarray<int,1>> & k);
  void task_putbarcj  (int j, int k);
  void task_putbarcj  (int j,        const std::shared_ptr<monty::ndarray<int,1>> & k);
  int  task_barvardim (int index);

  int task_append_var(int num);
  int task_append_con(int num);

  void task_append_zerocones (int numcone);
  void task_clear_cones   ( const std::shared_ptr<monty::ndarray<int,1>> & idxs );
  void task_put_zerocones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs );
  void task_put_quadcones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs );
  void task_put_rquadcones( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs );
  void task_put_pexpcones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs );
  void task_put_ppowcones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs, const std::shared_ptr<monty::ndarray<double,1>> & alpha );
  void task_put_dexpcones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs );
  void task_put_dpowcones ( const std::shared_ptr<monty::ndarray<int,1>> & idxs, int conesize, int numcone,  const std::shared_ptr<monty::ndarray<int,1>> & membs, const std::shared_ptr<monty::ndarray<double,1>> & alpha );

  void task_putarowlist(
    const std::shared_ptr<monty::ndarray<int,1>>       & idxs, 
    const std::shared_ptr<monty::ndarray<long long,1>> & ptrb, 
    const std::shared_ptr<monty::ndarray<int,1>>       & subj, 
    const std::shared_ptr<monty::ndarray<double,1>>    & cof);
  void task_putaijlist(
    const std::shared_ptr<monty::ndarray<int,1>>       & subi, 
    const std::shared_ptr<monty::ndarray<int,1>>       & subj, 
    const std::shared_ptr<monty::ndarray<double,1>>    & cof, 
    long long                           num);

  void task_setnumvar(int num);
  void task_cleanup(int oldnum, int oldnumcon, int oldnumcone, int oldnumbarvar);
  void task_solve();

  void task_putobjective( 
    bool                             maximize,
    const std::shared_ptr<monty::ndarray<int,1>>    & subj    ,
    const std::shared_ptr<monty::ndarray<double,1>> & cof     ,
    double                           cfix    );

  void task_putclist(   
    const std::shared_ptr<monty::ndarray<int,1>>    & subj,
    const std::shared_ptr<monty::ndarray<double,1>> & cof);


  void task_putobjectivename(const std::string & name);

  void task_write(const std::string & filename);
  void task_dump (const std::string & filename);

  MSKtask_t task_get();
  MSKtask_t __mosek_2fusion_2BaseModel__task_get();
  
  void dispose();

  void task_putxx_slice(SolutionType which, int first, int last, std::shared_ptr<monty::ndarray<double,1>> & xx);

  static void env_syeig (int n, std::shared_ptr<monty::ndarray<double,1>> & a, std::shared_ptr<monty::ndarray<double,1>> & w);
  static void env_potrf (int n, std::shared_ptr<monty::ndarray<double,1>> & a);                        
  static void env_syevd (int n, std::shared_ptr<monty::ndarray<double,1>> & a, std::shared_ptr<monty::ndarray<double,1>> & w);

  static void env_putlicensecode(std::shared_ptr<monty::ndarray<int,1>> code);
  static void env_putlicensepath(const std::string &licfile);
  static void env_putlicensewait(int wait);

  static std::string env_getversion();

  void convertSolutionStatus(MSKsoltypee soltype, p_SolutionStruct * sol, MSKsolstae status, MSKprostae prosta);


};

// End of file 'src/fusion/cxx/BaseModel_p.h'
struct p_Model : public ::mosek::fusion::p_BaseModel
{
Model * _pubthis;
static mosek::fusion::p_Model* _get_impl(mosek::fusion::Model * _inst){ return static_cast< mosek::fusion::p_Model* >(mosek::fusion::p_BaseModel::_get_impl(_inst)); }
static mosek::fusion::p_Model * _get_impl(mosek::fusion::Model::t _inst) { return _get_impl(_inst.get()); }
p_Model(Model * _pubthis);
virtual ~p_Model() { /* std::cout << "~p_Model" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::WorkStack > xs{};monty::rc_ptr< ::mosek::fusion::WorkStack > ws{};monty::rc_ptr< ::mosek::fusion::WorkStack > rs{};monty::rc_ptr< ::mosek::fusion::Utils::StringIntMap > con_map{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::ModelConstraint >,1 > > cons{};std::shared_ptr< monty::ndarray< int,1 > > natconmap_type{};std::shared_ptr< monty::ndarray< double,1 > > natconmap_ub{};std::shared_ptr< monty::ndarray< double,1 > > natconmap_lb{};std::shared_ptr< monty::ndarray< double,1 > > natconmap_efix{};std::shared_ptr< monty::ndarray< int,1 > > natconmap_idx{};std::shared_ptr< monty::ndarray< long long,1 > > natconmap_slackidx{};std::shared_ptr< monty::ndarray< int,1 > > natconmap_blockid{};monty::rc_ptr< ::mosek::fusion::LinkedBlocks > natconmap{};std::shared_ptr< monty::ndarray< bool,1 > > initsol_xx_flag{};std::shared_ptr< monty::ndarray< double,1 > > initsol_xx{};monty::rc_ptr< ::mosek::fusion::Utils::StringIntMap > var_map{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::ModelVariable >,1 > > barvars{};std::shared_ptr< monty::ndarray< int,1 > > natbarvarmap_ptr{};std::shared_ptr< monty::ndarray< int,1 > > natbarvarmap_num{};int natbarvarmap_nblock{};std::shared_ptr< monty::ndarray< int,1 > > natbarvar_dim{};std::shared_ptr< monty::ndarray< long long,1 > > natbarvar_ptr{};int natbarvar_numbarvarelm{};std::shared_ptr< monty::ndarray< int,1 > > natbarvar_j{};std::shared_ptr< monty::ndarray< int,1 > > natbarvar_i{};std::shared_ptr< monty::ndarray< int,1 > > natbarvar_idx{};std::shared_ptr< monty::ndarray< int,1 > > natvarmap_type{};std::shared_ptr< monty::ndarray< int,1 > > natconemap_dim{};monty::rc_ptr< ::mosek::fusion::LinkedBlocks > natconemap{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::ModelVariable >,1 > > vars{};int bfixidx{};std::shared_ptr< monty::ndarray< int,1 > > natvarmap_idx{};std::shared_ptr< monty::ndarray< int,1 > > natvarmap_blockid{};monty::rc_ptr< ::mosek::fusion::LinkedBlocks > natvarmap{};mosek::fusion::SolutionType solutionptr{};mosek::fusion::AccSolutionStatus acceptable_sol{};std::string model_name{};virtual void destroy();
static Model::t _new_Model(monty::rc_ptr< ::mosek::fusion::Model > _464);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _464);
static Model::t _new_Model(const std::string &  _469);
void _initialize(const std::string &  _469);
static Model::t _new_Model();
void _initialize();
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > __mosek_2fusion_2Model__formstConstr(monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _472,std::shared_ptr< monty::ndarray< int,1 > > _473,std::shared_ptr< monty::ndarray< int,1 > > _474) ;
virtual void connames(std::shared_ptr< monty::ndarray< int,1 > > _475,const std::string &  _476,std::shared_ptr< monty::ndarray< int,1 > > _477,std::shared_ptr< monty::ndarray< long long,1 > > _478) ;
virtual void varnames(std::shared_ptr< monty::ndarray< int,1 > > _479,const std::string &  _480,std::shared_ptr< monty::ndarray< int,1 > > _481,std::shared_ptr< monty::ndarray< long long,1 > > _482) ;
virtual void varname(int _483,const std::string &  _484) ;
virtual void natbarvarmap_get(int _485,std::shared_ptr< monty::ndarray< int,1 > > _486) ;
virtual void natbarvar_get(int _490,std::shared_ptr< monty::ndarray< long long,1 > > _491) ;
virtual int natbarvarmap_alloc(int _498,int _499) ;
virtual int natvarmap_alloc(int _517) ;
virtual int natconmap_alloc(int _527) ;
virtual int natconemap_alloc(int _537) ;
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _540) ;
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _546) ;
static  void putlicensewait(bool _552);
static  void putlicensepath(const std::string &  _553);
static  void putlicensecode(std::shared_ptr< monty::ndarray< int,1 > > _554);
virtual /* override */ void dispose() ;
virtual void nativeVarToStr(int _557,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _558) ;
virtual MSKtask_t __mosek_2fusion_2Model__getTask() ;
virtual void getConstraintValues(bool _559,std::shared_ptr< monty::ndarray< int,1 > > _560,std::shared_ptr< monty::ndarray< double,1 > > _561,int _562) ;
virtual void getVariableDuals(bool _570,std::shared_ptr< monty::ndarray< long long,1 > > _571,std::shared_ptr< monty::ndarray< double,1 > > _572,int _573) ;
virtual void getVariableValues(bool _579,std::shared_ptr< monty::ndarray< long long,1 > > _580,std::shared_ptr< monty::ndarray< double,1 > > _581,int _582) ;
virtual void setVariableValues(bool _588,std::shared_ptr< monty::ndarray< long long,1 > > _589,std::shared_ptr< monty::ndarray< double,1 > > _590) ;
virtual void flushNames() ;
virtual void writeTask(const std::string &  _600) ;
virtual long long getSolverLIntInfo(const std::string &  _601) ;
virtual int getSolverIntInfo(const std::string &  _602) ;
virtual double getSolverDoubleInfo(const std::string &  _603) ;
virtual void setCallbackHandler(mosek::cbhandler_t  _604) ;
virtual void setDataCallbackHandler(mosek::datacbhandler_t  _605) ;
virtual void setLogHandler(mosek::msghandler_t  _606) ;
virtual void setSolverParam(const std::string &  _607,double _608) ;
virtual void setSolverParam(const std::string &  _609,int _610) ;
virtual void setSolverParam(const std::string &  _611,const std::string &  _612) ;
virtual void breakSolver() ;
virtual void solve() ;
virtual void flushSolutions() ;
virtual void flush_initsol(mosek::fusion::SolutionType _613) ;
virtual mosek::fusion::SolutionStatus getDualSolutionStatus() ;
virtual mosek::fusion::ProblemStatus getProblemStatus() ;
virtual mosek::fusion::SolutionStatus getPrimalSolutionStatus() ;
virtual double dualObjValue() ;
virtual double primalObjValue() ;
virtual monty::rc_ptr< ::mosek::fusion::SolutionStruct > __mosek_2fusion_2Model__get_sol_cache(mosek::fusion::SolutionType _620,bool _621,bool _622) ;
virtual monty::rc_ptr< ::mosek::fusion::SolutionStruct > __mosek_2fusion_2Model__get_sol_cache(mosek::fusion::SolutionType _628,bool _629) ;
virtual void setSolution_xx(std::shared_ptr< monty::ndarray< int,1 > > _630,std::shared_ptr< monty::ndarray< double,1 > > _631) ;
virtual void ensure_initsol_xx() ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_bars(mosek::fusion::SolutionType _638) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_barx(mosek::fusion::SolutionType _639) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_y(mosek::fusion::SolutionType _640) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_xc(mosek::fusion::SolutionType _641) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_snx(mosek::fusion::SolutionType _642) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_suc(mosek::fusion::SolutionType _643) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_slc(mosek::fusion::SolutionType _644) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_sux(mosek::fusion::SolutionType _645) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_slx(mosek::fusion::SolutionType _646) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_yx(mosek::fusion::SolutionType _647) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > getSolution_xx(mosek::fusion::SolutionType _648) ;
virtual void selectedSolution(mosek::fusion::SolutionType _649) ;
virtual mosek::fusion::AccSolutionStatus getAcceptedSolutionStatus() ;
virtual void acceptedSolutionStatus(mosek::fusion::AccSolutionStatus _650) ;
virtual mosek::fusion::ProblemStatus getProblemStatus(mosek::fusion::SolutionType _651) ;
virtual mosek::fusion::SolutionStatus getDualSolutionStatus(mosek::fusion::SolutionType _653) ;
virtual mosek::fusion::SolutionStatus getPrimalSolutionStatus(mosek::fusion::SolutionType _654) ;
virtual mosek::fusion::SolutionStatus getSolutionStatus(mosek::fusion::SolutionType _655,bool _656) ;
virtual void update(std::shared_ptr< monty::ndarray< int,1 > > _659,monty::rc_ptr< ::mosek::fusion::Expression > _660) ;
virtual void update(std::shared_ptr< monty::ndarray< int,1 > > _693,monty::rc_ptr< ::mosek::fusion::Expression > _694,std::shared_ptr< monty::ndarray< int,1 > > _695,bool _696) ;
virtual void updateObjective(monty::rc_ptr< ::mosek::fusion::Expression > _726,monty::rc_ptr< ::mosek::fusion::Variable > _727) ;
virtual void objective_(const std::string &  _761,mosek::fusion::ObjectiveSense _762,monty::rc_ptr< ::mosek::fusion::Expression > _763) ;
virtual void objective(double _792) ;
virtual void objective(mosek::fusion::ObjectiveSense _793,double _794) ;
virtual void objective(mosek::fusion::ObjectiveSense _795,monty::rc_ptr< ::mosek::fusion::Expression > _796) ;
virtual void objective(const std::string &  _797,double _798) ;
virtual void objective(const std::string &  _799,mosek::fusion::ObjectiveSense _800,double _801) ;
virtual void objective(const std::string &  _802,mosek::fusion::ObjectiveSense _803,monty::rc_ptr< ::mosek::fusion::Expression > _804) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(monty::rc_ptr< ::mosek::fusion::Expression > _805,monty::rc_ptr< ::mosek::fusion::ConeDomain > _806) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(const std::string &  _807,monty::rc_ptr< ::mosek::fusion::Expression > _808,monty::rc_ptr< ::mosek::fusion::ConeDomain > _809) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(monty::rc_ptr< ::mosek::fusion::Expression > _810,monty::rc_ptr< ::mosek::fusion::RangeDomain > _811) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(const std::string &  _812,monty::rc_ptr< ::mosek::fusion::Expression > _813,monty::rc_ptr< ::mosek::fusion::RangeDomain > _814) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(monty::rc_ptr< ::mosek::fusion::Expression > _815,monty::rc_ptr< ::mosek::fusion::LinearDomain > _816) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(const std::string &  _817,monty::rc_ptr< ::mosek::fusion::Expression > _818,monty::rc_ptr< ::mosek::fusion::LinearDomain > _819) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(monty::rc_ptr< ::mosek::fusion::Expression > _820,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _821) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(const std::string &  _822,monty::rc_ptr< ::mosek::fusion::Expression > _823,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _824) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(monty::rc_ptr< ::mosek::fusion::Expression > _825,monty::rc_ptr< ::mosek::fusion::PSDDomain > _826) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint(const std::string &  _827,monty::rc_ptr< ::mosek::fusion::Expression > _828,monty::rc_ptr< ::mosek::fusion::PSDDomain > _829) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _830) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _831,int _832,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _833) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _834,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _835) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _836,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _837) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _838,int _839,int _840,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _841) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _842,int _843,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _844) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _845,std::shared_ptr< monty::ndarray< int,1 > > _846,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _847) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(monty::rc_ptr< ::mosek::fusion::PSDDomain > _848) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _849,int _850,monty::rc_ptr< ::mosek::fusion::PSDDomain > _851) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _852,monty::rc_ptr< ::mosek::fusion::PSDDomain > _853) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _854,monty::rc_ptr< ::mosek::fusion::PSDDomain > _855) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _856,int _857,int _858,monty::rc_ptr< ::mosek::fusion::PSDDomain > _859) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _860,int _861,monty::rc_ptr< ::mosek::fusion::PSDDomain > _862) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _863,std::shared_ptr< monty::ndarray< int,1 > > _864,monty::rc_ptr< ::mosek::fusion::PSDDomain > _865) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(monty::rc_ptr< ::mosek::fusion::ConeDomain > _866) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(monty::rc_ptr< ::mosek::fusion::RangeDomain > _867) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(monty::rc_ptr< ::mosek::fusion::LinearDomain > _868) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(std::shared_ptr< monty::ndarray< int,1 > > _869,monty::rc_ptr< ::mosek::fusion::ConeDomain > _870) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(std::shared_ptr< monty::ndarray< int,1 > > _871,monty::rc_ptr< ::mosek::fusion::RangeDomain > _872) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(std::shared_ptr< monty::ndarray< int,1 > > _873,monty::rc_ptr< ::mosek::fusion::LinearDomain > _874) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(std::shared_ptr< monty::ndarray< int,1 > > _875) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _876,monty::rc_ptr< ::mosek::fusion::ConeDomain > _877) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _878,monty::rc_ptr< ::mosek::fusion::RangeDomain > _879) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _880,monty::rc_ptr< ::mosek::fusion::LinearDomain > _881) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(int _882) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable() ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _883,monty::rc_ptr< ::mosek::fusion::ConeDomain > _884) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _885,monty::rc_ptr< ::mosek::fusion::RangeDomain > _886) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _887,monty::rc_ptr< ::mosek::fusion::LinearDomain > _888) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _889,std::shared_ptr< monty::ndarray< int,1 > > _890,monty::rc_ptr< ::mosek::fusion::ConeDomain > _891) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _892,std::shared_ptr< monty::ndarray< int,1 > > _893,monty::rc_ptr< ::mosek::fusion::RangeDomain > _894) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _895,std::shared_ptr< monty::ndarray< int,1 > > _896,monty::rc_ptr< ::mosek::fusion::LinearDomain > _897) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _898,std::shared_ptr< monty::ndarray< int,1 > > _899) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _900,int _901,monty::rc_ptr< ::mosek::fusion::ConeDomain > _902) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _903,int _904,monty::rc_ptr< ::mosek::fusion::RangeDomain > _905) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _906,int _907,monty::rc_ptr< ::mosek::fusion::LinearDomain > _908) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _909,int _910) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable(const std::string &  _911) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__ranged_variable(const std::string &  _912,std::shared_ptr< monty::ndarray< int,1 > > _913,monty::rc_ptr< ::mosek::fusion::RangeDomain > _914) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable_(const std::string &  _935,std::shared_ptr< monty::ndarray< int,1 > > _936,monty::rc_ptr< ::mosek::fusion::ConeDomain > _937) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable_(const std::string &  _965,std::shared_ptr< monty::ndarray< int,1 > > _966,monty::rc_ptr< ::mosek::fusion::LinearDomain > _967) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__variable_(const std::string &  _1009,std::shared_ptr< monty::ndarray< int,1 > > _1010,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _1011) ;
virtual monty::rc_ptr< ::mosek::fusion::SymmetricVariable > __mosek_2fusion_2Model__variable_(const std::string &  _1033,std::shared_ptr< monty::ndarray< int,1 > > _1034,monty::rc_ptr< ::mosek::fusion::PSDDomain > _1035) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint_(const std::string &  _1050,monty::rc_ptr< ::mosek::fusion::Expression > _1051,monty::rc_ptr< ::mosek::fusion::RangeDomain > _1052) ;
virtual void update_bfix(std::shared_ptr< monty::ndarray< int,1 > > _1092,std::shared_ptr< monty::ndarray< double,1 > > _1093) ;
virtual void putarows(std::shared_ptr< monty::ndarray< int,1 > > _1095,monty::rc_ptr< ::mosek::fusion::WorkStack > _1096,int _1097,int _1098,int _1099,int _1100,int _1101) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint_(const std::string &  _1138,monty::rc_ptr< ::mosek::fusion::Expression > _1139,monty::rc_ptr< ::mosek::fusion::PSDDomain > _1140) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint_(const std::string &  _1206,monty::rc_ptr< ::mosek::fusion::Expression > _1207,monty::rc_ptr< ::mosek::fusion::LinPSDDomain > _1208) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint_(const std::string &  _1259,monty::rc_ptr< ::mosek::fusion::Expression > _1260,monty::rc_ptr< ::mosek::fusion::ConeDomain > _1261) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__constraint_(const std::string &  _1311,monty::rc_ptr< ::mosek::fusion::Expression > _1312,monty::rc_ptr< ::mosek::fusion::LinearDomain > _1313) ;
static  std::string getVersion();
virtual bool hasConstraint(const std::string &  _1360) ;
virtual bool hasVariable(const std::string &  _1361) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__getConstraint(int _1362) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Model__getConstraint(const std::string &  _1363) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__getVariable(int _1364) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Model__getVariable(const std::string &  _1365) ;
virtual std::string getName() ;
virtual monty::rc_ptr< ::mosek::fusion::Model > __mosek_2fusion_2Model__clone() ;
}; // struct Model;

// mosek.fusion.Debug from file 'src/fusion/cxx/Debug_p.h'
// namespace mosek::fusion
struct p_Debug
{
  Debug * _pubthis;

  p_Debug(Debug * _pubthis) : _pubthis(_pubthis) {}

  static Debug::t o ()                 { return monty::rc_ptr<Debug>(new Debug()); }
  Debug::t p (const std::string & val) { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (      int val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (long long val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (   double val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t p (     bool val)           { std::cout << val; return Debug::t(_pubthis); }
  Debug::t lf()                        { std::cout << std::endl; return Debug::t(_pubthis); }

  static p_Debug * _get_impl(Debug * _inst) { return _inst->ptr; }

  template<typename T>
  Debug::t p(const std::shared_ptr<monty::ndarray<T,1>> & val)
  {
    if (val->size() > 0)
    {
      std::cout << (*val)[0];
      for (int i = 1; i < val->size(); ++i)
        std::cout << "," << (*val)[i];
    }
    return Debug::t(_pubthis);
  }

  Debug::t __mosek_2fusion_2Debug__p (const std::string & val) { std::cout << val; return Debug::t(_pubthis); }

  template<class C>
  Debug::t __mosek_2fusion_2Debug__p (C val) { std::cout << val; return Debug::t(_pubthis); }
  Debug::t __mosek_2fusion_2Debug__lf()      { std::cout << std::endl; return Debug::t(_pubthis); }
  
};
// End of file 'src/fusion/cxx/Debug_p.h'
struct p_Sort
{
Sort * _pubthis;
static mosek::fusion::p_Sort* _get_impl(mosek::fusion::Sort * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Sort * _get_impl(mosek::fusion::Sort::t _inst) { return _get_impl(_inst.get()); }
p_Sort(Sort * _pubthis);
virtual ~p_Sort() { /* std::cout << "~p_Sort" << std::endl;*/ };
virtual void destroy();
static  void argTransposeSort(std::shared_ptr< monty::ndarray< long long,1 > > _151,std::shared_ptr< monty::ndarray< long long,1 > > _152,int _153,int _154,int _155,std::shared_ptr< monty::ndarray< long long,1 > > _156);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _164,std::shared_ptr< monty::ndarray< long long,1 > > _165);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _166,std::shared_ptr< monty::ndarray< int,1 > > _167);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _168,std::shared_ptr< monty::ndarray< long long,1 > > _169,std::shared_ptr< monty::ndarray< long long,1 > > _170);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _171,std::shared_ptr< monty::ndarray< int,1 > > _172,std::shared_ptr< monty::ndarray< int,1 > > _173);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _174,std::shared_ptr< monty::ndarray< long long,1 > > _175,long long _176,long long _177);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _178,std::shared_ptr< monty::ndarray< int,1 > > _179,long long _180,long long _181);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _182,std::shared_ptr< monty::ndarray< long long,1 > > _183,std::shared_ptr< monty::ndarray< long long,1 > > _184,long long _185,long long _186);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _187,std::shared_ptr< monty::ndarray< int,1 > > _188,std::shared_ptr< monty::ndarray< int,1 > > _189,long long _190,long long _191);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _192,std::shared_ptr< monty::ndarray< long long,1 > > _193,long long _194,long long _195,bool _196);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _199,std::shared_ptr< monty::ndarray< int,1 > > _200,long long _201,long long _202,bool _203);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _206,std::shared_ptr< monty::ndarray< long long,1 > > _207,std::shared_ptr< monty::ndarray< long long,1 > > _208,long long _209,long long _210,bool _211);
static  void argsort(std::shared_ptr< monty::ndarray< long long,1 > > _214,std::shared_ptr< monty::ndarray< int,1 > > _215,std::shared_ptr< monty::ndarray< int,1 > > _216,long long _217,long long _218,bool _219);
static  void argbucketsort(std::shared_ptr< monty::ndarray< long long,1 > > _222,std::shared_ptr< monty::ndarray< long long,1 > > _223,long long _224,long long _225,long long _226,long long _227);
static  void argbucketsort(std::shared_ptr< monty::ndarray< long long,1 > > _228,std::shared_ptr< monty::ndarray< int,1 > > _229,long long _230,long long _231,int _232,int _233);
static  void getminmax(std::shared_ptr< monty::ndarray< long long,1 > > _234,std::shared_ptr< monty::ndarray< long long,1 > > _235,std::shared_ptr< monty::ndarray< long long,1 > > _236,long long _237,long long _238,std::shared_ptr< monty::ndarray< long long,1 > > _239);
static  void getminmax(std::shared_ptr< monty::ndarray< long long,1 > > _242,std::shared_ptr< monty::ndarray< int,1 > > _243,std::shared_ptr< monty::ndarray< int,1 > > _244,long long _245,long long _246,std::shared_ptr< monty::ndarray< int,1 > > _247);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _250,std::shared_ptr< monty::ndarray< long long,1 > > _251,long long _252,long long _253,bool _254);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _256,std::shared_ptr< monty::ndarray< int,1 > > _257,long long _258,long long _259,bool _260);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _262,std::shared_ptr< monty::ndarray< long long,1 > > _263,std::shared_ptr< monty::ndarray< long long,1 > > _264,long long _265,long long _266,bool _267);
static  bool issorted(std::shared_ptr< monty::ndarray< long long,1 > > _269,std::shared_ptr< monty::ndarray< int,1 > > _270,std::shared_ptr< monty::ndarray< int,1 > > _271,long long _272,long long _273,bool _274);
}; // struct Sort;

struct p_IndexCounter
{
IndexCounter * _pubthis;
static mosek::fusion::p_IndexCounter* _get_impl(mosek::fusion::IndexCounter * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_IndexCounter * _get_impl(mosek::fusion::IndexCounter::t _inst) { return _get_impl(_inst.get()); }
p_IndexCounter(IndexCounter * _pubthis);
virtual ~p_IndexCounter() { /* std::cout << "~p_IndexCounter" << std::endl;*/ };
long long start{};std::shared_ptr< monty::ndarray< int,1 > > dims{};std::shared_ptr< monty::ndarray< long long,1 > > strides{};std::shared_ptr< monty::ndarray< long long,1 > > st{};std::shared_ptr< monty::ndarray< int,1 > > ii{};int n{};virtual void destroy();
static IndexCounter::t _new_IndexCounter(std::shared_ptr< monty::ndarray< int,1 > > _276);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _276);
static IndexCounter::t _new_IndexCounter(long long _278,std::shared_ptr< monty::ndarray< int,1 > > _279,std::shared_ptr< monty::ndarray< int,1 > > _280);
void _initialize(long long _278,std::shared_ptr< monty::ndarray< int,1 > > _279,std::shared_ptr< monty::ndarray< int,1 > > _280);
static IndexCounter::t _new_IndexCounter(long long _283,std::shared_ptr< monty::ndarray< int,1 > > _284,std::shared_ptr< monty::ndarray< long long,1 > > _285);
void _initialize(long long _283,std::shared_ptr< monty::ndarray< int,1 > > _284,std::shared_ptr< monty::ndarray< long long,1 > > _285);
virtual bool atEnd() ;
virtual std::shared_ptr< monty::ndarray< int,1 > > getIndex() ;
virtual long long next() ;
virtual long long get() ;
virtual void inc() ;
virtual void reset() ;
}; // struct IndexCounter;

struct p_CommonTools
{
CommonTools * _pubthis;
static mosek::fusion::p_CommonTools* _get_impl(mosek::fusion::CommonTools * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_CommonTools * _get_impl(mosek::fusion::CommonTools::t _inst) { return _get_impl(_inst.get()); }
p_CommonTools(CommonTools * _pubthis);
virtual ~p_CommonTools() { /* std::cout << "~p_CommonTools" << std::endl;*/ };
virtual void destroy();
static  std::shared_ptr< monty::ndarray< long long,1 > > resize(std::shared_ptr< monty::ndarray< long long,1 > > _291,int _292);
static  std::shared_ptr< monty::ndarray< int,1 > > resize(std::shared_ptr< monty::ndarray< int,1 > > _294,int _295);
static  std::shared_ptr< monty::ndarray< double,1 > > resize(std::shared_ptr< monty::ndarray< double,1 > > _297,int _298);
static  int binarySearch(std::shared_ptr< monty::ndarray< int,1 > > _300,int _301);
static  int binarySearch(std::shared_ptr< monty::ndarray< long long,1 > > _305,long long _306);
static  int binarySearchR(std::shared_ptr< monty::ndarray< long long,1 > > _308,long long _309);
static  int binarySearchL(std::shared_ptr< monty::ndarray< long long,1 > > _313,long long _314);
static  void ndIncr(std::shared_ptr< monty::ndarray< int,1 > > _318,std::shared_ptr< monty::ndarray< int,1 > > _319,std::shared_ptr< monty::ndarray< int,1 > > _320);
static  void transposeTriplets(std::shared_ptr< monty::ndarray< int,1 > > _322,std::shared_ptr< monty::ndarray< int,1 > > _323,std::shared_ptr< monty::ndarray< double,1 > > _324,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< long long,1 > >,1 > > _325,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< long long,1 > >,1 > > _326,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _327,long long _328,int _329,int _330);
static  void transposeTriplets(std::shared_ptr< monty::ndarray< int,1 > > _343,std::shared_ptr< monty::ndarray< int,1 > > _344,std::shared_ptr< monty::ndarray< double,1 > > _345,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _346,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _347,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _348,long long _349,int _350,int _351);
static  void tripletSort(std::shared_ptr< monty::ndarray< int,1 > > _364,std::shared_ptr< monty::ndarray< int,1 > > _365,std::shared_ptr< monty::ndarray< double,1 > > _366,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _367,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< int,1 > >,1 > > _368,std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< double,1 > >,1 > > _369,long long _370,int _371,int _372);
static  void argMSort(std::shared_ptr< monty::ndarray< int,1 > > _398,std::shared_ptr< monty::ndarray< int,1 > > _399);
static  void mergeInto(std::shared_ptr< monty::ndarray< int,1 > > _404,std::shared_ptr< monty::ndarray< int,1 > > _405,std::shared_ptr< monty::ndarray< int,1 > > _406,int _407,int _408,int _409);
static  void argQsort(std::shared_ptr< monty::ndarray< long long,1 > > _415,std::shared_ptr< monty::ndarray< long long,1 > > _416,std::shared_ptr< monty::ndarray< long long,1 > > _417,long long _418,long long _419);
static  void argQsort(std::shared_ptr< monty::ndarray< long long,1 > > _420,std::shared_ptr< monty::ndarray< int,1 > > _421,std::shared_ptr< monty::ndarray< int,1 > > _422,long long _423,long long _424);
}; // struct CommonTools;

struct p_SolutionStruct
{
SolutionStruct * _pubthis;
static mosek::fusion::p_SolutionStruct* _get_impl(mosek::fusion::SolutionStruct * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SolutionStruct * _get_impl(mosek::fusion::SolutionStruct::t _inst) { return _get_impl(_inst.get()); }
p_SolutionStruct(SolutionStruct * _pubthis);
virtual ~p_SolutionStruct() { /* std::cout << "~p_SolutionStruct" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > yx{};std::shared_ptr< monty::ndarray< double,1 > > snx{};std::shared_ptr< monty::ndarray< double,1 > > sux{};std::shared_ptr< monty::ndarray< double,1 > > slx{};std::shared_ptr< monty::ndarray< double,1 > > bars{};std::shared_ptr< monty::ndarray< double,1 > > barx{};std::shared_ptr< monty::ndarray< double,1 > > y{};std::shared_ptr< monty::ndarray< double,1 > > suc{};std::shared_ptr< monty::ndarray< double,1 > > slc{};std::shared_ptr< monty::ndarray< double,1 > > xx{};std::shared_ptr< monty::ndarray< double,1 > > xc{};double dobj{};double pobj{};mosek::fusion::ProblemStatus probstatus{};mosek::fusion::SolutionStatus dstatus{};mosek::fusion::SolutionStatus pstatus{};int sol_numbarvar{};int sol_numcone{};int sol_numvar{};int sol_numcon{};virtual void destroy();
static SolutionStruct::t _new_SolutionStruct(int _425,int _426,int _427,int _428);
void _initialize(int _425,int _426,int _427,int _428);
static SolutionStruct::t _new_SolutionStruct(monty::rc_ptr< ::mosek::fusion::SolutionStruct > _429);
void _initialize(monty::rc_ptr< ::mosek::fusion::SolutionStruct > _429);
virtual monty::rc_ptr< ::mosek::fusion::SolutionStruct > __mosek_2fusion_2SolutionStruct__clone() ;
virtual void resize(int _430,int _431,int _432,int _433) ;
virtual bool isDualAcceptable(mosek::fusion::AccSolutionStatus _453) ;
virtual bool isPrimalAcceptable(mosek::fusion::AccSolutionStatus _454) ;
virtual bool isAcceptable(mosek::fusion::SolutionStatus _455,mosek::fusion::AccSolutionStatus _456) ;
}; // struct SolutionStruct;

struct p_ConNZStruct
{
ConNZStruct * _pubthis;
static mosek::fusion::p_ConNZStruct* _get_impl(mosek::fusion::ConNZStruct * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_ConNZStruct * _get_impl(mosek::fusion::ConNZStruct::t _inst) { return _get_impl(_inst.get()); }
p_ConNZStruct(ConNZStruct * _pubthis);
virtual ~p_ConNZStruct() { /* std::cout << "~p_ConNZStruct" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > barmidx{};std::shared_ptr< monty::ndarray< int,1 > > barsubj{};std::shared_ptr< monty::ndarray< int,1 > > barsubi{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< int,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};virtual void destroy();
static ConNZStruct::t _new_ConNZStruct(std::shared_ptr< monty::ndarray< long long,1 > > _457,std::shared_ptr< monty::ndarray< int,1 > > _458,std::shared_ptr< monty::ndarray< double,1 > > _459,std::shared_ptr< monty::ndarray< double,1 > > _460,std::shared_ptr< monty::ndarray< int,1 > > _461,std::shared_ptr< monty::ndarray< int,1 > > _462,std::shared_ptr< monty::ndarray< int,1 > > _463);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _457,std::shared_ptr< monty::ndarray< int,1 > > _458,std::shared_ptr< monty::ndarray< double,1 > > _459,std::shared_ptr< monty::ndarray< double,1 > > _460,std::shared_ptr< monty::ndarray< int,1 > > _461,std::shared_ptr< monty::ndarray< int,1 > > _462,std::shared_ptr< monty::ndarray< int,1 > > _463);
}; // struct ConNZStruct;

struct p_BaseVariable : public /*implements*/ virtual ::mosek::fusion::Variable
{
BaseVariable * _pubthis;
static mosek::fusion::p_BaseVariable* _get_impl(mosek::fusion::BaseVariable * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_BaseVariable * _get_impl(mosek::fusion::BaseVariable::t _inst) { return _get_impl(_inst.get()); }
p_BaseVariable(BaseVariable * _pubthis);
virtual ~p_BaseVariable() { /* std::cout << "~p_BaseVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< long long,1 > > nativeidxs{};monty::rc_ptr< ::mosek::fusion::Model > model{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static BaseVariable::t _new_BaseVariable(monty::rc_ptr< ::mosek::fusion::BaseVariable > _1607,monty::rc_ptr< ::mosek::fusion::Model > _1608);
void _initialize(monty::rc_ptr< ::mosek::fusion::BaseVariable > _1607,monty::rc_ptr< ::mosek::fusion::Model > _1608);
static BaseVariable::t _new_BaseVariable(monty::rc_ptr< ::mosek::fusion::Model > _1609,std::shared_ptr< monty::ndarray< int,1 > > _1610,std::shared_ptr< monty::ndarray< long long,1 > > _1611,std::shared_ptr< monty::ndarray< long long,1 > > _1612);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1609,std::shared_ptr< monty::ndarray< int,1 > > _1610,std::shared_ptr< monty::ndarray< long long,1 > > _1611,std::shared_ptr< monty::ndarray< long long,1 > > _1612);
virtual /* override */ std::string toString() ;
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2BaseVariable__eval() ;
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2Expression__eval() { return __mosek_2fusion_2BaseVariable__eval(); }
virtual void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _1615,monty::rc_ptr< ::mosek::fusion::WorkStack > _1616,monty::rc_ptr< ::mosek::fusion::WorkStack > _1617) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__reshape(int _1637,int _1638,int _1639) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__reshape(int _1637,int _1638,int _1639) { return __mosek_2fusion_2BaseVariable__reshape(_1637,_1638,_1639); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__reshape(int _1640,int _1641) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__reshape(int _1640,int _1641) { return __mosek_2fusion_2BaseVariable__reshape(_1640,_1641); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__reshape(int _1642) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__reshape(int _1642) { return __mosek_2fusion_2BaseVariable__reshape(_1642); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__reshape(std::shared_ptr< monty::ndarray< int,1 > > _1643) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__reshape(std::shared_ptr< monty::ndarray< int,1 > > _1643) { return __mosek_2fusion_2BaseVariable__reshape(_1643); }
virtual void setLevel(std::shared_ptr< monty::ndarray< double,1 > > _1647) ;
virtual monty::rc_ptr< ::mosek::fusion::Model > __mosek_2fusion_2BaseVariable__getModel() ;
virtual monty::rc_ptr< ::mosek::fusion::Model > __mosek_2fusion_2Variable__getModel() { return __mosek_2fusion_2BaseVariable__getModel(); }
virtual int getND() ;
virtual int getDim(int _1650) ;
virtual std::shared_ptr< monty::ndarray< int,1 > > getShape() ;
virtual long long getSize() ;
virtual std::shared_ptr< monty::ndarray< double,1 > > dual() ;
virtual std::shared_ptr< monty::ndarray< double,1 > > level() ;
virtual void makeContinuous() ;
virtual void makeInteger() ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__transpose() ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__transpose() { return __mosek_2fusion_2BaseVariable__transpose(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(int _1671,int _1672,int _1673) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(int _1671,int _1672,int _1673) { return __mosek_2fusion_2BaseVariable__index(_1671,_1672,_1673); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(int _1674,int _1675) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(int _1674,int _1675) { return __mosek_2fusion_2BaseVariable__index(_1674,_1675); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(std::shared_ptr< monty::ndarray< int,1 > > _1676) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(std::shared_ptr< monty::ndarray< int,1 > > _1676) { return __mosek_2fusion_2BaseVariable__index(_1676); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(int _1679) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(int _1679) { return __mosek_2fusion_2BaseVariable__index(_1679); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1680,std::shared_ptr< monty::ndarray< int,1 > > _1681,std::shared_ptr< monty::ndarray< int,1 > > _1682) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1680,std::shared_ptr< monty::ndarray< int,1 > > _1681,std::shared_ptr< monty::ndarray< int,1 > > _1682) { return __mosek_2fusion_2BaseVariable__pick(_1680,_1681,_1682); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1685,std::shared_ptr< monty::ndarray< int,1 > > _1686) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1685,std::shared_ptr< monty::ndarray< int,1 > > _1686) { return __mosek_2fusion_2BaseVariable__pick(_1685,_1686); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__pick(std::shared_ptr< monty::ndarray< int,2 > > _1689) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__pick(std::shared_ptr< monty::ndarray< int,2 > > _1689) { return __mosek_2fusion_2BaseVariable__pick(_1689); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1710) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__pick(std::shared_ptr< monty::ndarray< int,1 > > _1710) { return __mosek_2fusion_2BaseVariable__pick(_1710); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__antidiag(int _1720) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__antidiag(int _1720) { return __mosek_2fusion_2BaseVariable__antidiag(_1720); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__antidiag() ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__antidiag() { return __mosek_2fusion_2BaseVariable__antidiag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__diag(int _1721) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__diag(int _1721) { return __mosek_2fusion_2BaseVariable__diag(_1721); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__diag() ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__diag() { return __mosek_2fusion_2BaseVariable__diag(); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__general_diag(std::shared_ptr< monty::ndarray< int,1 > > _1722,std::shared_ptr< monty::ndarray< int,1 > > _1723,int _1724) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__slice(std::shared_ptr< monty::ndarray< int,1 > > _1745,std::shared_ptr< monty::ndarray< int,1 > > _1746) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__slice(std::shared_ptr< monty::ndarray< int,1 > > _1745,std::shared_ptr< monty::ndarray< int,1 > > _1746) { return __mosek_2fusion_2BaseVariable__slice(_1745,_1746); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__slice(int _1780,int _1781) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__slice(int _1780,int _1781) { return __mosek_2fusion_2BaseVariable__slice(_1780,_1781); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseVariable__asExpr() ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Variable__asExpr() { return __mosek_2fusion_2BaseVariable__asExpr(); }
virtual int inst(int _1790,std::shared_ptr< monty::ndarray< long long,1 > > _1791,int _1792,std::shared_ptr< monty::ndarray< long long,1 > > _1793) ;
virtual int numInst() ;
virtual void inst(int _1796,std::shared_ptr< monty::ndarray< long long,1 > > _1797) ;
virtual void set_values(std::shared_ptr< monty::ndarray< double,1 > > _1804,bool _1805) ;
virtual void dual_lu(int _1810,std::shared_ptr< monty::ndarray< double,1 > > _1811,bool _1812) ;
virtual void values(int _1815,std::shared_ptr< monty::ndarray< double,1 > > _1816,bool _1817) ;
virtual void make_continuous() ;
virtual void make_integer() ;
}; // struct BaseVariable;

struct p_SliceVariable : public ::mosek::fusion::p_BaseVariable
{
SliceVariable * _pubthis;
static mosek::fusion::p_SliceVariable* _get_impl(mosek::fusion::SliceVariable * _inst){ return static_cast< mosek::fusion::p_SliceVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_SliceVariable * _get_impl(mosek::fusion::SliceVariable::t _inst) { return _get_impl(_inst.get()); }
p_SliceVariable(SliceVariable * _pubthis);
virtual ~p_SliceVariable() { /* std::cout << "~p_SliceVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< long long,1 > > nativeidxs{};virtual void destroy();
static SliceVariable::t _new_SliceVariable(monty::rc_ptr< ::mosek::fusion::Model > _1367,std::shared_ptr< monty::ndarray< int,1 > > _1368,std::shared_ptr< monty::ndarray< long long,1 > > _1369,std::shared_ptr< monty::ndarray< long long,1 > > _1370);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1367,std::shared_ptr< monty::ndarray< int,1 > > _1368,std::shared_ptr< monty::ndarray< long long,1 > > _1369,std::shared_ptr< monty::ndarray< long long,1 > > _1370);
}; // struct SliceVariable;

struct p_ModelVariable : public ::mosek::fusion::p_BaseVariable
{
ModelVariable * _pubthis;
static mosek::fusion::p_ModelVariable* _get_impl(mosek::fusion::ModelVariable * _inst){ return static_cast< mosek::fusion::p_ModelVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_ModelVariable * _get_impl(mosek::fusion::ModelVariable::t _inst) { return _get_impl(_inst.get()); }
p_ModelVariable(ModelVariable * _pubthis);
virtual ~p_ModelVariable() { /* std::cout << "~p_ModelVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< int,1 > > shape{};std::shared_ptr< monty::ndarray< long long,1 > > nativeidxs{};long long varid{};std::string name{};virtual void destroy();
static ModelVariable::t _new_ModelVariable(monty::rc_ptr< ::mosek::fusion::ModelVariable > _1570,monty::rc_ptr< ::mosek::fusion::Model > _1571);
void _initialize(monty::rc_ptr< ::mosek::fusion::ModelVariable > _1570,monty::rc_ptr< ::mosek::fusion::Model > _1571);
static ModelVariable::t _new_ModelVariable(monty::rc_ptr< ::mosek::fusion::Model > _1572,const std::string &  _1573,std::shared_ptr< monty::ndarray< int,1 > > _1574,long long _1575,std::shared_ptr< monty::ndarray< long long,1 > > _1576,std::shared_ptr< monty::ndarray< long long,1 > > _1577);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1572,const std::string &  _1573,std::shared_ptr< monty::ndarray< int,1 > > _1574,long long _1575,std::shared_ptr< monty::ndarray< long long,1 > > _1576,std::shared_ptr< monty::ndarray< long long,1 > > _1577);
virtual void flushNames() { throw monty::AbstractClassError("Call to abstract method"); }
virtual void elementName(long long _1578,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1579) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1580) { throw monty::AbstractClassError("Call to abstract method"); }
}; // struct ModelVariable;

struct p_SymRangedVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ virtual ::mosek::fusion::SymmetricVariable
{
SymRangedVariable * _pubthis;
static mosek::fusion::p_SymRangedVariable* _get_impl(mosek::fusion::SymRangedVariable * _inst){ return static_cast< mosek::fusion::p_SymRangedVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_SymRangedVariable * _get_impl(mosek::fusion::SymRangedVariable::t _inst) { return _get_impl(_inst.get()); }
p_SymRangedVariable(SymRangedVariable * _pubthis);
virtual ~p_SymRangedVariable() { /* std::cout << "~p_SymRangedVariable" << std::endl;*/ };
int dim{};std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};bool names_flushed{};std::string name{};virtual void destroy();
static SymRangedVariable::t _new_SymRangedVariable(monty::rc_ptr< ::mosek::fusion::SymRangedVariable > _1371,monty::rc_ptr< ::mosek::fusion::Model > _1372);
void _initialize(monty::rc_ptr< ::mosek::fusion::SymRangedVariable > _1371,monty::rc_ptr< ::mosek::fusion::Model > _1372);
static SymRangedVariable::t _new_SymRangedVariable(monty::rc_ptr< ::mosek::fusion::Model > _1373,const std::string &  _1374,long long _1375,int _1376,std::shared_ptr< monty::ndarray< long long,1 > > _1377,std::shared_ptr< monty::ndarray< int,1 > > _1378);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1373,const std::string &  _1374,long long _1375,int _1376,std::shared_ptr< monty::ndarray< long long,1 > > _1377,std::shared_ptr< monty::ndarray< int,1 > > _1378);
virtual void dual_u(int _1379,std::shared_ptr< monty::ndarray< double,1 > > _1380) ;
virtual void dual_l(int _1381,std::shared_ptr< monty::ndarray< double,1 > > _1382) ;
virtual /* override */ void flushNames() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2SymRangedVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1386) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1386) { return __mosek_2fusion_2SymRangedVariable__clone(_1386); }
static  std::shared_ptr< monty::ndarray< long long,1 > > mirror_idxs(int _1387,std::shared_ptr< monty::ndarray< long long,1 > > _1388,std::shared_ptr< monty::ndarray< int,1 > > _1389);
static  std::shared_ptr< monty::ndarray< long long,1 > > mirror_sp(int _1405,std::shared_ptr< monty::ndarray< long long,1 > > _1406);
}; // struct SymRangedVariable;

struct p_RangedVariable : public ::mosek::fusion::p_ModelVariable
{
RangedVariable * _pubthis;
static mosek::fusion::p_RangedVariable* _get_impl(mosek::fusion::RangedVariable * _inst){ return static_cast< mosek::fusion::p_RangedVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_RangedVariable * _get_impl(mosek::fusion::RangedVariable::t _inst) { return _get_impl(_inst.get()); }
p_RangedVariable(RangedVariable * _pubthis);
virtual ~p_RangedVariable() { /* std::cout << "~p_RangedVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};std::string name{};bool names_flushed{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};virtual void destroy();
static RangedVariable::t _new_RangedVariable(monty::rc_ptr< ::mosek::fusion::RangedVariable > _1417,monty::rc_ptr< ::mosek::fusion::Model > _1418);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedVariable > _1417,monty::rc_ptr< ::mosek::fusion::Model > _1418);
static RangedVariable::t _new_RangedVariable(monty::rc_ptr< ::mosek::fusion::Model > _1419,const std::string &  _1420,long long _1421,std::shared_ptr< monty::ndarray< int,1 > > _1422,std::shared_ptr< monty::ndarray< long long,1 > > _1423,std::shared_ptr< monty::ndarray< int,1 > > _1424);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1419,const std::string &  _1420,long long _1421,std::shared_ptr< monty::ndarray< int,1 > > _1422,std::shared_ptr< monty::ndarray< long long,1 > > _1423,std::shared_ptr< monty::ndarray< int,1 > > _1424);
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > __mosek_2fusion_2RangedVariable__elementDesc(long long _1425,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1426) ;
virtual /* override */ void flushNames() ;
virtual void dual_u(int _1430,std::shared_ptr< monty::ndarray< double,1 > > _1431) ;
virtual void dual_l(int _1432,std::shared_ptr< monty::ndarray< double,1 > > _1433) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2RangedVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1434) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1434) { return __mosek_2fusion_2RangedVariable__clone(_1434); }
static  std::shared_ptr< monty::ndarray< long long,1 > > globalNativeIndexes(std::shared_ptr< monty::ndarray< int,1 > > _1435);
}; // struct RangedVariable;

struct p_LinearPSDVariable : public ::mosek::fusion::p_ModelVariable
{
LinearPSDVariable * _pubthis;
static mosek::fusion::p_LinearPSDVariable* _get_impl(mosek::fusion::LinearPSDVariable * _inst){ return static_cast< mosek::fusion::p_LinearPSDVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_LinearPSDVariable * _get_impl(mosek::fusion::LinearPSDVariable::t _inst) { return _get_impl(_inst.get()); }
p_LinearPSDVariable(LinearPSDVariable * _pubthis);
virtual ~p_LinearPSDVariable() { /* std::cout << "~p_LinearPSDVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};std::string name{};int varid{};std::shared_ptr< monty::ndarray< long long,1 > > nativeidxs{};int conedim{};virtual void destroy();
static LinearPSDVariable::t _new_LinearPSDVariable(monty::rc_ptr< ::mosek::fusion::LinearPSDVariable > _1438,monty::rc_ptr< ::mosek::fusion::Model > _1439);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearPSDVariable > _1438,monty::rc_ptr< ::mosek::fusion::Model > _1439);
static LinearPSDVariable::t _new_LinearPSDVariable(monty::rc_ptr< ::mosek::fusion::Model > _1440,const std::string &  _1441,int _1442,std::shared_ptr< monty::ndarray< int,1 > > _1443,int _1444,std::shared_ptr< monty::ndarray< long long,1 > > _1445);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1440,const std::string &  _1441,int _1442,std::shared_ptr< monty::ndarray< int,1 > > _1443,int _1444,std::shared_ptr< monty::ndarray< long long,1 > > _1445);
virtual /* override */ void flushNames() ;
virtual /* override */ std::string toString() ;
virtual void make_continuous(std::shared_ptr< monty::ndarray< long long,1 > > _1448) ;
virtual void make_integer(std::shared_ptr< monty::ndarray< long long,1 > > _1449) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2LinearPSDVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1450) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1450) { return __mosek_2fusion_2LinearPSDVariable__clone(_1450); }
static  std::shared_ptr< monty::ndarray< long long,1 > > globalNativeIndexes(std::shared_ptr< monty::ndarray< long long,1 > > _1451);
}; // struct LinearPSDVariable;

struct p_PSDVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ virtual ::mosek::fusion::SymmetricVariable
{
PSDVariable * _pubthis;
static mosek::fusion::p_PSDVariable* _get_impl(mosek::fusion::PSDVariable * _inst){ return static_cast< mosek::fusion::p_PSDVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_PSDVariable * _get_impl(mosek::fusion::PSDVariable::t _inst) { return _get_impl(_inst.get()); }
p_PSDVariable(PSDVariable * _pubthis);
virtual ~p_PSDVariable() { /* std::cout << "~p_PSDVariable" << std::endl;*/ };
int conedim2{};int conedim1{};std::shared_ptr< monty::ndarray< int,1 > > shape{};std::string name{};std::shared_ptr< monty::ndarray< long long,1 > > nativeidxs{};int varid{};virtual void destroy();
static PSDVariable::t _new_PSDVariable(monty::rc_ptr< ::mosek::fusion::PSDVariable > _1453,monty::rc_ptr< ::mosek::fusion::Model > _1454);
void _initialize(monty::rc_ptr< ::mosek::fusion::PSDVariable > _1453,monty::rc_ptr< ::mosek::fusion::Model > _1454);
static PSDVariable::t _new_PSDVariable(monty::rc_ptr< ::mosek::fusion::Model > _1455,const std::string &  _1456,int _1457,std::shared_ptr< monty::ndarray< int,1 > > _1458,int _1459,int _1460,std::shared_ptr< monty::ndarray< long long,1 > > _1461);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1455,const std::string &  _1456,int _1457,std::shared_ptr< monty::ndarray< int,1 > > _1458,int _1459,int _1460,std::shared_ptr< monty::ndarray< long long,1 > > _1461);
virtual /* override */ void flushNames() ;
virtual /* override */ std::string toString() ;
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > __mosek_2fusion_2PSDVariable__elementDesc(long long _1464,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1465) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2PSDVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1466) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1466) { return __mosek_2fusion_2PSDVariable__clone(_1466); }
static  std::shared_ptr< monty::ndarray< long long,1 > > fullnativeidxs(std::shared_ptr< monty::ndarray< int,1 > > _1467,int _1468,int _1469,std::shared_ptr< monty::ndarray< long long,1 > > _1470);
}; // struct PSDVariable;

struct p_SymLinearVariable : public ::mosek::fusion::p_ModelVariable, public /*implements*/ virtual ::mosek::fusion::SymmetricVariable
{
SymLinearVariable * _pubthis;
static mosek::fusion::p_SymLinearVariable* _get_impl(mosek::fusion::SymLinearVariable * _inst){ return static_cast< mosek::fusion::p_SymLinearVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_SymLinearVariable * _get_impl(mosek::fusion::SymLinearVariable::t _inst) { return _get_impl(_inst.get()); }
p_SymLinearVariable(SymLinearVariable * _pubthis);
virtual ~p_SymLinearVariable() { /* std::cout << "~p_SymLinearVariable" << std::endl;*/ };
int dim{};std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};bool names_flushed{};std::string name{};virtual void destroy();
static SymLinearVariable::t _new_SymLinearVariable(monty::rc_ptr< ::mosek::fusion::SymLinearVariable > _1495,monty::rc_ptr< ::mosek::fusion::Model > _1496);
void _initialize(monty::rc_ptr< ::mosek::fusion::SymLinearVariable > _1495,monty::rc_ptr< ::mosek::fusion::Model > _1496);
static SymLinearVariable::t _new_SymLinearVariable(monty::rc_ptr< ::mosek::fusion::Model > _1497,const std::string &  _1498,long long _1499,int _1500,std::shared_ptr< monty::ndarray< long long,1 > > _1501,std::shared_ptr< monty::ndarray< int,1 > > _1502);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1497,const std::string &  _1498,long long _1499,int _1500,std::shared_ptr< monty::ndarray< long long,1 > > _1501,std::shared_ptr< monty::ndarray< int,1 > > _1502);
virtual /* override */ void flushNames() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2SymLinearVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1506) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1506) { return __mosek_2fusion_2SymLinearVariable__clone(_1506); }
static  std::shared_ptr< monty::ndarray< long long,1 > > mirror_idxs(int _1507,std::shared_ptr< monty::ndarray< long long,1 > > _1508,std::shared_ptr< monty::ndarray< int,1 > > _1509);
static  std::shared_ptr< monty::ndarray< long long,1 > > mirror_sp(int _1525,std::shared_ptr< monty::ndarray< long long,1 > > _1526);
}; // struct SymLinearVariable;

struct p_LinearVariable : public ::mosek::fusion::p_ModelVariable
{
LinearVariable * _pubthis;
static mosek::fusion::p_LinearVariable* _get_impl(mosek::fusion::LinearVariable * _inst){ return static_cast< mosek::fusion::p_LinearVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_LinearVariable * _get_impl(mosek::fusion::LinearVariable::t _inst) { return _get_impl(_inst.get()); }
p_LinearVariable(LinearVariable * _pubthis);
virtual ~p_LinearVariable() { /* std::cout << "~p_LinearVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};bool names_flushed{};std::string name{};virtual void destroy();
static LinearVariable::t _new_LinearVariable(monty::rc_ptr< ::mosek::fusion::LinearVariable > _1537,monty::rc_ptr< ::mosek::fusion::Model > _1538);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearVariable > _1537,monty::rc_ptr< ::mosek::fusion::Model > _1538);
static LinearVariable::t _new_LinearVariable(monty::rc_ptr< ::mosek::fusion::Model > _1539,const std::string &  _1540,long long _1541,std::shared_ptr< monty::ndarray< int,1 > > _1542,std::shared_ptr< monty::ndarray< long long,1 > > _1543,std::shared_ptr< monty::ndarray< int,1 > > _1544);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1539,const std::string &  _1540,long long _1541,std::shared_ptr< monty::ndarray< int,1 > > _1542,std::shared_ptr< monty::ndarray< long long,1 > > _1543,std::shared_ptr< monty::ndarray< int,1 > > _1544);
virtual /* override */ std::string toString() ;
virtual /* override */ void flushNames() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2LinearVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1550) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1550) { return __mosek_2fusion_2LinearVariable__clone(_1550); }
static  std::shared_ptr< monty::ndarray< long long,1 > > globalNativeIndexes(std::shared_ptr< monty::ndarray< int,1 > > _1551);
}; // struct LinearVariable;

struct p_ConicVariable : public ::mosek::fusion::p_ModelVariable
{
ConicVariable * _pubthis;
static mosek::fusion::p_ConicVariable* _get_impl(mosek::fusion::ConicVariable * _inst){ return static_cast< mosek::fusion::p_ConicVariable* >(mosek::fusion::p_ModelVariable::_get_impl(_inst)); }
static mosek::fusion::p_ConicVariable * _get_impl(mosek::fusion::ConicVariable::t _inst) { return _get_impl(_inst.get()); }
p_ConicVariable(ConicVariable * _pubthis);
virtual ~p_ConicVariable() { /* std::cout << "~p_ConicVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};std::shared_ptr< monty::ndarray< int,1 > > shape{};std::string name{};bool names_flushed{};int varid{};virtual void destroy();
static ConicVariable::t _new_ConicVariable(monty::rc_ptr< ::mosek::fusion::ConicVariable > _1554,monty::rc_ptr< ::mosek::fusion::Model > _1555);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConicVariable > _1554,monty::rc_ptr< ::mosek::fusion::Model > _1555);
static ConicVariable::t _new_ConicVariable(monty::rc_ptr< ::mosek::fusion::Model > _1556,const std::string &  _1557,int _1558,std::shared_ptr< monty::ndarray< int,1 > > _1559,std::shared_ptr< monty::ndarray< int,1 > > _1560);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _1556,const std::string &  _1557,int _1558,std::shared_ptr< monty::ndarray< int,1 > > _1559,std::shared_ptr< monty::ndarray< int,1 > > _1560);
virtual /* override */ std::string toString() ;
virtual /* override */ void flushNames() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ConicVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1566) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelVariable > __mosek_2fusion_2ModelVariable__clone(monty::rc_ptr< ::mosek::fusion::Model > _1566) { return __mosek_2fusion_2ConicVariable__clone(_1566); }
static  std::shared_ptr< monty::ndarray< long long,1 > > globalNativeIndexes(std::shared_ptr< monty::ndarray< int,1 > > _1567);
}; // struct ConicVariable;

struct p_NilVariable : public ::mosek::fusion::p_BaseVariable, public /*implements*/ virtual ::mosek::fusion::SymmetricVariable
{
NilVariable * _pubthis;
static mosek::fusion::p_NilVariable* _get_impl(mosek::fusion::NilVariable * _inst){ return static_cast< mosek::fusion::p_NilVariable* >(mosek::fusion::p_BaseVariable::_get_impl(_inst)); }
static mosek::fusion::p_NilVariable * _get_impl(mosek::fusion::NilVariable::t _inst) { return _get_impl(_inst.get()); }
p_NilVariable(NilVariable * _pubthis);
virtual ~p_NilVariable() { /* std::cout << "~p_NilVariable" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static NilVariable::t _new_NilVariable(std::shared_ptr< monty::ndarray< int,1 > > _1581);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _1581);
static NilVariable::t _new_NilVariable();
void _initialize();
virtual void flushNames() ;
virtual monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > __mosek_2fusion_2NilVariable__elementDesc(long long _1583,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1584) ;
virtual void elementName(long long _1585,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _1586) ;
virtual /* override */ int numInst() ;
virtual int inst(int _1587,std::shared_ptr< monty::ndarray< long long,1 > > _1588,std::shared_ptr< monty::ndarray< long long,1 > > _1589) ;
virtual /* override */ void inst(int _1590,std::shared_ptr< monty::ndarray< long long,1 > > _1591) ;
virtual /* override */ void set_values(std::shared_ptr< monty::ndarray< double,1 > > _1592,bool _1593) ;
virtual /* override */ void values(int _1594,std::shared_ptr< monty::ndarray< double,1 > > _1595,bool _1596) ;
virtual /* override */ void make_continuous() ;
virtual /* override */ void make_integer() ;
virtual /* override */ std::string toString() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2NilVariable__index(std::shared_ptr< monty::ndarray< int,1 > > _1597) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(std::shared_ptr< monty::ndarray< int,1 > > _1597) { return __mosek_2fusion_2NilVariable__index(_1597); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(std::shared_ptr< monty::ndarray< int,1 > > _1597) { return __mosek_2fusion_2NilVariable__index(_1597); }
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2NilVariable__index(int _1599) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__index(int _1599) { return __mosek_2fusion_2NilVariable__index(_1599); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__index(int _1599) { return __mosek_2fusion_2NilVariable__index(_1599); }
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2NilVariable__slice(std::shared_ptr< monty::ndarray< int,1 > > _1601,std::shared_ptr< monty::ndarray< int,1 > > _1602) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__slice(std::shared_ptr< monty::ndarray< int,1 > > _1601,std::shared_ptr< monty::ndarray< int,1 > > _1602) { return __mosek_2fusion_2NilVariable__slice(_1601,_1602); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__slice(std::shared_ptr< monty::ndarray< int,1 > > _1601,std::shared_ptr< monty::ndarray< int,1 > > _1602) { return __mosek_2fusion_2NilVariable__slice(_1601,_1602); }
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2NilVariable__slice(int _1605,int _1606) ;
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2BaseVariable__slice(int _1605,int _1606) { return __mosek_2fusion_2NilVariable__slice(_1605,_1606); }
virtual monty::rc_ptr< ::mosek::fusion::Variable > __mosek_2fusion_2Variable__slice(int _1605,int _1606) { return __mosek_2fusion_2NilVariable__slice(_1605,_1606); }
}; // struct NilVariable;

struct p_Var
{
Var * _pubthis;
static mosek::fusion::p_Var* _get_impl(mosek::fusion::Var * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Var * _get_impl(mosek::fusion::Var::t _inst) { return _get_impl(_inst.get()); }
p_Var(Var * _pubthis);
virtual ~p_Var() { /* std::cout << "~p_Var" << std::endl;*/ };
virtual void destroy();
static  monty::rc_ptr< ::mosek::fusion::Variable > empty(std::shared_ptr< monty::ndarray< int,1 > > _1859);
static  monty::rc_ptr< ::mosek::fusion::Variable > compress(monty::rc_ptr< ::mosek::fusion::Variable > _1861);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _1869,int _1870);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _1871,int _1872,int _1873);
static  monty::rc_ptr< ::mosek::fusion::Variable > flatten(monty::rc_ptr< ::mosek::fusion::Variable > _1874);
static  monty::rc_ptr< ::mosek::fusion::Variable > reshape(monty::rc_ptr< ::mosek::fusion::Variable > _1875,std::shared_ptr< monty::ndarray< int,1 > > _1876);
static  monty::rc_ptr< ::mosek::fusion::Variable > index_permute_(monty::rc_ptr< ::mosek::fusion::Variable > _1877,std::shared_ptr< monty::ndarray< int,1 > > _1878);
static  monty::rc_ptr< ::mosek::fusion::Variable > hrepeat(monty::rc_ptr< ::mosek::fusion::Variable > _1907,int _1908);
static  monty::rc_ptr< ::mosek::fusion::Variable > vrepeat(monty::rc_ptr< ::mosek::fusion::Variable > _1909,int _1910);
static  monty::rc_ptr< ::mosek::fusion::Variable > repeat(monty::rc_ptr< ::mosek::fusion::Variable > _1911,int _1912);
static  monty::rc_ptr< ::mosek::fusion::Variable > repeat(monty::rc_ptr< ::mosek::fusion::Variable > _1913,int _1914,int _1915);
static  monty::rc_ptr< ::mosek::fusion::Variable > drepeat(monty::rc_ptr< ::mosek::fusion::Variable > _1916,int _1917,int _1918);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > >,1 > > _1982);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _1984,monty::rc_ptr< ::mosek::fusion::Variable > _1985,monty::rc_ptr< ::mosek::fusion::Variable > _1986);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(monty::rc_ptr< ::mosek::fusion::Variable > _1987,monty::rc_ptr< ::mosek::fusion::Variable > _1988);
static  monty::rc_ptr< ::mosek::fusion::Variable > vstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1989);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _1990,monty::rc_ptr< ::mosek::fusion::Variable > _1991,monty::rc_ptr< ::mosek::fusion::Variable > _1992);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(monty::rc_ptr< ::mosek::fusion::Variable > _1993,monty::rc_ptr< ::mosek::fusion::Variable > _1994);
static  monty::rc_ptr< ::mosek::fusion::Variable > hstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _1995);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(monty::rc_ptr< ::mosek::fusion::Variable > _1996,monty::rc_ptr< ::mosek::fusion::Variable > _1997,monty::rc_ptr< ::mosek::fusion::Variable > _1998,int _1999);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(monty::rc_ptr< ::mosek::fusion::Variable > _2000,monty::rc_ptr< ::mosek::fusion::Variable > _2001,int _2002);
static  monty::rc_ptr< ::mosek::fusion::Variable > stack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2003,int _2004);
static  monty::rc_ptr< ::mosek::fusion::Variable > promote(monty::rc_ptr< ::mosek::fusion::Variable > _2007,int _2008);
static  monty::rc_ptr< ::mosek::fusion::Variable > dstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _2013,int _2014);
}; // struct Var;

struct p_ConstraintCache
{
ConstraintCache * _pubthis;
static mosek::fusion::p_ConstraintCache* _get_impl(mosek::fusion::ConstraintCache * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_ConstraintCache * _get_impl(mosek::fusion::ConstraintCache::t _inst) { return _get_impl(_inst.get()); }
p_ConstraintCache(ConstraintCache * _pubthis);
virtual ~p_ConstraintCache() { /* std::cout << "~p_ConstraintCache" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > barmatidx{};std::shared_ptr< monty::ndarray< int,1 > > barsubj{};std::shared_ptr< monty::ndarray< int,1 > > barsubi{};long long nbarnz{};long long nunordered{};std::shared_ptr< monty::ndarray< int,1 > > buffer_subi{};std::shared_ptr< monty::ndarray< int,1 > > buffer_subj{};std::shared_ptr< monty::ndarray< double,1 > > buffer_cof{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< int,1 > > subi{};std::shared_ptr< monty::ndarray< int,1 > > subj{};long long nnz{};int nrows{};virtual void destroy();
static ConstraintCache::t _new_ConstraintCache(monty::rc_ptr< ::mosek::fusion::ConstraintCache > _2137);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConstraintCache > _2137);
static ConstraintCache::t _new_ConstraintCache(std::shared_ptr< monty::ndarray< long long,1 > > _2138,std::shared_ptr< monty::ndarray< double,1 > > _2139,std::shared_ptr< monty::ndarray< int,1 > > _2140,std::shared_ptr< monty::ndarray< double,1 > > _2141,std::shared_ptr< monty::ndarray< int,1 > > _2142,std::shared_ptr< monty::ndarray< int,1 > > _2143,std::shared_ptr< monty::ndarray< int,1 > > _2144);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _2138,std::shared_ptr< monty::ndarray< double,1 > > _2139,std::shared_ptr< monty::ndarray< int,1 > > _2140,std::shared_ptr< monty::ndarray< double,1 > > _2141,std::shared_ptr< monty::ndarray< int,1 > > _2142,std::shared_ptr< monty::ndarray< int,1 > > _2143,std::shared_ptr< monty::ndarray< int,1 > > _2144);
virtual void unchecked_add_fx(std::shared_ptr< monty::ndarray< double,1 > > _2147) ;
virtual long long order_barentries() ;
virtual void add_bar(std::shared_ptr< monty::ndarray< int,1 > > _2157,std::shared_ptr< monty::ndarray< int,1 > > _2158,std::shared_ptr< monty::ndarray< int,1 > > _2159) ;
virtual void unchecked_add_l(std::shared_ptr< monty::ndarray< long long,1 > > _2165,std::shared_ptr< monty::ndarray< int,1 > > _2166,std::shared_ptr< monty::ndarray< double,1 > > _2167,std::shared_ptr< monty::ndarray< double,1 > > _2168) ;
virtual void add(std::shared_ptr< monty::ndarray< long long,1 > > _2177,std::shared_ptr< monty::ndarray< int,1 > > _2178,std::shared_ptr< monty::ndarray< double,1 > > _2179,std::shared_ptr< monty::ndarray< double,1 > > _2180) ;
virtual long long flush(std::shared_ptr< monty::ndarray< int,1 > > _2181,std::shared_ptr< monty::ndarray< int,1 > > _2182,std::shared_ptr< monty::ndarray< double,1 > > _2183,std::shared_ptr< monty::ndarray< double,1 > > _2184) ;
virtual long long numUnsorted() ;
virtual monty::rc_ptr< ::mosek::fusion::ConstraintCache > __mosek_2fusion_2ConstraintCache__clone() ;
}; // struct ConstraintCache;

struct p_Constraint
{
Constraint * _pubthis;
static mosek::fusion::p_Constraint* _get_impl(mosek::fusion::Constraint * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Constraint * _get_impl(mosek::fusion::Constraint::t _inst) { return _get_impl(_inst.get()); }
p_Constraint(Constraint * _pubthis);
virtual ~p_Constraint() { /* std::cout << "~p_Constraint" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};std::shared_ptr< monty::ndarray< int,1 > > shape{};monty::rc_ptr< ::mosek::fusion::Model > model{};virtual void destroy();
static Constraint::t _new_Constraint(monty::rc_ptr< ::mosek::fusion::Constraint > _2258,monty::rc_ptr< ::mosek::fusion::Model > _2259);
void _initialize(monty::rc_ptr< ::mosek::fusion::Constraint > _2258,monty::rc_ptr< ::mosek::fusion::Model > _2259);
static Constraint::t _new_Constraint(monty::rc_ptr< ::mosek::fusion::Model > _2260,std::shared_ptr< monty::ndarray< int,1 > > _2261,std::shared_ptr< monty::ndarray< int,1 > > _2262);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2260,std::shared_ptr< monty::ndarray< int,1 > > _2261,std::shared_ptr< monty::ndarray< int,1 > > _2262);
virtual /* override */ std::string toString() ;
virtual void toStringArray(std::shared_ptr< monty::ndarray< long long,1 > > _2263,long long _2264,std::shared_ptr< monty::ndarray< std::string,1 > > _2265) ;
virtual std::shared_ptr< monty::ndarray< double,1 > > dual() ;
virtual std::shared_ptr< monty::ndarray< double,1 > > level() ;
virtual void values(bool _2268,int _2269,std::shared_ptr< monty::ndarray< double,1 > > _2270) ;
virtual void update(std::shared_ptr< monty::ndarray< double,1 > > _2271) ;
virtual void update(monty::rc_ptr< ::mosek::fusion::Expression > _2272) ;
virtual void update(monty::rc_ptr< ::mosek::fusion::Expression > _2276,monty::rc_ptr< ::mosek::fusion::Variable > _2277,bool _2278) ;
virtual void update(monty::rc_ptr< ::mosek::fusion::Expression > _2297,monty::rc_ptr< ::mosek::fusion::Variable > _2298) ;
virtual monty::rc_ptr< ::mosek::fusion::Model > __mosek_2fusion_2Constraint__get_model() ;
virtual int get_nd() ;
virtual long long size() ;
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _2301,int _2302);
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(monty::rc_ptr< ::mosek::fusion::Constraint > _2303,monty::rc_ptr< ::mosek::fusion::Constraint > _2304,monty::rc_ptr< ::mosek::fusion::Constraint > _2305,int _2306);
static  monty::rc_ptr< ::mosek::fusion::Constraint > stack(monty::rc_ptr< ::mosek::fusion::Constraint > _2307,monty::rc_ptr< ::mosek::fusion::Constraint > _2308,int _2309);
static  monty::rc_ptr< ::mosek::fusion::Constraint > hstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _2310);
static  monty::rc_ptr< ::mosek::fusion::Constraint > vstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _2311);
static  monty::rc_ptr< ::mosek::fusion::Constraint > hstack(monty::rc_ptr< ::mosek::fusion::Constraint > _2312,monty::rc_ptr< ::mosek::fusion::Constraint > _2313,monty::rc_ptr< ::mosek::fusion::Constraint > _2314);
static  monty::rc_ptr< ::mosek::fusion::Constraint > vstack(monty::rc_ptr< ::mosek::fusion::Constraint > _2315,monty::rc_ptr< ::mosek::fusion::Constraint > _2316,monty::rc_ptr< ::mosek::fusion::Constraint > _2317);
static  monty::rc_ptr< ::mosek::fusion::Constraint > hstack(monty::rc_ptr< ::mosek::fusion::Constraint > _2318,monty::rc_ptr< ::mosek::fusion::Constraint > _2319);
static  monty::rc_ptr< ::mosek::fusion::Constraint > vstack(monty::rc_ptr< ::mosek::fusion::Constraint > _2320,monty::rc_ptr< ::mosek::fusion::Constraint > _2321);
static  monty::rc_ptr< ::mosek::fusion::Constraint > dstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Constraint >,1 > > _2322,int _2323);
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Constraint__index(std::shared_ptr< monty::ndarray< int,1 > > _2374) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Constraint__index(int _2381) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Constraint__slice(std::shared_ptr< monty::ndarray< int,1 > > _2382,std::shared_ptr< monty::ndarray< int,1 > > _2383) ;
virtual monty::rc_ptr< ::mosek::fusion::Constraint > __mosek_2fusion_2Constraint__slice(int _2402,int _2403) ;
virtual int getND() ;
virtual int getSize() ;
virtual monty::rc_ptr< ::mosek::fusion::Model > __mosek_2fusion_2Constraint__getModel() ;
virtual std::shared_ptr< monty::ndarray< int,1 > > getShape() ;
}; // struct Constraint;

struct p_SliceConstraint : public ::mosek::fusion::p_Constraint
{
SliceConstraint * _pubthis;
static mosek::fusion::p_SliceConstraint* _get_impl(mosek::fusion::SliceConstraint * _inst){ return static_cast< mosek::fusion::p_SliceConstraint* >(mosek::fusion::p_Constraint::_get_impl(_inst)); }
static mosek::fusion::p_SliceConstraint * _get_impl(mosek::fusion::SliceConstraint::t _inst) { return _get_impl(_inst.get()); }
p_SliceConstraint(SliceConstraint * _pubthis);
virtual ~p_SliceConstraint() { /* std::cout << "~p_SliceConstraint" << std::endl;*/ };
virtual void destroy();
static SliceConstraint::t _new_SliceConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2207,std::shared_ptr< monty::ndarray< int,1 > > _2208,std::shared_ptr< monty::ndarray< int,1 > > _2209);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2207,std::shared_ptr< monty::ndarray< int,1 > > _2208,std::shared_ptr< monty::ndarray< int,1 > > _2209);
virtual /* override */ std::string toString() ;
}; // struct SliceConstraint;

struct p_ModelConstraint : public ::mosek::fusion::p_Constraint
{
ModelConstraint * _pubthis;
static mosek::fusion::p_ModelConstraint* _get_impl(mosek::fusion::ModelConstraint * _inst){ return static_cast< mosek::fusion::p_ModelConstraint* >(mosek::fusion::p_Constraint::_get_impl(_inst)); }
static mosek::fusion::p_ModelConstraint * _get_impl(mosek::fusion::ModelConstraint::t _inst) { return _get_impl(_inst.get()); }
p_ModelConstraint(ModelConstraint * _pubthis);
virtual ~p_ModelConstraint() { /* std::cout << "~p_ModelConstraint" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};bool names_flushed{};std::string name{};virtual void destroy();
static ModelConstraint::t _new_ModelConstraint(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _2247,monty::rc_ptr< ::mosek::fusion::Model > _2248);
void _initialize(monty::rc_ptr< ::mosek::fusion::ModelConstraint > _2247,monty::rc_ptr< ::mosek::fusion::Model > _2248);
static ModelConstraint::t _new_ModelConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2249,const std::string &  _2250,std::shared_ptr< monty::ndarray< int,1 > > _2251,std::shared_ptr< monty::ndarray< int,1 > > _2252);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2249,const std::string &  _2250,std::shared_ptr< monty::ndarray< int,1 > > _2251,std::shared_ptr< monty::ndarray< int,1 > > _2252);
virtual /* override */ std::string toString() ;
virtual void flushNames() ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2257) { throw monty::AbstractClassError("Call to abstract method"); }
}; // struct ModelConstraint;

struct p_LinearPSDConstraint : public ::mosek::fusion::p_ModelConstraint
{
LinearPSDConstraint * _pubthis;
static mosek::fusion::p_LinearPSDConstraint* _get_impl(mosek::fusion::LinearPSDConstraint * _inst){ return static_cast< mosek::fusion::p_LinearPSDConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_LinearPSDConstraint * _get_impl(mosek::fusion::LinearPSDConstraint::t _inst) { return _get_impl(_inst.get()); }
p_LinearPSDConstraint(LinearPSDConstraint * _pubthis);
virtual ~p_LinearPSDConstraint() { /* std::cout << "~p_LinearPSDConstraint" << std::endl;*/ };
int conedim{};std::shared_ptr< monty::ndarray< int,1 > > shape{};int conid{};std::shared_ptr< monty::ndarray< long long,1 > > slackidxs{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};virtual void destroy();
static LinearPSDConstraint::t _new_LinearPSDConstraint(monty::rc_ptr< ::mosek::fusion::LinearPSDConstraint > _2083,monty::rc_ptr< ::mosek::fusion::Model > _2084);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearPSDConstraint > _2083,monty::rc_ptr< ::mosek::fusion::Model > _2084);
static LinearPSDConstraint::t _new_LinearPSDConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2085,const std::string &  _2086,int _2087,std::shared_ptr< monty::ndarray< int,1 > > _2088,int _2089,std::shared_ptr< monty::ndarray< int,1 > > _2090,std::shared_ptr< monty::ndarray< long long,1 > > _2091);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2085,const std::string &  _2086,int _2087,std::shared_ptr< monty::ndarray< int,1 > > _2088,int _2089,std::shared_ptr< monty::ndarray< int,1 > > _2090,std::shared_ptr< monty::ndarray< long long,1 > > _2091);
virtual void domainToString(long long _2092,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2093) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2LinearPSDConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2097) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2097) { return __mosek_2fusion_2LinearPSDConstraint__clone(_2097); }
}; // struct LinearPSDConstraint;

struct p_PSDConstraint : public ::mosek::fusion::p_ModelConstraint
{
PSDConstraint * _pubthis;
static mosek::fusion::p_PSDConstraint* _get_impl(mosek::fusion::PSDConstraint * _inst){ return static_cast< mosek::fusion::p_PSDConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_PSDConstraint * _get_impl(mosek::fusion::PSDConstraint::t _inst) { return _get_impl(_inst.get()); }
p_PSDConstraint(PSDConstraint * _pubthis);
virtual ~p_PSDConstraint() { /* std::cout << "~p_PSDConstraint" << std::endl;*/ };
bool names_flushed{};int conedim1{};int conedim0{};std::shared_ptr< monty::ndarray< int,1 > > shape{};std::string name{};std::shared_ptr< monty::ndarray< long long,1 > > slackidxs{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};int conid{};virtual void destroy();
static PSDConstraint::t _new_PSDConstraint(monty::rc_ptr< ::mosek::fusion::PSDConstraint > _2098,monty::rc_ptr< ::mosek::fusion::Model > _2099);
void _initialize(monty::rc_ptr< ::mosek::fusion::PSDConstraint > _2098,monty::rc_ptr< ::mosek::fusion::Model > _2099);
static PSDConstraint::t _new_PSDConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2100,const std::string &  _2101,int _2102,std::shared_ptr< monty::ndarray< int,1 > > _2103,int _2104,int _2105,std::shared_ptr< monty::ndarray< long long,1 > > _2106,std::shared_ptr< monty::ndarray< int,1 > > _2107);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2100,const std::string &  _2101,int _2102,std::shared_ptr< monty::ndarray< int,1 > > _2103,int _2104,int _2105,std::shared_ptr< monty::ndarray< long long,1 > > _2106,std::shared_ptr< monty::ndarray< int,1 > > _2107);
virtual /* override */ std::string toString() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2PSDConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2108) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2108) { return __mosek_2fusion_2PSDConstraint__clone(_2108); }
static  std::shared_ptr< monty::ndarray< int,1 > > computenidxs(std::shared_ptr< monty::ndarray< int,1 > > _2109,int _2110,int _2111,std::shared_ptr< monty::ndarray< int,1 > > _2112);
}; // struct PSDConstraint;

struct p_RangedConstraint : public ::mosek::fusion::p_ModelConstraint
{
RangedConstraint * _pubthis;
static mosek::fusion::p_RangedConstraint* _get_impl(mosek::fusion::RangedConstraint * _inst){ return static_cast< mosek::fusion::p_RangedConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_RangedConstraint * _get_impl(mosek::fusion::RangedConstraint::t _inst) { return _get_impl(_inst.get()); }
p_RangedConstraint(RangedConstraint * _pubthis);
virtual ~p_RangedConstraint() { /* std::cout << "~p_RangedConstraint" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static RangedConstraint::t _new_RangedConstraint(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _2211,monty::rc_ptr< ::mosek::fusion::Model > _2212);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangedConstraint > _2211,monty::rc_ptr< ::mosek::fusion::Model > _2212);
static RangedConstraint::t _new_RangedConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2213,const std::string &  _2214,std::shared_ptr< monty::ndarray< int,1 > > _2215,std::shared_ptr< monty::ndarray< int,1 > > _2216);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2213,const std::string &  _2214,std::shared_ptr< monty::ndarray< int,1 > > _2215,std::shared_ptr< monty::ndarray< int,1 > > _2216);
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2RangedConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2217) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2217) { return __mosek_2fusion_2RangedConstraint__clone(_2217); }
}; // struct RangedConstraint;

struct p_ConicConstraint : public ::mosek::fusion::p_ModelConstraint
{
ConicConstraint * _pubthis;
static mosek::fusion::p_ConicConstraint* _get_impl(mosek::fusion::ConicConstraint * _inst){ return static_cast< mosek::fusion::p_ConicConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_ConicConstraint * _get_impl(mosek::fusion::ConicConstraint::t _inst) { return _get_impl(_inst.get()); }
p_ConicConstraint(ConicConstraint * _pubthis);
virtual ~p_ConicConstraint() { /* std::cout << "~p_ConicConstraint" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > nativeslack{};std::shared_ptr< monty::ndarray< int,1 > > nativeidxs{};bool names_flushed{};std::string name{};std::shared_ptr< monty::ndarray< int,1 > > shape{};monty::rc_ptr< ::mosek::fusion::ConeDomain > dom{};int conid{};virtual void destroy();
static ConicConstraint::t _new_ConicConstraint(monty::rc_ptr< ::mosek::fusion::ConicConstraint > _2218,monty::rc_ptr< ::mosek::fusion::Model > _2219);
void _initialize(monty::rc_ptr< ::mosek::fusion::ConicConstraint > _2218,monty::rc_ptr< ::mosek::fusion::Model > _2219);
static ConicConstraint::t _new_ConicConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2220,const std::string &  _2221,monty::rc_ptr< ::mosek::fusion::ConeDomain > _2222,std::shared_ptr< monty::ndarray< int,1 > > _2223,int _2224,std::shared_ptr< monty::ndarray< int,1 > > _2225,std::shared_ptr< monty::ndarray< int,1 > > _2226);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2220,const std::string &  _2221,monty::rc_ptr< ::mosek::fusion::ConeDomain > _2222,std::shared_ptr< monty::ndarray< int,1 > > _2223,int _2224,std::shared_ptr< monty::ndarray< int,1 > > _2225,std::shared_ptr< monty::ndarray< int,1 > > _2226);
virtual /* override */ void flushNames() ;
virtual /* override */ std::string toString() ;
virtual void domainToString(long long _2233,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2234) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ConicConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2235) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2235) { return __mosek_2fusion_2ConicConstraint__clone(_2235); }
}; // struct ConicConstraint;

struct p_LinearConstraint : public ::mosek::fusion::p_ModelConstraint
{
LinearConstraint * _pubthis;
static mosek::fusion::p_LinearConstraint* _get_impl(mosek::fusion::LinearConstraint * _inst){ return static_cast< mosek::fusion::p_LinearConstraint* >(mosek::fusion::p_ModelConstraint::_get_impl(_inst)); }
static mosek::fusion::p_LinearConstraint * _get_impl(mosek::fusion::LinearConstraint::t _inst) { return _get_impl(_inst.get()); }
p_LinearConstraint(LinearConstraint * _pubthis);
virtual ~p_LinearConstraint() { /* std::cout << "~p_LinearConstraint" << std::endl;*/ };
std::string name{};int conid{};virtual void destroy();
static LinearConstraint::t _new_LinearConstraint(monty::rc_ptr< ::mosek::fusion::LinearConstraint > _2236,monty::rc_ptr< ::mosek::fusion::Model > _2237);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearConstraint > _2236,monty::rc_ptr< ::mosek::fusion::Model > _2237);
static LinearConstraint::t _new_LinearConstraint(monty::rc_ptr< ::mosek::fusion::Model > _2238,const std::string &  _2239,int _2240,std::shared_ptr< monty::ndarray< int,1 > > _2241,std::shared_ptr< monty::ndarray< int,1 > > _2242);
void _initialize(monty::rc_ptr< ::mosek::fusion::Model > _2238,const std::string &  _2239,int _2240,std::shared_ptr< monty::ndarray< int,1 > > _2241,std::shared_ptr< monty::ndarray< int,1 > > _2242);
virtual /* override */ std::string toString() ;
virtual void domainToString(long long _2244,monty::rc_ptr< ::mosek::fusion::Utils::StringBuffer > _2245) ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2LinearConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2246) ;
virtual monty::rc_ptr< ::mosek::fusion::ModelConstraint > __mosek_2fusion_2ModelConstraint__clone(monty::rc_ptr< ::mosek::fusion::Model > _2246) { return __mosek_2fusion_2LinearConstraint__clone(_2246); }
}; // struct LinearConstraint;

struct p_Set
{
Set * _pubthis;
static mosek::fusion::p_Set* _get_impl(mosek::fusion::Set * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Set * _get_impl(mosek::fusion::Set::t _inst) { return _get_impl(_inst.get()); }
p_Set(Set * _pubthis);
virtual ~p_Set() { /* std::cout << "~p_Set" << std::endl;*/ };
virtual void destroy();
static  long long size(std::shared_ptr< monty::ndarray< int,1 > > _2408);
static  bool match(std::shared_ptr< monty::ndarray< int,1 > > _2411,std::shared_ptr< monty::ndarray< int,1 > > _2412);
static  long long linearidx(std::shared_ptr< monty::ndarray< int,1 > > _2414,std::shared_ptr< monty::ndarray< int,1 > > _2415);
static  std::shared_ptr< monty::ndarray< int,1 > > idxtokey(std::shared_ptr< monty::ndarray< int,1 > > _2418,long long _2419);
static  void idxtokey(std::shared_ptr< monty::ndarray< int,1 > > _2421,long long _2422,std::shared_ptr< monty::ndarray< int,1 > > _2423);
static  std::string indexToString(std::shared_ptr< monty::ndarray< int,1 > > _2427,long long _2428);
static  std::string keyToString(std::shared_ptr< monty::ndarray< int,1 > > _2435);
static  void indexToKey(std::shared_ptr< monty::ndarray< int,1 > > _2438,long long _2439,std::shared_ptr< monty::ndarray< int,1 > > _2440);
static  std::shared_ptr< monty::ndarray< long long,1 > > strides(std::shared_ptr< monty::ndarray< int,1 > > _2444);
static  std::shared_ptr< monty::ndarray< int,1 > > make(std::shared_ptr< monty::ndarray< int,1 > > _2448,std::shared_ptr< monty::ndarray< int,1 > > _2449);
static  std::shared_ptr< monty::ndarray< int,1 > > make(std::shared_ptr< monty::ndarray< int,1 > > _2453);
static  std::shared_ptr< monty::ndarray< int,1 > > make(int _2455,int _2456,int _2457);
static  std::shared_ptr< monty::ndarray< int,1 > > make(int _2458,int _2459);
static  std::shared_ptr< monty::ndarray< int,1 > > make(int _2460);
static  std::shared_ptr< monty::ndarray< int,1 > > scalar();
static  std::shared_ptr< monty::ndarray< int,1 > > make(std::shared_ptr< monty::ndarray< std::string,1 > > _2461);
}; // struct Set;

struct p_ConeDomain
{
ConeDomain * _pubthis;
static mosek::fusion::p_ConeDomain* _get_impl(mosek::fusion::ConeDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_ConeDomain * _get_impl(mosek::fusion::ConeDomain::t _inst) { return _get_impl(_inst.get()); }
p_ConeDomain(ConeDomain * _pubthis);
virtual ~p_ConeDomain() { /* std::cout << "~p_ConeDomain" << std::endl;*/ };
double alpha{};std::shared_ptr< monty::ndarray< int,1 > > shape{};bool int_flag{};bool axisset{};int axisidx{};mosek::fusion::QConeKey key{};virtual void destroy();
static ConeDomain::t _new_ConeDomain(mosek::fusion::QConeKey _2462,double _2463,std::shared_ptr< monty::ndarray< int,1 > > _2464);
void _initialize(mosek::fusion::QConeKey _2462,double _2463,std::shared_ptr< monty::ndarray< int,1 > > _2464);
static ConeDomain::t _new_ConeDomain(mosek::fusion::QConeKey _2465,std::shared_ptr< monty::ndarray< int,1 > > _2466);
void _initialize(mosek::fusion::QConeKey _2465,std::shared_ptr< monty::ndarray< int,1 > > _2466);
virtual bool match_shape(std::shared_ptr< monty::ndarray< int,1 > > _2467) ;
virtual monty::rc_ptr< ::mosek::fusion::ConeDomain > __mosek_2fusion_2ConeDomain__integral() ;
virtual bool axisIsSet() ;
virtual int getAxis() ;
virtual monty::rc_ptr< ::mosek::fusion::ConeDomain > __mosek_2fusion_2ConeDomain__axis(int _2468) ;
}; // struct ConeDomain;

struct p_LinPSDDomain
{
LinPSDDomain * _pubthis;
static mosek::fusion::p_LinPSDDomain* _get_impl(mosek::fusion::LinPSDDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinPSDDomain * _get_impl(mosek::fusion::LinPSDDomain::t _inst) { return _get_impl(_inst.get()); }
p_LinPSDDomain(LinPSDDomain * _pubthis);
virtual ~p_LinPSDDomain() { /* std::cout << "~p_LinPSDDomain" << std::endl;*/ };
int conedim{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static LinPSDDomain::t _new_LinPSDDomain(std::shared_ptr< monty::ndarray< int,1 > > _2469,int _2470);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2469,int _2470);
static LinPSDDomain::t _new_LinPSDDomain(std::shared_ptr< monty::ndarray< int,1 > > _2471);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2471);
static LinPSDDomain::t _new_LinPSDDomain();
void _initialize();
}; // struct LinPSDDomain;

struct p_PSDDomain
{
PSDDomain * _pubthis;
static mosek::fusion::p_PSDDomain* _get_impl(mosek::fusion::PSDDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_PSDDomain * _get_impl(mosek::fusion::PSDDomain::t _inst) { return _get_impl(_inst.get()); }
p_PSDDomain(PSDDomain * _pubthis);
virtual ~p_PSDDomain() { /* std::cout << "~p_PSDDomain" << std::endl;*/ };
bool axisIsSet{};int conedim2{};int conedim1{};mosek::fusion::PSDKey key{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static PSDDomain::t _new_PSDDomain(mosek::fusion::PSDKey _2472,std::shared_ptr< monty::ndarray< int,1 > > _2473,int _2474,int _2475);
void _initialize(mosek::fusion::PSDKey _2472,std::shared_ptr< monty::ndarray< int,1 > > _2473,int _2474,int _2475);
static PSDDomain::t _new_PSDDomain(mosek::fusion::PSDKey _2477,std::shared_ptr< monty::ndarray< int,1 > > _2478);
void _initialize(mosek::fusion::PSDKey _2477,std::shared_ptr< monty::ndarray< int,1 > > _2478);
static PSDDomain::t _new_PSDDomain(mosek::fusion::PSDKey _2479);
void _initialize(mosek::fusion::PSDKey _2479);
virtual monty::rc_ptr< ::mosek::fusion::PSDDomain > __mosek_2fusion_2PSDDomain__axis(int _2480,int _2481) ;
}; // struct PSDDomain;

struct p_RangeDomain
{
RangeDomain * _pubthis;
static mosek::fusion::p_RangeDomain* _get_impl(mosek::fusion::RangeDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_RangeDomain * _get_impl(mosek::fusion::RangeDomain::t _inst) { return _get_impl(_inst.get()); }
p_RangeDomain(RangeDomain * _pubthis);
virtual ~p_RangeDomain() { /* std::cout << "~p_RangeDomain" << std::endl;*/ };
bool cardinal_flag{};bool scalable{};std::shared_ptr< monty::ndarray< double,1 > > ub{};std::shared_ptr< monty::ndarray< double,1 > > lb{};std::shared_ptr< monty::ndarray< int,2 > > sparsity{};bool empty{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static RangeDomain::t _new_RangeDomain(bool _2483,std::shared_ptr< monty::ndarray< double,1 > > _2484,std::shared_ptr< monty::ndarray< double,1 > > _2485,std::shared_ptr< monty::ndarray< int,1 > > _2486);
void _initialize(bool _2483,std::shared_ptr< monty::ndarray< double,1 > > _2484,std::shared_ptr< monty::ndarray< double,1 > > _2485,std::shared_ptr< monty::ndarray< int,1 > > _2486);
static RangeDomain::t _new_RangeDomain(bool _2487,std::shared_ptr< monty::ndarray< double,1 > > _2488,std::shared_ptr< monty::ndarray< double,1 > > _2489,std::shared_ptr< monty::ndarray< int,1 > > _2490,std::shared_ptr< monty::ndarray< int,2 > > _2491);
void _initialize(bool _2487,std::shared_ptr< monty::ndarray< double,1 > > _2488,std::shared_ptr< monty::ndarray< double,1 > > _2489,std::shared_ptr< monty::ndarray< int,1 > > _2490,std::shared_ptr< monty::ndarray< int,2 > > _2491);
static RangeDomain::t _new_RangeDomain(bool _2492,std::shared_ptr< monty::ndarray< double,1 > > _2493,std::shared_ptr< monty::ndarray< double,1 > > _2494,std::shared_ptr< monty::ndarray< int,1 > > _2495,std::shared_ptr< monty::ndarray< int,2 > > _2496,int _2497);
void _initialize(bool _2492,std::shared_ptr< monty::ndarray< double,1 > > _2493,std::shared_ptr< monty::ndarray< double,1 > > _2494,std::shared_ptr< monty::ndarray< int,1 > > _2495,std::shared_ptr< monty::ndarray< int,2 > > _2496,int _2497);
static RangeDomain::t _new_RangeDomain(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2498);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2498);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricRangeDomain > __mosek_2fusion_2RangeDomain__symmetric() ;
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > __mosek_2fusion_2RangeDomain__sparse(std::shared_ptr< monty::ndarray< int,2 > > _2499) ;
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > __mosek_2fusion_2RangeDomain__sparse(std::shared_ptr< monty::ndarray< int,1 > > _2502) ;
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > __mosek_2fusion_2RangeDomain__sparse() ;
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > __mosek_2fusion_2RangeDomain__integral() ;
virtual monty::rc_ptr< ::mosek::fusion::RangeDomain > __mosek_2fusion_2RangeDomain__withShape(std::shared_ptr< monty::ndarray< int,1 > > _2504) ;
virtual bool match_shape(std::shared_ptr< monty::ndarray< int,1 > > _2505) ;
}; // struct RangeDomain;

struct p_SymmetricRangeDomain : public ::mosek::fusion::p_RangeDomain
{
SymmetricRangeDomain * _pubthis;
static mosek::fusion::p_SymmetricRangeDomain* _get_impl(mosek::fusion::SymmetricRangeDomain * _inst){ return static_cast< mosek::fusion::p_SymmetricRangeDomain* >(mosek::fusion::p_RangeDomain::_get_impl(_inst)); }
static mosek::fusion::p_SymmetricRangeDomain * _get_impl(mosek::fusion::SymmetricRangeDomain::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricRangeDomain(SymmetricRangeDomain * _pubthis);
virtual ~p_SymmetricRangeDomain() { /* std::cout << "~p_SymmetricRangeDomain" << std::endl;*/ };
int dim{};virtual void destroy();
static SymmetricRangeDomain::t _new_SymmetricRangeDomain(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2482);
void _initialize(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2482);
}; // struct SymmetricRangeDomain;

struct p_SymmetricLinearDomain
{
SymmetricLinearDomain * _pubthis;
static mosek::fusion::p_SymmetricLinearDomain* _get_impl(mosek::fusion::SymmetricLinearDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricLinearDomain * _get_impl(mosek::fusion::SymmetricLinearDomain::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricLinearDomain(SymmetricLinearDomain * _pubthis);
virtual ~p_SymmetricLinearDomain() { /* std::cout << "~p_SymmetricLinearDomain" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,2 > > sparsity{};bool cardinal_flag{};mosek::fusion::RelationKey key{};std::shared_ptr< monty::ndarray< int,1 > > shape{};monty::rc_ptr< ::mosek::fusion::LinearDomain > dom{};int dim{};virtual void destroy();
static SymmetricLinearDomain::t _new_SymmetricLinearDomain(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2507);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2507);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > __mosek_2fusion_2SymmetricLinearDomain__sparse(std::shared_ptr< monty::ndarray< int,2 > > _2508) ;
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > __mosek_2fusion_2SymmetricLinearDomain__sparse(std::shared_ptr< monty::ndarray< int,1 > > _2511) ;
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > __mosek_2fusion_2SymmetricLinearDomain__integral() ;
virtual bool match_shape(std::shared_ptr< monty::ndarray< int,1 > > _2513) ;
}; // struct SymmetricLinearDomain;

struct p_LinearDomain
{
LinearDomain * _pubthis;
static mosek::fusion::p_LinearDomain* _get_impl(mosek::fusion::LinearDomain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinearDomain * _get_impl(mosek::fusion::LinearDomain::t _inst) { return _get_impl(_inst.get()); }
p_LinearDomain(LinearDomain * _pubthis);
virtual ~p_LinearDomain() { /* std::cout << "~p_LinearDomain" << std::endl;*/ };
bool empty{};bool scalable{};std::shared_ptr< monty::ndarray< int,2 > > sparsity{};bool cardinal_flag{};mosek::fusion::RelationKey key{};std::shared_ptr< monty::ndarray< double,1 > > bnd{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static LinearDomain::t _new_LinearDomain(mosek::fusion::RelationKey _2515,bool _2516,std::shared_ptr< monty::ndarray< double,1 > > _2517,std::shared_ptr< monty::ndarray< int,1 > > _2518);
void _initialize(mosek::fusion::RelationKey _2515,bool _2516,std::shared_ptr< monty::ndarray< double,1 > > _2517,std::shared_ptr< monty::ndarray< int,1 > > _2518);
static LinearDomain::t _new_LinearDomain(mosek::fusion::RelationKey _2519,bool _2520,std::shared_ptr< monty::ndarray< double,1 > > _2521,std::shared_ptr< monty::ndarray< int,1 > > _2522,std::shared_ptr< monty::ndarray< int,2 > > _2523,int _2524);
void _initialize(mosek::fusion::RelationKey _2519,bool _2520,std::shared_ptr< monty::ndarray< double,1 > > _2521,std::shared_ptr< monty::ndarray< int,1 > > _2522,std::shared_ptr< monty::ndarray< int,2 > > _2523,int _2524);
static LinearDomain::t _new_LinearDomain(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2525);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2525);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > __mosek_2fusion_2LinearDomain__symmetric() ;
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > __mosek_2fusion_2LinearDomain__sparse(std::shared_ptr< monty::ndarray< int,2 > > _2526) ;
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > __mosek_2fusion_2LinearDomain__sparse(std::shared_ptr< monty::ndarray< int,1 > > _2529) ;
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > __mosek_2fusion_2LinearDomain__sparse() ;
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > __mosek_2fusion_2LinearDomain__integral() ;
virtual monty::rc_ptr< ::mosek::fusion::LinearDomain > __mosek_2fusion_2LinearDomain__withShape(std::shared_ptr< monty::ndarray< int,1 > > _2531) ;
virtual bool match_shape(std::shared_ptr< monty::ndarray< int,1 > > _2532) ;
}; // struct LinearDomain;

struct p_Domain
{
Domain * _pubthis;
static mosek::fusion::p_Domain* _get_impl(mosek::fusion::Domain * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Domain * _get_impl(mosek::fusion::Domain::t _inst) { return _get_impl(_inst.get()); }
p_Domain(Domain * _pubthis);
virtual ~p_Domain() { /* std::cout << "~p_Domain" << std::endl;*/ };
virtual void destroy();
static  long long dimsize(std::shared_ptr< monty::ndarray< int,1 > > _2534);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > mkLinearDomain(mosek::fusion::RelationKey _2537,monty::rc_ptr< ::mosek::fusion::Matrix > _2538);
static  long long prod(std::shared_ptr< monty::ndarray< int,1 > > _2544);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(bool _2547,std::shared_ptr< monty::ndarray< double,1 > > _2548,std::shared_ptr< monty::ndarray< double,1 > > _2549,std::shared_ptr< monty::ndarray< int,2 > > _2550,std::shared_ptr< monty::ndarray< int,1 > > _2551);
static  monty::rc_ptr< ::mosek::fusion::SymmetricRangeDomain > symmetric(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2553);
static  monty::rc_ptr< ::mosek::fusion::SymmetricLinearDomain > symmetric(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2554);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > sparse(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2555,std::shared_ptr< monty::ndarray< int,2 > > _2556);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > sparse(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2557,std::shared_ptr< monty::ndarray< int,1 > > _2558);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > sparse(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2559,std::shared_ptr< monty::ndarray< int,2 > > _2560);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > sparse(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2561,std::shared_ptr< monty::ndarray< int,1 > > _2562);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > integral(monty::rc_ptr< ::mosek::fusion::RangeDomain > _2563);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > integral(monty::rc_ptr< ::mosek::fusion::LinearDomain > _2564);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > integral(monty::rc_ptr< ::mosek::fusion::ConeDomain > _2565);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > axis(monty::rc_ptr< ::mosek::fusion::ConeDomain > _2566,int _2567);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDPowerCone(double _2568,std::shared_ptr< monty::ndarray< int,1 > > _2569);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDPowerCone(double _2571,int _2572);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDPowerCone(double _2573);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPPowerCone(double _2574,std::shared_ptr< monty::ndarray< int,1 > > _2575);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPPowerCone(double _2577,int _2578);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPPowerCone(double _2579);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDExpCone(std::shared_ptr< monty::ndarray< int,1 > > _2580);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDExpCone(int _2582);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inDExpCone();
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPExpCone(std::shared_ptr< monty::ndarray< int,1 > > _2583);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPExpCone(int _2585);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inPExpCone();
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inRotatedQCone(std::shared_ptr< monty::ndarray< int,1 > > _2586);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inRotatedQCone(int _2588,int _2589);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inRotatedQCone(int _2590);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inRotatedQCone();
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inQCone(std::shared_ptr< monty::ndarray< int,1 > > _2591);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inQCone(int _2593,int _2594);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inQCone(int _2595);
static  monty::rc_ptr< ::mosek::fusion::ConeDomain > inQCone();
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD(int _2596,int _2597);
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD(int _2598);
static  monty::rc_ptr< ::mosek::fusion::LinPSDDomain > isLinPSD();
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD(int _2599,int _2600);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD(int _2601);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > isTrilPSD();
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone(int _2602,int _2603);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone(int _2604);
static  monty::rc_ptr< ::mosek::fusion::PSDDomain > inPSDCone();
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary();
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(std::shared_ptr< monty::ndarray< int,1 > > _2605);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(int _2606,int _2607);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > binary(int _2608);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _2609,std::shared_ptr< monty::ndarray< double,1 > > _2610,std::shared_ptr< monty::ndarray< int,1 > > _2611);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _2612,double _2613,std::shared_ptr< monty::ndarray< int,1 > > _2614);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _2616,std::shared_ptr< monty::ndarray< double,1 > > _2617,std::shared_ptr< monty::ndarray< int,1 > > _2618);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _2620,double _2621,std::shared_ptr< monty::ndarray< int,1 > > _2622);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _2623,std::shared_ptr< monty::ndarray< double,1 > > _2624);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(std::shared_ptr< monty::ndarray< double,1 > > _2625,double _2626);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _2628,std::shared_ptr< monty::ndarray< double,1 > > _2629);
static  monty::rc_ptr< ::mosek::fusion::RangeDomain > inRange(double _2631,double _2632);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(monty::rc_ptr< ::mosek::fusion::Matrix > _2633);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,1 > > _2634,std::shared_ptr< monty::ndarray< int,1 > > _2635);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,2 > > _2636);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(std::shared_ptr< monty::ndarray< double,1 > > _2639);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _2640,std::shared_ptr< monty::ndarray< int,1 > > _2641);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _2643,int _2644,int _2645);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _2647,int _2648);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > greaterThan(double _2650);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(monty::rc_ptr< ::mosek::fusion::Matrix > _2651);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,1 > > _2652,std::shared_ptr< monty::ndarray< int,1 > > _2653);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,2 > > _2654);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(std::shared_ptr< monty::ndarray< double,1 > > _2657);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _2658,std::shared_ptr< monty::ndarray< int,1 > > _2659);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _2660,int _2661,int _2662);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _2663,int _2664);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > lessThan(double _2665);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(monty::rc_ptr< ::mosek::fusion::Matrix > _2666);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,1 > > _2667,std::shared_ptr< monty::ndarray< int,1 > > _2668);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,2 > > _2669);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(std::shared_ptr< monty::ndarray< double,1 > > _2672);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _2673,std::shared_ptr< monty::ndarray< int,1 > > _2674);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _2675,int _2676,int _2677);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _2678,int _2679);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > equalsTo(double _2680);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(std::shared_ptr< monty::ndarray< int,1 > > _2681);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(int _2683,int _2684);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded(int _2685);
static  monty::rc_ptr< ::mosek::fusion::LinearDomain > unbounded();
}; // struct Domain;

struct p_BaseExpression : public /*implements*/ virtual ::mosek::fusion::Expression
{
BaseExpression * _pubthis;
static mosek::fusion::p_BaseExpression* _get_impl(mosek::fusion::BaseExpression * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_BaseExpression * _get_impl(mosek::fusion::BaseExpression::t _inst) { return _get_impl(_inst.get()); }
p_BaseExpression(BaseExpression * _pubthis);
virtual ~p_BaseExpression() { /* std::cout << "~p_BaseExpression" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static BaseExpression::t _new_BaseExpression(std::shared_ptr< monty::ndarray< int,1 > > _4841);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _4841);
virtual /* override */ std::string toString() ;
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2BaseExpression__eval() ;
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2Expression__eval() { return __mosek_2fusion_2BaseExpression__eval(); }
static  void storeexpr(monty::rc_ptr< ::mosek::fusion::WorkStack > _4857,std::shared_ptr< monty::ndarray< int,1 > > _4858,std::shared_ptr< monty::ndarray< int,1 > > _4859,std::shared_ptr< monty::ndarray< long long,1 > > _4860,std::shared_ptr< monty::ndarray< long long,1 > > _4861,std::shared_ptr< monty::ndarray< double,1 > > _4862,std::shared_ptr< monty::ndarray< double,1 > > _4863);
virtual void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4874,monty::rc_ptr< ::mosek::fusion::WorkStack > _4875,monty::rc_ptr< ::mosek::fusion::WorkStack > _4876) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__pick(std::shared_ptr< monty::ndarray< int,2 > > _4877) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__pick(std::shared_ptr< monty::ndarray< int,2 > > _4877) { return __mosek_2fusion_2BaseExpression__pick(_4877); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__pick(std::shared_ptr< monty::ndarray< int,1 > > _4878) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__pick(std::shared_ptr< monty::ndarray< int,1 > > _4878) { return __mosek_2fusion_2BaseExpression__pick(_4878); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__index(std::shared_ptr< monty::ndarray< int,1 > > _4881) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__index(std::shared_ptr< monty::ndarray< int,1 > > _4881) { return __mosek_2fusion_2BaseExpression__index(_4881); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__index(int _4884) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__index(int _4884) { return __mosek_2fusion_2BaseExpression__index(_4884); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__slice(std::shared_ptr< monty::ndarray< int,1 > > _4886,std::shared_ptr< monty::ndarray< int,1 > > _4887) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__slice(std::shared_ptr< monty::ndarray< int,1 > > _4886,std::shared_ptr< monty::ndarray< int,1 > > _4887) { return __mosek_2fusion_2BaseExpression__slice(_4886,_4887); }
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2BaseExpression__slice(int _4888,int _4889) ;
virtual monty::rc_ptr< ::mosek::fusion::Expression > __mosek_2fusion_2Expression__slice(int _4888,int _4889) { return __mosek_2fusion_2BaseExpression__slice(_4888,_4889); }
virtual long long getSize() ;
virtual int getND() ;
virtual int getDim(int _4890) ;
virtual std::shared_ptr< monty::ndarray< int,1 > > getShape() ;
}; // struct BaseExpression;

struct p_ExprConst : public ::mosek::fusion::p_BaseExpression
{
ExprConst * _pubthis;
static mosek::fusion::p_ExprConst* _get_impl(mosek::fusion::ExprConst * _inst){ return static_cast< mosek::fusion::p_ExprConst* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprConst * _get_impl(mosek::fusion::ExprConst::t _inst) { return _get_impl(_inst.get()); }
p_ExprConst(ExprConst * _pubthis);
virtual ~p_ExprConst() { /* std::cout << "~p_ExprConst" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > sparsity{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};virtual void destroy();
static ExprConst::t _new_ExprConst(std::shared_ptr< monty::ndarray< int,1 > > _2686,std::shared_ptr< monty::ndarray< long long,1 > > _2687,std::shared_ptr< monty::ndarray< double,1 > > _2688);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2686,std::shared_ptr< monty::ndarray< long long,1 > > _2687,std::shared_ptr< monty::ndarray< double,1 > > _2688);
static ExprConst::t _new_ExprConst(std::shared_ptr< monty::ndarray< int,1 > > _2689,std::shared_ptr< monty::ndarray< long long,1 > > _2690,double _2691);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2689,std::shared_ptr< monty::ndarray< long long,1 > > _2690,double _2691);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2694,monty::rc_ptr< ::mosek::fusion::WorkStack > _2695,monty::rc_ptr< ::mosek::fusion::WorkStack > _2696) ;
static  void validate(std::shared_ptr< monty::ndarray< int,1 > > _2710,std::shared_ptr< monty::ndarray< double,1 > > _2711,std::shared_ptr< monty::ndarray< long long,1 > > _2712);
virtual /* override */ std::string toString() ;
}; // struct ExprConst;

struct p_ExprPick : public ::mosek::fusion::p_BaseExpression
{
ExprPick * _pubthis;
static mosek::fusion::p_ExprPick* _get_impl(mosek::fusion::ExprPick * _inst){ return static_cast< mosek::fusion::p_ExprPick* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprPick * _get_impl(mosek::fusion::ExprPick::t _inst) { return _get_impl(_inst.get()); }
p_ExprPick(ExprPick * _pubthis);
virtual ~p_ExprPick() { /* std::cout << "~p_ExprPick" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > idxs{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprPick::t _new_ExprPick(monty::rc_ptr< ::mosek::fusion::Expression > _2715,std::shared_ptr< monty::ndarray< int,2 > > _2716);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _2715,std::shared_ptr< monty::ndarray< int,2 > > _2716);
static ExprPick::t _new_ExprPick(monty::rc_ptr< ::mosek::fusion::Expression > _2727,std::shared_ptr< monty::ndarray< long long,1 > > _2728);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _2727,std::shared_ptr< monty::ndarray< long long,1 > > _2728);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2732,monty::rc_ptr< ::mosek::fusion::WorkStack > _2733,monty::rc_ptr< ::mosek::fusion::WorkStack > _2734) ;
virtual /* override */ std::string toString() ;
}; // struct ExprPick;

struct p_ExprSlice : public ::mosek::fusion::p_BaseExpression
{
ExprSlice * _pubthis;
static mosek::fusion::p_ExprSlice* _get_impl(mosek::fusion::ExprSlice * _inst){ return static_cast< mosek::fusion::p_ExprSlice* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprSlice * _get_impl(mosek::fusion::ExprSlice::t _inst) { return _get_impl(_inst.get()); }
p_ExprSlice(ExprSlice * _pubthis);
virtual ~p_ExprSlice() { /* std::cout << "~p_ExprSlice" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > last{};std::shared_ptr< monty::ndarray< int,1 > > first{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprSlice::t _new_ExprSlice(monty::rc_ptr< ::mosek::fusion::Expression > _2786,std::shared_ptr< monty::ndarray< int,1 > > _2787,std::shared_ptr< monty::ndarray< int,1 > > _2788);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _2786,std::shared_ptr< monty::ndarray< int,1 > > _2787,std::shared_ptr< monty::ndarray< int,1 > > _2788);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2789,monty::rc_ptr< ::mosek::fusion::WorkStack > _2790,monty::rc_ptr< ::mosek::fusion::WorkStack > _2791) ;
static  std::shared_ptr< monty::ndarray< int,1 > > makeShape(std::shared_ptr< monty::ndarray< int,1 > > _2845,std::shared_ptr< monty::ndarray< int,1 > > _2846,std::shared_ptr< monty::ndarray< int,1 > > _2847);
virtual /* override */ std::string toString() ;
}; // struct ExprSlice;

struct p_ExprPermuteDims : public ::mosek::fusion::p_BaseExpression
{
ExprPermuteDims * _pubthis;
static mosek::fusion::p_ExprPermuteDims* _get_impl(mosek::fusion::ExprPermuteDims * _inst){ return static_cast< mosek::fusion::p_ExprPermuteDims* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprPermuteDims * _get_impl(mosek::fusion::ExprPermuteDims::t _inst) { return _get_impl(_inst.get()); }
p_ExprPermuteDims(ExprPermuteDims * _pubthis);
virtual ~p_ExprPermuteDims() { /* std::cout << "~p_ExprPermuteDims" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > dperm{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprPermuteDims::t _new_ExprPermuteDims(std::shared_ptr< monty::ndarray< int,1 > > _2852,monty::rc_ptr< ::mosek::fusion::Expression > _2853);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2852,monty::rc_ptr< ::mosek::fusion::Expression > _2853);
static ExprPermuteDims::t _new_ExprPermuteDims(std::shared_ptr< monty::ndarray< int,1 > > _2859,monty::rc_ptr< ::mosek::fusion::Expression > _2860,int _2861);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _2859,monty::rc_ptr< ::mosek::fusion::Expression > _2860,int _2861);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2862,monty::rc_ptr< ::mosek::fusion::WorkStack > _2863,monty::rc_ptr< ::mosek::fusion::WorkStack > _2864) ;
static  std::shared_ptr< monty::ndarray< int,1 > > computeshape(std::shared_ptr< monty::ndarray< int,1 > > _2916,std::shared_ptr< monty::ndarray< int,1 > > _2917);
}; // struct ExprPermuteDims;

struct p_ExprTranspose : public ::mosek::fusion::p_BaseExpression
{
ExprTranspose * _pubthis;
static mosek::fusion::p_ExprTranspose* _get_impl(mosek::fusion::ExprTranspose * _inst){ return static_cast< mosek::fusion::p_ExprTranspose* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprTranspose * _get_impl(mosek::fusion::ExprTranspose::t _inst) { return _get_impl(_inst.get()); }
p_ExprTranspose(ExprTranspose * _pubthis);
virtual ~p_ExprTranspose() { /* std::cout << "~p_ExprTranspose" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprTranspose::t _new_ExprTranspose(monty::rc_ptr< ::mosek::fusion::Expression > _2919);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _2919);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2920,monty::rc_ptr< ::mosek::fusion::WorkStack > _2921,monty::rc_ptr< ::mosek::fusion::WorkStack > _2922) ;
virtual /* override */ std::string toString() ;
static  std::shared_ptr< monty::ndarray< int,1 > > transposeShape(std::shared_ptr< monty::ndarray< int,1 > > _2966);
}; // struct ExprTranspose;

struct p_ExprStack : public ::mosek::fusion::p_BaseExpression
{
ExprStack * _pubthis;
static mosek::fusion::p_ExprStack* _get_impl(mosek::fusion::ExprStack * _inst){ return static_cast< mosek::fusion::p_ExprStack* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprStack * _get_impl(mosek::fusion::ExprStack::t _inst) { return _get_impl(_inst.get()); }
p_ExprStack(ExprStack * _pubthis);
virtual ~p_ExprStack() { /* std::cout << "~p_ExprStack" << std::endl;*/ };
int dim{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > exprs{};virtual void destroy();
static ExprStack::t _new_ExprStack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _2967,int _2968);
void _initialize(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _2967,int _2968);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _2970,monty::rc_ptr< ::mosek::fusion::WorkStack > _2971,monty::rc_ptr< ::mosek::fusion::WorkStack > _2972) ;
static  std::shared_ptr< monty::ndarray< int,1 > > getshape(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _3120,int _3121);
virtual /* override */ std::string toString() ;
}; // struct ExprStack;

struct p_ExprInner : public ::mosek::fusion::p_BaseExpression
{
ExprInner * _pubthis;
static mosek::fusion::p_ExprInner* _get_impl(mosek::fusion::ExprInner * _inst){ return static_cast< mosek::fusion::p_ExprInner* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprInner * _get_impl(mosek::fusion::ExprInner::t _inst) { return _get_impl(_inst.get()); }
p_ExprInner(ExprInner * _pubthis);
virtual ~p_ExprInner() { /* std::cout << "~p_ExprInner" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > vcof{};std::shared_ptr< monty::ndarray< long long,1 > > vsub{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprInner::t _new_ExprInner(monty::rc_ptr< ::mosek::fusion::Expression > _3135,std::shared_ptr< monty::ndarray< long long,1 > > _3136,std::shared_ptr< monty::ndarray< double,1 > > _3137);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _3135,std::shared_ptr< monty::ndarray< long long,1 > > _3136,std::shared_ptr< monty::ndarray< double,1 > > _3137);
static ExprInner::t _new_ExprInner(monty::rc_ptr< ::mosek::fusion::Expression > _3141,std::shared_ptr< monty::ndarray< double,1 > > _3142);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _3141,std::shared_ptr< monty::ndarray< double,1 > > _3142);
static ExprInner::t _new_ExprInner(monty::rc_ptr< ::mosek::fusion::Expression > _3144,std::shared_ptr< monty::ndarray< int,2 > > _3145,std::shared_ptr< monty::ndarray< double,1 > > _3146);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _3144,std::shared_ptr< monty::ndarray< int,2 > > _3145,std::shared_ptr< monty::ndarray< double,1 > > _3146);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3147,monty::rc_ptr< ::mosek::fusion::WorkStack > _3148,monty::rc_ptr< ::mosek::fusion::WorkStack > _3149) ;
static  std::shared_ptr< monty::ndarray< long long,1 > > range(int _3185);
static  std::shared_ptr< monty::ndarray< long long,1 > > convert(std::shared_ptr< monty::ndarray< int,1 > > _3187,std::shared_ptr< monty::ndarray< int,2 > > _3188);
virtual /* override */ std::string toString() ;
}; // struct ExprInner;

struct p_ExprMulDiagRight : public ::mosek::fusion::p_BaseExpression
{
ExprMulDiagRight * _pubthis;
static mosek::fusion::p_ExprMulDiagRight* _get_impl(mosek::fusion::ExprMulDiagRight * _inst){ return static_cast< mosek::fusion::p_ExprMulDiagRight* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulDiagRight * _get_impl(mosek::fusion::ExprMulDiagRight::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulDiagRight(ExprMulDiagRight * _pubthis);
virtual ~p_ExprMulDiagRight() { /* std::cout << "~p_ExprMulDiagRight" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< double,1 > > mval{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdim1{};int mdim0{};virtual void destroy();
static ExprMulDiagRight::t _new_ExprMulDiagRight(int _3195,int _3196,std::shared_ptr< monty::ndarray< int,1 > > _3197,std::shared_ptr< monty::ndarray< int,1 > > _3198,std::shared_ptr< monty::ndarray< double,1 > > _3199,monty::rc_ptr< ::mosek::fusion::Expression > _3200,int _3201);
void _initialize(int _3195,int _3196,std::shared_ptr< monty::ndarray< int,1 > > _3197,std::shared_ptr< monty::ndarray< int,1 > > _3198,std::shared_ptr< monty::ndarray< double,1 > > _3199,monty::rc_ptr< ::mosek::fusion::Expression > _3200,int _3201);
static ExprMulDiagRight::t _new_ExprMulDiagRight(int _3202,int _3203,std::shared_ptr< monty::ndarray< int,1 > > _3204,std::shared_ptr< monty::ndarray< int,1 > > _3205,std::shared_ptr< monty::ndarray< double,1 > > _3206,monty::rc_ptr< ::mosek::fusion::Expression > _3207);
void _initialize(int _3202,int _3203,std::shared_ptr< monty::ndarray< int,1 > > _3204,std::shared_ptr< monty::ndarray< int,1 > > _3205,std::shared_ptr< monty::ndarray< double,1 > > _3206,monty::rc_ptr< ::mosek::fusion::Expression > _3207);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3208,monty::rc_ptr< ::mosek::fusion::WorkStack > _3209,monty::rc_ptr< ::mosek::fusion::WorkStack > _3210) ;
static  int validate(int _3302,int _3303,std::shared_ptr< monty::ndarray< int,1 > > _3304,std::shared_ptr< monty::ndarray< int,1 > > _3305,std::shared_ptr< monty::ndarray< double,1 > > _3306,monty::rc_ptr< ::mosek::fusion::Expression > _3307);
virtual /* override */ std::string toString() ;
}; // struct ExprMulDiagRight;

struct p_ExprMulDiagLeft : public ::mosek::fusion::p_BaseExpression
{
ExprMulDiagLeft * _pubthis;
static mosek::fusion::p_ExprMulDiagLeft* _get_impl(mosek::fusion::ExprMulDiagLeft * _inst){ return static_cast< mosek::fusion::p_ExprMulDiagLeft* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulDiagLeft * _get_impl(mosek::fusion::ExprMulDiagLeft::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulDiagLeft(ExprMulDiagLeft * _pubthis);
virtual ~p_ExprMulDiagLeft() { /* std::cout << "~p_ExprMulDiagLeft" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< double,1 > > mval{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdim1{};int mdim0{};virtual void destroy();
static ExprMulDiagLeft::t _new_ExprMulDiagLeft(int _3315,int _3316,std::shared_ptr< monty::ndarray< int,1 > > _3317,std::shared_ptr< monty::ndarray< int,1 > > _3318,std::shared_ptr< monty::ndarray< double,1 > > _3319,monty::rc_ptr< ::mosek::fusion::Expression > _3320,int _3321);
void _initialize(int _3315,int _3316,std::shared_ptr< monty::ndarray< int,1 > > _3317,std::shared_ptr< monty::ndarray< int,1 > > _3318,std::shared_ptr< monty::ndarray< double,1 > > _3319,monty::rc_ptr< ::mosek::fusion::Expression > _3320,int _3321);
static ExprMulDiagLeft::t _new_ExprMulDiagLeft(int _3322,int _3323,std::shared_ptr< monty::ndarray< int,1 > > _3324,std::shared_ptr< monty::ndarray< int,1 > > _3325,std::shared_ptr< monty::ndarray< double,1 > > _3326,monty::rc_ptr< ::mosek::fusion::Expression > _3327);
void _initialize(int _3322,int _3323,std::shared_ptr< monty::ndarray< int,1 > > _3324,std::shared_ptr< monty::ndarray< int,1 > > _3325,std::shared_ptr< monty::ndarray< double,1 > > _3326,monty::rc_ptr< ::mosek::fusion::Expression > _3327);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3328,monty::rc_ptr< ::mosek::fusion::WorkStack > _3329,monty::rc_ptr< ::mosek::fusion::WorkStack > _3330) ;
static  int validate(int _3415,int _3416,std::shared_ptr< monty::ndarray< int,1 > > _3417,std::shared_ptr< monty::ndarray< int,1 > > _3418,std::shared_ptr< monty::ndarray< double,1 > > _3419,monty::rc_ptr< ::mosek::fusion::Expression > _3420);
virtual /* override */ std::string toString() ;
}; // struct ExprMulDiagLeft;

struct p_ExprMulElement : public ::mosek::fusion::p_BaseExpression
{
ExprMulElement * _pubthis;
static mosek::fusion::p_ExprMulElement* _get_impl(mosek::fusion::ExprMulElement * _inst){ return static_cast< mosek::fusion::p_ExprMulElement* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulElement * _get_impl(mosek::fusion::ExprMulElement::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulElement(ExprMulElement * _pubthis);
virtual ~p_ExprMulElement() { /* std::cout << "~p_ExprMulElement" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< long long,1 > > msp{};std::shared_ptr< monty::ndarray< double,1 > > mcof{};virtual void destroy();
static ExprMulElement::t _new_ExprMulElement(std::shared_ptr< monty::ndarray< double,1 > > _3428,std::shared_ptr< monty::ndarray< long long,1 > > _3429,monty::rc_ptr< ::mosek::fusion::Expression > _3430);
void _initialize(std::shared_ptr< monty::ndarray< double,1 > > _3428,std::shared_ptr< monty::ndarray< long long,1 > > _3429,monty::rc_ptr< ::mosek::fusion::Expression > _3430);
static ExprMulElement::t _new_ExprMulElement(std::shared_ptr< monty::ndarray< double,1 > > _3435,std::shared_ptr< monty::ndarray< long long,1 > > _3436,monty::rc_ptr< ::mosek::fusion::Expression > _3437,int _3438);
void _initialize(std::shared_ptr< monty::ndarray< double,1 > > _3435,std::shared_ptr< monty::ndarray< long long,1 > > _3436,monty::rc_ptr< ::mosek::fusion::Expression > _3437,int _3438);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3439,monty::rc_ptr< ::mosek::fusion::WorkStack > _3440,monty::rc_ptr< ::mosek::fusion::WorkStack > _3441) ;
virtual /* override */ std::string toString() ;
}; // struct ExprMulElement;

struct p_ExprMulScalarConst : public ::mosek::fusion::p_BaseExpression
{
ExprMulScalarConst * _pubthis;
static mosek::fusion::p_ExprMulScalarConst* _get_impl(mosek::fusion::ExprMulScalarConst * _inst){ return static_cast< mosek::fusion::p_ExprMulScalarConst* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulScalarConst * _get_impl(mosek::fusion::ExprMulScalarConst::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulScalarConst(ExprMulScalarConst * _pubthis);
virtual ~p_ExprMulScalarConst() { /* std::cout << "~p_ExprMulScalarConst" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};double c{};virtual void destroy();
static ExprMulScalarConst::t _new_ExprMulScalarConst(double _3488,monty::rc_ptr< ::mosek::fusion::Expression > _3489);
void _initialize(double _3488,monty::rc_ptr< ::mosek::fusion::Expression > _3489);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3490,monty::rc_ptr< ::mosek::fusion::WorkStack > _3491,monty::rc_ptr< ::mosek::fusion::WorkStack > _3492) ;
virtual /* override */ std::string toString() ;
}; // struct ExprMulScalarConst;

struct p_ExprScalarMul : public ::mosek::fusion::p_BaseExpression
{
ExprScalarMul * _pubthis;
static mosek::fusion::p_ExprScalarMul* _get_impl(mosek::fusion::ExprScalarMul * _inst){ return static_cast< mosek::fusion::p_ExprScalarMul* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprScalarMul * _get_impl(mosek::fusion::ExprScalarMul::t _inst) { return _get_impl(_inst.get()); }
p_ExprScalarMul(ExprScalarMul * _pubthis);
virtual ~p_ExprScalarMul() { /* std::cout << "~p_ExprScalarMul" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< double,1 > > mval{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdim1{};int mdim0{};virtual void destroy();
static ExprScalarMul::t _new_ExprScalarMul(int _3500,int _3501,std::shared_ptr< monty::ndarray< int,1 > > _3502,std::shared_ptr< monty::ndarray< int,1 > > _3503,std::shared_ptr< monty::ndarray< double,1 > > _3504,monty::rc_ptr< ::mosek::fusion::Expression > _3505,int _3506);
void _initialize(int _3500,int _3501,std::shared_ptr< monty::ndarray< int,1 > > _3502,std::shared_ptr< monty::ndarray< int,1 > > _3503,std::shared_ptr< monty::ndarray< double,1 > > _3504,monty::rc_ptr< ::mosek::fusion::Expression > _3505,int _3506);
static ExprScalarMul::t _new_ExprScalarMul(int _3507,int _3508,std::shared_ptr< monty::ndarray< int,1 > > _3509,std::shared_ptr< monty::ndarray< int,1 > > _3510,std::shared_ptr< monty::ndarray< double,1 > > _3511,monty::rc_ptr< ::mosek::fusion::Expression > _3512);
void _initialize(int _3507,int _3508,std::shared_ptr< monty::ndarray< int,1 > > _3509,std::shared_ptr< monty::ndarray< int,1 > > _3510,std::shared_ptr< monty::ndarray< double,1 > > _3511,monty::rc_ptr< ::mosek::fusion::Expression > _3512);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3513,monty::rc_ptr< ::mosek::fusion::WorkStack > _3514,monty::rc_ptr< ::mosek::fusion::WorkStack > _3515) ;
static  int validate(int _3540,int _3541,std::shared_ptr< monty::ndarray< int,1 > > _3542,std::shared_ptr< monty::ndarray< int,1 > > _3543,std::shared_ptr< monty::ndarray< double,1 > > _3544,monty::rc_ptr< ::mosek::fusion::Expression > _3545);
virtual /* override */ std::string toString() ;
}; // struct ExprScalarMul;

struct p_ExprMulRight : public ::mosek::fusion::p_BaseExpression
{
ExprMulRight * _pubthis;
static mosek::fusion::p_ExprMulRight* _get_impl(mosek::fusion::ExprMulRight * _inst){ return static_cast< mosek::fusion::p_ExprMulRight* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulRight * _get_impl(mosek::fusion::ExprMulRight::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulRight(ExprMulRight * _pubthis);
virtual ~p_ExprMulRight() { /* std::cout << "~p_ExprMulRight" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< double,1 > > mval{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdim1{};int mdim0{};virtual void destroy();
static ExprMulRight::t _new_ExprMulRight(int _3551,int _3552,std::shared_ptr< monty::ndarray< int,1 > > _3553,std::shared_ptr< monty::ndarray< int,1 > > _3554,std::shared_ptr< monty::ndarray< double,1 > > _3555,monty::rc_ptr< ::mosek::fusion::Expression > _3556,int _3557);
void _initialize(int _3551,int _3552,std::shared_ptr< monty::ndarray< int,1 > > _3553,std::shared_ptr< monty::ndarray< int,1 > > _3554,std::shared_ptr< monty::ndarray< double,1 > > _3555,monty::rc_ptr< ::mosek::fusion::Expression > _3556,int _3557);
static ExprMulRight::t _new_ExprMulRight(int _3558,int _3559,std::shared_ptr< monty::ndarray< int,1 > > _3560,std::shared_ptr< monty::ndarray< int,1 > > _3561,std::shared_ptr< monty::ndarray< double,1 > > _3562,monty::rc_ptr< ::mosek::fusion::Expression > _3563);
void _initialize(int _3558,int _3559,std::shared_ptr< monty::ndarray< int,1 > > _3560,std::shared_ptr< monty::ndarray< int,1 > > _3561,std::shared_ptr< monty::ndarray< double,1 > > _3562,monty::rc_ptr< ::mosek::fusion::Expression > _3563);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3564,monty::rc_ptr< ::mosek::fusion::WorkStack > _3565,monty::rc_ptr< ::mosek::fusion::WorkStack > _3566) ;
static  std::shared_ptr< monty::ndarray< int,1 > > computeshape(int _3716,std::shared_ptr< monty::ndarray< int,1 > > _3717);
static  int validate(int _3718,int _3719,std::shared_ptr< monty::ndarray< int,1 > > _3720,std::shared_ptr< monty::ndarray< int,1 > > _3721,std::shared_ptr< monty::ndarray< double,1 > > _3722,monty::rc_ptr< ::mosek::fusion::Expression > _3723);
virtual /* override */ std::string toString() ;
}; // struct ExprMulRight;

struct p_ExprMulLeft : public ::mosek::fusion::p_BaseExpression
{
ExprMulLeft * _pubthis;
static mosek::fusion::p_ExprMulLeft* _get_impl(mosek::fusion::ExprMulLeft * _inst){ return static_cast< mosek::fusion::p_ExprMulLeft* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulLeft * _get_impl(mosek::fusion::ExprMulLeft::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulLeft(ExprMulLeft * _pubthis);
virtual ~p_ExprMulLeft() { /* std::cout << "~p_ExprMulLeft" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};std::shared_ptr< monty::ndarray< double,1 > > mval{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdim1{};int mdim0{};virtual void destroy();
static ExprMulLeft::t _new_ExprMulLeft(int _3732,int _3733,std::shared_ptr< monty::ndarray< int,1 > > _3734,std::shared_ptr< monty::ndarray< int,1 > > _3735,std::shared_ptr< monty::ndarray< double,1 > > _3736,monty::rc_ptr< ::mosek::fusion::Expression > _3737,int _3738);
void _initialize(int _3732,int _3733,std::shared_ptr< monty::ndarray< int,1 > > _3734,std::shared_ptr< monty::ndarray< int,1 > > _3735,std::shared_ptr< monty::ndarray< double,1 > > _3736,monty::rc_ptr< ::mosek::fusion::Expression > _3737,int _3738);
static ExprMulLeft::t _new_ExprMulLeft(int _3739,int _3740,std::shared_ptr< monty::ndarray< int,1 > > _3741,std::shared_ptr< monty::ndarray< int,1 > > _3742,std::shared_ptr< monty::ndarray< double,1 > > _3743,monty::rc_ptr< ::mosek::fusion::Expression > _3744);
void _initialize(int _3739,int _3740,std::shared_ptr< monty::ndarray< int,1 > > _3741,std::shared_ptr< monty::ndarray< int,1 > > _3742,std::shared_ptr< monty::ndarray< double,1 > > _3743,monty::rc_ptr< ::mosek::fusion::Expression > _3744);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3745,monty::rc_ptr< ::mosek::fusion::WorkStack > _3746,monty::rc_ptr< ::mosek::fusion::WorkStack > _3747) ;
static  std::shared_ptr< monty::ndarray< int,1 > > computeshape(int _3845,int _3846,std::shared_ptr< monty::ndarray< int,1 > > _3847);
static  int validate(int _3848,int _3849,std::shared_ptr< monty::ndarray< int,1 > > _3850,std::shared_ptr< monty::ndarray< int,1 > > _3851,std::shared_ptr< monty::ndarray< double,1 > > _3852,monty::rc_ptr< ::mosek::fusion::Expression > _3853);
virtual /* override */ std::string toString() ;
}; // struct ExprMulLeft;

struct p_ExprMulVar : public ::mosek::fusion::p_BaseExpression
{
ExprMulVar * _pubthis;
static mosek::fusion::p_ExprMulVar* _get_impl(mosek::fusion::ExprMulVar * _inst){ return static_cast< mosek::fusion::p_ExprMulVar* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulVar * _get_impl(mosek::fusion::ExprMulVar::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulVar(ExprMulVar * _pubthis);
virtual ~p_ExprMulVar() { /* std::cout << "~p_ExprMulVar" << std::endl;*/ };
bool left{};monty::rc_ptr< ::mosek::fusion::Variable > x{};std::shared_ptr< monty::ndarray< double,1 > > mcof{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdimj{};int mdimi{};virtual void destroy();
static ExprMulVar::t _new_ExprMulVar(bool _3862,int _3863,int _3864,std::shared_ptr< monty::ndarray< int,1 > > _3865,std::shared_ptr< monty::ndarray< int,1 > > _3866,std::shared_ptr< monty::ndarray< double,1 > > _3867,monty::rc_ptr< ::mosek::fusion::Variable > _3868);
void _initialize(bool _3862,int _3863,int _3864,std::shared_ptr< monty::ndarray< int,1 > > _3865,std::shared_ptr< monty::ndarray< int,1 > > _3866,std::shared_ptr< monty::ndarray< double,1 > > _3867,monty::rc_ptr< ::mosek::fusion::Variable > _3868);
static ExprMulVar::t _new_ExprMulVar(bool _3871,int _3872,int _3873,std::shared_ptr< monty::ndarray< int,1 > > _3874,std::shared_ptr< monty::ndarray< int,1 > > _3875,std::shared_ptr< monty::ndarray< double,1 > > _3876,monty::rc_ptr< ::mosek::fusion::Variable > _3877,int _3878);
void _initialize(bool _3871,int _3872,int _3873,std::shared_ptr< monty::ndarray< int,1 > > _3874,std::shared_ptr< monty::ndarray< int,1 > > _3875,std::shared_ptr< monty::ndarray< double,1 > > _3876,monty::rc_ptr< ::mosek::fusion::Variable > _3877,int _3878);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _3879,monty::rc_ptr< ::mosek::fusion::WorkStack > _3880,monty::rc_ptr< ::mosek::fusion::WorkStack > _3881) ;
virtual void eval_right(monty::rc_ptr< ::mosek::fusion::WorkStack > _3882,monty::rc_ptr< ::mosek::fusion::WorkStack > _3883,monty::rc_ptr< ::mosek::fusion::WorkStack > _3884) ;
virtual void eval_left(monty::rc_ptr< ::mosek::fusion::WorkStack > _3990,monty::rc_ptr< ::mosek::fusion::WorkStack > _3991,monty::rc_ptr< ::mosek::fusion::WorkStack > _3992) ;
virtual void validate(int _4058,int _4059,std::shared_ptr< monty::ndarray< int,1 > > _4060,std::shared_ptr< monty::ndarray< int,1 > > _4061,std::shared_ptr< monty::ndarray< double,1 > > _4062) ;
static  std::shared_ptr< monty::ndarray< int,1 > > resshape(int _4066,int _4067,std::shared_ptr< monty::ndarray< int,1 > > _4068,bool _4069);
virtual /* override */ std::string toString() ;
}; // struct ExprMulVar;

struct p_ExprMulScalarVar : public ::mosek::fusion::p_BaseExpression
{
ExprMulScalarVar * _pubthis;
static mosek::fusion::p_ExprMulScalarVar* _get_impl(mosek::fusion::ExprMulScalarVar * _inst){ return static_cast< mosek::fusion::p_ExprMulScalarVar* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulScalarVar * _get_impl(mosek::fusion::ExprMulScalarVar::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulScalarVar(ExprMulScalarVar * _pubthis);
virtual ~p_ExprMulScalarVar() { /* std::cout << "~p_ExprMulScalarVar" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Variable > x{};std::shared_ptr< monty::ndarray< double,1 > > mcof{};std::shared_ptr< monty::ndarray< int,1 > > msubj{};std::shared_ptr< monty::ndarray< int,1 > > msubi{};int mdimj{};int mdimi{};virtual void destroy();
static ExprMulScalarVar::t _new_ExprMulScalarVar(int _4070,int _4071,std::shared_ptr< monty::ndarray< int,1 > > _4072,std::shared_ptr< monty::ndarray< int,1 > > _4073,std::shared_ptr< monty::ndarray< double,1 > > _4074,monty::rc_ptr< ::mosek::fusion::Variable > _4075);
void _initialize(int _4070,int _4071,std::shared_ptr< monty::ndarray< int,1 > > _4072,std::shared_ptr< monty::ndarray< int,1 > > _4073,std::shared_ptr< monty::ndarray< double,1 > > _4074,monty::rc_ptr< ::mosek::fusion::Variable > _4075);
static ExprMulScalarVar::t _new_ExprMulScalarVar(int _4078,int _4079,std::shared_ptr< monty::ndarray< int,1 > > _4080,std::shared_ptr< monty::ndarray< int,1 > > _4081,std::shared_ptr< monty::ndarray< double,1 > > _4082,monty::rc_ptr< ::mosek::fusion::Variable > _4083,int _4084);
void _initialize(int _4078,int _4079,std::shared_ptr< monty::ndarray< int,1 > > _4080,std::shared_ptr< monty::ndarray< int,1 > > _4081,std::shared_ptr< monty::ndarray< double,1 > > _4082,monty::rc_ptr< ::mosek::fusion::Variable > _4083,int _4084);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4085,monty::rc_ptr< ::mosek::fusion::WorkStack > _4086,monty::rc_ptr< ::mosek::fusion::WorkStack > _4087) ;
virtual /* override */ std::string toString() ;
}; // struct ExprMulScalarVar;

struct p_ExprMulVarScalarConst : public ::mosek::fusion::p_BaseExpression
{
ExprMulVarScalarConst * _pubthis;
static mosek::fusion::p_ExprMulVarScalarConst* _get_impl(mosek::fusion::ExprMulVarScalarConst * _inst){ return static_cast< mosek::fusion::p_ExprMulVarScalarConst* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprMulVarScalarConst * _get_impl(mosek::fusion::ExprMulVarScalarConst::t _inst) { return _get_impl(_inst.get()); }
p_ExprMulVarScalarConst(ExprMulVarScalarConst * _pubthis);
virtual ~p_ExprMulVarScalarConst() { /* std::cout << "~p_ExprMulVarScalarConst" << std::endl;*/ };
double c{};monty::rc_ptr< ::mosek::fusion::Variable > x{};virtual void destroy();
static ExprMulVarScalarConst::t _new_ExprMulVarScalarConst(monty::rc_ptr< ::mosek::fusion::Variable > _4106,double _4107);
void _initialize(monty::rc_ptr< ::mosek::fusion::Variable > _4106,double _4107);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4108,monty::rc_ptr< ::mosek::fusion::WorkStack > _4109,monty::rc_ptr< ::mosek::fusion::WorkStack > _4110) ;
virtual /* override */ std::string toString() ;
}; // struct ExprMulVarScalarConst;

struct p_ExprAdd : public ::mosek::fusion::p_BaseExpression
{
ExprAdd * _pubthis;
static mosek::fusion::p_ExprAdd* _get_impl(mosek::fusion::ExprAdd * _inst){ return static_cast< mosek::fusion::p_ExprAdd* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprAdd * _get_impl(mosek::fusion::ExprAdd::t _inst) { return _get_impl(_inst.get()); }
p_ExprAdd(ExprAdd * _pubthis);
virtual ~p_ExprAdd() { /* std::cout << "~p_ExprAdd" << std::endl;*/ };
double m2{};double m1{};monty::rc_ptr< ::mosek::fusion::Expression > e2{};monty::rc_ptr< ::mosek::fusion::Expression > e1{};virtual void destroy();
static ExprAdd::t _new_ExprAdd(monty::rc_ptr< ::mosek::fusion::Expression > _4128,monty::rc_ptr< ::mosek::fusion::Expression > _4129,double _4130,double _4131);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4128,monty::rc_ptr< ::mosek::fusion::Expression > _4129,double _4130,double _4131);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4133,monty::rc_ptr< ::mosek::fusion::WorkStack > _4134,monty::rc_ptr< ::mosek::fusion::WorkStack > _4135) ;
virtual /* override */ std::string toString() ;
}; // struct ExprAdd;

struct p_ExprWSum : public ::mosek::fusion::p_BaseExpression
{
ExprWSum * _pubthis;
static mosek::fusion::p_ExprWSum* _get_impl(mosek::fusion::ExprWSum * _inst){ return static_cast< mosek::fusion::p_ExprWSum* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprWSum * _get_impl(mosek::fusion::ExprWSum::t _inst) { return _get_impl(_inst.get()); }
p_ExprWSum(ExprWSum * _pubthis);
virtual ~p_ExprWSum() { /* std::cout << "~p_ExprWSum" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > w{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > es{};virtual void destroy();
static ExprWSum::t _new_ExprWSum(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _4245,std::shared_ptr< monty::ndarray< double,1 > > _4246);
void _initialize(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _4245,std::shared_ptr< monty::ndarray< double,1 > > _4246);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4253,monty::rc_ptr< ::mosek::fusion::WorkStack > _4254,monty::rc_ptr< ::mosek::fusion::WorkStack > _4255) ;
virtual /* override */ std::string toString() ;
}; // struct ExprWSum;

struct p_ExprSumReduce : public ::mosek::fusion::p_BaseExpression
{
ExprSumReduce * _pubthis;
static mosek::fusion::p_ExprSumReduce* _get_impl(mosek::fusion::ExprSumReduce * _inst){ return static_cast< mosek::fusion::p_ExprSumReduce* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprSumReduce * _get_impl(mosek::fusion::ExprSumReduce::t _inst) { return _get_impl(_inst.get()); }
p_ExprSumReduce(ExprSumReduce * _pubthis);
virtual ~p_ExprSumReduce() { /* std::cout << "~p_ExprSumReduce" << std::endl;*/ };
int dim{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprSumReduce::t _new_ExprSumReduce(int _4322,monty::rc_ptr< ::mosek::fusion::Expression > _4323);
void _initialize(int _4322,monty::rc_ptr< ::mosek::fusion::Expression > _4323);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4325,monty::rc_ptr< ::mosek::fusion::WorkStack > _4326,monty::rc_ptr< ::mosek::fusion::WorkStack > _4327) ;
static  std::shared_ptr< monty::ndarray< int,1 > > computeShape(int _4431,std::shared_ptr< monty::ndarray< int,1 > > _4432);
virtual /* override */ std::string toString() ;
}; // struct ExprSumReduce;

struct p_ExprDenseTril : public ::mosek::fusion::p_BaseExpression
{
ExprDenseTril * _pubthis;
static mosek::fusion::p_ExprDenseTril* _get_impl(mosek::fusion::ExprDenseTril * _inst){ return static_cast< mosek::fusion::p_ExprDenseTril* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprDenseTril * _get_impl(mosek::fusion::ExprDenseTril::t _inst) { return _get_impl(_inst.get()); }
p_ExprDenseTril(ExprDenseTril * _pubthis);
virtual ~p_ExprDenseTril() { /* std::cout << "~p_ExprDenseTril" << std::endl;*/ };
int dim1{};int dim0{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprDenseTril::t _new_ExprDenseTril(int _4436,int _4437,monty::rc_ptr< ::mosek::fusion::Expression > _4438,int _4439);
void _initialize(int _4436,int _4437,monty::rc_ptr< ::mosek::fusion::Expression > _4438,int _4439);
static ExprDenseTril::t _new_ExprDenseTril(int _4440,int _4441,monty::rc_ptr< ::mosek::fusion::Expression > _4442);
void _initialize(int _4440,int _4441,monty::rc_ptr< ::mosek::fusion::Expression > _4442);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4444,monty::rc_ptr< ::mosek::fusion::WorkStack > _4445,monty::rc_ptr< ::mosek::fusion::WorkStack > _4446) ;
}; // struct ExprDenseTril;

struct p_ExprDense : public ::mosek::fusion::p_BaseExpression
{
ExprDense * _pubthis;
static mosek::fusion::p_ExprDense* _get_impl(mosek::fusion::ExprDense * _inst){ return static_cast< mosek::fusion::p_ExprDense* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprDense * _get_impl(mosek::fusion::ExprDense::t _inst) { return _get_impl(_inst.get()); }
p_ExprDense(ExprDense * _pubthis);
virtual ~p_ExprDense() { /* std::cout << "~p_ExprDense" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprDense::t _new_ExprDense(monty::rc_ptr< ::mosek::fusion::Expression > _4519);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4519);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4520,monty::rc_ptr< ::mosek::fusion::WorkStack > _4521,monty::rc_ptr< ::mosek::fusion::WorkStack > _4522) ;
virtual /* override */ std::string toString() ;
}; // struct ExprDense;

struct p_ExprSymmetrize : public ::mosek::fusion::p_BaseExpression
{
ExprSymmetrize * _pubthis;
static mosek::fusion::p_ExprSymmetrize* _get_impl(mosek::fusion::ExprSymmetrize * _inst){ return static_cast< mosek::fusion::p_ExprSymmetrize* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprSymmetrize * _get_impl(mosek::fusion::ExprSymmetrize::t _inst) { return _get_impl(_inst.get()); }
p_ExprSymmetrize(ExprSymmetrize * _pubthis);
virtual ~p_ExprSymmetrize() { /* std::cout << "~p_ExprSymmetrize" << std::endl;*/ };
int dim1{};int dim0{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprSymmetrize::t _new_ExprSymmetrize(int _4545,int _4546,monty::rc_ptr< ::mosek::fusion::Expression > _4547,int _4548);
void _initialize(int _4545,int _4546,monty::rc_ptr< ::mosek::fusion::Expression > _4547,int _4548);
static ExprSymmetrize::t _new_ExprSymmetrize(int _4549,int _4550,monty::rc_ptr< ::mosek::fusion::Expression > _4551);
void _initialize(int _4549,int _4550,monty::rc_ptr< ::mosek::fusion::Expression > _4551);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4553,monty::rc_ptr< ::mosek::fusion::WorkStack > _4554,monty::rc_ptr< ::mosek::fusion::WorkStack > _4555) ;
}; // struct ExprSymmetrize;

struct p_ExprCompress : public ::mosek::fusion::p_BaseExpression
{
ExprCompress * _pubthis;
static mosek::fusion::p_ExprCompress* _get_impl(mosek::fusion::ExprCompress * _inst){ return static_cast< mosek::fusion::p_ExprCompress* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprCompress * _get_impl(mosek::fusion::ExprCompress::t _inst) { return _get_impl(_inst.get()); }
p_ExprCompress(ExprCompress * _pubthis);
virtual ~p_ExprCompress() { /* std::cout << "~p_ExprCompress" << std::endl;*/ };
double eps{};monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprCompress::t _new_ExprCompress(monty::rc_ptr< ::mosek::fusion::Expression > _4654);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4654);
static ExprCompress::t _new_ExprCompress(monty::rc_ptr< ::mosek::fusion::Expression > _4655,double _4656);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4655,double _4656);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4657,monty::rc_ptr< ::mosek::fusion::WorkStack > _4658,monty::rc_ptr< ::mosek::fusion::WorkStack > _4659) ;
static  void arg_sort(monty::rc_ptr< ::mosek::fusion::WorkStack > _4725,monty::rc_ptr< ::mosek::fusion::WorkStack > _4726,int _4727,int _4728,int _4729,int _4730,int _4731);
static  void merge_sort(int _4767,int _4768,int _4769,int _4770,int _4771,int _4772,std::shared_ptr< monty::ndarray< int,1 > > _4773,std::shared_ptr< monty::ndarray< long long,1 > > _4774);
virtual /* override */ std::string toString() ;
}; // struct ExprCompress;

struct p_ExprCondense : public ::mosek::fusion::p_BaseExpression
{
ExprCondense * _pubthis;
static mosek::fusion::p_ExprCondense* _get_impl(mosek::fusion::ExprCondense * _inst){ return static_cast< mosek::fusion::p_ExprCondense* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprCondense * _get_impl(mosek::fusion::ExprCondense::t _inst) { return _get_impl(_inst.get()); }
p_ExprCondense(ExprCondense * _pubthis);
virtual ~p_ExprCondense() { /* std::cout << "~p_ExprCondense" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > expr{};virtual void destroy();
static ExprCondense::t _new_ExprCondense(monty::rc_ptr< ::mosek::fusion::Expression > _4797);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4797);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4798,monty::rc_ptr< ::mosek::fusion::WorkStack > _4799,monty::rc_ptr< ::mosek::fusion::WorkStack > _4800) ;
}; // struct ExprCondense;

struct p_ExprFromVar : public ::mosek::fusion::p_BaseExpression
{
ExprFromVar * _pubthis;
static mosek::fusion::p_ExprFromVar* _get_impl(mosek::fusion::ExprFromVar * _inst){ return static_cast< mosek::fusion::p_ExprFromVar* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprFromVar * _get_impl(mosek::fusion::ExprFromVar::t _inst) { return _get_impl(_inst.get()); }
p_ExprFromVar(ExprFromVar * _pubthis);
virtual ~p_ExprFromVar() { /* std::cout << "~p_ExprFromVar" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Variable > x{};virtual void destroy();
static ExprFromVar::t _new_ExprFromVar(monty::rc_ptr< ::mosek::fusion::Variable > _4807);
void _initialize(monty::rc_ptr< ::mosek::fusion::Variable > _4807);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4808,monty::rc_ptr< ::mosek::fusion::WorkStack > _4809,monty::rc_ptr< ::mosek::fusion::WorkStack > _4810) ;
virtual /* override */ std::string toString() ;
}; // struct ExprFromVar;

struct p_ExprReshape : public ::mosek::fusion::p_BaseExpression
{
ExprReshape * _pubthis;
static mosek::fusion::p_ExprReshape* _get_impl(mosek::fusion::ExprReshape * _inst){ return static_cast< mosek::fusion::p_ExprReshape* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_ExprReshape * _get_impl(mosek::fusion::ExprReshape::t _inst) { return _get_impl(_inst.get()); }
p_ExprReshape(ExprReshape * _pubthis);
virtual ~p_ExprReshape() { /* std::cout << "~p_ExprReshape" << std::endl;*/ };
monty::rc_ptr< ::mosek::fusion::Expression > e{};virtual void destroy();
static ExprReshape::t _new_ExprReshape(std::shared_ptr< monty::ndarray< int,1 > > _4828,monty::rc_ptr< ::mosek::fusion::Expression > _4829);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _4828,monty::rc_ptr< ::mosek::fusion::Expression > _4829);
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _4831,monty::rc_ptr< ::mosek::fusion::WorkStack > _4832,monty::rc_ptr< ::mosek::fusion::WorkStack > _4833) ;
virtual /* override */ std::string toString() ;
}; // struct ExprReshape;

struct p_Expr : public ::mosek::fusion::p_BaseExpression
{
Expr * _pubthis;
static mosek::fusion::p_Expr* _get_impl(mosek::fusion::Expr * _inst){ return static_cast< mosek::fusion::p_Expr* >(mosek::fusion::p_BaseExpression::_get_impl(_inst)); }
static mosek::fusion::p_Expr * _get_impl(mosek::fusion::Expr::t _inst) { return _get_impl(_inst.get()); }
p_Expr(Expr * _pubthis);
virtual ~p_Expr() { /* std::cout << "~p_Expr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > inst{};std::shared_ptr< monty::ndarray< double,1 > > cof_v{};std::shared_ptr< monty::ndarray< long long,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};std::shared_ptr< monty::ndarray< int,1 > > shape{};virtual void destroy();
static Expr::t _new_Expr(std::shared_ptr< monty::ndarray< long long,1 > > _4968,std::shared_ptr< monty::ndarray< long long,1 > > _4969,std::shared_ptr< monty::ndarray< double,1 > > _4970,std::shared_ptr< monty::ndarray< double,1 > > _4971,std::shared_ptr< monty::ndarray< int,1 > > _4972,std::shared_ptr< monty::ndarray< long long,1 > > _4973);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _4968,std::shared_ptr< monty::ndarray< long long,1 > > _4969,std::shared_ptr< monty::ndarray< double,1 > > _4970,std::shared_ptr< monty::ndarray< double,1 > > _4971,std::shared_ptr< monty::ndarray< int,1 > > _4972,std::shared_ptr< monty::ndarray< long long,1 > > _4973);
static Expr::t _new_Expr(std::shared_ptr< monty::ndarray< long long,1 > > _4984,std::shared_ptr< monty::ndarray< long long,1 > > _4985,std::shared_ptr< monty::ndarray< double,1 > > _4986,std::shared_ptr< monty::ndarray< double,1 > > _4987,std::shared_ptr< monty::ndarray< int,1 > > _4988,std::shared_ptr< monty::ndarray< long long,1 > > _4989,int _4990);
void _initialize(std::shared_ptr< monty::ndarray< long long,1 > > _4984,std::shared_ptr< monty::ndarray< long long,1 > > _4985,std::shared_ptr< monty::ndarray< double,1 > > _4986,std::shared_ptr< monty::ndarray< double,1 > > _4987,std::shared_ptr< monty::ndarray< int,1 > > _4988,std::shared_ptr< monty::ndarray< long long,1 > > _4989,int _4990);
static Expr::t _new_Expr(monty::rc_ptr< ::mosek::fusion::Expression > _4991);
void _initialize(monty::rc_ptr< ::mosek::fusion::Expression > _4991);
virtual long long prod(std::shared_ptr< monty::ndarray< int,1 > > _5016) ;
static  std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > varstack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > >,1 > > _5019);
static  std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > varstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5022,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5023);
static  monty::rc_ptr< ::mosek::fusion::Expression > condense(monty::rc_ptr< ::mosek::fusion::Expression > _5027);
static  monty::rc_ptr< ::mosek::fusion::Expression > flatten(monty::rc_ptr< ::mosek::fusion::Expression > _5028);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _5029,int _5030,int _5031);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _5032,int _5033);
static  monty::rc_ptr< ::mosek::fusion::Expression > reshape(monty::rc_ptr< ::mosek::fusion::Expression > _5034,std::shared_ptr< monty::ndarray< int,1 > > _5035);
virtual long long size() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2Expr__eval() ;
virtual monty::rc_ptr< ::mosek::fusion::FlatExpr > __mosek_2fusion_2BaseExpression__eval() { return __mosek_2fusion_2Expr__eval(); }
static  monty::rc_ptr< ::mosek::fusion::Expression > zeros(std::shared_ptr< monty::ndarray< int,1 > > _5038);
static  monty::rc_ptr< ::mosek::fusion::Expression > zeros(int _5039);
static  monty::rc_ptr< ::mosek::fusion::Expression > ones();
static  monty::rc_ptr< ::mosek::fusion::Expression > ones(std::shared_ptr< monty::ndarray< int,1 > > _5040,std::shared_ptr< monty::ndarray< int,2 > > _5041);
static  monty::rc_ptr< ::mosek::fusion::Expression > ones(std::shared_ptr< monty::ndarray< int,1 > > _5042);
static  monty::rc_ptr< ::mosek::fusion::Expression > ones(int _5043);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5044);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(monty::rc_ptr< ::mosek::fusion::Matrix > _5045);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(double _5054);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< int,1 > > _5055,std::shared_ptr< monty::ndarray< int,2 > > _5056,double _5057);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< int,1 > > _5065,std::shared_ptr< monty::ndarray< int,2 > > _5066,std::shared_ptr< monty::ndarray< double,1 > > _5067);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< int,1 > > _5075,double _5076);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(int _5077,double _5078);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< double,2 > > _5080);
static  monty::rc_ptr< ::mosek::fusion::Expression > constTerm(std::shared_ptr< monty::ndarray< double,1 > > _5083);
virtual long long numNonzeros() ;
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Expression > _5084,int _5085);
static  monty::rc_ptr< ::mosek::fusion::Expression > sum(monty::rc_ptr< ::mosek::fusion::Expression > _5086);
static  monty::rc_ptr< ::mosek::fusion::Expression > neg(monty::rc_ptr< ::mosek::fusion::Expression > _5087);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(bool _5088,monty::rc_ptr< ::mosek::fusion::Matrix > _5089,monty::rc_ptr< ::mosek::fusion::Expression > _5090);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Variable > _5097,monty::rc_ptr< ::mosek::fusion::Matrix > _5098);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Matrix > _5099,monty::rc_ptr< ::mosek::fusion::Variable > _5100);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Expression > _5101,monty::rc_ptr< ::mosek::fusion::Matrix > _5102);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Matrix > _5103,monty::rc_ptr< ::mosek::fusion::Expression > _5104);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Variable > _5105,std::shared_ptr< monty::ndarray< double,2 > > _5106);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(monty::rc_ptr< ::mosek::fusion::Expression > _5113,std::shared_ptr< monty::ndarray< double,2 > > _5114);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(std::shared_ptr< monty::ndarray< double,2 > > _5121,monty::rc_ptr< ::mosek::fusion::Variable > _5122);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulDiag(std::shared_ptr< monty::ndarray< double,2 > > _5129,monty::rc_ptr< ::mosek::fusion::Expression > _5130);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::Matrix > _5137,monty::rc_ptr< ::mosek::fusion::Expression > _5138);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(std::shared_ptr< monty::ndarray< double,1 > > _5147,monty::rc_ptr< ::mosek::fusion::Expression > _5148);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm_(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5150,monty::rc_ptr< ::mosek::fusion::Expression > _5151);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _5154,double _5155);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(double _5156,monty::rc_ptr< ::mosek::fusion::Expression > _5157);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _5158,std::shared_ptr< monty::ndarray< double,1 > > _5159);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(std::shared_ptr< monty::ndarray< double,1 > > _5160,monty::rc_ptr< ::mosek::fusion::Expression > _5161);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _5162,std::shared_ptr< monty::ndarray< double,2 > > _5163);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(std::shared_ptr< monty::ndarray< double,2 > > _5164,monty::rc_ptr< ::mosek::fusion::Expression > _5165);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Expression > _5166,monty::rc_ptr< ::mosek::fusion::Matrix > _5167);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Matrix > _5168,monty::rc_ptr< ::mosek::fusion::Expression > _5169);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(bool _5170,std::shared_ptr< monty::ndarray< double,1 > > _5171,monty::rc_ptr< ::mosek::fusion::Expression > _5172);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(bool _5187,std::shared_ptr< monty::ndarray< double,2 > > _5188,monty::rc_ptr< ::mosek::fusion::Expression > _5189);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(bool _5204,monty::rc_ptr< ::mosek::fusion::Matrix > _5205,monty::rc_ptr< ::mosek::fusion::Expression > _5206);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Variable > _5215,monty::rc_ptr< ::mosek::fusion::Matrix > _5216);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(monty::rc_ptr< ::mosek::fusion::Matrix > _5222,monty::rc_ptr< ::mosek::fusion::Variable > _5223);
static  monty::rc_ptr< ::mosek::fusion::Expression > mul(bool _5229,int _5230,int _5231,std::shared_ptr< monty::ndarray< int,1 > > _5232,std::shared_ptr< monty::ndarray< int,1 > > _5233,std::shared_ptr< monty::ndarray< double,1 > > _5234,monty::rc_ptr< ::mosek::fusion::Variable > _5235);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _5237,monty::rc_ptr< ::mosek::fusion::Matrix > _5238);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _5246,std::shared_ptr< monty::ndarray< double,2 > > _5247);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _5251,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5252);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Expression > _5253,std::shared_ptr< monty::ndarray< double,1 > > _5254);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::Matrix > _5259,monty::rc_ptr< ::mosek::fusion::Expression > _5260);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5261,monty::rc_ptr< ::mosek::fusion::Expression > _5262);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,2 > > _5263,monty::rc_ptr< ::mosek::fusion::Expression > _5264);
static  monty::rc_ptr< ::mosek::fusion::Expression > dot(std::shared_ptr< monty::ndarray< double,1 > > _5265,monty::rc_ptr< ::mosek::fusion::Expression > _5266);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(std::shared_ptr< monty::ndarray< double,1 > > _5267,monty::rc_ptr< ::mosek::fusion::Expression > _5268);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Expression > _5272,std::shared_ptr< monty::ndarray< double,1 > > _5273);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Matrix > _5276,monty::rc_ptr< ::mosek::fusion::Variable > _5277);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Variable > _5284,monty::rc_ptr< ::mosek::fusion::Matrix > _5285);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(std::shared_ptr< monty::ndarray< double,1 > > _5292,monty::rc_ptr< ::mosek::fusion::Variable > _5293);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer(monty::rc_ptr< ::mosek::fusion::Variable > _5295,std::shared_ptr< monty::ndarray< double,1 > > _5296);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer_(int _5298,std::shared_ptr< monty::ndarray< long long,1 > > _5299,std::shared_ptr< monty::ndarray< long long,1 > > _5300,std::shared_ptr< monty::ndarray< double,1 > > _5301,std::shared_ptr< monty::ndarray< double,1 > > _5302,std::shared_ptr< monty::ndarray< long long,1 > > _5303,std::shared_ptr< monty::ndarray< double,1 > > _5304,std::shared_ptr< monty::ndarray< int,1 > > _5305,int _5306,bool _5307);
static  monty::rc_ptr< ::mosek::fusion::Expression > outer_(monty::rc_ptr< ::mosek::fusion::Variable > _5337,int _5338,std::shared_ptr< monty::ndarray< double,1 > > _5339,std::shared_ptr< monty::ndarray< int,1 > > _5340,int _5341,bool _5342);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > >,1 > > _5359);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5365,double _5366,double _5367);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5368,double _5369,monty::rc_ptr< ::mosek::fusion::Expression > _5370);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5371,monty::rc_ptr< ::mosek::fusion::Expression > _5372,double _5373);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5374,monty::rc_ptr< ::mosek::fusion::Expression > _5375,monty::rc_ptr< ::mosek::fusion::Expression > _5376);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5377,double _5378,double _5379);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5380,double _5381,monty::rc_ptr< ::mosek::fusion::Expression > _5382);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5383,monty::rc_ptr< ::mosek::fusion::Expression > _5384,double _5385);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5386,monty::rc_ptr< ::mosek::fusion::Expression > _5387,monty::rc_ptr< ::mosek::fusion::Expression > _5388);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(double _5389,monty::rc_ptr< ::mosek::fusion::Expression > _5390);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5391,double _5392);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(monty::rc_ptr< ::mosek::fusion::Expression > _5393,monty::rc_ptr< ::mosek::fusion::Expression > _5394);
static  monty::rc_ptr< ::mosek::fusion::Expression > vstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5395);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5397,monty::rc_ptr< ::mosek::fusion::Expression > _5398,monty::rc_ptr< ::mosek::fusion::Expression > _5399);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5400,monty::rc_ptr< ::mosek::fusion::Expression > _5401,double _5402);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5403,double _5404,monty::rc_ptr< ::mosek::fusion::Expression > _5405);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5406,double _5407,double _5408);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5409,monty::rc_ptr< ::mosek::fusion::Expression > _5410,monty::rc_ptr< ::mosek::fusion::Expression > _5411);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5412,monty::rc_ptr< ::mosek::fusion::Expression > _5413,double _5414);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5415,double _5416,monty::rc_ptr< ::mosek::fusion::Expression > _5417);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(double _5418,monty::rc_ptr< ::mosek::fusion::Expression > _5419);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5420,double _5421);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(monty::rc_ptr< ::mosek::fusion::Expression > _5422,monty::rc_ptr< ::mosek::fusion::Expression > _5423);
static  monty::rc_ptr< ::mosek::fusion::Expression > hstack(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5424);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5426,monty::rc_ptr< ::mosek::fusion::Expression > _5427,monty::rc_ptr< ::mosek::fusion::Expression > _5428,monty::rc_ptr< ::mosek::fusion::Expression > _5429);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5430,monty::rc_ptr< ::mosek::fusion::Expression > _5431,monty::rc_ptr< ::mosek::fusion::Expression > _5432,double _5433);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5434,monty::rc_ptr< ::mosek::fusion::Expression > _5435,double _5436,monty::rc_ptr< ::mosek::fusion::Expression > _5437);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5438,monty::rc_ptr< ::mosek::fusion::Expression > _5439,double _5440,double _5441);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5442,double _5443,monty::rc_ptr< ::mosek::fusion::Expression > _5444,monty::rc_ptr< ::mosek::fusion::Expression > _5445);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5446,double _5447,monty::rc_ptr< ::mosek::fusion::Expression > _5448,double _5449);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5450,double _5451,double _5452,monty::rc_ptr< ::mosek::fusion::Expression > _5453);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5454,double _5455,monty::rc_ptr< ::mosek::fusion::Expression > _5456);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5457,monty::rc_ptr< ::mosek::fusion::Expression > _5458,double _5459);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5460,monty::rc_ptr< ::mosek::fusion::Expression > _5461,monty::rc_ptr< ::mosek::fusion::Expression > _5462);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack(int _5463,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5464);
static  monty::rc_ptr< ::mosek::fusion::Expression > stack_(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5465,int _5466);
static  std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > promote(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5467,int _5468);
static  monty::rc_ptr< ::mosek::fusion::Expression > repeat(monty::rc_ptr< ::mosek::fusion::Expression > _5481,int _5482,int _5483);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Expression >,1 > > _5485);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5487);
static  monty::rc_ptr< ::mosek::fusion::Expression > add_(monty::rc_ptr< ::mosek::fusion::Expression > _5520,double _5521,monty::rc_ptr< ::mosek::fusion::Expression > _5522,double _5523);
static  monty::rc_ptr< ::mosek::fusion::Expression > transpose(monty::rc_ptr< ::mosek::fusion::Expression > _5534);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Matrix > _5535,monty::rc_ptr< ::mosek::fusion::Expression > _5536);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5537,monty::rc_ptr< ::mosek::fusion::Expression > _5538);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,2 > > _5539,monty::rc_ptr< ::mosek::fusion::Expression > _5540);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(std::shared_ptr< monty::ndarray< double,1 > > _5541,monty::rc_ptr< ::mosek::fusion::Expression > _5542);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _5543,monty::rc_ptr< ::mosek::fusion::Matrix > _5544);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _5545,std::shared_ptr< monty::ndarray< double,2 > > _5546);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _5547,std::shared_ptr< monty::ndarray< double,1 > > _5548);
static  monty::rc_ptr< ::mosek::fusion::Expression > mulElm(monty::rc_ptr< ::mosek::fusion::Expression > _5549,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5550);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5551,monty::rc_ptr< ::mosek::fusion::Expression > _5552);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5553,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5554);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Matrix > _5555,monty::rc_ptr< ::mosek::fusion::Expression > _5556);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5557,monty::rc_ptr< ::mosek::fusion::Matrix > _5558);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(double _5559,monty::rc_ptr< ::mosek::fusion::Expression > _5560);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5561,double _5562);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,2 > > _5563,monty::rc_ptr< ::mosek::fusion::Expression > _5564);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(std::shared_ptr< monty::ndarray< double,1 > > _5565,monty::rc_ptr< ::mosek::fusion::Expression > _5566);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5567,std::shared_ptr< monty::ndarray< double,2 > > _5568);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5569,std::shared_ptr< monty::ndarray< double,1 > > _5570);
static  monty::rc_ptr< ::mosek::fusion::Expression > sub(monty::rc_ptr< ::mosek::fusion::Expression > _5571,monty::rc_ptr< ::mosek::fusion::Expression > _5572);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5573,monty::rc_ptr< ::mosek::fusion::Expression > _5574);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5575,monty::rc_ptr< ::mosek::fusion::NDSparseArray > _5576);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Matrix > _5577,monty::rc_ptr< ::mosek::fusion::Expression > _5578);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5579,monty::rc_ptr< ::mosek::fusion::Matrix > _5580);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(double _5581,monty::rc_ptr< ::mosek::fusion::Expression > _5582);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5583,double _5584);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,2 > > _5585,monty::rc_ptr< ::mosek::fusion::Expression > _5586);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(std::shared_ptr< monty::ndarray< double,1 > > _5587,monty::rc_ptr< ::mosek::fusion::Expression > _5588);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5589,std::shared_ptr< monty::ndarray< double,2 > > _5590);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5591,std::shared_ptr< monty::ndarray< double,1 > > _5592);
static  monty::rc_ptr< ::mosek::fusion::Expression > add(monty::rc_ptr< ::mosek::fusion::Expression > _5593,monty::rc_ptr< ::mosek::fusion::Expression > _5594);
virtual /* override */ int getND() ;
virtual /* override */ std::shared_ptr< monty::ndarray< int,1 > > getShape() ;
virtual /* override */ void eval(monty::rc_ptr< ::mosek::fusion::WorkStack > _5595,monty::rc_ptr< ::mosek::fusion::WorkStack > _5596,monty::rc_ptr< ::mosek::fusion::WorkStack > _5597) ;
static  void validateData(std::shared_ptr< monty::ndarray< long long,1 > > _5599,std::shared_ptr< monty::ndarray< long long,1 > > _5600,std::shared_ptr< monty::ndarray< double,1 > > _5601,std::shared_ptr< monty::ndarray< double,1 > > _5602,std::shared_ptr< monty::ndarray< int,1 > > _5603,std::shared_ptr< monty::ndarray< long long,1 > > _5604);
static  monty::rc_ptr< ::mosek::fusion::Model > extractModel(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _5617);
}; // struct Expr;

struct p_WorkStack
{
WorkStack * _pubthis;
static mosek::fusion::p_WorkStack* _get_impl(mosek::fusion::WorkStack * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_WorkStack * _get_impl(mosek::fusion::WorkStack::t _inst) { return _get_impl(_inst.get()); }
p_WorkStack(WorkStack * _pubthis);
virtual ~p_WorkStack() { /* std::cout << "~p_WorkStack" << std::endl;*/ };
int cof_base{};int bfix_base{};int nidxs_base{};int sp_base{};int shape_base{};int ptr_base{};bool hassp{};int nelem{};int nnz{};int nd{};int pf64{};int pi64{};int pi32{};std::shared_ptr< monty::ndarray< double,1 > > f64{};std::shared_ptr< monty::ndarray< long long,1 > > i64{};std::shared_ptr< monty::ndarray< int,1 > > i32{};virtual void destroy();
static WorkStack::t _new_WorkStack();
void _initialize();
virtual bool peek_hassp() ;
virtual int peek_nnz() ;
virtual int peek_nelem() ;
virtual int peek_dim(int _4891) ;
virtual int peek_nd() ;
virtual void alloc_expr(int _4892,int _4893,int _4894,bool _4895) ;
virtual void move_expr(monty::rc_ptr< ::mosek::fusion::WorkStack > _4896) ;
virtual void peek_expr() ;
virtual void pop_expr() ;
virtual void ensure_sparsity() ;
virtual void clear() ;
virtual int allocf64(int _4911) ;
virtual int alloci64(int _4914) ;
virtual int alloci32(int _4917) ;
virtual void pushf64(double _4920) ;
virtual void pushi64(long long _4921) ;
virtual void pushi32(int _4922) ;
virtual void ensuref64(int _4923) ;
virtual void ensurei64(int _4926) ;
virtual void ensurei32(int _4929) ;
virtual int popf64(int _4932) ;
virtual int popi64(int _4933) ;
virtual int popi32(int _4934) ;
virtual void popf64(int _4935,std::shared_ptr< monty::ndarray< double,1 > > _4936,int _4937) ;
virtual void popi64(int _4938,std::shared_ptr< monty::ndarray< long long,1 > > _4939,int _4940) ;
virtual void popi32(int _4941,std::shared_ptr< monty::ndarray< int,1 > > _4942,int _4943) ;
virtual double popf64() ;
virtual long long popi64() ;
virtual int popi32() ;
virtual double peekf64() ;
virtual long long peeki64() ;
virtual int peeki32() ;
virtual double peekf64(int _4944) ;
virtual long long peeki64(int _4945) ;
virtual int peeki32(int _4946) ;
}; // struct WorkStack;

struct p_SymmetricExpr
{
SymmetricExpr * _pubthis;
static mosek::fusion::p_SymmetricExpr* _get_impl(mosek::fusion::SymmetricExpr * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricExpr * _get_impl(mosek::fusion::SymmetricExpr::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricExpr(SymmetricExpr * _pubthis);
virtual ~p_SymmetricExpr() { /* std::cout << "~p_SymmetricExpr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > xs{};monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > b{};std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > Ms{};int n{};virtual void destroy();
static SymmetricExpr::t _new_SymmetricExpr(int _4947,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > _4948,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4949,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4950);
void _initialize(int _4947,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::SymmetricMatrix >,1 > > _4948,std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Variable >,1 > > _4949,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4950);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > add(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4951,monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _4952);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > mul(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4953,double _4954);
static  monty::rc_ptr< ::mosek::fusion::SymmetricExpr > add(monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4956,monty::rc_ptr< ::mosek::fusion::SymmetricExpr > _4957);
virtual /* override */ std::string toString() ;
}; // struct SymmetricExpr;

struct p_FlatExpr
{
FlatExpr * _pubthis;
static mosek::fusion::p_FlatExpr* _get_impl(mosek::fusion::FlatExpr * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_FlatExpr * _get_impl(mosek::fusion::FlatExpr::t _inst) { return _get_impl(_inst.get()); }
p_FlatExpr(FlatExpr * _pubthis);
virtual ~p_FlatExpr() { /* std::cout << "~p_FlatExpr" << std::endl;*/ };
std::shared_ptr< monty::ndarray< long long,1 > > inst{};std::shared_ptr< monty::ndarray< int,1 > > shape{};long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< long long,1 > > subj{};std::shared_ptr< monty::ndarray< long long,1 > > ptrb{};std::shared_ptr< monty::ndarray< double,1 > > bfix{};virtual void destroy();
static FlatExpr::t _new_FlatExpr(monty::rc_ptr< ::mosek::fusion::FlatExpr > _5630);
void _initialize(monty::rc_ptr< ::mosek::fusion::FlatExpr > _5630);
static FlatExpr::t _new_FlatExpr(std::shared_ptr< monty::ndarray< double,1 > > _5631,std::shared_ptr< monty::ndarray< long long,1 > > _5632,std::shared_ptr< monty::ndarray< long long,1 > > _5633,std::shared_ptr< monty::ndarray< double,1 > > _5634,std::shared_ptr< monty::ndarray< int,1 > > _5635,std::shared_ptr< monty::ndarray< long long,1 > > _5636);
void _initialize(std::shared_ptr< monty::ndarray< double,1 > > _5631,std::shared_ptr< monty::ndarray< long long,1 > > _5632,std::shared_ptr< monty::ndarray< long long,1 > > _5633,std::shared_ptr< monty::ndarray< double,1 > > _5634,std::shared_ptr< monty::ndarray< int,1 > > _5635,std::shared_ptr< monty::ndarray< long long,1 > > _5636);
virtual /* override */ std::string toString() ;
virtual int size() ;
}; // struct FlatExpr;

struct p_SymmetricMatrix
{
SymmetricMatrix * _pubthis;
static mosek::fusion::p_SymmetricMatrix* _get_impl(mosek::fusion::SymmetricMatrix * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_SymmetricMatrix * _get_impl(mosek::fusion::SymmetricMatrix::t _inst) { return _get_impl(_inst.get()); }
p_SymmetricMatrix(SymmetricMatrix * _pubthis);
virtual ~p_SymmetricMatrix() { /* std::cout << "~p_SymmetricMatrix" << std::endl;*/ };
int nnz{};double scale{};std::shared_ptr< monty::ndarray< double,1 > > vval{};std::shared_ptr< monty::ndarray< int,1 > > vsubj{};std::shared_ptr< monty::ndarray< int,1 > > vsubi{};std::shared_ptr< monty::ndarray< double,1 > > uval{};std::shared_ptr< monty::ndarray< int,1 > > usubj{};std::shared_ptr< monty::ndarray< int,1 > > usubi{};int d1{};int d0{};virtual void destroy();
static SymmetricMatrix::t _new_SymmetricMatrix(int _5638,int _5639,std::shared_ptr< monty::ndarray< int,1 > > _5640,std::shared_ptr< monty::ndarray< int,1 > > _5641,std::shared_ptr< monty::ndarray< double,1 > > _5642,std::shared_ptr< monty::ndarray< int,1 > > _5643,std::shared_ptr< monty::ndarray< int,1 > > _5644,std::shared_ptr< monty::ndarray< double,1 > > _5645,double _5646);
void _initialize(int _5638,int _5639,std::shared_ptr< monty::ndarray< int,1 > > _5640,std::shared_ptr< monty::ndarray< int,1 > > _5641,std::shared_ptr< monty::ndarray< double,1 > > _5642,std::shared_ptr< monty::ndarray< int,1 > > _5643,std::shared_ptr< monty::ndarray< int,1 > > _5644,std::shared_ptr< monty::ndarray< double,1 > > _5645,double _5646);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > rankOne(int _5647,std::shared_ptr< monty::ndarray< int,1 > > _5648,std::shared_ptr< monty::ndarray< double,1 > > _5649);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > rankOne(std::shared_ptr< monty::ndarray< double,1 > > _5657);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > antiDiag(std::shared_ptr< monty::ndarray< double,1 > > _5665);
static  monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _5672);
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > __mosek_2fusion_2SymmetricMatrix__add(monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _5678) ;
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > __mosek_2fusion_2SymmetricMatrix__sub(monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > _5698) ;
virtual monty::rc_ptr< ::mosek::fusion::SymmetricMatrix > __mosek_2fusion_2SymmetricMatrix__mul(double _5699) ;
virtual int getdim() ;
}; // struct SymmetricMatrix;

struct p_NDSparseArray
{
NDSparseArray * _pubthis;
static mosek::fusion::p_NDSparseArray* _get_impl(mosek::fusion::NDSparseArray * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_NDSparseArray * _get_impl(mosek::fusion::NDSparseArray::t _inst) { return _get_impl(_inst.get()); }
p_NDSparseArray(NDSparseArray * _pubthis);
virtual ~p_NDSparseArray() { /* std::cout << "~p_NDSparseArray" << std::endl;*/ };
std::shared_ptr< monty::ndarray< double,1 > > cof{};std::shared_ptr< monty::ndarray< long long,1 > > inst{};std::shared_ptr< monty::ndarray< int,1 > > dims{};long long size{};virtual void destroy();
static NDSparseArray::t _new_NDSparseArray(std::shared_ptr< monty::ndarray< int,1 > > _5700,std::shared_ptr< monty::ndarray< int,2 > > _5701,std::shared_ptr< monty::ndarray< double,1 > > _5702);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _5700,std::shared_ptr< monty::ndarray< int,2 > > _5701,std::shared_ptr< monty::ndarray< double,1 > > _5702);
static NDSparseArray::t _new_NDSparseArray(std::shared_ptr< monty::ndarray< int,1 > > _5722,std::shared_ptr< monty::ndarray< long long,1 > > _5723,std::shared_ptr< monty::ndarray< double,1 > > _5724);
void _initialize(std::shared_ptr< monty::ndarray< int,1 > > _5722,std::shared_ptr< monty::ndarray< long long,1 > > _5723,std::shared_ptr< monty::ndarray< double,1 > > _5724);
static NDSparseArray::t _new_NDSparseArray(monty::rc_ptr< ::mosek::fusion::Matrix > _5738);
void _initialize(monty::rc_ptr< ::mosek::fusion::Matrix > _5738);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(monty::rc_ptr< ::mosek::fusion::Matrix > _5746);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(std::shared_ptr< monty::ndarray< int,1 > > _5747,std::shared_ptr< monty::ndarray< long long,1 > > _5748,std::shared_ptr< monty::ndarray< double,1 > > _5749);
static  monty::rc_ptr< ::mosek::fusion::NDSparseArray > make(std::shared_ptr< monty::ndarray< int,1 > > _5750,std::shared_ptr< monty::ndarray< int,2 > > _5751,std::shared_ptr< monty::ndarray< double,1 > > _5752);
}; // struct NDSparseArray;

struct p_Matrix
{
Matrix * _pubthis;
static mosek::fusion::p_Matrix* _get_impl(mosek::fusion::Matrix * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Matrix * _get_impl(mosek::fusion::Matrix::t _inst) { return _get_impl(_inst.get()); }
p_Matrix(Matrix * _pubthis);
virtual ~p_Matrix() { /* std::cout << "~p_Matrix" << std::endl;*/ };
int dimj{};int dimi{};virtual void destroy();
static Matrix::t _new_Matrix(int _5821,int _5822);
void _initialize(int _5821,int _5822);
virtual /* override */ std::string toString() ;
virtual void switchDims() ;
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _5824,monty::rc_ptr< ::mosek::fusion::Matrix > _5825);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Matrix >,1 > > _5827);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(int _5845,double _5846,int _5847);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(int _5848,double _5849);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _5850,double _5851,int _5852);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(int _5853,double _5854);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(std::shared_ptr< monty::ndarray< double,1 > > _5855,int _5856);
static  monty::rc_ptr< ::mosek::fusion::Matrix > antidiag(std::shared_ptr< monty::ndarray< double,1 > > _5866);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _5867,int _5868);
static  monty::rc_ptr< ::mosek::fusion::Matrix > diag(std::shared_ptr< monty::ndarray< double,1 > > _5876);
static  monty::rc_ptr< ::mosek::fusion::Matrix > ones(int _5877,int _5878);
static  monty::rc_ptr< ::mosek::fusion::Matrix > eye(int _5879);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(monty::rc_ptr< ::mosek::fusion::Matrix > _5881);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(int _5882,int _5883,double _5884);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(int _5885,int _5886,std::shared_ptr< monty::ndarray< double,1 > > _5887);
static  monty::rc_ptr< ::mosek::fusion::Matrix > dense(std::shared_ptr< monty::ndarray< double,2 > > _5888);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(monty::rc_ptr< ::mosek::fusion::Matrix > _5889);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< std::shared_ptr< monty::ndarray< monty::rc_ptr< ::mosek::fusion::Matrix >,1 > >,1 > > _5893);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< double,2 > > _5924);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _5937,int _5938);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _5939,int _5940,std::shared_ptr< monty::ndarray< int,1 > > _5941,std::shared_ptr< monty::ndarray< int,1 > > _5942,double _5943);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< int,1 > > _5945,std::shared_ptr< monty::ndarray< int,1 > > _5946,double _5947);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(std::shared_ptr< monty::ndarray< int,1 > > _5952,std::shared_ptr< monty::ndarray< int,1 > > _5953,std::shared_ptr< monty::ndarray< double,1 > > _5954);
static  monty::rc_ptr< ::mosek::fusion::Matrix > sparse(int _5959,int _5960,std::shared_ptr< monty::ndarray< int,1 > > _5961,std::shared_ptr< monty::ndarray< int,1 > > _5962,std::shared_ptr< monty::ndarray< double,1 > > _5963);
virtual double get(int _5968,int _5969) { throw monty::AbstractClassError("Call to abstract method"); }
virtual bool isSparse() { throw monty::AbstractClassError("Call to abstract method"); }
virtual std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray() { throw monty::AbstractClassError("Call to abstract method"); }
virtual void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _5970,std::shared_ptr< monty::ndarray< int,1 > > _5971,std::shared_ptr< monty::ndarray< double,1 > > _5972) { throw monty::AbstractClassError("Call to abstract method"); }
virtual monty::rc_ptr< ::mosek::fusion::Matrix > __mosek_2fusion_2Matrix__transpose() { throw monty::AbstractClassError("Call to abstract method"); }
virtual long long numNonzeros() { throw monty::AbstractClassError("Call to abstract method"); }
virtual int numColumns() ;
virtual int numRows() ;
}; // struct Matrix;

struct p_DenseMatrix : public ::mosek::fusion::p_Matrix
{
DenseMatrix * _pubthis;
static mosek::fusion::p_DenseMatrix* _get_impl(mosek::fusion::DenseMatrix * _inst){ return static_cast< mosek::fusion::p_DenseMatrix* >(mosek::fusion::p_Matrix::_get_impl(_inst)); }
static mosek::fusion::p_DenseMatrix * _get_impl(mosek::fusion::DenseMatrix::t _inst) { return _get_impl(_inst.get()); }
p_DenseMatrix(DenseMatrix * _pubthis);
virtual ~p_DenseMatrix() { /* std::cout << "~p_DenseMatrix" << std::endl;*/ };
long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > data{};virtual void destroy();
static DenseMatrix::t _new_DenseMatrix(int _5753,int _5754,std::shared_ptr< monty::ndarray< double,1 > > _5755);
void _initialize(int _5753,int _5754,std::shared_ptr< monty::ndarray< double,1 > > _5755);
static DenseMatrix::t _new_DenseMatrix(monty::rc_ptr< ::mosek::fusion::Matrix > _5756);
void _initialize(monty::rc_ptr< ::mosek::fusion::Matrix > _5756);
static DenseMatrix::t _new_DenseMatrix(std::shared_ptr< monty::ndarray< double,2 > > _5761);
void _initialize(std::shared_ptr< monty::ndarray< double,2 > > _5761);
static DenseMatrix::t _new_DenseMatrix(int _5764,int _5765,double _5766);
void _initialize(int _5764,int _5765,double _5766);
virtual /* override */ std::string toString() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Matrix > __mosek_2fusion_2DenseMatrix__transpose() ;
virtual monty::rc_ptr< ::mosek::fusion::Matrix > __mosek_2fusion_2Matrix__transpose() { return __mosek_2fusion_2DenseMatrix__transpose(); }
virtual /* override */ bool isSparse() ;
virtual /* override */ std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray() ;
virtual /* override */ void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _5779,std::shared_ptr< monty::ndarray< int,1 > > _5780,std::shared_ptr< monty::ndarray< double,1 > > _5781) ;
virtual /* override */ double get(int _5785,int _5786) ;
virtual /* override */ long long numNonzeros() ;
}; // struct DenseMatrix;

struct p_SparseMatrix : public ::mosek::fusion::p_Matrix
{
SparseMatrix * _pubthis;
static mosek::fusion::p_SparseMatrix* _get_impl(mosek::fusion::SparseMatrix * _inst){ return static_cast< mosek::fusion::p_SparseMatrix* >(mosek::fusion::p_Matrix::_get_impl(_inst)); }
static mosek::fusion::p_SparseMatrix * _get_impl(mosek::fusion::SparseMatrix::t _inst) { return _get_impl(_inst.get()); }
p_SparseMatrix(SparseMatrix * _pubthis);
virtual ~p_SparseMatrix() { /* std::cout << "~p_SparseMatrix" << std::endl;*/ };
long long nnz{};std::shared_ptr< monty::ndarray< double,1 > > val{};std::shared_ptr< monty::ndarray< int,1 > > subj{};std::shared_ptr< monty::ndarray< int,1 > > subi{};virtual void destroy();
static SparseMatrix::t _new_SparseMatrix(int _5787,int _5788,std::shared_ptr< monty::ndarray< int,1 > > _5789,std::shared_ptr< monty::ndarray< int,1 > > _5790,std::shared_ptr< monty::ndarray< double,1 > > _5791,long long _5792);
void _initialize(int _5787,int _5788,std::shared_ptr< monty::ndarray< int,1 > > _5789,std::shared_ptr< monty::ndarray< int,1 > > _5790,std::shared_ptr< monty::ndarray< double,1 > > _5791,long long _5792);
static SparseMatrix::t _new_SparseMatrix(int _5797,int _5798,std::shared_ptr< monty::ndarray< int,1 > > _5799,std::shared_ptr< monty::ndarray< int,1 > > _5800,std::shared_ptr< monty::ndarray< double,1 > > _5801);
void _initialize(int _5797,int _5798,std::shared_ptr< monty::ndarray< int,1 > > _5799,std::shared_ptr< monty::ndarray< int,1 > > _5800,std::shared_ptr< monty::ndarray< double,1 > > _5801);
virtual std::shared_ptr< monty::ndarray< long long,1 > > formPtrb() ;
virtual /* override */ std::string toString() ;
virtual /* override */ long long numNonzeros() ;
virtual /* override */ monty::rc_ptr< ::mosek::fusion::Matrix > __mosek_2fusion_2SparseMatrix__transpose() ;
virtual monty::rc_ptr< ::mosek::fusion::Matrix > __mosek_2fusion_2Matrix__transpose() { return __mosek_2fusion_2SparseMatrix__transpose(); }
virtual /* override */ bool isSparse() ;
virtual /* override */ std::shared_ptr< monty::ndarray< double,1 > > getDataAsArray() ;
virtual /* override */ void getDataAsTriplets(std::shared_ptr< monty::ndarray< int,1 > > _5813,std::shared_ptr< monty::ndarray< int,1 > > _5814,std::shared_ptr< monty::ndarray< double,1 > > _5815) ;
virtual /* override */ double get(int _5816,int _5817) ;
}; // struct SparseMatrix;

struct p_LinkedBlocks
{
LinkedBlocks * _pubthis;
static mosek::fusion::p_LinkedBlocks* _get_impl(mosek::fusion::LinkedBlocks * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinkedBlocks * _get_impl(mosek::fusion::LinkedBlocks::t _inst) { return _get_impl(_inst.get()); }
p_LinkedBlocks(LinkedBlocks * _pubthis);
virtual ~p_LinkedBlocks() { /* std::cout << "~p_LinkedBlocks" << std::endl;*/ };
std::shared_ptr< monty::ndarray< int,1 > > bfirst{};std::shared_ptr< monty::ndarray< int,1 > > bsize{};monty::rc_ptr< ::mosek::fusion::LinkedInts > blocks{};monty::rc_ptr< ::mosek::fusion::LinkedInts > ints{};virtual void destroy();
static LinkedBlocks::t _new_LinkedBlocks();
void _initialize();
static LinkedBlocks::t _new_LinkedBlocks(int _5996);
void _initialize(int _5996);
static LinkedBlocks::t _new_LinkedBlocks(monty::rc_ptr< ::mosek::fusion::LinkedBlocks > _5997);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinkedBlocks > _5997);
virtual void free(int _5998) ;
virtual int alloc(int _6000) ;
virtual int maxidx(int _6005) ;
virtual void get(int _6006,std::shared_ptr< monty::ndarray< int,1 > > _6007,int _6008) ;
virtual int numblocks() ;
virtual int blocksize(int _6009) ;
virtual int capacity() ;
virtual bool validate() ;
}; // struct LinkedBlocks;

struct p_LinkedInts
{
LinkedInts * _pubthis;
static mosek::fusion::p_LinkedInts* _get_impl(mosek::fusion::LinkedInts * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_LinkedInts * _get_impl(mosek::fusion::LinkedInts::t _inst) { return _get_impl(_inst.get()); }
p_LinkedInts(LinkedInts * _pubthis);
virtual ~p_LinkedInts() { /* std::cout << "~p_LinkedInts" << std::endl;*/ };
int nfree{};int last_free{};int first_free{};int first_used{};std::shared_ptr< monty::ndarray< int,1 > > prev{};std::shared_ptr< monty::ndarray< int,1 > > next{};virtual void destroy();
static LinkedInts::t _new_LinkedInts(int _6010);
void _initialize(int _6010);
static LinkedInts::t _new_LinkedInts();
void _initialize();
static LinkedInts::t _new_LinkedInts(monty::rc_ptr< ::mosek::fusion::LinkedInts > _6013);
void _initialize(monty::rc_ptr< ::mosek::fusion::LinkedInts > _6013);
virtual void free(int _6014,int _6015) ;
virtual int alloc() ;
virtual int alloc(int _6021) ;
virtual void alloc(int _6022,std::shared_ptr< monty::ndarray< int,1 > > _6023,int _6024) ;
virtual void get(int _6027,int _6028,std::shared_ptr< monty::ndarray< int,1 > > _6029,int _6030) ;
virtual int maxidx(int _6033,int _6034) ;
virtual int allocblock(int _6038) ;
virtual void recap(int _6044) ;
virtual int capacity() ;
virtual bool validate() ;
}; // struct LinkedInts;

struct p_Parameters
{
Parameters * _pubthis;
static mosek::fusion::p_Parameters* _get_impl(mosek::fusion::Parameters * _inst){ assert(_inst); assert(_inst->_impl); return _inst->_impl; }
static mosek::fusion::p_Parameters * _get_impl(mosek::fusion::Parameters::t _inst) { return _get_impl(_inst.get()); }
p_Parameters(Parameters * _pubthis);
virtual ~p_Parameters() { /* std::cout << "~p_Parameters" << std::endl;*/ };
virtual void destroy();
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6053,const std::string &  _6054,double _6055);
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6149,const std::string &  _6150,int _6151);
static  void setParameter(monty::rc_ptr< ::mosek::fusion::Model > _6245,const std::string &  _6246,const std::string &  _6247);
static  int string_to_rescode_value(const std::string &  _6485);
static  int string_to_boundkey_value(const std::string &  _6486);
static  int string_to_prosta_value(const std::string &  _6487);
static  int string_to_parametertype_value(const std::string &  _6488);
static  int string_to_language_value(const std::string &  _6489);
static  int string_to_mpsformat_value(const std::string &  _6490);
static  int string_to_nametype_value(const std::string &  _6491);
static  int string_to_iinfitem_value(const std::string &  _6492);
static  int string_to_presolvemode_value(const std::string &  _6493);
static  int string_to_simseltype_value(const std::string &  _6494);
static  int string_to_internal_liinf_value(const std::string &  _6495);
static  int string_to_stakey_value(const std::string &  _6496);
static  int string_to_miocontsoltype_value(const std::string &  _6497);
static  int string_to_problemitem_value(const std::string &  _6498);
static  int string_to_dparam_value(const std::string &  _6499);
static  int string_to_internal_iinf_value(const std::string &  _6500);
static  int string_to_solveform_value(const std::string &  _6501);
static  int string_to_problemtype_value(const std::string &  _6502);
static  int string_to_uplo_value(const std::string &  _6503);
static  int string_to_scalingtype_value(const std::string &  _6504);
static  int string_to_dataformat_value(const std::string &  _6505);
static  int string_to_basindtype_value(const std::string &  _6506);
static  int string_to_callbackcode_value(const std::string &  _6507);
static  int string_to_rescodetype_value(const std::string &  _6508);
static  int string_to_simdupvec_value(const std::string &  _6509);
static  int string_to_sparam_value(const std::string &  _6510);
static  int string_to_purify_value(const std::string &  _6511);
static  int string_to_value_value(const std::string &  _6512);
static  int string_to_iomode_value(const std::string &  _6513);
static  int string_to_dinfitem_value(const std::string &  _6514);
static  int string_to_streamtype_value(const std::string &  _6515);
static  int string_to_scalingmethod_value(const std::string &  _6516);
static  int string_to_mionodeseltype_value(const std::string &  _6517);
static  int string_to_optimizertype_value(const std::string &  _6518);
static  int string_to_objsense_value(const std::string &  _6519);
static  int string_to_inftype_value(const std::string &  _6520);
static  int string_to_sensitivitytype_value(const std::string &  _6521);
static  int string_to_liinfitem_value(const std::string &  _6522);
static  int string_to_onoffkey_value(const std::string &  _6523);
static  int string_to_xmlwriteroutputtype_value(const std::string &  _6524);
static  int string_to_simhotstart_value(const std::string &  _6525);
static  int string_to_simreform_value(const std::string &  _6526);
static  int string_to_checkconvexitytype_value(const std::string &  _6527);
static  int string_to_variabletype_value(const std::string &  _6528);
static  int string_to_transpose_value(const std::string &  _6529);
static  int string_to_conetype_value(const std::string &  _6530);
static  int string_to_mark_value(const std::string &  _6531);
static  int string_to_soltype_value(const std::string &  _6532);
static  int string_to_scopr_value(const std::string &  _6533);
static  int string_to_iparam_value(const std::string &  _6534);
static  int string_to_orderingtype_value(const std::string &  _6535);
static  int string_to_compresstype_value(const std::string &  _6536);
static  int string_to_solitem_value(const std::string &  _6537);
static  int string_to_branchdir_value(const std::string &  _6538);
static  int string_to_symmattype_value(const std::string &  _6539);
static  int string_to_startpointtype_value(const std::string &  _6540);
static  int string_to_feature_value(const std::string &  _6541);
static  int string_to_internal_dinf_value(const std::string &  _6542);
static  int string_to_simdegen_value(const std::string &  _6543);
static  int string_to_solsta_value(const std::string &  _6544);
static  int string_to_intpnthotstart_value(const std::string &  _6545);
static  int string_to_miomode_value(const std::string &  _6546);
}; // struct Parameters;

}
}
namespace mosek
{
namespace fusion
{
namespace Utils
{
// mosek.fusion.Utils.IntMap from file 'src/fusion/cxx/IntMap_p.h'
struct p_IntMap 
{
  IntMap * _pubself;

  static p_IntMap * _get_impl(IntMap * _inst) { return _inst->_impl.get(); }

  p_IntMap(IntMap * _pubself) : _pubself(_pubself) {}

  static IntMap::t _new_IntMap() { return new IntMap(); }

  ::std::unordered_map<long long,int> m;

  bool hasItem (long long key) { return m.find(key) != m.end(); }
  int  getItem (long long key) { return m.find(key)->second; } // will probably throw something or crash of no such key
  void setItem (long long key, int val) { m[key] = val; }

  std::shared_ptr<monty::ndarray<long long,1>> keys()
  { 
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<long long,1>>(new monty::ndarray<long long,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->first;

    return res;    
  }

  std::shared_ptr<monty::ndarray<int,1>> values()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<int,1>>(new monty::ndarray<int,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->second;

    return res;
  }

  IntMap::t clone();
  IntMap::t __mosek_2fusion_2Utils_2IntMap__clone();
};



struct p_StringIntMap
{
  StringIntMap * _pubself;

  static p_StringIntMap * _get_impl(StringIntMap * _inst) { return _inst->_impl.get(); }

  p_StringIntMap(StringIntMap * _pubself) : _pubself(_pubself) {}

  static StringIntMap::t _new_StringIntMap() { return new StringIntMap(); }

  ::std::unordered_map<std::string,int> m;

  bool hasItem (const std::string & key) { return m.find(key) != m.end(); }
  int  getItem (const std::string & key) { return m.find(key)->second; } // will probably throw something or crash of no such key
  void setItem (const std::string & key, int val) { m[key] = val; }

  std::shared_ptr<monty::ndarray<std::string,1>> keys()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<std::string,1>>(new monty::ndarray<std::string,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->first;

    return res;
  }

  std::shared_ptr<monty::ndarray<int,1>> values()
  {
    size_t size = m.size();
    auto res = std::shared_ptr<monty::ndarray<int,1>>(new monty::ndarray<int,1>(monty::shape((int)size)));

    ptrdiff_t i = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
      (*res)[i++] = it->second;

    return res;
  }

  StringIntMap::t clone();
  StringIntMap::t __mosek_2fusion_2Utils_2StringIntMap__clone();
};
// End of file 'src/fusion/cxx/IntMap_p.h'
// mosek.fusion.Utils.StringBuffer from file 'src/fusion/cxx/StringBuffer_p.h'
// namespace mosek::fusion::Utils
struct p_StringBuffer
{
  StringBuffer * _pubthis; 
  std::stringstream ss;

  p_StringBuffer(StringBuffer * _pubthis) : _pubthis(_pubthis) {}

  static p_StringBuffer * _get_impl(StringBuffer::t ptr) { return ptr->_impl.get(); }
  static p_StringBuffer * _get_impl(StringBuffer * ptr) { return ptr->_impl.get(); }

  static StringBuffer::t _new_StringBuffer() { return new StringBuffer(); }

  StringBuffer::t clear ();
  
  StringBuffer::t a (const monty::ndarray<std::string,1> & val);
  StringBuffer::t a (const monty::ndarray<int,1> & val);
  StringBuffer::t a (const monty::ndarray<long long,1> & val);
  StringBuffer::t a (const monty::ndarray<double,1> & val);
  

  StringBuffer::t a (const int & val);
  StringBuffer::t a (const long long & val);
  StringBuffer::t a (const double & val);
  StringBuffer::t a (const bool & val);
  StringBuffer::t a (const std::string & val);

  StringBuffer::t lf ();
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__clear ();

  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const monty::ndarray<std::string,1> & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const monty::ndarray<int,1> & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const monty::ndarray<long long,1> & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const monty::ndarray<double,1> & val);

  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const int & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const long long & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const double & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const bool & val);
  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__a (const std::string & val);

  StringBuffer::t __mosek_2fusion_2Utils_2StringBuffer__lf ();

  std::string toString () const;
};
// End of file 'src/fusion/cxx/StringBuffer_p.h'
}
}
}
#endif
