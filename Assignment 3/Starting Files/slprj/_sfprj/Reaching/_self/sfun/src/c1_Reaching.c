/* Include files */

#include "Reaching_sfun.h"
#include "c1_Reaching.h"
#include "mwmathutil.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_NO_ACTIVE_LEAF           ((uint8_T)0U)
#define CALL_EVENT                     (-1)
#define c1_IN_Finish                   (1U)
#define c1_IN_Initializing             (2U)
#define c1_IN_RandomAngleList          (3U)
#define c1_IN_ReachingHome             (4U)
#define c1_IN_ReachingTarget           (5U)
#define c1_IN_SpawnHome                (6U)
#define c1_IN_SpawnTarget              (7U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static emlrtMCInfo c1_emlrtMCI = { 141,/* lineNo */
  13,                                  /* colNo */
  "rng",                               /* fName */
  "C:\\Program Files\\MATLAB\\R2024b\\toolbox\\eml\\lib\\matlab\\randfun\\rng.m"/* pName */
};

static emlrtMCInfo c1_b_emlrtMCI = { 125,/* lineNo */
  13,                                  /* colNo */
  "eml_rand_mt19937ar",                /* fName */
  "C:\\Program Files\\MATLAB\\R2024b\\toolbox\\eml\\eml\\+coder\\+internal\\+randfun\\eml_rand_mt19937ar.m"/* pName */
};

static emlrtMCInfo c1_c_emlrtMCI = { 87,/* lineNo */
  33,                                  /* colNo */
  "eml_int_forloop_overflow_check",    /* fName */
  "C:\\Program Files\\MATLAB\\R2024b\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_overflow_check.m"/* pName */
};

static emlrtMCInfo c1_d_emlrtMCI = { 82,/* lineNo */
  5,                                   /* colNo */
  "power",                             /* fName */
  "C:\\Program Files\\MATLAB\\R2024b\\toolbox\\eml\\lib\\matlab\\ops\\power.m"/* pName */
};

static emlrtMCInfo c1_e_emlrtMCI = { 13,/* lineNo */
  9,                                   /* colNo */
  "sqrt",                              /* fName */
  "C:\\Program Files\\MATLAB\\R2024b\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m"/* pName */
};

static uint32_T c1_uv[625] = { 5489U, 1301868182U, 2938499221U, 2950281878U,
  1875628136U, 751856242U, 944701696U, 2243192071U, 694061057U, 219885934U,
  2066767472U, 3182869408U, 485472502U, 2336857883U, 1071588843U, 3418470598U,
  951210697U, 3693558366U, 2923482051U, 1793174584U, 2982310801U, 1586906132U,
  1951078751U, 1808158765U, 1733897588U, 431328322U, 4202539044U, 530658942U,
  1714810322U, 3025256284U, 3342585396U, 1937033938U, 2640572511U, 1654299090U,
  3692403553U, 4233871309U, 3497650794U, 862629010U, 2943236032U, 2426458545U,
  1603307207U, 1133453895U, 3099196360U, 2208657629U, 2747653927U, 931059398U,
  761573964U, 3157853227U, 785880413U, 730313442U, 124945756U, 2937117055U,
  3295982469U, 1724353043U, 3021675344U, 3884886417U, 4010150098U, 4056961966U,
  699635835U, 2681338818U, 1339167484U, 720757518U, 2800161476U, 2376097373U,
  1532957371U, 3902664099U, 1238982754U, 3725394514U, 3449176889U, 3570962471U,
  4287636090U, 4087307012U, 3603343627U, 202242161U, 2995682783U, 1620962684U,
  3704723357U, 371613603U, 2814834333U, 2111005706U, 624778151U, 2094172212U,
  4284947003U, 1211977835U, 991917094U, 1570449747U, 2962370480U, 1259410321U,
  170182696U, 146300961U, 2836829791U, 619452428U, 2723670296U, 1881399711U,
  1161269684U, 1675188680U, 4132175277U, 780088327U, 3409462821U, 1036518241U,
  1834958505U, 3048448173U, 161811569U, 618488316U, 44795092U, 3918322701U,
  1924681712U, 3239478144U, 383254043U, 4042306580U, 2146983041U, 3992780527U,
  3518029708U, 3545545436U, 3901231469U, 1896136409U, 2028528556U, 2339662006U,
  501326714U, 2060962201U, 2502746480U, 561575027U, 581893337U, 3393774360U,
  1778912547U, 3626131687U, 2175155826U, 319853231U, 986875531U, 819755096U,
  2915734330U, 2688355739U, 3482074849U, 2736559U, 2296975761U, 1029741190U,
  2876812646U, 690154749U, 579200347U, 4027461746U, 1285330465U, 2701024045U,
  4117700889U, 759495121U, 3332270341U, 2313004527U, 2277067795U, 4131855432U,
  2722057515U, 1264804546U, 3848622725U, 2211267957U, 4100593547U, 959123777U,
  2130745407U, 3194437393U, 486673947U, 1377371204U, 17472727U, 352317554U,
  3955548058U, 159652094U, 1232063192U, 3835177280U, 49423123U, 3083993636U,
  733092U, 2120519771U, 2573409834U, 1112952433U, 3239502554U, 761045320U,
  1087580692U, 2540165110U, 641058802U, 1792435497U, 2261799288U, 1579184083U,
  627146892U, 2165744623U, 2200142389U, 2167590760U, 2381418376U, 1793358889U,
  3081659520U, 1663384067U, 2009658756U, 2689600308U, 739136266U, 2304581039U,
  3529067263U, 591360555U, 525209271U, 3131882996U, 294230224U, 2076220115U,
  3113580446U, 1245621585U, 1386885462U, 3203270426U, 123512128U, 12350217U,
  354956375U, 4282398238U, 3356876605U, 3888857667U, 157639694U, 2616064085U,
  1563068963U, 2762125883U, 4045394511U, 4180452559U, 3294769488U, 1684529556U,
  1002945951U, 3181438866U, 22506664U, 691783457U, 2685221343U, 171579916U,
  3878728600U, 2475806724U, 2030324028U, 3331164912U, 1708711359U, 1970023127U,
  2859691344U, 2588476477U, 2748146879U, 136111222U, 2967685492U, 909517429U,
  2835297809U, 3206906216U, 3186870716U, 341264097U, 2542035121U, 3353277068U,
  548223577U, 3170936588U, 1678403446U, 297435620U, 2337555430U, 466603495U,
  1132321815U, 1208589219U, 696392160U, 894244439U, 2562678859U, 470224582U,
  3306867480U, 201364898U, 2075966438U, 1767227936U, 2929737987U, 3674877796U,
  2654196643U, 3692734598U, 3528895099U, 2796780123U, 3048728353U, 842329300U,
  191554730U, 2922459673U, 3489020079U, 3979110629U, 1022523848U, 2202932467U,
  3583655201U, 3565113719U, 587085778U, 4176046313U, 3013713762U, 950944241U,
  396426791U, 3784844662U, 3477431613U, 3594592395U, 2782043838U, 3392093507U,
  3106564952U, 2829419931U, 1358665591U, 2206918825U, 3170783123U, 31522386U,
  2988194168U, 1782249537U, 1105080928U, 843500134U, 1225290080U, 1521001832U,
  3605886097U, 2802786495U, 2728923319U, 3996284304U, 903417639U, 1171249804U,
  1020374987U, 2824535874U, 423621996U, 1988534473U, 2493544470U, 1008604435U,
  1756003503U, 1488867287U, 1386808992U, 732088248U, 1780630732U, 2482101014U,
  976561178U, 1543448953U, 2602866064U, 2021139923U, 1952599828U, 2360242564U,
  2117959962U, 2753061860U, 2388623612U, 4138193781U, 2962920654U, 2284970429U,
  766920861U, 3457264692U, 2879611383U, 815055854U, 2332929068U, 1254853997U,
  3740375268U, 3799380844U, 4091048725U, 2006331129U, 1982546212U, 686850534U,
  1907447564U, 2682801776U, 2780821066U, 998290361U, 1342433871U, 4195430425U,
  607905174U, 3902331779U, 2454067926U, 1708133115U, 1170874362U, 2008609376U,
  3260320415U, 2211196135U, 433538229U, 2728786374U, 2189520818U, 262554063U,
  1182318347U, 3710237267U, 1221022450U, 715966018U, 2417068910U, 2591870721U,
  2870691989U, 3418190842U, 4238214053U, 1540704231U, 1575580968U, 2095917976U,
  4078310857U, 2313532447U, 2110690783U, 4056346629U, 4061784526U, 1123218514U,
  551538993U, 597148360U, 4120175196U, 3581618160U, 3181170517U, 422862282U,
  3227524138U, 1713114790U, 662317149U, 1230418732U, 928171837U, 1324564878U,
  1928816105U, 1786535431U, 2878099422U, 3290185549U, 539474248U, 1657512683U,
  552370646U, 1671741683U, 3655312128U, 1552739510U, 2605208763U, 1441755014U,
  181878989U, 3124053868U, 1447103986U, 3183906156U, 1728556020U, 3502241336U,
  3055466967U, 1013272474U, 818402132U, 1715099063U, 2900113506U, 397254517U,
  4194863039U, 1009068739U, 232864647U, 2540223708U, 2608288560U, 2415367765U,
  478404847U, 3455100648U, 3182600021U, 2115988978U, 434269567U, 4117179324U,
  3461774077U, 887256537U, 3545801025U, 286388911U, 3451742129U, 1981164769U,
  786667016U, 3310123729U, 3097811076U, 2224235657U, 2959658883U, 3370969234U,
  2514770915U, 3345656436U, 2677010851U, 2206236470U, 271648054U, 2342188545U,
  4292848611U, 3646533909U, 3754009956U, 3803931226U, 4160647125U, 1477814055U,
  4043852216U, 1876372354U, 3133294443U, 3871104810U, 3177020907U, 2074304428U,
  3479393793U, 759562891U, 164128153U, 1839069216U, 2114162633U, 3989947309U,
  3611054956U, 1333547922U, 835429831U, 494987340U, 171987910U, 1252001001U,
  370809172U, 3508925425U, 2535703112U, 1276855041U, 1922855120U, 835673414U,
  3030664304U, 613287117U, 171219893U, 3423096126U, 3376881639U, 2287770315U,
  1658692645U, 1262815245U, 3957234326U, 1168096164U, 2968737525U, 2655813712U,
  2132313144U, 3976047964U, 326516571U, 353088456U, 3679188938U, 3205649712U,
  2654036126U, 1249024881U, 880166166U, 691800469U, 2229503665U, 1673458056U,
  4032208375U, 1851778863U, 2563757330U, 376742205U, 1794655231U, 340247333U,
  1505873033U, 396524441U, 879666767U, 3335579166U, 3260764261U, 3335999539U,
  506221798U, 4214658741U, 975887814U, 2080536343U, 3360539560U, 571586418U,
  138896374U, 4234352651U, 2737620262U, 3928362291U, 1516365296U, 38056726U,
  3599462320U, 3585007266U, 3850961033U, 471667319U, 1536883193U, 2310166751U,
  1861637689U, 2530999841U, 4139843801U, 2710569485U, 827578615U, 2012334720U,
  2907369459U, 3029312804U, 2820112398U, 1965028045U, 35518606U, 2478379033U,
  643747771U, 1924139484U, 4123405127U, 3811735531U, 3429660832U, 3285177704U,
  1948416081U, 1311525291U, 1183517742U, 1739192232U, 3979815115U, 2567840007U,
  4116821529U, 213304419U, 4125718577U, 1473064925U, 2442436592U, 1893310111U,
  4195361916U, 3747569474U, 828465101U, 2991227658U, 750582866U, 1205170309U,
  1409813056U, 678418130U, 1171531016U, 3821236156U, 354504587U, 4202874632U,
  3882511497U, 1893248677U, 1903078632U, 26340130U, 2069166240U, 3657122492U,
  3725758099U, 831344905U, 811453383U, 3447711422U, 2434543565U, 4166886888U,
  3358210805U, 4142984013U, 2988152326U, 3527824853U, 982082992U, 2809155763U,
  190157081U, 3340214818U, 2365432395U, 2548636180U, 2894533366U, 3474657421U,
  2372634704U, 2845748389U, 43024175U, 2774226648U, 1987702864U, 3186502468U,
  453610222U, 4204736567U, 1392892630U, 2471323686U, 2470534280U, 3541393095U,
  4269885866U, 3909911300U, 759132955U, 1482612480U, 667715263U, 1795580598U,
  2337923983U, 3390586366U, 581426223U, 1515718634U, 476374295U, 705213300U,
  363062054U, 2084697697U, 2407503428U, 2292957699U, 2426213835U, 2199989172U,
  1987356470U, 4026755612U, 2147252133U, 270400031U, 1367820199U, 2369854699U,
  2844269403U, 79981964U, 624U };

/* Function Declarations */
static void initSimStructsc1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void initSubchartIOPointersc1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance);
static void initialize_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void initialize_params_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance);
static void mdl_start_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void mdl_terminate_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c1_Reaching(SFc1_ReachingInstanceStruct *
  chartInstance);
static void mdl_cleanup_runtime_resources_c1_Reaching
  (SFc1_ReachingInstanceStruct *chartInstance);
static void enable_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void disable_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void c1_set_sim_state_side_effects_c1_Reaching
  (SFc1_ReachingInstanceStruct *chartInstance);
static void sf_gateway_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void c1_chartstep_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void ext_mode_exec_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance);
static void c1_update_jit_animation_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance);
static void c1_do_animation_call_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance);
static void set_sim_state_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void c1_ReachingHome(SFc1_ReachingInstanceStruct *chartInstance);
static void c1_enter_atomic_SpawnHome(SFc1_ReachingInstanceStruct *chartInstance);
static void c1_enter_atomic_SpawnTarget(SFc1_ReachingInstanceStruct
  *chartInstance);
static void c1_randomAngle(SFc1_ReachingInstanceStruct *chartInstance, real_T
  c1_angle_list[8], real_T c1_b_random_angle_list[8]);
static real_T c1_now(SFc1_ReachingInstanceStruct *chartInstance);
static real_T c1_mod(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_x);
static void c1_rand(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_r[8]);
static void c1_check_forloop_overflow_error(SFc1_ReachingInstanceStruct
  *chartInstance, boolean_T c1_overflow);
static void c1_computeTargetPose(SFc1_ReachingInstanceStruct *chartInstance,
  real_T c1_single_angle, real_T c1_b_radius, real_T c1_point_coordinates[3]);
static real_T c1_sqrt(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_x);
static const mxArray *c1_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance);
static const mxArray *c1_b_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance);
static const mxArray *c1_c_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance);
static void c1_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, real_T c1_y[3]);
static void c1_b_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static real_T c1_c_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, real_T c1_y[8]);
static void c1_f_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[8]);
static uint32_T c1_g_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr);
static uint32_T c1_h_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr);
static void c1_i_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr,
  uint32_T c1_y[625]);
static void c1_j_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr, uint32_T c1_y[625]);
static void c1_k_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr,
  uint32_T c1_y[2]);
static void c1_l_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr, uint32_T c1_y[2]);
static uint8_T c1_m_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier);
static uint8_T c1_n_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static uint32_T c1_o_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier);
static uint32_T c1_p_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_q_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T c1_y[13]);
static void c1_r_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T c1_y[13]);
static const mxArray *c1_s_emlrt_marshallIn(SFc1_ReachingInstanceStruct
  *chartInstance, const mxArray *c1_nullptr, const char_T *c1_identifier);
static const mxArray *c1_t_emlrt_marshallIn(SFc1_ReachingInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_slStringInitializeDynamicBuffers(SFc1_ReachingInstanceStruct
  *chartInstance);
static void c1_init_sf_message_store_memory(SFc1_ReachingInstanceStruct
  *chartInstance);
static void c1_chart_data_browse_helper(SFc1_ReachingInstanceStruct
  *chartInstance, int32_T c1_ssIdNumber, const mxArray **c1_mxData, uint8_T
  *c1_isValueBrowsable);
static void c1_b_sqrt(SFc1_ReachingInstanceStruct *chartInstance, real_T *c1_x);
static void init_dsm_address_info(SFc1_ReachingInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_ReachingInstanceStruct *chartInstance);

/* Function Definitions */
static void initSimStructsc1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSubchartIOPointersc1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initialize_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  sf_is_first_init_cond(chartInstance->S);
  sim_mode_is_external(chartInstance->S);
  chartInstance->c1_seed_not_empty = false;
  chartInstance->c1_method_not_empty = false;
  chartInstance->c1_state_not_empty = false;
  chartInstance->c1_b_state_not_empty = false;
  chartInstance->c1_c_state_not_empty = false;
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_temporalCounter_i1 = 0U;
  chartInstance->c1_temporalCounter_i1 = 0U;
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  if (sf_get_output_port_reusable(chartInstance->S, 1) == 0) {
    for (c1_i = 0; c1_i < 3; c1_i++) {
      (*chartInstance->c1_target_pos)[c1_i] = 0.0;
    }

    for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
      covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 10U,
                        (*chartInstance->c1_target_pos)[c1_i1]);
    }
  }

  chartInstance->c1_counter = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 1U,
                    chartInstance->c1_counter);
  chartInstance->c1_time = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 7U, chartInstance->c1_time);
  chartInstance->c1_target_color = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 6U,
                    chartInstance->c1_target_color);
  chartInstance->c1_radius = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 4U,
                    chartInstance->c1_radius);
  chartInstance->c1_angle = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 0U, chartInstance->c1_angle);
  if (sf_get_output_port_reusable(chartInstance->S, 2) == 0) {
    for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
      (*chartInstance->c1_color)[c1_i2] = 0.0;
    }

    for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
      covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 11U,
                        (*chartInstance->c1_color)[c1_i3]);
    }
  }

  if (sf_get_output_port_reusable(chartInstance->S, 3) == 0) {
    *chartInstance->c1_stop = 0.0;
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 12U,
                      *chartInstance->c1_stop);
  }

  chartInstance->c1_ext_loop = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 3U,
                    chartInstance->c1_ext_loop);
  chartInstance->c1_counter_point = 0.0;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 2U,
                    chartInstance->c1_counter_point);
  for (c1_i4 = 0; c1_i4 < 8; c1_i4++) {
    chartInstance->c1_random_angle_list[c1_i4] = 0.0;
  }

  for (c1_i5 = 0; c1_i5 < 8; c1_i5++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 5U,
                      chartInstance->c1_random_angle_list[c1_i5]);
  }

  chartInstance->c1_is_active_c1_Reaching = 0U;
  chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void mdl_start_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void mdl_setup_runtime_resources_c1_Reaching(SFc1_ReachingInstanceStruct *
  chartInstance)
{
  static const int32_T c1_b_postfixPredicateTree[3] = { 0, 1, -3 };

  static const int32_T c1_c_postfixPredicateTree[3] = { 0, 1, -3 };

  static const int32_T c1_d_postfixPredicateTree[3] = { 0, 1, -3 };

  static const int32_T c1_postfixPredicateTree[3] = { 0, 1, -3 };

  static const int32_T c1_b_condTxtEndIdx[2] = { 13, 113 };

  static const int32_T c1_b_condTxtStartIdx[2] = { 0, 14 };

  static const int32_T c1_c_condTxtEndIdx[2] = { 13, 92 };

  static const int32_T c1_c_condTxtStartIdx[2] = { 0, 14 };

  static const int32_T c1_condTxtEndIdx[2] = { 13, 112 };

  static const int32_T c1_condTxtStartIdx[2] = { 0, 14 };

  static const int32_T c1_d_condTxtEndIdx[2] = { 15, 36 };

  static const int32_T c1_d_condTxtStartIdx[2] = { 1, 18 };

  static const uint32_T c1_b_decisionTxtEndIdx = 0U;
  static const uint32_T c1_b_decisionTxtStartIdx = 0U;
  static const uint32_T c1_c_decisionTxtEndIdx = 0U;
  static const uint32_T c1_c_decisionTxtStartIdx = 0U;
  static const uint32_T c1_d_decisionTxtEndIdx = 0U;
  static const uint32_T c1_d_decisionTxtStartIdx = 0U;
  static const uint32_T c1_decisionTxtEndIdx = 0U;
  static const uint32_T c1_decisionTxtStartIdx = 0U;
  static const uint32_T c1_e_decisionTxtEndIdx = 0U;
  static const uint32_T c1_e_decisionTxtStartIdx = 0U;
  static const uint32_T c1_f_decisionTxtEndIdx = 0U;
  static const uint32_T c1_f_decisionTxtStartIdx = 0U;
  static const uint32_T c1_g_decisionTxtEndIdx = 0U;
  static const uint32_T c1_g_decisionTxtStartIdx = 0U;
  static const uint32_T c1_h_decisionTxtEndIdx = 0U;
  static const uint32_T c1_h_decisionTxtStartIdx = 0U;
  static const uint32_T c1_i_decisionTxtEndIdx = 0U;
  static const uint32_T c1_i_decisionTxtStartIdx = 0U;
  setDataBrowseFcn(chartInstance->S, (void *)&c1_chart_data_browse_helper);
  chartInstance->c1_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c1_RuntimeVar,
    &chartInstance->c1_IsDebuggerActive,
    &chartInstance->c1_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c1_mlFcnLineNumber, &chartInstance->c1_IsHeatMapPresent, 0);
  sfListenerRegisterHover(chartInstance->c1_RuntimeVar, (void *)
    &sf_c1_Reaching_getDebuggerHoverDataFor);
  sfSetAnimationVectors(chartInstance->S, &chartInstance->c1_JITStateAnimation[0],
                        &chartInstance->c1_JITTransitionAnimation[0]);
  covrtCreateStateflowInstanceData(chartInstance->c1_covrtInstance, 9U, 0U, 12U,
    37U);
  covrtChartInitFcn(chartInstance->c1_covrtInstance, 7U, true, false, false);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c1_decisionTxtStartIdx, &c1_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 1U, 0U, false, false, false,
                    0U, &c1_b_decisionTxtStartIdx, &c1_b_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 2U, 0U, false, false, false,
                    0U, &c1_c_decisionTxtStartIdx, &c1_c_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 3U, 0U, false, false, false,
                    0U, &c1_d_decisionTxtStartIdx, &c1_d_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 4U, 0U, false, false, false,
                    0U, &c1_e_decisionTxtStartIdx, &c1_e_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 5U, 0U, false, false, false,
                    0U, &c1_f_decisionTxtStartIdx, &c1_f_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 6U, 0U, false, false, false,
                    0U, &c1_g_decisionTxtStartIdx, &c1_g_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 7U, 0U, false, false, false,
                    0U, &c1_h_decisionTxtStartIdx, &c1_h_decisionTxtEndIdx);
  covrtStateInitFcn(chartInstance->c1_covrtInstance, 8U, 0U, false, false, false,
                    0U, &c1_i_decisionTxtStartIdx, &c1_i_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 2U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 1U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 10U, 0, NULL, NULL, 0U,
                    NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 3U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 11U, 0, NULL, NULL, 0U,
                    NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 4U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 5U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 6U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 7U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 8U, 0, NULL, NULL, 0U, NULL);
  covrtTransInitFcn(chartInstance->c1_covrtInstance, 9U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 8U, 1U, 0U, 0U, 0U,
                  1U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c1_covrtInstance, 4U, 8U, 0U, "randomAngle",
                     0, -1, 720);
  covrtEmlSaturationInitFcn(chartInstance->c1_covrtInstance, 4U, 8U, 0U, 596, -1,
    610);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 7U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c1_covrtInstance, 4U, 7U, 0U,
                     "computeTargetPose", 0, -1, 301);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 1U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 2U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 6U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 4U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 5U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 3U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 4U, 0U, 0U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 10U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 2U, 1U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 10U, 0U, 0, 112, -1,
                    112, false);
  covrtEmlMCDCInitFcn(chartInstance->c1_covrtInstance, 5U, 10U, 0U, 0, 112, 2U,
                      0U, &c1_condTxtStartIdx[0], &c1_condTxtEndIdx[0], 3U,
                      &c1_postfixPredicateTree[0], false);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 11U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 2U, 1U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 11U, 0U, 0, 113, -1,
                    113, false);
  covrtEmlMCDCInitFcn(chartInstance->c1_covrtInstance, 5U, 11U, 0U, 0, 113, 2U,
                      0U, &c1_b_condTxtStartIdx[0], &c1_b_condTxtEndIdx[0], 3U,
                      &c1_b_postfixPredicateTree[0], false);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 4U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 4U, 0U, 1, 79, -1, 79,
                    false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 4U, 0U, 1, 79,
    -1, 3U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 5U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 5U, 0U, 1, 78, -1, 78,
                    false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 5U, 0U, 1, 78,
    -1, 4U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 6U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 2U, 1U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 6U, 0U, 0, 92, -1, 92,
                    false);
  covrtEmlMCDCInitFcn(chartInstance->c1_covrtInstance, 5U, 6U, 0U, 0, 92, 2U, 0U,
                      &c1_c_condTxtStartIdx[0], &c1_c_condTxtEndIdx[0], 3U,
                      &c1_c_postfixPredicateTree[0], false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 6U, 0U, 14, 92,
    -1, 3U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 7U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 7U, 0U, 1, 79, -1, 79,
                    false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 7U, 0U, 1, 79,
    -1, 3U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 8U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 8U, 0U, 1, 78, -1, 78,
                    false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 8U, 0U, 1, 78,
    -1, 4U);
  covrtEmlInitFcn(chartInstance->c1_covrtInstance, "", 5U, 9U, 0U, 0U, 1U, 0U,
                  0U, 0U, 0U, 0U, 2U, 1U);
  covrtEmlIfInitFcn(chartInstance->c1_covrtInstance, 5U, 9U, 0U, 1, 36, -1, 36,
                    false);
  covrtEmlMCDCInitFcn(chartInstance->c1_covrtInstance, 5U, 9U, 0U, 1, 36, 2U, 0U,
                      &c1_d_condTxtStartIdx[0], &c1_d_condTxtEndIdx[0], 3U,
                      &c1_d_postfixPredicateTree[0], false);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 9U, 0U, 1, 15,
    -1, 0U);
  covrtEmlRelationalInitFcn(chartInstance->c1_covrtInstance, 5U, 9U, 1U, 18, 36,
    -1, 0U);
}

static void mdl_cleanup_runtime_resources_c1_Reaching
  (SFc1_ReachingInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c1_RuntimeVar);
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
  covrtDeleteStateflowInstanceData(chartInstance->c1_covrtInstance);
}

static void enable_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_set_sim_state_side_effects_c1_Reaching
  (SFc1_ReachingInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    if ((chartInstance->c1_is_c1_Reaching == c1_IN_ReachingHome) && (sf_mex_sub
         (chartInstance->c1_setSimStateSideEffectsInfo,
          "setSimStateSideEffectsInfo", 1U, 5U) == 0.0)) {
      chartInstance->c1_temporalCounter_i1 = 0U;
    }

    if ((chartInstance->c1_is_c1_Reaching == c1_IN_ReachingTarget) &&
        (sf_mex_sub(chartInstance->c1_setSimStateSideEffectsInfo,
                    "setSimStateSideEffectsInfo", 1U, 6U) == 0.0)) {
      chartInstance->c1_temporalCounter_i1 = 0U;
    }

    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void sf_gateway_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  int32_T c1_i;
  int32_T c1_i1;
  for (c1_i = 0; c1_i < 8; c1_i++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 9U,
                      (*chartInstance->c1_angles)[c1_i]);
  }

  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 8U,
                      (*chartInstance->c1_cursor_pos)[c1_i1]);
  }

  c1_set_sim_state_side_effects_c1_Reaching(chartInstance);
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c1_temporalCounter_i1 < 31) {
    chartInstance->c1_temporalCounter_i1++;
  }

  chartInstance->c1_JITTransitionAnimation[0] = 0U;
  chartInstance->c1_JITTransitionAnimation[1] = 0U;
  chartInstance->c1_JITTransitionAnimation[2] = 0U;
  chartInstance->c1_JITTransitionAnimation[3] = 0U;
  chartInstance->c1_JITTransitionAnimation[4] = 0U;
  chartInstance->c1_JITTransitionAnimation[5] = 0U;
  chartInstance->c1_JITTransitionAnimation[6] = 0U;
  chartInstance->c1_JITTransitionAnimation[7] = 0U;
  chartInstance->c1_JITTransitionAnimation[8] = 0U;
  chartInstance->c1_JITTransitionAnimation[9] = 0U;
  chartInstance->c1_JITTransitionAnimation[10] = 0U;
  chartInstance->c1_JITTransitionAnimation[11] = 0U;
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_Reaching(chartInstance);
  c1_update_jit_animation_c1_Reaching(chartInstance);
  c1_do_animation_call_c1_Reaching(chartInstance);
}

static void c1_chartstep_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  static real_T c1_dv2[3] = { 0.9, 0.5, 0.95 };

  static real_T c1_dv3[3] = { 0.0, 1.0, 0.0 };

  real_T c1_dv[8];
  real_T c1_dv1[8];
  real_T c1_a;
  real_T c1_ab_a;
  real_T c1_b_a;
  real_T c1_b_c;
  real_T c1_bb_a;
  real_T c1_c;
  real_T c1_c_a;
  real_T c1_c_c;
  real_T c1_cb_a;
  real_T c1_d;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d3;
  real_T c1_d_a;
  real_T c1_d_c;
  real_T c1_db_a;
  real_T c1_e_a;
  real_T c1_e_c;
  real_T c1_eb_a;
  real_T c1_f_a;
  real_T c1_f_c;
  real_T c1_fb_a;
  real_T c1_g_a;
  real_T c1_g_c;
  real_T c1_gb_a;
  real_T c1_h_a;
  real_T c1_h_c;
  real_T c1_hb_a;
  real_T c1_i_a;
  real_T c1_ib_a;
  real_T c1_j_a;
  real_T c1_jb_a;
  real_T c1_k_a;
  real_T c1_kb_a;
  real_T c1_l_a;
  real_T c1_lb_a;
  real_T c1_m_a;
  real_T c1_mb_a;
  real_T c1_n_a;
  real_T c1_nb_a;
  real_T c1_o_a;
  real_T c1_ob_a;
  real_T c1_p_a;
  real_T c1_q_a;
  real_T c1_r_a;
  real_T c1_s_a;
  real_T c1_t_a;
  real_T c1_u_a;
  real_T c1_v_a;
  real_T c1_w_a;
  real_T c1_x_a;
  real_T c1_y_a;
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  boolean_T c1_guard1;
  boolean_T c1_out;
  if (chartInstance->c1_is_active_c1_Reaching == 0) {
    chartInstance->c1_is_active_c1_Reaching = 1U;
    chartInstance->c1_JITTransitionAnimation[0U] = 1U;
    chartInstance->c1_is_c1_Reaching = c1_IN_Initializing;
    chartInstance->c1_ext_loop = 1.0;
    chartInstance->c1_dataWrittenToVector[8U] = true;
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 3U,
                      chartInstance->c1_ext_loop);
    chartInstance->c1_radius = 10.0;
    chartInstance->c1_dataWrittenToVector[4U] = true;
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 4U,
                      chartInstance->c1_radius);
    chartInstance->c1_counter_point = 1.0;
    chartInstance->c1_dataWrittenToVector[9U] = true;
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 2U,
                      chartInstance->c1_counter_point);
  } else {
    switch (chartInstance->c1_is_c1_Reaching) {
     case c1_IN_Finish:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0, c1_IN_Finish);
      *chartInstance->c1_stop = 1.0;
      chartInstance->c1_dataWrittenToVector[7U] = true;
      covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 12U,
                        *chartInstance->c1_stop);
      break;

     case c1_IN_Initializing:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_Initializing);
      chartInstance->c1_JITTransitionAnimation[1U] = 1U;
      chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
      chartInstance->c1_is_c1_Reaching = c1_IN_RandomAngleList;
      for (c1_i = 0; c1_i < 8; c1_i++) {
        c1_dv[c1_i] = (*chartInstance->c1_angles)[c1_i];
      }

      c1_randomAngle(chartInstance, c1_dv, c1_dv1);
      for (c1_i1 = 0; c1_i1 < 8; c1_i1++) {
        chartInstance->c1_random_angle_list[c1_i1] = c1_dv1[c1_i1];
      }

      chartInstance->c1_dataWrittenToVector[10U] = true;
      for (c1_i2 = 0; c1_i2 < 8; c1_i2++) {
        covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 5U,
                          chartInstance->c1_random_angle_list[c1_i2]);
      }
      break;

     case c1_IN_RandomAngleList:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_RandomAngleList);
      chartInstance->c1_JITTransitionAnimation[3U] = 1U;
      chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
      chartInstance->c1_is_c1_Reaching = c1_IN_SpawnTarget;
      c1_enter_atomic_SpawnTarget(chartInstance);
      break;

     case c1_IN_ReachingHome:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_ReachingHome);
      c1_ReachingHome(chartInstance);
      break;

     case c1_IN_ReachingTarget:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_ReachingTarget);
      if (!chartInstance->c1_dataWrittenToVector[0U]) {
        sf_read_before_write_error(chartInstance->S, 10U, 32U, 7, 10);
      }

      c1_a = (*chartInstance->c1_target_pos)[0] - (*chartInstance->c1_cursor_pos)
        [0];
      c1_d_a = c1_a;
      c1_g_a = c1_d_a;
      c1_j_a = c1_g_a;
      c1_m_a = c1_j_a;
      c1_c = c1_m_a * c1_m_a;
      c1_p_a = (*chartInstance->c1_target_pos)[1] -
        (*chartInstance->c1_cursor_pos)[1];
      c1_s_a = c1_p_a;
      c1_v_a = c1_s_a;
      c1_y_a = c1_v_a;
      c1_cb_a = c1_y_a;
      c1_d_c = c1_cb_a * c1_cb_a;
      c1_d = c1_c + c1_d_c;
      c1_b_sqrt(chartInstance, &c1_d);
      if (covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 5, 0,
                         covrtRelationalopUpdateFcn
                         (chartInstance->c1_covrtInstance, 5U, 5U, 0U, c1_d, 0.4,
                          -1, 4U, c1_d > 0.4))) {
        c1_out = true;
      } else {
        chartInstance->c1_dataWrittenToVector[0U] = true;
        c1_out = false;
      }

      if (c1_out) {
        chartInstance->c1_JITTransitionAnimation[5U] = 1U;
        chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
        chartInstance->c1_is_c1_Reaching = c1_IN_SpawnTarget;
        c1_enter_atomic_SpawnTarget(chartInstance);
      } else {
        sf_temporal_value_range_check_min(chartInstance->S, 34U, 10.0, 0.0);
        c1_guard1 = false;
        if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 6, 0,
                             chartInstance->c1_temporalCounter_i1 >= 10)) {
          c1_fb_a = (*chartInstance->c1_target_pos)[0] -
            (*chartInstance->c1_cursor_pos)[0];
          c1_gb_a = c1_fb_a;
          c1_hb_a = c1_gb_a;
          c1_ib_a = c1_hb_a;
          c1_jb_a = c1_ib_a;
          c1_g_c = c1_jb_a * c1_jb_a;
          c1_kb_a = (*chartInstance->c1_target_pos)[1] -
            (*chartInstance->c1_cursor_pos)[1];
          c1_lb_a = c1_kb_a;
          c1_mb_a = c1_lb_a;
          c1_nb_a = c1_mb_a;
          c1_ob_a = c1_nb_a;
          c1_h_c = c1_ob_a * c1_ob_a;
          c1_d3 = c1_g_c + c1_h_c;
          c1_b_sqrt(chartInstance, &c1_d3);
          if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 6, 1,
                               covrtRelationalopUpdateFcn
                               (chartInstance->c1_covrtInstance, 5U, 6U, 0U,
                                c1_d3, 0.4, -1, 3U, c1_d3 <= 0.4))) {
            covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 6, 0, true);
            covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 6, 0, true);
            c1_d_out = true;
          } else {
            chartInstance->c1_dataWrittenToVector[0U] = true;
            c1_guard1 = true;
          }
        } else {
          if (!chartInstance->c1_dataWrittenToVector[0U]) {
            sf_read_before_write_error(chartInstance->S, 10U, 34U, 20, 10);
          }

          c1_guard1 = true;
        }

        if (c1_guard1) {
          covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 6, 0, false);
          covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 6, 0, false);
          c1_d_out = false;
        }

        if (c1_d_out) {
          chartInstance->c1_JITTransitionAnimation[6U] = 1U;
          chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
          chartInstance->c1_is_c1_Reaching = c1_IN_SpawnHome;
          c1_enter_atomic_SpawnHome(chartInstance);
        }
      }
      break;

     case c1_IN_SpawnHome:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_SpawnHome);
      if (!chartInstance->c1_dataWrittenToVector[0U]) {
        sf_read_before_write_error(chartInstance->S, 10U, 37U, 7, 10);
      }

      c1_b_a = (*chartInstance->c1_target_pos)[0] -
        (*chartInstance->c1_cursor_pos)[0];
      c1_e_a = c1_b_a;
      c1_h_a = c1_e_a;
      c1_k_a = c1_h_a;
      c1_n_a = c1_k_a;
      c1_b_c = c1_n_a * c1_n_a;
      c1_q_a = (*chartInstance->c1_target_pos)[1] -
        (*chartInstance->c1_cursor_pos)[1];
      c1_t_a = c1_q_a;
      c1_w_a = c1_t_a;
      c1_ab_a = c1_w_a;
      c1_db_a = c1_ab_a;
      c1_e_c = c1_db_a * c1_db_a;
      c1_d1 = c1_b_c + c1_e_c;
      c1_b_sqrt(chartInstance, &c1_d1);
      if (covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 7, 0,
                         covrtRelationalopUpdateFcn
                         (chartInstance->c1_covrtInstance, 5U, 7U, 0U, c1_d1,
                          0.4, -1, 3U, c1_d1 <= 0.4))) {
        c1_b_out = true;
      } else {
        chartInstance->c1_dataWrittenToVector[0U] = true;
        c1_b_out = false;
      }

      if (c1_b_out) {
        chartInstance->c1_JITTransitionAnimation[7U] = 1U;
        chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
        chartInstance->c1_temporalCounter_i1 = 0U;
        chartInstance->c1_is_c1_Reaching = c1_IN_ReachingHome;
        for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
          (*chartInstance->c1_color)[c1_i3] = c1_dv2[c1_i3];
        }

        chartInstance->c1_dataWrittenToVector[6U] = true;
        for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
          covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 11U,
                            (*chartInstance->c1_color)[c1_i5]);
        }
      }
      break;

     case c1_IN_SpawnTarget:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0,
                        c1_IN_SpawnTarget);
      if (!chartInstance->c1_dataWrittenToVector[0U]) {
        sf_read_before_write_error(chartInstance->S, 10U, 31U, 7, 10);
      }

      c1_c_a = (*chartInstance->c1_target_pos)[0] -
        (*chartInstance->c1_cursor_pos)[0];
      c1_f_a = c1_c_a;
      c1_i_a = c1_f_a;
      c1_l_a = c1_i_a;
      c1_o_a = c1_l_a;
      c1_c_c = c1_o_a * c1_o_a;
      c1_r_a = (*chartInstance->c1_target_pos)[1] -
        (*chartInstance->c1_cursor_pos)[1];
      c1_u_a = c1_r_a;
      c1_x_a = c1_u_a;
      c1_bb_a = c1_x_a;
      c1_eb_a = c1_bb_a;
      c1_f_c = c1_eb_a * c1_eb_a;
      c1_d2 = c1_c_c + c1_f_c;
      c1_b_sqrt(chartInstance, &c1_d2);
      if (covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 4, 0,
                         covrtRelationalopUpdateFcn
                         (chartInstance->c1_covrtInstance, 5U, 4U, 0U, c1_d2,
                          0.4, -1, 3U, c1_d2 <= 0.4))) {
        c1_c_out = true;
      } else {
        chartInstance->c1_dataWrittenToVector[0U] = true;
        c1_c_out = false;
      }

      if (c1_c_out) {
        chartInstance->c1_JITTransitionAnimation[4U] = 1U;
        chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
        chartInstance->c1_temporalCounter_i1 = 0U;
        chartInstance->c1_is_c1_Reaching = c1_IN_ReachingTarget;
        for (c1_i4 = 0; c1_i4 < 3; c1_i4++) {
          (*chartInstance->c1_color)[c1_i4] = c1_dv3[c1_i4];
        }

        chartInstance->c1_dataWrittenToVector[6U] = true;
        for (c1_i6 = 0; c1_i6 < 3; c1_i6++) {
          covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 11U,
                            (*chartInstance->c1_color)[c1_i6]);
        }
      }
      break;

     default:
      covrtDecUpdateFcn(chartInstance->c1_covrtInstance, 1U, 0, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
      break;
    }
  }
}

static void ext_mode_exec_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

void mdlZeroCrossings_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_jit_animation_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  chartInstance->c1_JITStateAnimation[0U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_Initializing);
  chartInstance->c1_JITStateAnimation[1U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_RandomAngleList);
  chartInstance->c1_JITStateAnimation[2U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_SpawnTarget);
  chartInstance->c1_JITStateAnimation[3U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_ReachingTarget);
  chartInstance->c1_JITStateAnimation[4U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_SpawnHome);
  chartInstance->c1_JITStateAnimation[5U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_ReachingHome);
  chartInstance->c1_JITStateAnimation[6U] = (uint8_T)
    (chartInstance->c1_is_c1_Reaching == c1_IN_Finish);
}

static void c1_do_animation_call_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static const mxArray *get_sim_state_c1_Reaching(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  const mxArray *c1_b_y = NULL;
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_d_y = NULL;
  const mxArray *c1_e_y = NULL;
  const mxArray *c1_f_y = NULL;
  const mxArray *c1_g_y = NULL;
  const mxArray *c1_h_y = NULL;
  const mxArray *c1_i_y = NULL;
  const mxArray *c1_j_y = NULL;
  const mxArray *c1_k_y = NULL;
  const mxArray *c1_l_y = NULL;
  const mxArray *c1_m_y = NULL;
  const mxArray *c1_n_y = NULL;
  const mxArray *c1_o_y = NULL;
  const mxArray *c1_p_y = NULL;
  const mxArray *c1_q_y = NULL;
  const mxArray *c1_r_y = NULL;
  const mxArray *c1_s_y = NULL;
  const mxArray *c1_st;
  const mxArray *c1_t_y = NULL;
  const mxArray *c1_u_y = NULL;
  const mxArray *c1_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(20, 1), false);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", *chartInstance->c1_color, 0, 0U, 1,
    0U, 2, 1, 3), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", chartInstance->c1_stop, 0, 0U, 0, 0U,
    0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", *chartInstance->c1_target_pos, 0, 0U,
    1, 0U, 2, 1, 3), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &chartInstance->c1_angle, 0, 0U, 0,
    0U, 0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &chartInstance->c1_counter, 0, 0U, 0,
    0U, 0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &chartInstance->c1_counter_point, 0,
    0U, 0, 0U, 0), false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &chartInstance->c1_ext_loop, 0, 0U,
    0, 0U, 0), false);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &chartInstance->c1_radius, 0, 0U, 0,
    0U, 0), false);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", chartInstance->c1_random_angle_list,
    0, 0U, 1, 0U, 1, 8), false);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &chartInstance->c1_target_color, 0,
    0U, 0, 0U, 0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &chartInstance->c1_time, 0, 0U, 0,
    0U, 0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_m_y = NULL;
  if (!chartInstance->c1_method_not_empty) {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", NULL, 0, 0U, 1, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", &chartInstance->c1_method, 7, 0U,
      0, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_n_y = NULL;
  if (!chartInstance->c1_method_not_empty) {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", NULL, 0, 0U, 1, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", &chartInstance->c1_seed, 7, 0U, 0,
      0U, 0), false);
  }

  sf_mex_setcell(c1_y, 12, c1_n_y);
  c1_o_y = NULL;
  if (!chartInstance->c1_method_not_empty) {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", NULL, 0, 0U, 1, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", &chartInstance->c1_c_state, 7, 0U,
      0, 0U, 0), false);
  }

  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_p_y = NULL;
  if (!chartInstance->c1_state_not_empty) {
    sf_mex_assign(&c1_p_y, sf_mex_create("y", NULL, 0, 0U, 1, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_p_y, sf_mex_create("y", chartInstance->c1_state, 7, 0U, 1,
      0U, 1, 625), false);
  }

  sf_mex_setcell(c1_y, 14, c1_p_y);
  c1_q_y = NULL;
  if (!chartInstance->c1_b_state_not_empty) {
    sf_mex_assign(&c1_q_y, sf_mex_create("y", NULL, 0, 0U, 1, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c1_q_y, sf_mex_create("y", chartInstance->c1_b_state, 7, 0U,
      1, 0U, 1, 2), false);
  }

  sf_mex_setcell(c1_y, 15, c1_q_y);
  c1_r_y = NULL;
  sf_mex_assign(&c1_r_y, sf_mex_create("y",
    &chartInstance->c1_is_active_c1_Reaching, 3, 0U, 0, 0U, 0), false);
  sf_mex_setcell(c1_y, 16, c1_r_y);
  c1_s_y = NULL;
  sf_mex_assign(&c1_s_y, sf_mex_create("y", &chartInstance->c1_is_c1_Reaching, 7,
    0U, 0, 0U, 0), false);
  sf_mex_setcell(c1_y, 17, c1_s_y);
  c1_t_y = NULL;
  sf_mex_assign(&c1_t_y, sf_mex_create("y",
    &chartInstance->c1_temporalCounter_i1, 3, 0U, 0, 0U, 0), false);
  sf_mex_setcell(c1_y, 18, c1_t_y);
  c1_u_y = NULL;
  sf_mex_assign(&c1_u_y, sf_mex_create("y",
    chartInstance->c1_dataWrittenToVector, 11, 0U, 1, 0U, 1, 13), false);
  sf_mex_setcell(c1_y, 19, c1_u_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_Reaching(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv2[8];
  real_T c1_dv[3];
  real_T c1_dv1[3];
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  uint32_T c1_b_uv[625];
  uint32_T c1_uv1[2];
  boolean_T c1_bv[13];
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "color", c1_dv);
  for (c1_i = 0; c1_i < 3; c1_i++) {
    (*chartInstance->c1_color)[c1_i] = c1_dv[c1_i];
  }

  *chartInstance->c1_stop = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 1)), "stop");
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
                      "target_pos", c1_dv1);
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    (*chartInstance->c1_target_pos)[c1_i1] = c1_dv1[c1_i1];
  }

  chartInstance->c1_angle = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 3)), "angle");
  chartInstance->c1_counter = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 4)), "counter");
  chartInstance->c1_counter_point = c1_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 5)), "counter_point");
  chartInstance->c1_ext_loop = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 6)), "ext_loop");
  chartInstance->c1_radius = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 7)), "radius");
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 8)),
                        "random_angle_list", c1_dv2);
  for (c1_i2 = 0; c1_i2 < 8; c1_i2++) {
    chartInstance->c1_random_angle_list[c1_i2] = c1_dv2[c1_i2];
  }

  chartInstance->c1_target_color = c1_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 9)), "target_color");
  chartInstance->c1_time = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 10)), "time");
  chartInstance->c1_method = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 11)), "method", &chartInstance->c1_method_not_empty);
  chartInstance->c1_seed = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 12)), "seed", &chartInstance->c1_seed_not_empty);
  chartInstance->c1_c_state = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 13)), "state", &chartInstance->c1_c_state_not_empty);
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 14)),
                        "state", &chartInstance->c1_state_not_empty, c1_b_uv);
  for (c1_i3 = 0; c1_i3 < 625; c1_i3++) {
    chartInstance->c1_state[c1_i3] = c1_b_uv[c1_i3];
  }

  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 15)),
                        "state", &chartInstance->c1_b_state_not_empty, c1_uv1);
  for (c1_i4 = 0; c1_i4 < 2; c1_i4++) {
    chartInstance->c1_b_state[c1_i4] = c1_uv1[c1_i4];
  }

  chartInstance->c1_is_active_c1_Reaching = c1_m_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 16)), "is_active_c1_Reaching");
  chartInstance->c1_is_c1_Reaching = c1_o_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 17)), "is_c1_Reaching");
  chartInstance->c1_temporalCounter_i1 = c1_m_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 18)), "temporalCounter_i1");
  c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 19)),
                        "dataWrittenToVector", c1_bv);
  for (c1_i5 = 0; c1_i5 < 13; c1_i5++) {
    chartInstance->c1_dataWrittenToVector[c1_i5] = c1_bv[c1_i5];
  }

  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 20)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_jit_animation_c1_Reaching(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_ReachingHome(SFc1_ReachingInstanceStruct *chartInstance)
{
  const mxArray *c1_b_y = NULL;
  const mxArray *c1_y = NULL;
  real_T c1_dv[8];
  real_T c1_dv1[8];
  real_T c1_a;
  real_T c1_ab_a;
  real_T c1_b_a;
  real_T c1_b_c;
  real_T c1_bb_a;
  real_T c1_c;
  real_T c1_c_a;
  real_T c1_c_c;
  real_T c1_cb_a;
  real_T c1_d;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d_a;
  real_T c1_d_c;
  real_T c1_db_a;
  real_T c1_e_a;
  real_T c1_e_c;
  real_T c1_eb_a;
  real_T c1_f_a;
  real_T c1_f_c;
  real_T c1_g_a;
  real_T c1_h_a;
  real_T c1_i_a;
  real_T c1_j_a;
  real_T c1_k_a;
  real_T c1_l_a;
  real_T c1_m_a;
  real_T c1_n_a;
  real_T c1_o_a;
  real_T c1_p_a;
  real_T c1_q_a;
  real_T c1_r_a;
  real_T c1_s_a;
  real_T c1_t_a;
  real_T c1_u_a;
  real_T c1_v_a;
  real_T c1_w_a;
  real_T c1_x_a;
  real_T c1_y_a;
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  boolean_T c1_b;
  boolean_T c1_b1;
  boolean_T c1_b2;
  boolean_T c1_b3;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  boolean_T c1_guard1;
  boolean_T c1_out;
  if (!chartInstance->c1_dataWrittenToVector[0U]) {
    sf_read_before_write_error(chartInstance->S, 10U, 38U, 7, 10);
  }

  c1_a = (*chartInstance->c1_target_pos)[0] - (*chartInstance->c1_cursor_pos)[0];
  c1_b_a = c1_a;
  c1_c_a = c1_b_a;
  c1_d_a = c1_c_a;
  c1_e_a = c1_d_a;
  c1_c = c1_e_a * c1_e_a;
  c1_f_a = (*chartInstance->c1_target_pos)[1] - (*chartInstance->c1_cursor_pos)
    [1];
  c1_g_a = c1_f_a;
  c1_h_a = c1_g_a;
  c1_i_a = c1_h_a;
  c1_j_a = c1_i_a;
  c1_b_c = c1_j_a * c1_j_a;
  c1_d = c1_c + c1_b_c;
  c1_b_sqrt(chartInstance, &c1_d);
  if (covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 8, 0,
                     covrtRelationalopUpdateFcn(chartInstance->c1_covrtInstance,
        5U, 8U, 0U, c1_d, 0.4, -1, 4U, c1_d > 0.4))) {
    c1_out = true;
  } else {
    chartInstance->c1_dataWrittenToVector[0U] = true;
    c1_out = false;
  }

  if (c1_out) {
    chartInstance->c1_JITTransitionAnimation[8U] = 1U;
    chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
    chartInstance->c1_is_c1_Reaching = c1_IN_SpawnHome;
    c1_enter_atomic_SpawnHome(chartInstance);
  } else {
    if (!chartInstance->c1_dataWrittenToVector[8U]) {
      sf_read_before_write_error(chartInstance->S, 3U, 40U, 1, 8);
    }

    c1_guard1 = false;
    if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 9, 0,
                         covrtRelationalopUpdateFcn
                         (chartInstance->c1_covrtInstance, 5U, 9U, 0U,
                          chartInstance->c1_ext_loop, 10.0, -1, 0U,
                          chartInstance->c1_ext_loop == 10.0))) {
      if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 9, 1,
                           covrtRelationalopUpdateFcn
                           (chartInstance->c1_covrtInstance, 5U, 9U, 1U,
                            chartInstance->c1_counter_point, 8.0, -1, 0U,
                            chartInstance->c1_counter_point == 8.0))) {
        covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 9, 0, true);
        covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 9, 0, true);
        c1_b_out = true;
      } else {
        c1_guard1 = true;
      }
    } else {
      if (!chartInstance->c1_dataWrittenToVector[9U]) {
        sf_read_before_write_error(chartInstance->S, 2U, 40U, 18, 13);
      }

      c1_guard1 = true;
    }

    if (c1_guard1) {
      covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 9, 0, false);
      covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 9, 0, false);
      c1_b_out = false;
    }

    if (c1_b_out) {
      chartInstance->c1_JITTransitionAnimation[9U] = 1U;
      chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
      chartInstance->c1_is_c1_Reaching = c1_IN_Finish;
      *chartInstance->c1_stop = 1.0;
      chartInstance->c1_dataWrittenToVector[7U] = true;
      covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 12U,
                        *chartInstance->c1_stop);
    } else {
      sf_temporal_value_range_check_min(chartInstance->S, 41U, 20.0, 0.0);
      c1_guard1 = false;
      if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 10, 0,
                           chartInstance->c1_temporalCounter_i1 >= 20)) {
        c1_b = (chartInstance->c1_counter_point == 8.0);
        if (!chartInstance->c1_dataWrittenToVector[0U]) {
          sf_read_before_write_error(chartInstance->S, 10U, 41U, 41, 10);
        }

        c1_k_a = (*chartInstance->c1_target_pos)[0] -
          (*chartInstance->c1_cursor_pos)[0];
        c1_l_a = c1_k_a;
        c1_m_a = c1_l_a;
        c1_n_a = c1_m_a;
        c1_o_a = c1_n_a;
        c1_c_c = c1_o_a * c1_o_a;
        c1_p_a = (*chartInstance->c1_target_pos)[1] -
          (*chartInstance->c1_cursor_pos)[1];
        c1_q_a = c1_p_a;
        c1_r_a = c1_q_a;
        c1_s_a = c1_r_a;
        c1_u_a = c1_s_a;
        c1_d_c = c1_u_a * c1_u_a;
        c1_d1 = c1_c_c + c1_d_c;
        c1_b_sqrt(chartInstance, &c1_d1);
        c1_b2 = (c1_d1 < 0.4);
        chartInstance->c1_dataWrittenToVector[0U] = true;
        if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 10, 1, c1_b &&
                             c1_b2)) {
          covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 10, 0, true);
          covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 10, 0, true);
          c1_c_out = true;
        } else {
          c1_guard1 = true;
        }
      } else {
        if (!chartInstance->c1_dataWrittenToVector[9U]) {
          sf_read_before_write_error(chartInstance->S, 2U, 41U, 14, 13);
        }

        c1_guard1 = true;
      }

      if (c1_guard1) {
        covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 10, 0, false);
        covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 10, 0, false);
        c1_c_out = false;
      }

      if (c1_c_out) {
        chartInstance->c1_JITTransitionAnimation[10U] = 1U;
        if (!chartInstance->c1_dataWrittenToVector[8U]) {
          sf_read_before_write_error(chartInstance->S, 3U, 41U, 125, 8);
        }

        chartInstance->c1_ext_loop++;
        chartInstance->c1_dataWrittenToVector[8U] = true;
        covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 3U,
                          chartInstance->c1_ext_loop);
        if (!chartInstance->c1_dataWrittenToVector[8U]) {
          sf_read_before_write_error(chartInstance->S, 3U, 41U, 114, 8);
        }

        sf_mex_printf("%s =\\n", "ext_loop");
        c1_y = NULL;
        sf_mex_assign(&c1_y, sf_mex_create("y", &chartInstance->c1_ext_loop, 0,
          0U, 0, 0U, 0), false);
        sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL, "disp", 0U, 1U, 14, c1_y);
        chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
        chartInstance->c1_is_c1_Reaching = c1_IN_RandomAngleList;
        for (c1_i = 0; c1_i < 8; c1_i++) {
          c1_dv[c1_i] = (*chartInstance->c1_angles)[c1_i];
        }

        c1_randomAngle(chartInstance, c1_dv, c1_dv1);
        for (c1_i1 = 0; c1_i1 < 8; c1_i1++) {
          chartInstance->c1_random_angle_list[c1_i1] = c1_dv1[c1_i1];
        }

        chartInstance->c1_dataWrittenToVector[10U] = true;
        for (c1_i2 = 0; c1_i2 < 8; c1_i2++) {
          covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 5U,
                            chartInstance->c1_random_angle_list[c1_i2]);
        }
      } else {
        sf_temporal_value_range_check_min(chartInstance->S, 42U, 20.0, 0.0);
        c1_guard1 = false;
        if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 11, 0,
                             chartInstance->c1_temporalCounter_i1 >= 20)) {
          c1_b1 = (chartInstance->c1_counter_point != 8.0);
          if (!chartInstance->c1_dataWrittenToVector[0U]) {
            sf_read_before_write_error(chartInstance->S, 10U, 42U, 41, 10);
          }

          c1_t_a = (*chartInstance->c1_target_pos)[0] -
            (*chartInstance->c1_cursor_pos)[0];
          c1_v_a = c1_t_a;
          c1_w_a = c1_v_a;
          c1_x_a = c1_w_a;
          c1_y_a = c1_x_a;
          c1_e_c = c1_y_a * c1_y_a;
          c1_ab_a = (*chartInstance->c1_target_pos)[1] -
            (*chartInstance->c1_cursor_pos)[1];
          c1_bb_a = c1_ab_a;
          c1_cb_a = c1_bb_a;
          c1_db_a = c1_cb_a;
          c1_eb_a = c1_db_a;
          c1_f_c = c1_eb_a * c1_eb_a;
          c1_d2 = c1_e_c + c1_f_c;
          c1_b_sqrt(chartInstance, &c1_d2);
          c1_b3 = (c1_d2 <= 0.4);
          chartInstance->c1_dataWrittenToVector[0U] = true;
          if (covrtEmlCondEval(chartInstance->c1_covrtInstance, 5U, 11, 1, c1_b1
                               && c1_b3)) {
            covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 11, 0, true);
            covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 11, 0, true);
            c1_d_out = true;
          } else {
            c1_guard1 = true;
          }
        } else {
          if (!chartInstance->c1_dataWrittenToVector[9U]) {
            sf_read_before_write_error(chartInstance->S, 2U, 42U, 14, 13);
          }

          c1_guard1 = true;
        }

        if (c1_guard1) {
          covrtEmlMcdcEval(chartInstance->c1_covrtInstance, 5U, 11, 0, false);
          covrtEmlIfEval(chartInstance->c1_covrtInstance, 5U, 11, 0, false);
          c1_d_out = false;
        }

        if (c1_d_out) {
          chartInstance->c1_JITTransitionAnimation[11U] = 1U;
          if (!chartInstance->c1_dataWrittenToVector[9U]) {
            sf_read_before_write_error(chartInstance->S, 2U, 42U, 131, 13);
          }

          chartInstance->c1_counter_point++;
          chartInstance->c1_dataWrittenToVector[9U] = true;
          covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 2U,
                            chartInstance->c1_counter_point);
          if (!chartInstance->c1_dataWrittenToVector[9U]) {
            sf_read_before_write_error(chartInstance->S, 2U, 42U, 115, 13);
          }

          sf_mex_printf("%s =\\n", "counter_point");
          c1_b_y = NULL;
          sf_mex_assign(&c1_b_y, sf_mex_create("y",
            &chartInstance->c1_counter_point, 0, 0U, 0, 0U, 0), false);
          sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL, "disp", 0U, 1U, 14,
                      c1_b_y);
          chartInstance->c1_is_c1_Reaching = c1_IN_NO_ACTIVE_CHILD;
          chartInstance->c1_is_c1_Reaching = c1_IN_SpawnTarget;
          c1_enter_atomic_SpawnTarget(chartInstance);
        }
      }
    }
  }
}

static void c1_enter_atomic_SpawnHome(SFc1_ReachingInstanceStruct *chartInstance)
{
  static real_T c1_dv[3] = { 0.5, 0.0, 1.0 };

  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  for (c1_i = 0; c1_i < 3; c1_i++) {
    (*chartInstance->c1_target_pos)[c1_i] = 0.0;
  }

  chartInstance->c1_dataWrittenToVector[0U] = true;
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 10U,
                      (*chartInstance->c1_target_pos)[c1_i1]);
  }

  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    (*chartInstance->c1_color)[c1_i2] = c1_dv[c1_i2];
  }

  chartInstance->c1_dataWrittenToVector[6U] = true;
  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 11U,
                      (*chartInstance->c1_color)[c1_i3]);
  }
}

static void c1_enter_atomic_SpawnTarget(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  static real_T c1_dv[3] = { 1.0, 0.0, 0.0 };

  real_T c1_dv1[3];
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  for (c1_i = 0; c1_i < 3; c1_i++) {
    (*chartInstance->c1_color)[c1_i] = c1_dv[c1_i];
  }

  chartInstance->c1_dataWrittenToVector[6U] = true;
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 11U,
                      (*chartInstance->c1_color)[c1_i1]);
  }

  if (!chartInstance->c1_dataWrittenToVector[10U]) {
    sf_read_before_write_error(chartInstance->S, 5U, 7U, 67, 17);
  }

  if (!chartInstance->c1_dataWrittenToVector[9U]) {
    sf_read_before_write_error(chartInstance->S, 2U, 7U, 85, 13);
  }

  if (!chartInstance->c1_dataWrittenToVector[4U]) {
    sf_read_before_write_error(chartInstance->S, 4U, 7U, 101, 6);
  }

  c1_computeTargetPose(chartInstance, chartInstance->
                       c1_random_angle_list[sf_array_bounds_check
                       (chartInstance->S, 7U, 67, 32, 5,
                        sf_eml_array_bounds_check(chartInstance->S, 7U, 85, 13,
    5, (int32_T)sf_integer_check(chartInstance->S, 7U, 85, 13,
    chartInstance->c1_counter_point), 1, 8) - 1, 0, 7)],
                       chartInstance->c1_radius, c1_dv1);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    (*chartInstance->c1_target_pos)[c1_i2] = c1_dv1[c1_i2];
  }

  chartInstance->c1_dataWrittenToVector[0U] = true;
  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 10U,
                      (*chartInstance->c1_target_pos)[c1_i3]);
  }
}

static void c1_randomAngle(SFc1_ReachingInstanceStruct *chartInstance, real_T
  c1_angle_list[8], real_T c1_b_random_angle_list[8])
{
  static char_T c1_cv[22] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'r', 'n', 'g',
    ':', 'b', 'a', 'd', 'S', 'e', 't', 't', 'i', 'n', 'g', 's' };

  time_t c1_b_eTime;
  time_t c1_eTime;
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_d_y = NULL;
  real_T c1_random_indeces[8];
  real_T c1_a;
  real_T c1_b;
  real_T c1_b_b;
  real_T c1_b_mti;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_c_x;
  real_T c1_d;
  real_T c1_d1;
  real_T c1_d_a;
  real_T c1_d_x;
  real_T c1_e_a;
  real_T c1_e_x;
  real_T c1_f_a;
  real_T c1_f_x;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_h_b;
  real_T c1_i_b;
  real_T c1_s;
  real_T c1_s0;
  real_T c1_x;
  real_T c1_y;
  int32_T c1_idx[8];
  int32_T c1_iwork[8];
  int32_T c1_b_a;
  int32_T c1_b_i;
  int32_T c1_b_i2;
  int32_T c1_b_idx1;
  int32_T c1_b_idx2;
  int32_T c1_b_k;
  int32_T c1_b_p;
  int32_T c1_c_k;
  int32_T c1_e_b;
  int32_T c1_exitg1;
  int32_T c1_f_b;
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  int32_T c1_i6;
  int32_T c1_idx1;
  int32_T c1_idx2;
  int32_T c1_j;
  int32_T c1_k;
  int32_T c1_kEnd;
  int32_T c1_mti;
  int32_T c1_pEnd;
  int32_T c1_prevEpochTime;
  int32_T c1_q;
  int32_T c1_qEnd;
  int32_T c1_t;
  uint32_T c1_arg3;
  uint32_T c1_b_arg3;
  uint32_T c1_b_r;
  uint32_T c1_b_s;
  uint32_T c1_b_seed;
  uint32_T c1_b_t;
  uint32_T c1_b_varargin_1;
  uint32_T c1_c_arg3;
  uint32_T c1_c_seed;
  uint32_T c1_c_varargin_1;
  uint32_T c1_method2;
  uint32_T c1_r;
  uint32_T c1_u;
  uint32_T c1_u1;
  uint32_T c1_varargin_1;
  boolean_T c1_c_p;
  boolean_T c1_covSaturation = false;
  boolean_T c1_d_b;
  boolean_T c1_d_p;
  boolean_T c1_e_p;
  boolean_T c1_f_p;
  boolean_T c1_g_p;
  boolean_T c1_j_b;
  boolean_T c1_overflow;
  boolean_T c1_p;
  for (c1_i = 0; c1_i < 8; c1_i++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 13U, c1_angle_list[c1_i]);
  }

  covrtEmlFcnEval(chartInstance->c1_covrtInstance, 4U, 8, 0);
  if (!chartInstance->c1_seed_not_empty) {
    chartInstance->c1_seed = 0U;
    chartInstance->c1_seed_not_empty = true;
  }

  if (!chartInstance->c1_method_not_empty) {
    chartInstance->c1_method = 7U;
    chartInstance->c1_method_not_empty = true;
  }

  c1_x = c1_now(chartInstance) * 8.64E+6;
  c1_b_x = c1_x;
  c1_y = c1_b_x;
  c1_y = muDoubleScalarFloor(c1_y);
  c1_s = c1_mod(chartInstance, c1_y);
  c1_eTime = time(NULL);
  c1_prevEpochTime = (int32_T)c1_eTime + 1;
  do {
    c1_exitg1 = 0;
    c1_b_eTime = time(NULL);
    c1_t = (int32_T)c1_b_eTime;
    if (c1_t <= c1_prevEpochTime) {
      c1_c_x = c1_now(chartInstance) * 8.64E+6;
      c1_d_x = c1_c_x;
      c1_b_y = c1_d_x;
      c1_b_y = muDoubleScalarFloor(c1_b_y);
      c1_s0 = c1_mod(chartInstance, c1_b_y);
      if (c1_s != c1_s0) {
        c1_exitg1 = 1;
      }
    } else {
      c1_exitg1 = 1;
    }
  } while (c1_exitg1 == 0);

  c1_d = muDoubleScalarRound(c1_s);
  c1_covSaturation = false;
  if (c1_d < 4.294967296E+9) {
    if (c1_d >= 0.0) {
      c1_u = (uint32_T)c1_d;
    } else {
      c1_covSaturation = true;
      c1_u = 0U;
    }
  } else if (c1_d >= 4.294967296E+9) {
    c1_covSaturation = true;
    c1_u = MAX_uint32_T;
  } else {
    c1_u = 0U;
  }

  covrtSaturationUpdateFcn(chartInstance->c1_covrtInstance, 4, 8, 0, 0,
    c1_covSaturation);
  chartInstance->c1_seed = c1_u;
  if (!chartInstance->c1_method_not_empty) {
    chartInstance->c1_method = 7U;
    chartInstance->c1_method_not_empty = true;
  }

  c1_method2 = chartInstance->c1_method;
  if (c1_method2 == 7U) {
    c1_varargin_1 = chartInstance->c1_seed;
    if (!chartInstance->c1_state_not_empty) {
      for (c1_i1 = 0; c1_i1 < 625; c1_i1++) {
        chartInstance->c1_state[c1_i1] = c1_uv[c1_i1];
      }

      chartInstance->c1_state_not_empty = true;
    }

    c1_arg3 = c1_varargin_1;
    c1_b_seed = c1_arg3;
    c1_r = c1_b_seed;
    chartInstance->c1_state[0] = c1_b_seed;
    for (c1_mti = 0; c1_mti < 623; c1_mti++) {
      c1_b_mti = 2.0 + (real_T)c1_mti;
      c1_d1 = muDoubleScalarRound(c1_b_mti - 1.0);
      if (c1_d1 < 4.294967296E+9) {
        if (c1_d1 >= 0.0) {
          c1_u1 = (uint32_T)c1_d1;
        } else {
          c1_u1 = 0U;
        }
      } else if (c1_d1 >= 4.294967296E+9) {
        c1_u1 = MAX_uint32_T;
      } else {
        c1_u1 = 0U;
      }

      c1_r = (c1_r ^ c1_r >> 30U) * 1812433253U + c1_u1;
      chartInstance->c1_state[(int32_T)c1_b_mti - 1] = c1_r;
    }

    chartInstance->c1_state[624] = 624U;
  } else if (c1_method2 == 5U) {
    c1_b_varargin_1 = chartInstance->c1_seed;
    if (!chartInstance->c1_b_state_not_empty) {
      for (c1_i2 = 0; c1_i2 < 2; c1_i2++) {
        chartInstance->c1_b_state[c1_i2] = 362436069U + 158852560U * (uint32_T)
          c1_i2;
      }

      chartInstance->c1_b_state_not_empty = true;
    }

    c1_b_arg3 = c1_b_varargin_1;
    c1_b_s = c1_b_arg3;
    chartInstance->c1_b_state[0] = 362436069U;
    chartInstance->c1_b_state[1] = c1_b_s;
    if (chartInstance->c1_b_state[1] == 0U) {
      chartInstance->c1_b_state[1] = 521288629U;
    }
  } else if (c1_method2 == 4U) {
    c1_c_varargin_1 = chartInstance->c1_seed;
    if (!chartInstance->c1_c_state_not_empty) {
      chartInstance->c1_c_state = 1144108930U;
      chartInstance->c1_c_state_not_empty = true;
    }

    c1_c_arg3 = c1_c_varargin_1;
    c1_c_seed = c1_c_arg3;
    c1_b_r = c1_c_seed >> 16U;
    c1_b_t = c1_c_seed & 32768U;
    chartInstance->c1_c_state = c1_b_r << 16U;
    chartInstance->c1_c_state = c1_c_seed - chartInstance->c1_c_state;
    chartInstance->c1_c_state -= c1_b_t;
    chartInstance->c1_c_state <<= 16U;
    chartInstance->c1_c_state += c1_b_t;
    chartInstance->c1_c_state += c1_b_r;
    if (chartInstance->c1_c_state < 1U) {
      chartInstance->c1_c_state = 1144108930U;
    } else if (chartInstance->c1_c_state > 2147483646U) {
      chartInstance->c1_c_state = 2147483646U;
    }
  } else {
    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 22),
                  false);
    c1_d_y = NULL;
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 22),
                  false);
    sf_mex_call(chartInstance->c1_fEmlrtCtx, &c1_emlrtMCI, "error", 0U, 2U, 14,
                c1_c_y, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "getString", 1U, 1U, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "message", 1U, 1U, 14, c1_d_y)));
  }

  c1_rand(chartInstance, c1_random_indeces);
  for (c1_i3 = 0; c1_i3 < 8; c1_i3++) {
    c1_idx[c1_i3] = 0;
  }

  for (c1_k = 0; c1_k <= 6; c1_k += 2) {
    c1_idx1 = c1_k;
    c1_idx2 = c1_k;
    c1_a = c1_random_indeces[c1_idx1];
    c1_b = c1_random_indeces[c1_idx2 + 1];
    c1_c_a = c1_a;
    c1_b_b = c1_b;
    c1_d_a = c1_c_a;
    c1_c_b = c1_b_b;
    c1_p = (c1_d_a <= c1_c_b);
    if (c1_p) {
      c1_c_p = true;
    } else {
      c1_e_x = c1_b_b;
      c1_d_b = muDoubleScalarIsNaN(c1_e_x);
      if (c1_d_b) {
        c1_c_p = true;
      } else {
        c1_c_p = false;
      }
    }

    c1_d_p = c1_c_p;
    if (c1_d_p) {
      c1_idx[c1_k] = c1_k + 1;
      c1_idx[c1_k + 1] = c1_k + 2;
    } else {
      c1_idx[c1_k] = c1_k + 2;
      c1_idx[c1_k + 1] = c1_k + 1;
    }
  }

  c1_b_i = 2;
  while (c1_b_i < 8) {
    c1_b_a = c1_b_i;
    c1_b_i2 = c1_b_a << 1;
    c1_j = 1;
    for (c1_pEnd = 1 + c1_b_i; c1_pEnd < 9; c1_pEnd = c1_qEnd + c1_b_i) {
      c1_b_p = c1_j - 1;
      c1_q = c1_pEnd - 1;
      c1_qEnd = c1_j + c1_b_i2;
      c1_b_k = 0;
      c1_kEnd = c1_qEnd - c1_j;
      while (c1_b_k + 1 <= c1_kEnd) {
        c1_b_idx1 = c1_idx[c1_b_p] - 1;
        c1_b_idx2 = c1_idx[c1_q] - 1;
        c1_e_a = c1_random_indeces[c1_b_idx1];
        c1_g_b = c1_random_indeces[c1_b_idx2];
        c1_f_a = c1_e_a;
        c1_h_b = c1_g_b;
        c1_g_a = c1_f_a;
        c1_i_b = c1_h_b;
        c1_e_p = (c1_g_a <= c1_i_b);
        if (c1_e_p) {
          c1_f_p = true;
        } else {
          c1_f_x = c1_h_b;
          c1_j_b = muDoubleScalarIsNaN(c1_f_x);
          if (c1_j_b) {
            c1_f_p = true;
          } else {
            c1_f_p = false;
          }
        }

        c1_g_p = c1_f_p;
        if (c1_g_p) {
          c1_iwork[c1_b_k] = c1_idx[c1_b_p];
          c1_b_p++;
          if (c1_b_p + 1 == c1_pEnd) {
            while (c1_q + 1 < c1_qEnd) {
              c1_b_k++;
              c1_iwork[c1_b_k] = c1_idx[c1_q];
              c1_q++;
            }
          }
        } else {
          c1_iwork[c1_b_k] = c1_idx[c1_q];
          c1_q++;
          if (c1_q + 1 == c1_qEnd) {
            while (c1_b_p + 1 < c1_pEnd) {
              c1_b_k++;
              c1_iwork[c1_b_k] = c1_idx[c1_b_p];
              c1_b_p++;
            }
          }
        }

        c1_b_k++;
      }

      c1_b_p = c1_j - 2;
      c1_e_b = c1_kEnd;
      c1_f_b = c1_e_b;
      if (c1_f_b < 1) {
        c1_overflow = false;
      } else {
        c1_overflow = (c1_f_b > 2147483646);
      }

      if (c1_overflow) {
        c1_check_forloop_overflow_error(chartInstance, c1_overflow);
      }

      for (c1_c_k = 0; c1_c_k < c1_kEnd; c1_c_k++) {
        c1_b_k = c1_c_k;
        c1_idx[(c1_b_p + c1_b_k) + 1] = c1_iwork[c1_b_k];
      }

      c1_j = c1_qEnd;
    }

    c1_b_i = c1_b_i2;
  }

  for (c1_i4 = 0; c1_i4 < 8; c1_i4++) {
    c1_random_indeces[c1_i4] = (real_T)c1_idx[c1_i4];
  }

  for (c1_i5 = 0; c1_i5 < 8; c1_i5++) {
    c1_b_random_angle_list[c1_i5] = c1_angle_list[sf_eml_array_bounds_check
      (chartInstance->S, 23U, 698, 14, 13, (int32_T)sf_integer_check
       (chartInstance->S, 23U, 698, 14, c1_random_indeces[c1_i5]), 1, 8) - 1];
  }

  for (c1_i6 = 0; c1_i6 < 8; c1_i6++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 16U,
                      c1_b_random_angle_list[c1_i6]);
  }
}

static real_T c1_now(SFc1_ReachingInstanceStruct *chartInstance)
{
  time_t c1_rawtime;
  c1_sxaDueAh1f53T9ESYg9Uc4E c1_timeinfoDouble;
  struct tm c1_timeinfo;
  real_T c1_cDaysMonthWise[12];
  real_T c1_a;
  real_T c1_b_a;
  real_T c1_b_r;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_a;
  real_T c1_c_r;
  real_T c1_c_x;
  real_T c1_c_y;
  real_T c1_dDateNum;
  real_T c1_d_x;
  real_T c1_d_y;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_i_x;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_r;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_u_x;
  real_T c1_x;
  boolean_T c1_b;
  boolean_T c1_b_b;
  boolean_T c1_b_rEQ0;
  boolean_T c1_c_b;
  boolean_T c1_c_rEQ0;
  boolean_T c1_d_b;
  boolean_T c1_e_b;
  boolean_T c1_f_b;
  boolean_T c1_guard1;
  boolean_T c1_rEQ0;
  (void)chartInstance;
  c1_cDaysMonthWise[0] = 0.0;
  c1_cDaysMonthWise[1] = 31.0;
  c1_cDaysMonthWise[2] = 59.0;
  c1_cDaysMonthWise[3] = 90.0;
  c1_cDaysMonthWise[4] = 120.0;
  c1_cDaysMonthWise[5] = 151.0;
  c1_cDaysMonthWise[6] = 181.0;
  c1_cDaysMonthWise[7] = 212.0;
  c1_cDaysMonthWise[8] = 243.0;
  c1_cDaysMonthWise[9] = 273.0;
  c1_cDaysMonthWise[10] = 304.0;
  c1_cDaysMonthWise[11] = 334.0;
  time(&c1_rawtime);
  c1_timeinfo = *localtime(&c1_rawtime);
  c1_timeinfo.tm_year += 1900;
  c1_timeinfo.tm_mon++;
  c1_timeinfoDouble.tm_min = (real_T)c1_timeinfo.tm_min;
  c1_timeinfoDouble.tm_sec = (real_T)c1_timeinfo.tm_sec;
  c1_timeinfoDouble.tm_hour = (real_T)c1_timeinfo.tm_hour;
  c1_timeinfoDouble.tm_mday = (real_T)c1_timeinfo.tm_mday;
  c1_timeinfoDouble.tm_mon = (real_T)c1_timeinfo.tm_mon;
  c1_timeinfoDouble.tm_year = (real_T)c1_timeinfo.tm_year;
  c1_x = c1_timeinfoDouble.tm_year / 4.0;
  c1_b_x = c1_x;
  c1_b_y = c1_b_x;
  c1_b_y = muDoubleScalarCeil(c1_b_y);
  c1_c_x = c1_timeinfoDouble.tm_year / 100.0;
  c1_d_x = c1_c_x;
  c1_c_y = c1_d_x;
  c1_c_y = muDoubleScalarCeil(c1_c_y);
  c1_e_x = c1_timeinfoDouble.tm_year / 400.0;
  c1_f_x = c1_e_x;
  c1_d_y = c1_f_x;
  c1_d_y = muDoubleScalarCeil(c1_d_y);
  c1_dDateNum = ((((365.0 * c1_timeinfoDouble.tm_year + c1_b_y) - c1_c_y) +
                  c1_d_y) + c1_cDaysMonthWise[(int32_T)c1_timeinfoDouble.tm_mon
                 - 1]) + c1_timeinfoDouble.tm_mday;
  if (c1_timeinfoDouble.tm_mon > 2.0) {
    c1_g_x = c1_timeinfoDouble.tm_year;
    c1_a = c1_g_x;
    c1_h_x = c1_a;
    c1_i_x = c1_h_x;
    c1_j_x = c1_i_x;
    c1_b = muDoubleScalarIsNaN(c1_j_x);
    if (c1_b) {
      c1_r = rtNaN;
    } else {
      c1_k_x = c1_i_x;
      c1_b_b = muDoubleScalarIsInf(c1_k_x);
      if (c1_b_b) {
        c1_r = rtNaN;
      } else if (c1_i_x == 0.0) {
        c1_r = 0.0;
      } else {
        c1_r = muDoubleScalarRem(c1_i_x, 4.0);
        c1_rEQ0 = (c1_r == 0.0);
        if (c1_rEQ0) {
          c1_r = 0.0;
        } else if (c1_r < 0.0) {
          c1_r += 4.0;
        }
      }
    }

    c1_guard1 = false;
    if (c1_r == 0.0) {
      c1_l_x = c1_timeinfoDouble.tm_year;
      c1_b_a = c1_l_x;
      c1_m_x = c1_b_a;
      c1_o_x = c1_m_x;
      c1_p_x = c1_o_x;
      c1_c_b = muDoubleScalarIsNaN(c1_p_x);
      if (c1_c_b) {
        c1_b_r = rtNaN;
      } else {
        c1_t_x = c1_o_x;
        c1_e_b = muDoubleScalarIsInf(c1_t_x);
        if (c1_e_b) {
          c1_b_r = rtNaN;
        } else if (c1_o_x == 0.0) {
          c1_b_r = 0.0;
        } else {
          c1_b_r = muDoubleScalarRem(c1_o_x, 100.0);
          c1_b_rEQ0 = (c1_b_r == 0.0);
          if (c1_b_rEQ0) {
            c1_b_r = 0.0;
          } else if (c1_b_r < 0.0) {
            c1_b_r += 100.0;
          }
        }
      }

      if (c1_b_r != 0.0) {
        c1_dDateNum++;
      } else {
        c1_guard1 = true;
      }
    } else {
      c1_guard1 = true;
    }

    if (c1_guard1) {
      c1_n_x = c1_timeinfoDouble.tm_year;
      c1_c_a = c1_n_x;
      c1_q_x = c1_c_a;
      c1_r_x = c1_q_x;
      c1_s_x = c1_r_x;
      c1_d_b = muDoubleScalarIsNaN(c1_s_x);
      if (c1_d_b) {
        c1_c_r = rtNaN;
      } else {
        c1_u_x = c1_r_x;
        c1_f_b = muDoubleScalarIsInf(c1_u_x);
        if (c1_f_b) {
          c1_c_r = rtNaN;
        } else if (c1_r_x == 0.0) {
          c1_c_r = 0.0;
        } else {
          c1_c_r = muDoubleScalarRem(c1_r_x, 400.0);
          c1_c_rEQ0 = (c1_c_r == 0.0);
          if (c1_c_rEQ0) {
            c1_c_r = 0.0;
          } else if (c1_c_r < 0.0) {
            c1_c_r += 400.0;
          }
        }
      }

      if (c1_c_r == 0.0) {
        c1_dDateNum++;
      }
    }
  }

  c1_dDateNum += ((c1_timeinfoDouble.tm_hour * 3600.0 + c1_timeinfoDouble.tm_min
                   * 60.0) + c1_timeinfoDouble.tm_sec) / 86400.0;
  return c1_dDateNum;
}

static real_T c1_mod(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_a;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_r;
  boolean_T c1_b;
  boolean_T c1_b_b;
  boolean_T c1_rEQ0;
  (void)chartInstance;
  c1_a = c1_x;
  c1_b_x = c1_a;
  c1_c_x = c1_b_x;
  c1_d_x = c1_c_x;
  c1_b = muDoubleScalarIsNaN(c1_d_x);
  if (c1_b) {
    c1_r = rtNaN;
  } else {
    c1_e_x = c1_c_x;
    c1_b_b = muDoubleScalarIsInf(c1_e_x);
    if (c1_b_b) {
      c1_r = rtNaN;
    } else if (c1_c_x == 0.0) {
      c1_r = 0.0;
    } else {
      c1_r = muDoubleScalarRem(c1_c_x, 2.147483647E+9);
      c1_rEQ0 = (c1_r == 0.0);
      if (c1_rEQ0) {
        c1_r = 0.0;
      } else if (c1_r < 0.0) {
        c1_r += 2.147483647E+9;
      }
    }
  }

  return c1_r;
}

static void c1_rand(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_r[8])
{
  static char_T c1_cv[37] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'r', 'a', 'n', 'd', '_', 'i', 'n', 'v', 'a', 'l', 'i', 'd',
    'T', 'w', 'i', 's', 't', 'e', 'r', 'S', 't', 'a', 't', 'e' };

  const mxArray *c1_g_y = NULL;
  const mxArray *c1_i_y = NULL;
  real_T c1_b_j;
  real_T c1_b_r;
  real_T c1_c_kk;
  real_T c1_c_r;
  real_T c1_d;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d_k;
  real_T c1_d_r;
  real_T c1_e_k;
  real_T c1_f_k;
  int32_T c1_b_a;
  int32_T c1_b_k;
  int32_T c1_b_kk;
  int32_T c1_c_k;
  int32_T c1_exitg1;
  int32_T c1_g_k;
  int32_T c1_i;
  int32_T c1_i1;
  int32_T c1_j;
  int32_T c1_k;
  int32_T c1_kk;
  uint32_T c1_b_u[2];
  uint32_T c1_a;
  uint32_T c1_b;
  uint32_T c1_b_y;
  uint32_T c1_c_y;
  uint32_T c1_d_state;
  uint32_T c1_d_y;
  uint32_T c1_e_state;
  uint32_T c1_e_y;
  uint32_T c1_f_state;
  uint32_T c1_f_y;
  uint32_T c1_g_state;
  uint32_T c1_h_state;
  uint32_T c1_h_y;
  uint32_T c1_hi;
  uint32_T c1_icng;
  uint32_T c1_jsr;
  uint32_T c1_lo;
  uint32_T c1_mti;
  uint32_T c1_s;
  uint32_T c1_test1;
  uint32_T c1_test2;
  uint32_T c1_u;
  uint32_T c1_u1;
  uint32_T c1_ui;
  uint32_T c1_y;
  boolean_T c1_b_isvalid;
  boolean_T c1_exitg2;
  boolean_T c1_isvalid;
  if (!chartInstance->c1_method_not_empty) {
    chartInstance->c1_method = 7U;
    chartInstance->c1_method_not_empty = true;
  }

  if (chartInstance->c1_method == 4U) {
    if (!chartInstance->c1_c_state_not_empty) {
      chartInstance->c1_c_state = 1144108930U;
      chartInstance->c1_c_state_not_empty = true;
    }

    c1_d_state = chartInstance->c1_c_state;
    c1_e_state = c1_d_state;
    for (c1_c_k = 0; c1_c_k < 8; c1_c_k++) {
      c1_f_k = 1.0 + (real_T)c1_c_k;
      c1_f_state = c1_e_state;
      c1_g_state = c1_f_state;
      c1_s = c1_g_state;
      c1_hi = c1_s / 127773U;
      c1_lo = c1_s - c1_hi * 127773U;
      c1_test1 = 16807U * c1_lo;
      c1_test2 = 2836U * c1_hi;
      c1_a = c1_test1;
      c1_b = c1_test2;
      if (c1_a < c1_b) {
        c1_h_state = c1_b - c1_a;
        c1_h_state = ~c1_h_state;
        c1_h_state &= 2147483647U;
      } else {
        c1_h_state = c1_a - c1_b;
      }

      c1_c_r = (real_T)c1_h_state * 4.6566128752457969E-10;
      c1_g_state = c1_h_state;
      c1_d1 = c1_c_r;
      c1_e_state = c1_g_state;
      c1_r[(int32_T)c1_f_k - 1] = c1_d1;
    }

    chartInstance->c1_c_state = c1_e_state;
  } else if (chartInstance->c1_method == 5U) {
    if (!chartInstance->c1_b_state_not_empty) {
      for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
        chartInstance->c1_b_state[c1_i1] = 362436069U + 158852560U * (uint32_T)
          c1_i1;
      }

      chartInstance->c1_b_state_not_empty = true;
    }

    for (c1_b_k = 0; c1_b_k < 8; c1_b_k++) {
      c1_e_k = 1.0 + (real_T)c1_b_k;
      c1_icng = chartInstance->c1_b_state[0];
      c1_jsr = chartInstance->c1_b_state[1];
      c1_u = c1_jsr;
      c1_u1 = c1_icng;
      c1_u1 = 69069U * c1_u1 + 1234567U;
      c1_u ^= c1_u << 13;
      c1_u ^= c1_u >> 17;
      c1_u ^= c1_u << 5;
      c1_ui = c1_u1 + c1_u;
      chartInstance->c1_b_state[0] = c1_u1;
      chartInstance->c1_b_state[1] = c1_u;
      c1_b_r = (real_T)c1_ui * 2.328306436538696E-10;
      c1_d = c1_b_r;
      c1_r[(int32_T)c1_e_k - 1] = c1_d;
    }
  } else {
    if (!chartInstance->c1_state_not_empty) {
      for (c1_i = 0; c1_i < 625; c1_i++) {
        chartInstance->c1_state[c1_i] = c1_uv[c1_i];
      }

      chartInstance->c1_state_not_empty = true;
    }

    for (c1_k = 0; c1_k < 8; c1_k++) {
      c1_d_k = 1.0 + (real_T)c1_k;

      /* ========================= COPYRIGHT NOTICE ============================ */
      /*  This is a uniform (0,1) pseudorandom number generator based on: */
      /*  */
      /*  A C-program for MT19937, with initialization improved 2002/1/26. */
      /*  Coded by Takuji Nishimura and Makoto Matsumoto. */
      /*  */
      /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
      /*  All rights reserved. */
      /*  */
      /*  Redistribution and use in source and binary forms, with or without */
      /*  modification, are permitted provided that the following conditions */
      /*  are met: */
      /*  */
      /*    1. Redistributions of source code must retain the above copyright */
      /*       notice, this list of conditions and the following disclaimer. */
      /*  */
      /*    2. Redistributions in binary form must reproduce the above copyright */
      /*       notice, this list of conditions and the following disclaimer */
      /*       in the documentation and/or other materials provided with the */
      /*       distribution. */
      /*  */
      /*    3. The names of its contributors may not be used to endorse or */
      /*       promote products derived from this software without specific */
      /*       prior written permission. */
      /*  */
      /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
      /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
      /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
      /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT */
      /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
      /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
      /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, */
      /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY */
      /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT */
      /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
      /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
      /*  */
      /* =============================   END   ================================= */
      do {
        c1_exitg1 = 0;
        for (c1_j = 0; c1_j < 2; c1_j++) {
          c1_b_j = 1.0 + (real_T)c1_j;
          c1_mti = chartInstance->c1_state[624] + 1U;
          if (c1_mti >= 625U) {
            for (c1_kk = 0; c1_kk < 227; c1_kk++) {
              c1_c_kk = 1.0 + (real_T)c1_kk;
              c1_y = (chartInstance->c1_state[(int32_T)c1_c_kk - 1] &
                      2147483648U) | (chartInstance->c1_state[(int32_T)(c1_c_kk
                + 1.0) - 1] & 2147483647U);
              c1_b_y = c1_y;
              c1_d_y = c1_b_y;
              if ((c1_d_y & 1U) == 0U) {
                c1_d_y >>= 1U;
              } else {
                c1_d_y = c1_d_y >> 1U ^ 2567483615U;
              }

              chartInstance->c1_state[(int32_T)c1_c_kk - 1] =
                chartInstance->c1_state[(int32_T)(c1_c_kk + 397.0) - 1] ^ c1_d_y;
            }

            for (c1_b_kk = 0; c1_b_kk < 396; c1_b_kk++) {
              c1_c_kk = 228.0 + (real_T)c1_b_kk;
              c1_y = (chartInstance->c1_state[(int32_T)c1_c_kk - 1] &
                      2147483648U) | (chartInstance->c1_state[(int32_T)(c1_c_kk
                + 1.0) - 1] & 2147483647U);
              c1_f_y = c1_y;
              c1_h_y = c1_f_y;
              if ((c1_h_y & 1U) == 0U) {
                c1_h_y >>= 1U;
              } else {
                c1_h_y = c1_h_y >> 1U ^ 2567483615U;
              }

              chartInstance->c1_state[(int32_T)c1_c_kk - 1] =
                chartInstance->c1_state[(int32_T)((c1_c_kk + 1.0) - 228.0) - 1] ^
                c1_h_y;
            }

            c1_y = (chartInstance->c1_state[623] & 2147483648U) |
              (chartInstance->c1_state[0] & 2147483647U);
            c1_c_y = c1_y;
            c1_e_y = c1_c_y;
            if ((c1_e_y & 1U) == 0U) {
              c1_e_y >>= 1U;
            } else {
              c1_e_y = c1_e_y >> 1U ^ 2567483615U;
            }

            chartInstance->c1_state[623] = chartInstance->c1_state[396] ^ c1_e_y;
            c1_mti = 1U;
          }

          c1_y = chartInstance->c1_state[(int32_T)c1_mti - 1];
          chartInstance->c1_state[624] = c1_mti;
          c1_y ^= c1_y >> 11U;
          c1_y ^= c1_y << 7U & 2636928640U;
          c1_y ^= c1_y << 15U & 4022730752U;
          c1_y ^= c1_y >> 18U;
          c1_b_u[(int32_T)c1_b_j - 1] = c1_y;
        }

        c1_b_u[0] >>= 5U;
        c1_b_u[1] >>= 6U;
        if ((c1_b_u[0] == 0U) && (c1_b_u[1] == 0U)) {
          if ((chartInstance->c1_state[624] >= 1U) && (chartInstance->c1_state
               [624] < 625U)) {
            c1_isvalid = true;
          } else {
            c1_isvalid = false;
          }

          c1_b_isvalid = c1_isvalid;
          if (c1_isvalid) {
            c1_b_isvalid = false;
            c1_g_k = 0;
            c1_exitg2 = false;
            while ((!c1_exitg2) && (c1_g_k + 1 < 625)) {
              if (chartInstance->c1_state[c1_g_k] == 0U) {
                c1_b_a = c1_g_k + 1;
                c1_g_k = c1_b_a;
              } else {
                c1_b_isvalid = true;
                c1_exitg2 = true;
              }
            }
          }

          if (!c1_b_isvalid) {
            c1_g_y = NULL;
            sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1,
              37), false);
            c1_i_y = NULL;
            sf_mex_assign(&c1_i_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1,
              37), false);
            sf_mex_call(chartInstance->c1_fEmlrtCtx, &c1_b_emlrtMCI, "error", 0U,
                        2U, 14, c1_g_y, 14, sf_mex_call
                        (chartInstance->c1_fEmlrtCtx, NULL, "getString", 1U, 1U,
                         14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
              "message", 1U, 1U, 14, c1_i_y)));
          }
        } else {
          c1_exitg1 = 1;
        }
      } while (c1_exitg1 == 0);

      c1_d_r = 1.1102230246251565E-16 * ((real_T)c1_b_u[0] * 6.7108864E+7 +
        (real_T)c1_b_u[1]);
      c1_d2 = c1_d_r;
      c1_r[(int32_T)c1_d_k - 1] = c1_d2;
    }
  }
}

static void c1_check_forloop_overflow_error(SFc1_ReachingInstanceStruct
  *chartInstance, boolean_T c1_overflow)
{
  static char_T c1_cv[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  static char_T c1_cv1[5] = { 'i', 'n', 't', '3', '2' };

  const mxArray *c1_b_y = NULL;
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_y = NULL;
  if (c1_overflow) {
    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 34),
                  false);
    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 34),
                  false);
    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_cv1, 10, 0U, 1, 0U, 2, 1, 5),
                  false);
    sf_mex_call(chartInstance->c1_fEmlrtCtx, &c1_c_emlrtMCI, "error", 0U, 2U, 14,
                c1_y, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "getString", 1U, 1U, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "message", 1U, 2U, 14, c1_b_y, 14, c1_c_y)));
  }
}

static void c1_computeTargetPose(SFc1_ReachingInstanceStruct *chartInstance,
  real_T c1_single_angle, real_T c1_b_radius, real_T c1_point_coordinates[3])
{
  real_T c1_angleInDegrees;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_theta;
  real_T c1_x;
  real_T c1_y;
  int32_T c1_i;
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 14U, c1_single_angle);
  covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 15U, c1_b_radius);
  covrtEmlFcnEval(chartInstance->c1_covrtInstance, 4U, 7, 0);
  c1_angleInDegrees = c1_single_angle;
  c1_theta = 0.017453292519943295 * c1_angleInDegrees;
  c1_x = c1_theta;
  c1_b_x = c1_x;
  c1_b_x = muDoubleScalarCos(c1_b_x);
  c1_c_x = c1_b_radius * c1_b_x;
  c1_d_x = c1_theta;
  c1_e_x = c1_d_x;
  c1_e_x = muDoubleScalarSin(c1_e_x);
  c1_y = c1_b_radius * c1_e_x;
  c1_point_coordinates[0] = c1_c_x;
  c1_point_coordinates[1] = c1_y;
  c1_point_coordinates[2] = 0.0;
  for (c1_i = 0; c1_i < 3; c1_i++) {
    covrtSigUpdateFcn(chartInstance->c1_covrtInstance, 17U,
                      c1_point_coordinates[c1_i]);
  }
}

static real_T c1_sqrt(SFc1_ReachingInstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  c1_b_sqrt(chartInstance, &c1_b_x);
  return c1_b_x;
}

const mxArray *sf_c1_Reaching_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  const mxArray *c1_m = NULL;
  real_T c1_d;
  real_T c1_d1;
  c1_m = NULL;
  if (chartInstance->c1_is_c1_Reaching == c1_IN_ReachingHome) {
    c1_d1 = 0.1 * (real_T)chartInstance->c1_temporalCounter_i1;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d1, 0, 0U, 0, 0U, 0),
                  false);
  } else {
    c1_d = -1.0;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d, 0, 0U, 0, 0U, 0),
                  false);
  }

  return c1_m;
}

static const mxArray *c1_b_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  const mxArray *c1_m = NULL;
  real_T c1_d;
  real_T c1_d1;
  c1_m = NULL;
  if (chartInstance->c1_is_c1_Reaching == c1_IN_ReachingHome) {
    c1_d1 = 0.1 * (real_T)chartInstance->c1_temporalCounter_i1;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d1, 0, 0U, 0, 0U, 0),
                  false);
  } else {
    c1_d = -1.0;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d, 0, 0U, 0, 0U, 0),
                  false);
  }

  return c1_m;
}

static const mxArray *c1_c_sfAfterOrElapsed(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  const mxArray *c1_m = NULL;
  real_T c1_d;
  real_T c1_d1;
  c1_m = NULL;
  if (chartInstance->c1_is_c1_Reaching == c1_IN_ReachingTarget) {
    c1_d1 = 0.1 * (real_T)chartInstance->c1_temporalCounter_i1;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d1, 0, 0U, 0, 0U, 0),
                  false);
  } else {
    c1_d = -1.0;
    sf_mex_assign(&c1_m, sf_mex_create("unnamed temp", &c1_d, 0, 0U, 0, 0U, 0),
                  false);
  }

  return c1_m;
}

static void c1_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, real_T c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_nullptr);
}

static void c1_b_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv[3];
  int32_T c1_i;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c1_i = 0; c1_i < 3; c1_i++) {
    c1_y[c1_i] = c1_dv[c1_i];
  }

  sf_mex_destroy(&c1_u);
}

static real_T c1_c_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId);
  sf_mex_destroy(&c1_nullptr);
  return c1_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_d;
  real_T c1_y;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, real_T c1_y[8])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_nullptr);
}

static void c1_f_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[8])
{
  real_T c1_dv[8];
  int32_T c1_i;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv, 1, 0, 0U, 1, 0U, 1, 8);
  for (c1_i = 0; c1_i < 8; c1_i++) {
    c1_y[c1_i] = c1_dv[c1_i];
  }

  sf_mex_destroy(&c1_u);
}

static uint32_T c1_g_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr)
{
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId,
    c1_svPtr);
  sf_mex_destroy(&c1_nullptr);
  return c1_y;
}

static uint32_T c1_h_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr)
{
  uint32_T c1_b_u;
  uint32_T c1_y;
  (void)chartInstance;
  if (mxIsEmpty(c1_u)) {
    *c1_svPtr = false;
  } else {
    *c1_svPtr = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_b_u, 1, 7, 0U, 0, 0U, 0);
    c1_y = c1_b_u;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_i_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr,
  uint32_T c1_y[625])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId,
                        c1_svPtr, c1_y);
  sf_mex_destroy(&c1_nullptr);
}

static void c1_j_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr, uint32_T c1_y[625])
{
  int32_T c1_i;
  uint32_T c1_b_uv[625];
  (void)chartInstance;
  if (mxIsEmpty(c1_u)) {
    *c1_svPtr = false;
  } else {
    *c1_svPtr = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_b_uv, 1, 7, 0U, 1, 0U, 1,
                  625);
    for (c1_i = 0; c1_i < 625; c1_i++) {
      c1_y[c1_i] = c1_b_uv[c1_i];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_k_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T *c1_svPtr,
  uint32_T c1_y[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId,
                        c1_svPtr, c1_y);
  sf_mex_destroy(&c1_nullptr);
}

static void c1_l_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T
  *c1_svPtr, uint32_T c1_y[2])
{
  int32_T c1_i;
  uint32_T c1_b_uv[2];
  (void)chartInstance;
  if (mxIsEmpty(c1_u)) {
    *c1_svPtr = false;
  } else {
    *c1_svPtr = true;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_b_uv, 1, 7, 0U, 1, 0U, 1, 2);
    for (c1_i = 0; c1_i < 2; c1_i++) {
      c1_y[c1_i] = c1_b_uv[c1_i];
    }
  }

  sf_mex_destroy(&c1_u);
}

static uint8_T c1_m_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId);
  sf_mex_destroy(&c1_nullptr);
  return c1_y;
}

static uint8_T c1_n_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_b_u;
  uint8_T c1_y;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_b_u, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_b_u;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static uint32_T c1_o_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId);
  sf_mex_destroy(&c1_nullptr);
  return c1_y;
}

static uint32_T c1_p_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_b_u;
  uint32_T c1_y;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_b_u, 1, 7, 0U, 0, 0U, 0);
  c1_y = c1_b_u;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_q_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_nullptr, const char_T *c1_identifier, boolean_T c1_y[13])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nullptr), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_nullptr);
}

static void c1_r_emlrt_marshallIn(SFc1_ReachingInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T c1_y[13])
{
  int32_T c1_i;
  boolean_T c1_bv[13];
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_bv, 1, 11, 0U, 1, 0U, 1, 13);
  for (c1_i = 0; c1_i < 13; c1_i++) {
    c1_y[c1_i] = c1_bv[c1_i];
  }

  sf_mex_destroy(&c1_u);
}

static const mxArray *c1_s_emlrt_marshallIn(SFc1_ReachingInstanceStruct
  *chartInstance, const mxArray *c1_nullptr, const char_T *c1_identifier)
{
  emlrtMsgIdentifier c1_thisId;
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  c1_thisId.fIdentifier = (const char_T *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  sf_mex_assign(&c1_y, c1_t_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_nullptr), &c1_thisId), true);
  sf_mex_destroy(&c1_nullptr);
  return c1_y;
}

static const mxArray *c1_t_emlrt_marshallIn(SFc1_ReachingInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  (void)c1_parentId;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), true);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_slStringInitializeDynamicBuffers(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_init_sf_message_store_memory(SFc1_ReachingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

mxArray *sf_c1_Reaching_getDebuggerHoverDataFor(SFc1_ReachingInstanceStruct
  *chartInstance, uint32_T c1_u)
{
  const mxArray *c1_m = NULL;
  const mxArray *c1_m1 = NULL;
  const mxArray *c1_m2 = NULL;
  mxArray *c1_m3 = NULL;
  c1_m3 = NULL;
  switch (c1_u) {
   case 42U:
    sf_mex_assign(&c1_m, c1_b_sfAfterOrElapsed(chartInstance), false);
    sfAppendHoverData(&c1_m3, sf_mex_dup(c1_m), 42U, "afterOrElapsed", "", 36U,
                      -1, -1);
    break;

   case 34U:
    sf_mex_assign(&c1_m1, c1_c_sfAfterOrElapsed(chartInstance), false);
    sfAppendHoverData(&c1_m3, sf_mex_dup(c1_m1), 34U, "afterOrElapsed", "", 29U,
                      -1, -1);
    break;

   case 41U:
    sf_mex_assign(&c1_m2, c1_sfAfterOrElapsed(chartInstance), false);
    sfAppendHoverData(&c1_m3, sf_mex_dup(c1_m2), 41U, "afterOrElapsed", "", 36U,
                      -1, -1);
    break;
  }

  sf_mex_destroy(&c1_m);
  sf_mex_destroy(&c1_m1);
  sf_mex_destroy(&c1_m2);
  return c1_m3;
}

static void c1_chart_data_browse_helper(SFc1_ReachingInstanceStruct
  *chartInstance, int32_T c1_ssIdNumber, const mxArray **c1_mxData, uint8_T
  *c1_isValueBrowsable)
{
  real_T c1_d;
  *c1_mxData = NULL;
  *c1_mxData = NULL;
  *c1_isValueBrowsable = 1U;
  switch (c1_ssIdNumber) {
   case 4U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData",
      *chartInstance->c1_cursor_pos, 0, 0U, 1, 0U, 1, 3), false);
    break;

   case 9U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData",
      *chartInstance->c1_target_pos, 0, 0U, 1, 0U, 2, 1, 3), false);
    break;

   case 10U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &chartInstance->c1_counter,
      0, 0U, 0, 0U, 0), false);
    break;

   case 11U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &chartInstance->c1_time, 0,
      0U, 0, 0U, 0), false);
    break;

   case 12U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData",
      &chartInstance->c1_target_color, 0, 0U, 0, 0U, 0), false);
    break;

   case 13U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &chartInstance->c1_radius,
      0, 0U, 0, 0U, 0), false);
    break;

   case 14U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &chartInstance->c1_angle, 0,
      0U, 0, 0U, 0), false);
    break;

   case 15U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", *chartInstance->c1_angles,
      0, 0U, 1, 0U, 1, 8), false);
    break;

   case 43U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", *chartInstance->c1_color, 0,
      0U, 1, 0U, 2, 1, 3), false);
    break;

   case 44U:
    c1_d = *chartInstance->c1_stop;
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &c1_d, 0, 0U, 0, 0U, 0),
                  false);
    break;

   case 45U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData", &chartInstance->c1_ext_loop,
      0, 0U, 0, 0U, 0), false);
    break;

   case 46U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData",
      &chartInstance->c1_counter_point, 0, 0U, 0, 0U, 0), false);
    break;

   case 47U:
    sf_mex_assign(c1_mxData, sf_mex_create("mxData",
      chartInstance->c1_random_angle_list, 0, 0U, 1, 0U, 1, 8), false);
    break;
  }
}

static void c1_b_sqrt(SFc1_ReachingInstanceStruct *chartInstance, real_T *c1_x)
{
  static char_T c1_cv[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  static char_T c1_cv1[4] = { 's', 'q', 'r', 't' };

  const mxArray *c1_b_y = NULL;
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_y = NULL;
  real_T c1_b_x;
  boolean_T c1_b_p;
  boolean_T c1_p;
  c1_b_x = *c1_x;
  if (c1_b_x < 0.0) {
    c1_p = true;
  } else {
    c1_p = false;
  }

  c1_b_p = c1_p;
  if (c1_b_p) {
    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 30),
                  false);
    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_cv, 10, 0U, 1, 0U, 2, 1, 30),
                  false);
    c1_c_y = NULL;
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_cv1, 10, 0U, 1, 0U, 2, 1, 4),
                  false);
    sf_mex_call(chartInstance->c1_fEmlrtCtx, &c1_e_emlrtMCI, "error", 0U, 2U, 14,
                c1_y, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "getString", 1U, 1U, 14, sf_mex_call(chartInstance->c1_fEmlrtCtx, NULL,
      "message", 1U, 2U, 14, c1_b_y, 14, c1_c_y)));
  }

  *c1_x = muDoubleScalarSqrt(*c1_x);
}

static void init_dsm_address_info(SFc1_ReachingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_ReachingInstanceStruct *chartInstance)
{
  chartInstance->c1_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c1_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c1_cursor_pos = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_target_pos = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_angles = (real_T (*)[8])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_color = (real_T (*)[3])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_stop = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c1_Reaching_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3134945658U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3179307277U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(894733619U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1173782112U);
}

mxArray *sf_c1_Reaching_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_Reaching_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_vars");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("rawtime");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_Reaching_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_Reaching(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNrtmN1q2zAUx5UsTbPRhnQf0MtQRhljlKQdazsYcxuWLbBCKGXbhcFTbMURyJaRlZLd+XKPsIt"
    "e7FH2SHuE+StNooXZqbXEGzUIcRSknN85fx1LBoXOGfCfqt+2twEo+33Fb0UQPWuxXfDbw7iPxk"
    "vX43W/8S8OCsZdpncMv7ehFdpwOOrYfRqufwQm65fnrF+YWv9uPB49P19nmu+9UcT5pTnz16bm1"
    "2Jbp4SyOD7jOK2MA7RDjkYCR2mGowRcTp18+L8T+q8k+H9PyENgc8hMxDWHuhOO7DwVJdv8ZzfW"
    "FbRNgnLD8TgVx7rAsR7uj6HNEcsJx9tU+toUODYnHL7AsM3zkhevnSovFYEnsNGIa4TK2vdZ8/I"
    "0FUdZ4AhsBg08dPOSj0hf7xI4tgSOrZDDNqilhdteI9jlIE917EmqfbMhcG1M6vL4NZkTnt0bvS"
    "c5tpAc/2sZ/f/9/9PuFwvxATWi+d3Cn89zBeE8V5xalwAMnNgPJYGjKHDUxhCfPCXsv3qKjHOHl"
    "xCPrhCPwG69VLuMmgxa9TYmyFXPTi7en5yq5/uN/ec9lVNKenSkIouoBPdUC3ICe2qwW/tDW3UY"
    "voQcBT9rwdielQddLHz+Q8gI69aq9aBcRXroXknRwyghDi1BD63MemC2uWf9M/Vh3rnT5b6e4/m"
    "DVevBMyI91JEUPXxLiEdPiEdPen3QLN1svjhqHGphnPtDEsvlVi8y9PIj1svn5ehFF+Kh/wW98O"
    "bx8cEhZKJgbvUiQS/fY70o/019cQfsQKe2Kbm+1KXoJele9EiIT2BjV4M6x5dI05vaOYL6ANumt"
    "HvEjhSupHtRVeCqRlwzQHJ4dpeSp/sCT2BzZDmUQdKKv5Pg5mS9yoL7/E5sB74hDqgLdL7I+bY4"
    "418RQJ6xToDTqE6AV8pqv482lpLfB0J+A9uAHH5kmHNkX9APSOfRdf5at78AVD9YXg=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_Reaching_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "sFqcWcZYDYQL7avIYnyIUmB";
}

static void sf_opaque_initialize_c1_Reaching(void *chartInstanceVar)
{
  initialize_params_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
  initialize_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_Reaching(void *chartInstanceVar)
{
  enable_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_Reaching(void *chartInstanceVar)
{
  disable_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_Reaching(void *chartInstanceVar)
{
  sf_gateway_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_Reaching(SimStruct* S)
{
  return get_sim_state_c1_Reaching((SFc1_ReachingInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_Reaching(SimStruct* S, const mxArray *st)
{
  set_sim_state_c1_Reaching((SFc1_ReachingInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c1_Reaching(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_ReachingInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Reaching_optimization_info();
    }

    mdl_cleanup_runtime_resources_c1_Reaching((SFc1_ReachingInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c1_Reaching(void *chartInstanceVar)
{
  mdl_start_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc1_ReachingInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c1_Reaching(void *chartInstanceVar)
{
  mdl_terminate_c1_Reaching((SFc1_ReachingInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_Reaching(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_Reaching((SFc1_ReachingInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c1_Reaching_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [41] = {
    "eNrtW01z28YZBilKlh1blfPR5NCZcjx15HZcRZKdONE4DiV+xJyhKtak4jrDGXoJLIGtgV1qdyG",
    "ROenYc0+dTg45dXLsqeeeOv0H/Rs95tTp7gKgKIgmARCWmFaaoekF8e77sc/77LvYhZap7mnib0",
    "V8vt/VtCXxvSw+Wc37W/TbmZGPdz2nPfbb9RuapluA8iruEi3+n04MaELccLtd1I8pi12nDihwW",
    "AK9GDjwGWTEdjkiOJ7xCHchhVgXHfQI5bH0MuS4NsKvKi7WpWb23EK61bCIaxu7okNg7GN78Dq9",
    "PZfXhcYSolDnFQgNblHimlbFBubkKFB+XLSg/oq5TuxYMcgbbk+6yvZcm6OeDct9qFcx40BEgU3",
    "xt8EBh0Xej40QxBqBNHF6NgI4eqwtwBqwJ9DB4UHPEP/uu1xEL6Jeoa+DMOCEImCXHbsoER5Rtm",
    "4LO/cErO3YceYOL8GOa5oImzK61HUgFv4LnESIVbdIjiAFJtzHMXNQelfuqwEe4jJ6DlYlLBPlo",
    "Ot4o8ISySq95SMRIZZQb0XHRWDbLJ5sk/Rq8AjaSn8JcJBA1tMfQ5gxZDTJV4DKLIiZSS5Ghy70",
    "ZYsEGyj6CB+FpBTh/kaQZwRx5EhIQUOEeWj6sKNpmHQZJ05RpFGpVouo77xsFXNIu0CHkbmPAsS",
    "gMFjhKqZeAzHQsaW0iBJXXkbuAeLEohrrurh0TOgrEeO4JHsaK5kJ8aShYcIS5FARRlmg+ytgux",
    "FtdphgOAmPAyYYK55eISvzJ5GwDnQLGnI+QTbcg0x2wCLzs5hHdoS3R4gPSpDpFPWiZpLLoCEmE",
    "hml5qAHD/ArTI5xhRKn4VcEE3AFoWANQLGYFnbFtEQHFWF8NKspPGxKZCUpzxzAbdCR2PgSYjGz",
    "SF/lTAh0kVVlLEo3YdAssg30jZjaMUOMi3JqUFY5YKh69INMvHr0tt9+MMylKmtSMVJATMNYVEo",
    "7HVXswSZyoLrQAKKm8Jr+n9S7oZ3qvZ6drDfr/+8i5TK+XGFELjcmPm+NyK36bX2zLQpM3QpGLa",
    "z/ZoQ4R5HTzsmdxjf4vjcinxmjVxv5nhan7Lk4iUhlzsfpVkhPLiS35MfqH7sv//Ju4T/0+dO//",
    "euP1S+cWcbpnx/Ew/GK3/5ZUJcNZ66jc+Qu7306BQfvh3Ag26xyqD/Xv35RevHb2iNwVH2BB9UD",
    "Z9fLuyn2vhuyN7ieFx8uiE3xJNWrhr/Gkm3gerW/7P/TEXuXpsTj+gieNO3fX8wkf1IuhOXHxWs",
    "xFK9FtUa1CQ3h99L80CqFMB7H+ZE740dOzF2kNx/23ylE4a8boXGQbQ6oCXm7R9h5Pkluz3JhNv",
    "n7iXEFsGnDufHjF5H8uBby45rKD1fW2XPix5eR8HUr5MetUz8EwJB60jAX/pxUIo3Lcsgf2YZ93",
    "rZJWnk/67j8KpIfSyE/ltSazEAum5fx8PA1bd69HfLjtvIDG8Rpq7Rv26Lo1eaJx+5FypubIb9u",
    "nvJyME3OiT8fJponuVgPpGP/6oz2n9cfNV8cyC1iePL1mOuo7Ei/toa03pj1xjg/siE/VgMnfnd",
    "SUN9/OCmkUXecTIlHPRQP2S5ut+qUmBQ4ebVwbu3tNGs7u61nWxtbDzstTojdIf0WdOyWjTotb+",
    "naktnadXGrJ1aRYt0vf27La+vOPOAidv0nVryKty4bD4VvPTzUv00FD/0pcSiG8FCcGQ8Um+vOj",
    "4YfxtWd6jmWL29dNh5ODA8PeZgKHv40JR6dUDw6qfND29HNzU8+3XjUVnHuurYPlyu8pIGXv/t4",
    "eXkxeNFD8dDfAF745mefPXgEaBgwV3hJAS/f+Xgp/M/wC7PoA51gM2V+yaeCl2nrovdC8XlP7V2",
    "3gdxVge2zT6jTqcPvpOLXtHXRSsivFc+vMw6l48+HFzJOb4f8kW0O5YYusIv+cxK0edrfcsw8X/",
    "Db0jbINcI0ncepb7Nn7MtqgM/IE9quxxPa54XLfT66cSHj+05ofGXbABw8p4hzKPfroc695fwZ3",
    "CbdB5n3fbXL2sdLQ9/NiPNqErmFN7hPmKbcrP7F3Y/8sd8/iV+10P2rc+zHJH6Ksy/9pu2sr06+",
    "Pxf2KxdvPv2p3/6z+JDO7wV5NxpqE3bkhKB/3GUHlyn1qV1zvGtN2B893+hfPXhW085fbfrbvGe",
    "v1oiuDnk0uDoqGbpag9jk1mvG6dYU/5Zewwtx+PL7zOT5kGfO4l22H4O8RWH38zteRb7Nun4tfm",
    "+Ndfd7EO+rQO8ORKTX7q/dNQYYOEi/q/bt5YG9u9vb25sba7+882TN31tae/wReJJHLG/ALsLQu",
    "J/vuFy2MeF5eUYoj3CeWzCvjr12bXKcV72t5wNj8oE14k7RIQb2OgvuXTcQsInJ1g+w7MszrwRt",
    "KG5c1ykUt/mtexOt9W4SdgjDPDApswkdY8VIUIgISZHgLjK9Y9mNSgkBExPGkc7W7n/86BPRt65",
    "ucClUbhrDG6SG9Rs3hvkypX75eYifZHsYs23doNteDOQRy32qTvMlXs/KU0z0kubBKx64WB44DP",
    "HAYWo8sKl4QO4vzT0JbM4BCVzxwBm55SseSJUH/jqFBwYhHhikxgNbHg+M7JnPPR9sXfHBVV3w/",
    "10X0BAf0NT44KHiA3UoaO6J4OFcEMEVD5zKrS7G44EgLk+04J2yooVsY8xbLf7PNQi643719b/M",
    "TX6ukZ3w3ClOXv+wEM/Pt0f2MXTpYdXoN4l8p2oP9Ebs+W5hsv0rM9qfmeEcVwVhxKxkerMR963",
    "GneerYsQFVaBv/BdFkuhfiKj/JyH9sv1MnZPckYxYk6ckk+jPzeB/sGP3lHjvLyTRvzjDvmGgv6",
    "lqxGT6lyLqvx7SL9uNHjjGgfMJ/b+mJX9PSekPnJ/T584/aPH4KHgPpyx513+Z/usHO2KCHjDkv",
    "c8QXK5T+R738CcxMbPx7xhexj6XNkNeHSOR18fs15tbH2/Nsm/2X4uMaZw=",
    ""
  };

  static char newstr [2985] = "";
  newstr[0] = '\0';
  for (i = 0; i < 41; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c1_Reaching(SimStruct *S)
{
  const char* newstr = sf_c1_Reaching_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(2791326406U));
  ssSetChecksum1(S,(1929265172U));
  ssSetChecksum2(S,(3619047511U));
  ssSetChecksum3(S,(1832864146U));
}

static void mdlRTW_c1_Reaching(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlSetupRuntimeResources_c1_Reaching(SimStruct *S)
{
  SFc1_ReachingInstanceStruct *chartInstance;
  chartInstance = (SFc1_ReachingInstanceStruct *)utMalloc(sizeof
    (SFc1_ReachingInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_ReachingInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_Reaching;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_Reaching;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c1_Reaching;
  chartInstance->chartInfo.mdlTerminate = sf_opaque_mdl_terminate_c1_Reaching;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c1_Reaching;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_Reaching;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_Reaching;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_Reaching;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_Reaching;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_Reaching;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_Reaching;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_Reaching;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c1_Reaching(chartInstance);
}

void c1_Reaching_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c1_Reaching(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_Reaching(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_Reaching(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_Reaching_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
